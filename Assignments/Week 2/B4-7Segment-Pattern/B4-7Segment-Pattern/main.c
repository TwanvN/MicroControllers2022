/*
 * main.c
 *
 * Created: 2/9/2022 12:48:58 PM
 *  Author: Twanv
 */ 

#define F_CPU 8e6

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

typedef struct PatternInstruction {
	unsigned char value;
	unsigned int delay;
} PATTERN_INSTRUCTIONS;

/*
* List of the pre-programmed animation
*/
#define INSTRUCTION_SIZE 25
PATTERN_INSTRUCTIONS instructions[INSTRUCTION_SIZE] = {
	//Fill up circle
	{0b00100000, 200},
	{0b01100000, 200},
	{0b01100100, 200},
	{0b01100110, 200},
	{0b01100111, 200},
	{0b01110111, 200},
	//Empty clear circle
	{0b01010111, 200},
	{0b00010111, 200},
	{0b00010011, 200},
	{0b00010001, 200},
	{0b00010000, 200},
	{0b00000000, 400},
	//Fill middle lines
	{0b00100000, 200},
	{0b00101000, 200},
	{0b00101010, 400},
	//Clear middle lines
	{0b00101000, 200},
	{0b00100000, 200},
	{0b00000000, 400},
	//Fill vertical line
	{0b00010001, 400},
	{0b01010101, 1000},
	{0b00010001, 400},
	{0b00000000, 1000}
};

void wait( int ms )
{
	// Make the processor delay for 1 ms looped for the given ms
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void display(PATTERN_INSTRUCTIONS instruction){
	PORTA = instruction.value;
};

int main(void)
{
	DDRA = 0xFF;
    int index = 0;
	
    while( instructions[index].delay != 0 ) {
	    for (int i = 0; i < INSTRUCTION_SIZE; i++)
	    {
		    display(instructions[i]);
		    wait(instructions[i].delay);
	    }
    }
}