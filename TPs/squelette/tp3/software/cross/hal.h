/********************************************************************
 * Copyright (C) 2009, 2012 by Verimag                              *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

/*!
  \file hal.h
  \brief Harwdare Abstraction Layer : implementation for MicroBlaze
  ISS.


*/
#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include "address_map.h"


/* Dummy implementation of abort(): dereference a NULL pointer */
#define abort() ((*(int *)NULL) = 0)

/* TODO : implementer ces primitives pour la compilation croisée */
#define read_mem(a)     ( *( (volatile uint32_t*) (a) ) )
#define write_mem(a,d)  ( *( (volatile uint32_t*) (a) ) = (d) )
#define wait_for_irq()  abort()
#define cpu_relax()     ( (void) NULL )

/* printf is disabled, for now ... */
#define printf(x) my_printf(x)

void my_printf(const char *c)
{
	int i = 0;
	while (c[i] != '\0') {
		//*((volatile char*)(UART_BASEADDR + UART_FIFO_WRITE)) = c[i];
		write_mem(UART_BASEADDR + UART_FIFO_WRITE, c[i]);
		i++;
	}
}

#endif /* HAL_H */
