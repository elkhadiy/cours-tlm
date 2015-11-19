// SystemC library
#include "systemc.h"

// Modules
#include "Generator.h"
#include "bus.h"
#include "memory.h"
#include "LCDC.h"

// Misc defines
#include "defines.h"
#include "LCDC_registermap.h"

int sc_main(int, char**)
{
	// Instantiating modules
	Generator	gen1("Generator1");
	Bus			bus ("Bus"       );
	Memory		mem ("Memory", MEM_SIZE                 );
	LCDC		lcd ("LCD"   , sc_time(LCD_FREQ, SC_SEC));

	// Instantiating misc signals
	sc_signal<bool> sirq;

	// Binding masters to bus
	gen1.initiator.bind      (bus.target);
	lcd.initiator_socket.bind(bus.target);

	// Biding slaves to bus
	bus.initiator.bind(mem.target       );
	bus.initiator.bind(lcd.target_socket);
	
	// Binding direct signals
	gen1.irq.bind       (sirq);
	lcd.display_int.bind(sirq);

	// Building bus memory map
	bus.map(mem.target       ,  MEM_BASE      , MEM_SIZE  );
	bus.map(lcd.target_socket,  LCDC_ADDR_REG , SINGLE_REG);
	bus.map(lcd.target_socket,  LCDC_START_REG, SINGLE_REG);
	bus.map(lcd.target_socket,  LCDC_INT_REG  , SINGLE_REG);

	// Starting simulation
	sc_start(); return 0;
}
