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

#define TICK_CM 58

int timerOverflow = 0;

char ticksOnTrigger = 0;

ISR ( INT7_vect )
{
	PORTA = TCNT2;
	
	
	if(ticksOnTrigger == 0)
		ticksOnTrigger = TCNT2;
	else
	{
		unsigned char diff = TCNT2 - ticksOnTrigger;	// Getting the difference
		
		PORTD = diff;	// Setting DDRD to the value from the echo
		
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
	//_delay_ms(500);	
	
	//char string[10];
	
	// Init I/O
	DDRD = 0xFF;			// Port D to output
	DDRA = 0xFF;
	DDRE = 0b00001111;		// PORTE(7:4) input, PORTE(3:0) output

	// Init Interrupt hardware
	EICRB |= 0x40;			// ISC7 Rising edge
	EIMSK |= 0x80;			// Enable INT7
		
	initTimer();
	
	// Initing the LCD module
	//LCD_init();
	
	_delay_ms(1500);
					
    while (1) {		
		PORTE |= (1 << TRIGGER_PIN);
		
		_delay_us(10);
		
		PORTE &= ~(1 << TRIGGER_PIN);
		
		/*// Writing distance to LCD
		sprintf(string, "%d cm  ", timerOverflow);
		LCD_set_cursor(0);
		LCD_display_text(string);
		*/
		
	    _delay_ms( 500 );
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