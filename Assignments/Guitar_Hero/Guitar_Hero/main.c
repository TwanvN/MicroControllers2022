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

int timerRunning = 0;

/************************************************************************/
/* Interrupt called on TRIGGER_PIN going high and low                   */
/* Starts the timer to check the pulse length							*/
/************************************************************************/
ISR ( INT7_vect )
{
	PORTD ^= 0x01;
	//PORTD = TCNT1;
	
	// If timer is running: 
	// Stop the timer and save the length of the pulse 
	if (timerRunning == 1)
	{
		
	
	}
	
		
}

void initTimer();

int main(void)
{
	_delay_ms(500);	
	
	//char string[10];
	
	// Init I/O
	DDRD = 0xFF;			// Port D to output
	DDRE = 0b00001111;		// PORTD(7:4) input, PORTD(3:0) output

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
		
		/*
		// Writing distance to LCD
		sprintf(string, "%d cm  ", timerOverflow);
		LCD_set_cursor(0);
		LCD_display_text(string);
		*/
		
	    _delay_ms( 5000 );
    }
	
		
	return 1;
}

void initTimer()
{
	sei(); // turn_on intr all
	TCCR1A = 0b00000000; // Initialize T1: timer, prescaler=256,
	TCCR1B = 0b00001001; // compare output disconnected, CTC, RUN
}