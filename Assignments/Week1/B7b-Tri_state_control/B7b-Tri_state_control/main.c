/*
 * main.c
 *
 * Project created for the B7b assignment of week 1 micro controllers.
 * The program can control 6 LEDs with only 3 ports using charlie plexing
 *
 * Created: 2/2/2022 12:47:08 AM
 * Author: Jesse Krijgsman & Twan van Noorloos
 */ 

// Defining the CPU speed to make the _delay_ms function work
#define F_CPU 8e6

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

/*
* Given the number of the LED, this method turns on that LED using Charlie-plexing
*/
void setCharliePlexingLed(int lednr);

/*
* struct defines the value's needed to turn on one LED.
* This is done using the needed Tri-state value and the value for the PORT
*/
typedef struct
{
	char triState;
	char value;
} PIN_INSTRUCTION;

// Holding the values needed for all the six LED so they can quickly be looked up.
//			Pin 1		|	Pin 2		|	Pin 3			PORT		DDR
// LED 1 |	1			|	0			|	Tri-state		0b0010		0b0110
// LED 2 |	0			|	1			|	Tri-state		0b0100		0b0110
// LED 3 |	Tri-state	|	1			|	0				0b0100		0b1100
// LED 4 |	Tri-state	|	0			|	1				0b1000		0b1100
// LED 5 |	0			|	Tri-state	|	1				0b1000		0b1010
// LED 6 |	1			|	Tri-state	|	0				0b0010		0b1010
//
PIN_INSTRUCTION charliePlexArray[] = {
	{0b00000110, 0b00000010}, 
	{0b00000110, 0b00000100},
	{0b00001100, 0b00000100},
	{0b00001100, 0b00001000},
	{0b00001010, 0b00001000},
	{0b00001010, 0b00000010}
};

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
		
    while(1)
    {
		// Going over all 6 LEDs
		for (int i = 1; i <= 6; i++)
		{
			setCharliePlexingLed(i);	// Turning LED i on
			wait(500);					// Delay for 500 ms 
		}
    }
	
	return 1;
}

/*
* Setting one LED on using Charlie plexing
*/
void setCharliePlexingLed(int lednr) 
{
	// LEDs go from 1-6, array from 0-5 ==> LED = LED - 1
	lednr -= 1;
	
	// Setting the PORTA and DDRA to value from array
	PORTA = charliePlexArray[lednr].value;
	DDRA = charliePlexArray[lednr].triState;
}