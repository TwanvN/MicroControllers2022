/*
 * main.c
 *
 * Created: 2/16/2022 11:38:29 AM
 *  Author: Jesse
 */ 
#define F_CPU 8e6

#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initTimer();

#define TICKS_HIGH 195` // Tick time for 25ms with prescaler 1024
#define TICKS_LOW 117	// Tick time for 15ms with prescaler 1024

// Interrupt routine
// Flips the D7 bit and sets the correct ticks delay
ISR( TIMER2_COMP_vect ) {
	
	// Checking if D7 is high
	if (OCR2 == TICKS_LOW)
	{
		PORTD ^= (1 << 7);
		OCR2 = TICKS_HIGH;	// Set the delay to 25ms
	} else {
		PORTD ^= (1 << 7);
		OCR2 = TICKS_LOW;	// Set the delay to 15ms
	}
}


int main(void)
{
	DDRD = 0xFF;	// Setting D port to output
	
	initTimer();
	
    while(1)
    {
        //empty main
    }
}

// Starts the timer
void initTimer()
{
	OCR2 = TICKS_HIGH;	// Set the compare to 25ms
	TIMSK |= (1<<7);	// Set the compare interrupt flag
	sei();				// Start interrupts
	TCCR2 = 0b00001101;	// 1024 prescaler with compare on
}