#ifndef GENERATOR_H
#define GENERATOR_H

#include "systemc.h"
#include "ensitlm.h"

SC_MODULE(Generator)
{
	ensitlm::initiator_socket<Generator> initiator;
	sc_in<bool> irq;

	SC_CTOR(Generator);

	void generate(void);
};

#endif
