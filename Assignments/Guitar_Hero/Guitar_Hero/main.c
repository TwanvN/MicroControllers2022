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

#define TRIGGER_PIN 0
#define ECHO_PIN 7

#define TICK_CM 58.0

int currentDistance = 0;

char ticksOnTrigger = 0;

ISR ( INT7_vect )
{	
	PORTD = PINE;
	
	if( PINE & (1 << ECHO_PIN) )
		ticksOnTrigger = TCNT2;
	
	else
	{
		unsigned char diff = TCNT2 - ticksOnTrigger;	// Getting the difference
		
		currentDistance = ( diff * ( 32.0 / TICK_CM ) );	
				
		
		ticksOnTrigger = 0; // resetting ticksOnTrigger
	}
	
}

ISR ( TIMER2_OVF_vect )
{	
	TCNT2 = 0; // Resetting timer
}

void initTimer();

int main(void)
{	
	_delay_ms(500);	
	
	// Init I/O
	DDRD = 0xFF;			// Port D to output

	DDRE = 0b00001111;		// PORTE(7:4) input, PORTE(3:0) output

	// Init Interrupt hardware
	EICRB |= 0x40;			// ISC7 Rising edge
	EIMSK |= 0x80;			// Enable INT7
		
	initTimer();
	
	// Initing the LCD module
	LCD_init();
	
	_delay_ms(1500);
					
    while (1) {		
		PORTE |= (1 << TRIGGER_PIN);
		
		_delay_us(10);
		
		PORTE &= ~(1 << TRIGGER_PIN);
		
		char string[13];
		
		// Writing distance to LCD
		sprintf(string, "%d cm   ", currentDistance);
		LCD_set_cursor(0);
		LCD_display_text(string);
		
		
	    _delay_ms( 1000 );
    }
	
	return 1;
}

void initTimer()
{
	TCNT2 = 0;
	TIMSK |= 0b01000000;
	TCCR2 = 0b00001100;
	sei();
}