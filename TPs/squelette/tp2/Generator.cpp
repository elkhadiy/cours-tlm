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
}
