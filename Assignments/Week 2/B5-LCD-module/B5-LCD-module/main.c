
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "delay.h"

int main() {
	
	LCD_init();
	
	// test text
	char string[] = "test 123 twan";
	LCD_display_text(string);
	
	LCD_set_cursor(40);
	
	// test text
	char string2[] = "jesse 123 test";
	LCD_display_text(string2);
	
	// Loop forever
	while (1) {
		PORTC ^= (1<<0);	// Toggle PORTD.7
		delay_wait( 250 );
	}
}