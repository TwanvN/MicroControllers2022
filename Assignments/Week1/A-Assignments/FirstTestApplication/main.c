/*
 * main.c
 *
 * Project created for the A assignment of week 1 micro controllers.
 * Code will make the lights in DDRA flicker. This is used to test the board and simulator
 *
 * Created: 2/2/2022 10:33:08 AM
 *  Author: Jesse Krijgsman & Twan van Noorloos
 */ 

// Defining the CPU speed to make the _delay_ms function work
#define F_CPU 8e6


#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

/*
* Wait method was created by Etiënne Goossens and taken from the example projects given.
* Given the amount of milliseconds to wait the method waits for that long.ss
*/
void wait( int ms )
{
	// Make the processor delay for 1 ms looped for the given ms
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRD = 0xFF; // Setting all the pins in D to output 0b1111-1111
	
    while(1)
    {
        PORTD = 0xAA;	// Turn on first set of pins 0b1010-1010
		wait( 250 );	// Delay for 250 ms
		PORTD = 0x55;	// Turn on the other set of pins 0b0101-0101
		wait( 250 );	// Delay for 250 ms
    }
	
	return 1;
}