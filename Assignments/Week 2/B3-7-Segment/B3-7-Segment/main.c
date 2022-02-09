/*
 * Assignment B3. Using a look-up table to store all the details of hex-numbers
 * a seven segment display can be controlled. With the 
 *
 * Created: 2/9/2022 11:22:18 AM
 * Author: Twan van Noorloos & Jesse Krijgsman
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <xc.h>
#include <util/delay.h>

// Array contains the codes to display a code on the 7segment display
char letterCodes[] = {
	0x77, // 0
	0x44, // 1
	0x6B, // 2
	0x6E, // 3
	0x5C, // 4
	0x3E, // 5
	0x3F, // 6
	0x64, // 7
	0x7F, // 8
	0x7E, // 9
	0x7D, // A
	0x1F, // B
	0x33, // C
	0x4F, // D
	0x3B, // E
	0x39, // F
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

/*
* Given a number this method shows the number to the 7-segment display connected on port A
*/
void display(int digit){
	// Checking if the entered value is in bounds, show the given digit
	if (digit >= 0 && digit <= 15) PORTA = letterCodes[digit];
	// show the 0 digit
	else PORTA = letterCodes[14];
};

/*
* Main method to set up the 7-segment assignment
*/
int main(void)
{
	// setting DDRA to output for 7-segment 
	DDRA = 0xFF;
	// Setting DRRC to input
	DDRC = 0x00;
	
	// Setting the seven segment display to zero to start
	int digit = 0;
	display(digit);
	
	// main loop
    while(1)
    {
		// If button C0 is pressed digit-up
		// If C1 digit-down
		// If both are pressed go back to zero
        if (PINC == 0b00000001)	digit++;
        else if (PINC == 0b00000010) digit--;
		else if (PINC == 0b00000011) digit = 0;
			
		// refreshing the 7-segment display
		display(digit);
		
		wait(250);
    }
}