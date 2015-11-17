#include "systemc.h"
#include "Generator.h"
#include "bus.h"

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

	gen1.initiator.bind(bus.target);

	sc_start(); return 0;
}
