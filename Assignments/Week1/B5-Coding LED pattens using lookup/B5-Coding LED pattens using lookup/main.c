/*
 * main.c
 *
 * Project created for the A assignment of week 1 micro controllers.
 * Code will create an animation on the 4 rows of pins. The animation can be given in an array
 *
 * Created: 2/2/2022 10:33:08 AM
 * Author: Jesse Krijgsman & Twan van Noorloos
 */ 

// Defining the CPU speed to make the _delay_ms function work
#define F_CPU 8e6
#define ROWSIZE 4


#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

/*
* Wait method was created by Eti�nne Goossens and taken from the example projects given.
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
* struct to define one set of instructions from the animation / pattern
* - Value contains the bytes for each row on the matrix to display on. In the example this is 4*8
* - Delay tells how long the instruction needs to be displayed
*/
typedef struct PatternInstruction {
	unsigned char value[ROWSIZE];
	unsigned int delay;
} PATTERN_INSTRUCTION;

/*
* List of the pre-programmed animation
*/
#define INSTRUCTION_SIZE 25
PATTERN_INSTRUCTION instructions[INSTRUCTION_SIZE] = { 
	//  Instruction				  delay 
	{	{0x01, 0x01, 0x01, 0x01}, 100, }, // Light up the top row
	{	{0x03, 0x03, 0x03, 0x03}, 100, }, // Light up the second row
	{	{0x07, 0x07, 0x07, 0x07}, 100, }, // Light up the third row
	{	{0x0F, 0x0F, 0x0F, 0x0F}, 100, }, // Light up fourth row
	{	{0x1F, 0x1F, 0x1F, 0x1F}, 100, }, // Light up fifth row
	{	{0x3F, 0x3F, 0x3F, 0x3F}, 100, }, // Light up sixth row
	{	{0x7F, 0x7F, 0x7F, 0x7F}, 100, }, // Light up seventh row
	{	{0xFF, 0xFF, 0xFF, 0xFF}, 250, }, // Light up eight row
		
	{	{0x00, 0xFF, 0xFF, 0xFF}, 100, }, // Light up the top column
	{	{0x00, 0xFF, 0xFF, 0xFF}, 100, }, // Light up the second column
	{	{0x00, 0x00, 0xFF, 0xFF}, 100, }, // Light up the third column
	{	{0x00, 0x00, 0x00, 0xFF}, 250, }, // Light up fourth column
	
	{	{0x00, 0x00, 0x00, 0x01}, 100, }, // Light first diagonal
	{	{0x00, 0x00, 0x01, 0x02}, 100, }, // Light second diagonal
	{	{0x00, 0x01, 0x02, 0x04}, 125, }, // Light third diagonal	
	{	{0x01, 0x02, 0x04, 0x08}, 125, }, // Light fourth diagonal	
	{	{0x02, 0x04, 0x08, 0x10}, 150, }, // Light fifth diagonal
	{	{0x04, 0x08, 0x10, 0x20}, 150, }, // Light sixth diagonal
	{	{0x08, 0x10, 0x20, 0x40}, 175, }, // Light eight diagonal
	{	{0x10, 0x20, 0x40, 0x80}, 175, }, // Light ninth diagonal
	{	{0x20, 0x40, 0x80, 0x00}, 200, }, // Light eleventh diagonal
	{	{0x40, 0x80, 0x00, 0x00}, 200, }, // Light twelfth diagonal
	{	{0x80, 0x00, 0x00, 0x00}, 500, }, // Light thirteenth diagonal
};

/*
* Given one instruction this method sets all the lamps to that instruction
*/
void setLamps(PATTERN_INSTRUCTION instruction);

int main(void)
{
	// Initializing all rows to output 0b1111-1111
	DDRA = 0xFF; DDRB = 0xFF; DDRC = 0xFF; DDRD = 0xFF;
	
    while(1)
    {
		// Going over all the instructions 
		for (int i = 0; i < INSTRUCTION_SIZE; i++)
		{
			// Setting the lamps with the current instruction
			setLamps(instructions[i]);
			// Waiting for the specified delay from the current instruction
			wait(instructions[i].delay);
		}
    }
	
	return 1;
}

void setLamps(PATTERN_INSTRUCTION instruction) {
	// Setting all the PORTS to the given instruction
	PORTA = instruction.value[0];
	PORTB = instruction.value[1];
	PORTC = instruction.value[2];
	PORTD = instruction.value[3];
}