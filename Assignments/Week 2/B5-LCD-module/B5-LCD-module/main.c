
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "delay.h"

// Main method to test the display module
int main() {
	
	// Starting up the LCD display
	LCD_init();
	
	// Writing a test string to the first line
	char string[] = "test 123 Twan";
	LCD_display_text(string);
	
	// Moving the cursor to position 40 (line 2)
	LCD_set_cursor(40);
	
	// Writing a test string to the second line
	char string2[] = "Jesse 123 test";
	LCD_display_text(string2);
	
}