/*
 * main.c
 *
 * Project created for the B1 assignment of week 1 micro controllers.
 * Code will make the PORTD pin 6 and 7 light up and flicker
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
	DDRD = 0xC0;	// Turning pin 6 and 7 to output, rest to input 0b1100-0000;
	
	// Main loop
    while(1)
    {
        PORTD = 0x80;	// Turning pin 7 on and 6 off 0b1000-0000
		wait(500);		// Delay for 500 ms
		PORTD = 0x40;	// Turning pin 6 on and 7 off 0b0100-0000
		wait(500);		// Delay for 500 ms
    }
	
	return 1;
}