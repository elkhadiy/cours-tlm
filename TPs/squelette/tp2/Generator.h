#ifndef GENERATOR_H
#define GENERATOR_H

#include "systemc.h"
#include "ensitlm.h"

SC_MODULE(Generator)
{
	ensitlm::initiator_socket<Generator> initiator;
	sc_in<bool> irq;
	bool interrupted;
	sc_event  irq_event;

	SC_CTOR(Generator);

	void generate(void);
	void irq_handler(void);

private:
    inline void init_vram_from_rom(void);
	inline void start_lcdc(void);
	inline void init_lcdc(void);
	inline void scroll_vram(void);
};

#endif
