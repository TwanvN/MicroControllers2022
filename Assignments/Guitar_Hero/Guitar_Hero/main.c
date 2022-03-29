/*
 * main.c
 *
 * Created: 3/10/2022 3:30:28 PM
 *  Author: Jesse
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>

#include "LCD_Module.h"
#include "UTS_Ultrasone.h"

int main(void)
{	
	_delay_ms(500);	
	
	// Init I/O
	DDRD = 0xFF;			// Port D to output
			
	UTS_Init();
					
    while (1) {		
		
		UTS_Trigger();
		
		PORTD = currentDistance;
		
		
	    _delay_ms( 250 );
    }
	
	return 1;
}