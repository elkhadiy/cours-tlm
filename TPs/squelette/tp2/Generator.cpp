// Module header
#include "Generator.h"

// Misc defines
#include "defines.h"
#include "LCDC_registermap.h"
#define IDLE_PERIOD sc_time(20, SC_SEC)


Generator::Generator(sc_module_name name)
	: sc_module(name)
{
	SC_THREAD(generate);
}

void Generator::generate(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val ;
	ensitlm::addr_t addr;
	
	// Blanking the video memory
	cerr	<< FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT
			<< "Blanking video memory"
			<< endl;

	for (uint32_t i = 0; i < MEM_VBUF_SIZE; i += 4)
	{	
		val = 0xFFFFFFFF; // 4 pixels per uint32_t
		addr = MEM_VBUF_BASE+i;
		status = initiator.write(addr, val);
		if (status != tlm::TLM_OK_RESPONSE)
		{
			cerr	<< FG_RED << "[" << name() << "]\t" << FG_DEFAULT
					<< "Failed writing "
					<< std::hex
					<< val << FG_YELLOW << " @" << addr << FG_DEFAULT
					<< std::endl;
		}
	}
		
	cerr	<< FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT
			<< "Finished blanking video memory"
			<< endl;

	// Setting up the LCDC Controler
	cerr	<< FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT
			<< "Initializing LCDC"
			<< endl;

	// Configure the base address of the video memory buffer
	addr = LCDC_ADDR_BASE;
	val = MEM_VBUF_BASE;
	status = initiator.write(addr, val);
	if (status != tlm::TLM_OK_RESPONSE)
	{
		cerr	<< FG_RED << "[" << name() << "]\t" << FG_DEFAULT
			<< "Failed configuring LCDC_ADDR_BASE "
			<< std::hex
			<< val << FG_YELLOW << " @" << addr << FG_DEFAULT
			<< std::endl;
	}

	cerr	<< FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT
			<< "Finished initializing LCDC"
			<< endl;

	// Starting the LCDC Controller

	cerr	<< FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT
			<< "Starting LCDC"
			<< endl;

	addr = LCDC_START_REG;
	val = 0x1;
	status = initiator.write(addr, val);
	if (status != tlm::TLM_OK_RESPONSE)
	{
		cerr	<< FG_RED << "[" << name() << "]\t" << FG_DEFAULT
			<< "Failed to start the LCDC controller "
			<< std::hex
			<< val << FG_YELLOW << " @" << addr << FG_DEFAULT
			<< std::endl;
	}

	cerr	<< FG_GREEN << "[" << name() << "]\t" << FG_DEFAULT
			<< "LCDC started"
			<< endl;

	while(true) {
		
		wait(IDLE_PERIOD);
	}
}
