/*
 * main.c
 *
 * Created: 2/9/2022 10:33:04 AM
 *  Author: Twan van Noorloos & Jesse Krijgsman
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
 * Interrupt method which changes the light on PORTC
 * Does this by bit-shifting PORTC one to the left and checks
 * if the value is at the end and sets PORTC to the first LED
 */
ISR( INT1_vect ) {
	PORTC <<= 1;
	
	if (PORTC == 0x00)
		PORTC = 0x01;
}

/*
 * Interrupt method which changes the light on PORTC
 * Does this by bit-shifting PORTC one to the right and checks
 * if the value is at the start and sets PORTC to the last LED
 */
ISR( INT2_vect ) {
	PORTC >>= 1;
	
	if (PORTC == 0b00000000)
		PORTC = 0b10000000;
}

int main( void ) {
	// Init I/O
	DDRD = 0b11111001;
	DDRC = 0xFF;

	// Init Interrupt hardware
	EICRA |= 0x3C;			// INT2 rising edge, INT1 rising edge
	EIMSK |= 0x06;			// Enable INT2 & INT1
	
	// Enable global interrupt system
	sei();
	
	PORTC = 0x01;

	while (1) {
		
	}

	return 1;
}