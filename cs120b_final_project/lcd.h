#ifndef __LCD_H__
#define __LCD_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column , unsigned char *string);
void LCD_Custom_Char1 (unsigned char loc, unsigned char *msg);
void LCD_Custom_Char2 (unsigned char loc, unsigned char *msg);
void delay_ms(int miliSec);

#endif
