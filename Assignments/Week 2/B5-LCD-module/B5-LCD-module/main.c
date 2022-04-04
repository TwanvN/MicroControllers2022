
#define F_CPU 8e6

#include "LCD.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// Main method to test the display module
int main() {
		
	_delay_ms(500);	
		
	// Starting up the LCD display
	LCD_init();
	
	_delay_ms(1500);
	
	// Writing a test string to the first line
	char string[] = "test 123 Twan";
	LCD_display_text(string);
	
	// Moving the cursor to position 40 (line 2)
	LCD_set_cursor(40);
	
	// Writing a test string to the second line
	char string2[] = "Jesse 123 test";
	LCD_display_text(string2);
	
}