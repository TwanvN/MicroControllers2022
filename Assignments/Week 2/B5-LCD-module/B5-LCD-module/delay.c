/*
 * delay.c
 *
 * Created: 9-2-2022 13:55:39
 *  Author: Jesse
 */ 
#define F_CPU 8e6


#include <util/delay.h>

#include "delay.h"

void delay_wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}