#include "Memory.h"

Memory::Memory(sc_module_name name)
	: sc_module(name)
{

}

tlm::tlm_response_status
	Memory::write(const ensitlm::addr_t &a, const ensitlm::data_t &d)
{
	cout	<< "[" << name() << "] "
			<< "Write request of "
			<< std::dec << d
			<< std::hex << " \t@" << a
			<< std::dec << " \t(" << a << ")"
			<< endl;
	return tlm::TLM_OK_RESPONSE;
}

tlm::tlm_response_status
	Memory::read(const ensitlm::addr_t &a, ensitlm::data_t &d)
{
	cout	<< "Read request"
			<< " @" << a
			<< endl;

	return tlm::TLM_OK_RESPONSE;
}
