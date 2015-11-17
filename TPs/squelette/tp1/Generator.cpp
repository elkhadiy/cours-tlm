#include "Generator.h"
#include "defines.h"

// Random number generation
#include <stdlib.h> // srand, rand
#include <time.h> // time

#define NB_TEST_WRITES 10


Generator::Generator(sc_module_name name)
	: sc_module(name)
{
	SC_THREAD(generate);
}

void Generator::generate(void)
{
	tlm::tlm_response_status status;

	srand(time(NULL));

	ensitlm::data_t val  = rand() % 1000 + 1; // val in [1, 1000]
	ensitlm::addr_t addr = MEM_BASE;

	for (int i = 0; i < NB_TEST_WRITES; i++)
	{
		status = initiator.write(addr, val);

		if (status != tlm::TLM_OK_RESPONSE)
		{
			cout	<< FG_RED << "[" << name() << "] \t" << FG_DEFAULT
					<< "Failed writing " << std::dec
					<< val << FG_YELLOW << " @" << std::hex << addr << FG_DEFAULT
					<< std::endl;
		}

		addr += sizeof(ensitlm::data_t);
		val = rand() % 1000 + 1;

	}

	addr = MEM_BASE;
	
	for (int i = 0; i < NB_TEST_WRITES; i++)
	{
		status = initiator.read(addr, val);

		if (status != tlm::TLM_OK_RESPONSE)
		{
			cout	<<  FG_RED << "[" << name() << "] \t" << FG_DEFAULT
					<< "Failed reading @" << addr << FG_DEFAULT
					<< endl;
		} else {
			cout	<< FG_RED << "[" << name() << "] \t" << FG_DEFAULT
					<< FG_YELLOW << "@" << std::hex << addr << FG_DEFAULT
					<< ": " << std::dec << val
					<< endl; 
		}

		addr += sizeof(ensitlm::data_t);
	}
}
