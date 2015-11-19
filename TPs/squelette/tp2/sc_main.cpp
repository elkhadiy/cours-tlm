// SystemC library
#include "systemc.h"

// Modules
#include "Generator.h"
#include "bus.h"
#include "memory.h"
#include "LCDC.h"
#include "ROM.h"

// System global configuration
#include "defines.h"

int sc_main(int, char**)
{
	// Instantiating modules
	Generator	gen1("Generator1");
	Bus			bus ("Bus"       );
	Memory		mem ("Memory", MEM_SIZE                 );
	LCDC		lcd ("LCD"   , sc_time(LCD_FREQ, SC_SEC));
	ROM         rom ("ROM"       );

	// Instantiating misc signals
	sc_signal<bool> sirq;

	// Binding masters to bus
	gen1.initiator.bind      (bus.target);
	lcd.initiator_socket.bind(bus.target);

	// Biding slaves to bus
	bus.initiator.bind(mem.target       );
	bus.initiator.bind(lcd.target_socket);
	bus.initiator.bind(rom.socket);
	
	// Binding direct signals
	gen1.irq.bind       (sirq);
	lcd.display_int.bind(sirq);

	// Building bus memory map
	bus.map(mem.target       , MEM_BASE      , MEM_SIZE       );
	bus.map(lcd.target_socket, LCDC_ADDR_BASE, LCDC_ADDR_RANGE);
	bus.map(rom.socket       , ROM_BASE      , ROM_SIZE       );

	// Starting simulation
	sc_start(); return 0;
}
