/*
 * main.c
 *
 * Created: 2/23/2022 11:59:14 AM
 *  Author: Twanv
 */ 
#define F_CPU 8e6

#include <xc.h>
#include <util/delay.h>

/*
 * Sets the ADC-A correctly
 * External power at 5V, on port 1
 * Prescaler of 64
 */
void adcInit() {
	ADMUX = 0b01100001;		// 5 V, result left, Pin F1
	ADCSRA = 0b11100110;	// ADC on, no interrupts, freerunning on, prescaler 64
}

int main(void)
{
	DDRA = 0xFF;		// DDRA on output
	DDRB = 0xFF;		// DDRB on output
	DDRF = 0x00;		// DDRF on input
	
	adcInit();			// Init the ADC
	
    while(1)
    {
        PORTB = ADCL;	// Set last bits of ADC to PORTB
		PORTA = ADCH;	// Set first byte of ADC to PORTA
		_delay_ms(100);	// Delay for 100ms
    }
}