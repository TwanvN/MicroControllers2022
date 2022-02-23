/*
 * main.c
 *
 * Created: 2/23/2022 11:59:14 AM
 *  Author: Twanv
 */ 
#define F_CPU 8e6

#include <xc.h>
#include <util/delay.h>

void adcInit() {
	ADMUX = 0b01100011;  // Standard (5) V, on port F3
	
	ADCSRA = 0b10000110; // ADC-enable, no interrupt, no free running, division by 64
}

int main(void)
{
	DDRA = 0xFF;	// DDRA to output
	DDRF = 0x00;	// DDRF to input
	
	adcInit();	// Init the ADC
	
    while(1)
    {
		ADCSRA |= (1<<6);				// Start ADC
		while ( ADCSRA & (1<<6)) ;		// Wait for completion
		PORTA = ADCH;					// Setting the most significant bits to PORTA
		_delay_ms(100);					// Delay for 100ms
    }
}