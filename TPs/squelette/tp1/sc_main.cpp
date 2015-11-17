#include "systemc.h"
#include "Generator.h"
#include "bus.h"
#include "Memory.h"

int sc_main(int, char**)
{
	/*
	 +----------+	 +-------------+    +------------+
	 |	  +++  +-+	     +++  +++	     |          |
	 | Generator  | +--+ |  Bus   | +--+ |  Memoire |
	 |	  +++  +-+	     +++  +++	     |          |
	 +----------+	 +-------------+	+------------+
	 */
	Generator	gen1("Generator1");
	Bus			bus("Bus");
	Memory		mem("Memory");

	gen1.initiator.bind(bus.target);
	bus.initiator.bind(mem.target);

	sc_start(); return 0;
}
