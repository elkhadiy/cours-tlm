#include "Memory.h"
#include <new>
#include "defines.h"

Memory::Memory(sc_module_name name, int size)
	: sc_module(name)
{
	this->size = size;
	storage = new (std::nothrow) ensitlm::data_t [size];
	if (storage == NULL)
	{
		SC_REPORT_ERROR("SYSTEM", "Error allocating memory");
		abort();
	}
}

Memory::~Memory()
{
	delete[] storage;
}

tlm::tlm_response_status
	Memory::write(const ensitlm::addr_t &a, const ensitlm::data_t &d)
{
	cerr	<< FG_GREEN << "[" << name() << "] \t" << FG_DEFAULT
			<< "Write request of "
			<< std::dec << d
			<< std::hex << FG_YELLOW << " \t@" << a << FG_DEFAULT
			<< std::dec << " \t(" << FG_YELLOW  << a << FG_DEFAULT << ")"
			<< endl;
	
	storage[a/sizeof(ensitlm::data_t)] = d;
	
	return tlm::TLM_OK_RESPONSE;
}

tlm::tlm_response_status
	Memory::read(const ensitlm::addr_t &a, ensitlm::data_t &d)
{
	cerr	<< FG_GREEN << "[" << name() << "] \t" << FG_DEFAULT
			<< "Read request"
			<< FG_DEFAULT << " @" << std::hex << a << FG_DEFAULT
			<< ": " << std::dec << storage[a/sizeof(ensitlm::data_t)]
			<< endl;

	d = storage[a/sizeof(ensitlm::data_t)];

	return tlm::TLM_OK_RESPONSE;
}
