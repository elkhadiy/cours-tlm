#ifndef GENERATOR_H
#define GENERATOR_H

#include "systemc.h"
#include "ensitlm.h"

SC_MODULE(Generator)
{
	ensitlm::initiator_socket<Generator> initiator;
	sc_in<bool> irq;

	sc_event  irq_event;

	SC_CTOR(Generator);

	// This module's main thread
	void generate(void);
	// Handles interrupts comming from the lcdc module
	void irq_handler(void);

// some helper funtions
private:
	inline void init_vram_from_rom(void);
	inline void start_lcdc(void);
	inline void init_lcdc(void);
	inline void scroll_vram(void);
};

#endif
