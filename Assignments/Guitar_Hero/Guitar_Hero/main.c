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
	DDRF = 0xFF;
	DDRB = 0x00;
	
	TIMSK = 0b00011000;
	
	playFirstSong();
	
	return 1;
}

void initTimer()
{
	OCR2 = TICK_CM;
	TIMSK |= (1<<7);
	TCCR2 = 0b00001001;	// 8 prescaler with compare on
}