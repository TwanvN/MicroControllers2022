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

ISR ( INT7_vect )
{
	if (timerRunning == 0)
	{
		timerOverflow = 0; 
		timerRunning = 1;
	} 
	else
	{
		timerRunning = 0;		
	}
	
		
}

ISR ( TIMER2_COMP_vect )
{
	if (timerRunning)
		timerOverflow++;
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
	
	sei();
	
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
		PORTD = timerOverflow;
	    _delay_ms( 200 );
    }
	
	return 1;
}

void initTimer()
{
	OCR2 = TICK_CM;
	TIMSK |= (1<<7);
	TCCR2 = 0b00001001;	// 8 prescaler with compare on
}