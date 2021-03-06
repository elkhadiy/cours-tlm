// Module header
#include "Generator.h"

// Misc defines
#include "defines.h"

// Debug macros
// Needs a defined addr and val in scope
#define DBG_ERR(str) cerr << FG_RED << "[" << name() << "]\t" << FG_DEFAULT \
			  << str \
			  << std::hex \
			  << "0x" << val \
			  << FG_YELLOW << " @" << addr << FG_DEFAULT \
			  << std::endl

#define DBG_OK(str) cerr << FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT \
			 << str \
			 << endl


Generator::Generator(sc_module_name name)
	: sc_module(name)
{
	SC_THREAD(generate);

	SC_METHOD(irq_handler);
	sensitive << irq.pos();
	dont_initialize();
}

void Generator::irq_handler(void)
{
	DBG_OK("Received Interrupt");

	// Ackowledge the display_int interrupt
	// By setting INT_REG to 0
	tlm::tlm_response_status status;
	ensitlm::data_t val  = 0x0;
	ensitlm::addr_t addr = LCDC_INT_REG;

	status = initiator.write(addr, val);
	if(status != tlm::TLM_OK_RESPONSE) {
		DBG_ERR("Failed ACK LCDC_INT_REG ");
	}

	// Unlock the main thread;
	irq_event.notify();
}


inline void Generator::scroll_vram(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val ;
	ensitlm::addr_t addr;

	// Save the line to scroll
	ensitlm::data_t line_buf[MEM_VBUF_WIDTH/4] = {0};
	for(uint32_t i = 0; i < MEM_VBUF_WIDTH; i += 4) {
		addr = MEM_VBUF_BASE+i;
		status = initiator.read(addr, line_buf[i/4]);
		if(status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed reading from RAM ");
		}
	}
	// Scroll the screen by one line
	for(uint32_t i = MEM_VBUF_WIDTH; i < MEM_VBUF_SIZE; i += 4) {
		addr = MEM_VBUF_BASE+i;
		uint32_t buf;
		status = initiator.read(addr, buf);
		if(status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed reading from RAM ");
		}
		status = initiator.write(addr-MEM_VBUF_WIDTH, buf);
		if(status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed writing to RAM ");
		}
	}
	// Paste the saved line at the last line of pixels on the screen
	for(uint32_t i = 0; i < MEM_VBUF_WIDTH; i += 4) {
		addr = MEM_VBUF_BASE+(MEM_VBUF_HEIGHT-1)*MEM_VBUF_WIDTH+i;
		status = initiator.write(addr, line_buf[i/4]);
		if(status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed writing to RAM ");
		}
	}
}


inline void Generator::init_vram_from_rom(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val ;
	ensitlm::addr_t addr;

	DBG_OK("Initializing video memory");

	// for each 32bit word in ROM memory...
	for(uint32_t i = 0; i < ROM_SIZE; i += 4) {
		// ..read the 8 pixels' data contained in it (8*4bits=32bits)..
		addr = ROM_BASE+i;
		status = initiator.read(addr, val);
		if(status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed reading from ROM ");
		}

		uint32_t mask = 0xF;
		// ..store them in an array for easier management later on..
		uint8_t pixel[8] = {0};

		for(int8_t j = 7; j >= 0; j--) {
			pixel[j] = val & mask;
			pixel[j] = pixel[j] << 4;
			val = val >> 4;
		}

		// ..now pad them with 4 x 0bits to form the two words we push
		// onto the VRAM
		// to sum up :
		// we had in ROM : p0-p1-p2-p3-p4-p5-p6-p7 as one 32bit word
		// we convert that into :
		//  hi:   p0-0000-p1-0000-p2-0000-p3-0000
		//  lo:   p4-0000-p5-0000-p6-0000-p7-0000
		//                        as two 32bit words in VRAM
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
		if(status != tlm::TLM_OK_RESPONSE) {
			DBG_ERR("Failed writing to RAM ");
		}

		addr = MEM_VBUF_BASE+i*2+4;
		status = initiator.write(addr, lo);
		if(status != tlm::TLM_OK_RESPONSE) {
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
	if(status != tlm::TLM_OK_RESPONSE) {
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
	if(status != tlm::TLM_OK_RESPONSE) {
		DBG_ERR("Failed to start the LCDC controller ");
	}

	DBG_OK("LCDC started");
}

void Generator::generate(void)
{
	init_vram_from_rom();
	init_lcdc();
	start_lcdc();

	while(true) {
		wait(irq_event);
		scroll_vram();
	}
}
