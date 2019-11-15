#ifndef LCD_8BIT_H
#define LCD_8BIT_H

#include "bit.h"


#define LCD_DATA PORTD	
#define LCD_CTRL PORTB	
#define LCD_RS   3 		
#define LCD_E    4		


unsigned char LCD_rdy_g = 0;

unsigned char LCD_go_g = 0;

unsigned char LCD_string_g[16];

unsigned char LCD_write_str = 1;

unsigned char LCD_char_pos = 0; 

void LCD_WriteCmdStart(unsigned char cmd) {
	LCD_CTRL = SetBit(LCD_CTRL,LCD_RS, 0);
	LCD_DATA = cmd;
	LCD_CTRL = SetBit(LCD_CTRL,LCD_E, 1);
}
void LCD_WriteCmdEnd() {
	LCD_CTRL = SetBit(LCD_CTRL,LCD_E, 0);
}
void LCD_WriteDataStart(unsigned char Data) {
	LCD_CTRL = SetBit(LCD_CTRL,LCD_RS,1);
	LCD_DATA = Data;
	LCD_CTRL = SetBit(LCD_CTRL,LCD_E, 1);
}
void LCD_WriteDataEnd() {
	LCD_CTRL = SetBit(LCD_CTRL,LCD_E, 0);
}
void LCD_Cursor(unsigned char column) {
	if ( column < 8 ) {
		LCD_WriteCmdStart(0x80+column);
	}
	else {
		LCD_WriteCmdStart(0xB8+column);
	}
}

enum LI_States { LI_Init1, LI_Init2, LI_Init3, LI_Init4, LI_Init5,
		LI_WaitDisplayString, LI_PositionCursor, LI_DisplayChar, LI_WaitGo0 };

int LCDI_SMTick(int state) {
	static unsigned char i;
	switch(state) {
	case -1:
		state = LI_Init1;
		break;
	case LI_Init1:
		state = LI_Init2;
		i=0;
		break;
	case LI_Init2:
		if (i<10) { 
			state = LI_Init2;
		}
		else {
			state = LI_Init3;
		}
		break;
	case LI_Init3:
		state = LI_Init4;
		LCD_WriteCmdEnd();
		break;
	case LI_Init4:
		state = LI_Init5;
		LCD_WriteCmdEnd();
		break;
	case LI_Init5:
		state = LI_WaitDisplayString;
		LCD_WriteCmdEnd();
		break;
	case LI_WaitDisplayString:
		if (!LCD_go_g) {
			state = LI_WaitDisplayString;
		}
		else if (LCD_go_g) {
			LCD_rdy_g = 0;
			state = LI_PositionCursor;
			i=0;
		}
		break;
	case LI_PositionCursor:
		state = LI_DisplayChar;
		LCD_WriteCmdEnd();
		break;
	case LI_DisplayChar:
		if (i<16 && LCD_write_str) {
			state = LI_PositionCursor;
			LCD_WriteDataEnd();
			i++;
		}
		else {
			state = LI_WaitGo0;
			LCD_WriteDataEnd();
		}
		break;
	case LI_WaitGo0:
		if (!LCD_go_g) {
			state = LI_WaitDisplayString;
		}
		else if (LCD_go_g) {
			state = LI_WaitGo0;
		}
		break;
	default:
		state = LI_Init1;
	} 

	switch(state) { 
	case LI_Init1:
		LCD_rdy_g = 0;
		break;
	case LI_Init2:
		i++; // Waiting after power up
		break;
	case LI_Init3:
		LCD_WriteCmdStart(0x38);
		break;
	case LI_Init4:
		LCD_WriteCmdStart(0x0F);
		break;
	case LI_Init5:
		LCD_WriteCmdStart(0x01); 
		break;
	case LI_WaitDisplayString:
		LCD_rdy_g = 1;
		break;
	case LI_PositionCursor:
		if ( LCD_write_str ) {
			LCD_Cursor(i);
		} else {
			LCD_Cursor(LCD_char_pos);
		}
		break;
	case LI_DisplayChar:
		if ( LCD_write_str ) {
			LCD_WriteDataStart(LCD_string_g[i]);
		} else {
			LCD_WriteDataStart(LCD_string_g[0]);
		}
		break;
	case LI_WaitGo0:
		break;
	default:
		break;
	} 
	return state;
}

#endif