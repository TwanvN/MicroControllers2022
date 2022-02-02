/*
 * main.c
 *
 * Created: 2/2/2022 12:38:49 PM
 *  Author: Twanv
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

enum state {slow, fast};

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

enum state loopCheck(int ms, enum state currentState) {
	for (int i=0; i<ms; i += 10) {
		_delay_ms( 10 );
		
		if (PINC == 0b00000001)
		{
			if (currentState == fast){
				currentState = slow;
			} else if (currentState == slow){
				currentState = fast;
			}
			return currentState;
		}
	}
	
	return currentState;
}

int main(void)
{
	DDRD = 0b11111111;
	
	enum state currentState;
	currentState = slow;
	
    while(1)
    {
		
		if (currentState == slow)
		{
			PORTD = 0b10000000;
			currentState = loopCheck(1000, currentState);
			PORTD = 0b00000000;
			currentState = loopCheck(1000, currentState);
		} else if (currentState == fast) {
			PORTD = 0b10000000;
			currentState = loopCheck(250, currentState);
			PORTD = 0b00000000;
			currentState = loopCheck(250, currentState);
		}
    }
}