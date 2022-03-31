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
#include "song_module.h"
#include "TMP_TempoMeter.h"

#define TICK_CM 58
#define TICK_MS 250 

int timerOverflow = 0;
int seconds = 0;

int timerRunning = 0;

ISR ( TIMER0_COMP_vect )
{
	timerOverflow++;
		
}

void initTimer();
void pwmInit();

int updateTicks = 0;
int sensorTicks = 0;

int main(void)
{
	DDRF = 0xFF;
	DDRB = 0x00;
	DDRD = 0xFF;
	
	initTimer();
	pwmInit();
	TMP_init_meassure();
	
	TIMSK = 0b01000010;
	
	while (1) {
		
		if ( (timerOverflow - updateTicks) >= 1000 )
		{
			updateLight();
			
			updateTicks = timerOverflow;
		}
		
		if( (timerOverflow - sensorTicks) >= 100)
		{
			TMP_meassure();
			
			DDRD = TMP_isPlaying();
						
			sensorTicks = timerOverflow;
		}
		
		playFirstSong();
		
	}
		
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