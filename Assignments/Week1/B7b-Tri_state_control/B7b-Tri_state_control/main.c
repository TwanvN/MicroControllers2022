/*
 * main.c
 *
 * Created: 2/2/2022 2:39:01 PM
 *  Author: Jesse
 */ 
#include <xc.h>

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

#define PIN_A = 1;
#define PIN_B = 2;
#define PIN_C = 3;

void setCharliePlexingLed(int lednr);

typedef struct
{
	char triState;
	char value;
} PIN_INSTRUCTION;

PIN_INSTRUCTION charliePlexArray[] = {
	{0b00000110, 0b00000010},
	{0b00000110, 0b00000100},
	{0b00001100, 0b00000100},
	{0b00001100, 0b00001000},
	{0b00001010, 0b00001000},
	{0b00001010, 0b00000010}
};

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

int main(void)
{
		
    while(1)
    {
		for (int i = 1; i <= 6; i++)
		{
			setCharliePlexingLed(i);
			wait(500);
		}
    }
	
	return 1;
}

void setCharliePlexingLed(int lednr) 
{
	lednr -= 1;
	
	PORTA = charliePlexArray[lednr].value;
	DDRA = charliePlexArray[lednr].triState;
}