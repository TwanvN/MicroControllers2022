/*
 * main.c
 *
 * Created: 3/10/2022 3:30:28 PM
 *  Author: Jesse
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>

#include "LCD_Module.h"
#include "song_module.h"

#define TRIGGER_PIN 0

#define TICK_MS 250

int timerOverflow = 0;
int seconds = 0;

ISR ( TIMER0_COMP_vect )
{
	timerOverflow++;
	
	if (timerOverflow == 1000)
	{
		seconds++;
		timerOverflow = 0;
		updateLight();
	}
}

void initTimer();

int main(void)
{
	DDRF = 0xFF;
	DDRB = 0x00;
	
	TIMSK = 0b01000010;
	
	initTimer();
	
	while(1) {
		PORTF = seconds;
	}
	
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