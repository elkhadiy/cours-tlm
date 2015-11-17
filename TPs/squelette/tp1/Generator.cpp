#include "Generator.h"

Generator::Generator(sc_module_name name)
	: sc_module(name)
{
	SC_THREAD(generate);
}

void Generator::generate(void)
{
	tlm::tlm_response_status status;
	ensitlm::data_t val  = 42;
	ensitlm::addr_t addr = 1;

	while (true)
	{
		status = initiator.write(addr, val);

		if (status != tlm::TLM_OK_RESPONSE)
		{
			cout	<< "Failed writing to bus" 
					<< std::endl;
		}

		wait(10, SC_NS);
	}
}
