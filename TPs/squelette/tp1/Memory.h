#ifndef MEMORY_H
#define MEMORY_H

#include "systemc.h"
#include "ensitlm.h"

SC_MODULE(Memory)
{
	ensitlm::target_socket<Memory> target;

	ensitlm::data_t *storage;
	uint32_t size;

	tlm::tlm_response_status
			write(const ensitlm::addr_t &a, const ensitlm::data_t &d);

	tlm::tlm_response_status
			read (const ensitlm::addr_t &a, ensitlm::data_t &d);
	
	SC_HAS_PROCESS(Memory);
	Memory(sc_module_name name, uint32_t size);
	
	~Memory();
};

#endif
