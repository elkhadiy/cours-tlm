// Module header
#include "Generator.h"

// Misc defines
#include "defines.h"
#define IDLE_PERIOD sc_time(20, SC_SEC)

#define DBG_ERR(str) cerr	<< FG_RED << "[" << name() << "]\t" << FG_DEFAULT \
					<< str \
					<< std::hex \
					<< "0x" << val << FG_YELLOW << " @" << addr << FG_DEFAULT \
					<< std::endl

#define DBG_OK(str) cerr << FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT \
			<< str \
			<< endl


Generator::Generator(sc_module_name name)
	: sc_module(name)
{
	interrupted = false;

	SC_THREAD(generate);

	SC_METHOD(irq_handler);
	sensitive << irq;
}

void Generator::irq_handler(void)
{
	DBG_OK("Received Interrupt");

	// ack the display_int
	tlm::tlm_response_status status;
	ensitlm::data_t val  = 0x0;
	ensitlm::addr_t addr = LCDC_INT_REG;
		
	status = initiator.write(addr, val);
	if (status != tlm::TLM_OK_RESPONSE) {
		DBG_ERR("Failed ACK LCDC_INT_REG ");
	}

	// unlock the thread;
	//interrupted = true;
	irq_event.notify();
}

/*
inline void Generator::scroll_vram(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val ;
	ensitlm::addr_t addr;

	ensitlm::data_t line_buf[MEM_VBUF_WIDTH/4] = {0};
	ensitlm::data_t line2scroll[MEM_VBUF_WIDTH/4] = {0};
}
*/

inline void Generator::init_vram_from_rom(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val ;
	ensitlm::addr_t addr;
	
	DBG_OK("Initializing video memory");

	for (uint32_t i = 0; i < ROM_SIZE; i += 4)
	{	
		// lecture des 8 premiers pixels depuis la ROM
		addr = ROM_BASE+i;
		status = initiator.read(addr, val);
		if (status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed reading from ROM ");
		}

		uint32_t mask = 0xF;
		uint8_t pixel[8] = {0};

		for (int8_t j = 7; j >= 0; j--) {
			pixel[j] = val & mask;
			pixel[j] = pixel[j] << 4;
			val = val >> 4;
		}

		uint32_t hi = ((uint32_t)pixel[0] << 24)
					| ((uint32_t)pixel[1] << 16)
					| ((uint32_t)pixel[2] << 8)
					|  (uint32_t)pixel[3];

		uint32_t lo = ((uint32_t)pixel[4] << 24)
					| ((uint32_t)pixel[5] << 16)
					| ((uint32_t)pixel[6] << 8)
					|  (uint32_t)pixel[7];

		addr = MEM_VBUF_BASE+i*2;
		status = initiator.write(addr, hi);
		if (status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed writing to RAM ");
		}

		addr = MEM_VBUF_BASE+i*2+4;
		status = initiator.write(addr, lo);
		if (status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed writing to RAM ");
		}
	}
		
	DBG_OK("Finished initializing video memory");

}

inline void Generator::init_lcdc(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val ;
	ensitlm::addr_t addr;

	DBG_OK("Initializing LCDC");

	// Configure the base address of the video memory buffer
	addr = LCDC_ADDR_BASE;
	val = MEM_VBUF_BASE;
	status = initiator.write(addr, val);
	if (status != tlm::TLM_OK_RESPONSE) {
		DBG_ERR("Failed configuring LCDC_ADDR_BASE ");
	}

	DBG_OK("Finished initializing LCDC");
}

inline void Generator::start_lcdc(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val ;
	ensitlm::addr_t addr;

	DBG_OK("Starting LCDC");

	addr = LCDC_START_REG;
	val = 0x1;
	status = initiator.write(addr, val);
	if (status != tlm::TLM_OK_RESPONSE) {
		DBG_ERR("Failed to start the LCDC controller ");
	}

	DBG_OK("LCDC started");
}

void Generator::generate(void)
{
	// Initializigin the video memory
	init_vram_from_rom();
	// Setting up the LCDC Controller
	init_lcdc();
	// Starting the LCDC Controller
	start_lcdc();

	while(true) {
		//while(!interrupted) {
			wait(irq_event);
		//}
		//interrupted = false;
	}
}
