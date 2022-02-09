/*
 * LCD.h
 *
 * Created: 9-2-2022 13:50:18
 *  Author: Jesse
 */ 


#ifndef LCD_H_
#define LCD_H_


	void LCD_init();
	void LCD_display_text(char *str);
	void LCD_set_cursor(int position);


#endif /* LCD_H_ */