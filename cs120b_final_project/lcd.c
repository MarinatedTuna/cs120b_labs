#include "lcd.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

/*-------------------------------------------------------------------------*/
#define DATA_BUS PORTC		// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTD	// port connected to pins 4 and 6 of LCD disp.
#define RS 6			// pin number of uC connected to pin 4 of LCD disp.
#define E 7			// pin number of uC connected to pin 6 of LCD disp.
/*-------------------------------------------------------------------------*/

void LCD_ClearScreen(void) {
	LCD_WriteCommand(0x01);
}

void LCD_init(void) {

	//wait for 100 ms.
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x0f);
	LCD_WriteCommand(0x01);
	delay_ms(10);
}

void LCD_WriteCommand (unsigned char Command) {
	CLR_BIT(CONTROL_BUS,RS);
	DATA_BUS = Command;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
	SET_BIT(CONTROL_BUS,RS);
	DATA_BUS = Data;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(1);
}

void LCD_DisplayString( unsigned char column, unsigned char* string) {
	LCD_ClearScreen();
	unsigned char c = column;
	while(*string) {
		LCD_Cursor(c++);
		LCD_WriteData(*string++);
	}
}

void LCD_Cursor(unsigned char column) {
	if(column < 17) { //16x1 LCD: column < 9
		LCD_WriteCommand(0x80 + column - 1); //16x2 LCD: column < 17
	}
	else {
		LCD_WriteCommand(0xB8 + column - 9); // 16x1 LCD: column - 1
	}
}

//WEBSITE LINKS

//This is the website I used to help me generate custom characters
https://www.circuitvalley.com/2012/02/lcd-custom-character-hd44780-16x2.html

//This is the website I used to help me program the functions for custom character creation
https://www.electronicwings.com/avr-atmega/lcd-custom-character-display-using-atmega-16-32-

//writes custom characters into memory
void LCD_Custom_Char1 (unsigned char loc, unsigned char *msg)
{
	unsigned char j;
	if(loc<8)
	{
		LCD_WriteCommand(0x40 + (loc*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
		for(j=0;j<7;j++)	/* Write 7 byte for generation of 1 character */
		LCD_WriteData(msg[j]);
	}
}

//outputs custom characters onto screen
void LCD_Custom_Char2 (unsigned char loc, unsigned char *msg)
{
	unsigned char j;
	if(loc<8)
	{
		LCD_WriteCommand(0x80 + (loc*8));  /* Command 0x80 prints characters saved in CGRAM address */
		for(j=0;j<7;j++)	/* Write 7 byte for generation of 1 character */
		LCD_WriteData(msg[j]);
	}
}

void delay_ms(int miliSec) { //for 8 Mhz crystal
	int i,j;
	for(i=0;i<miliSec;i++)
	for(j=0;j<775;j++)
	{
		asm("nop");
	}
}
