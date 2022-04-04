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

// Defines
#define TICK_CM 58
#define TICK_MS 250 

int timerOverflow = 0;
int seconds = 0;

int timerRunning = 0;

void initTimer();
void pwmInit();

int updateTicks = 0;
int sensorTicks = 0;

/************************************************************************/
/* Timer 0 compare, increment value                                    */
/************************************************************************/
ISR ( TIMER0_COMP_vect )
{
	timerOverflow++;
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{
	// DDRF and DDRD to full output
	DDRF = 0xFF;
	DDRD = 0xFF;
	
	// DDRB to full input
	DDRB = 0x00;
	
	// Call the starting methods
	initTimer();
	pwmInit();
	TMP_init_meassure();
	
	while (1) {
		
		if ( (timerOverflow - updateTicks) >= 1000 )// Polling if 1000 millis have passed
		{
			updateLight();							// Switch to next light
			
			updateTicks = timerOverflow;			// Updating the last poll
		}
		
		if( (timerOverflow - sensorTicks) >= 100)	// Polling if 100 millis have passed
		{
			TMP_meassure();
			
			PORTD = TMP_isPlaying();				// Showing tempo playing bool to PORTD
						
			sensorTicks = timerOverflow;			// Updating the last poll
		}
		
		playFirstSong();							// Polling the buttons
		
	}
		
	return 1;
}

void initTimer()
{
	// Updating the second bit (Compare interrupt timer 0 enabled)
	TIMSK |= 0b00000010;
	
	OCR0 = TICK_MS;			// Compare on 1ms
	TIMSK |= (1<<7);		// niet nodig?
	TCCR0 = 0b00000011;		// Set timer 0 to pre-scaler 32
	sei();					// Start interrupts
}

void pwmInit() {
	DDRE = 0b0111111;		//Setting port E to output, except for E7
	TCNT3 = 0;
	
	TCCR3A = 0b00100001;	//Setting channel B on compare match
	TCCR3B = 0b01010010;	//Setting rising edge, waveform-generation and pre-scaler of 8
	
	OCR3A = 1000;			//The time where timer rises, or falls
	OCR3B = 0;				//Setting compare value for timer
}