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
#include "song_module.h"

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
	DDRB = 0x00;
	DDRF = 0xFF;
	DDRD = 0xFF;
			
	UTS_Init();
					
    while (1) {		
		
		UTS_Trigger();
		
		PORTD = currentDistance;
		
		
	    _delay_ms( 250 );
    }
	
	TIMSK = 0b01000010;
	
	initTimer();
	pwmInit();
	
	playFirstSong();
	
	return 1;
}

void initTimer()
{
	OCR0 = TICK_MS;
	TIMSK |= (1<<7);
	TCCR0 = 0b00000011;
	sei();
}

void pwmInit() {
	DDRE = 0xFF;
	TCNT3 = 0;
	
	TCCR3A = 0b00101001;
	TCCR3B = 0b01010010;
	
	OCR3A = 1000;
	OCR3B = 10;
}