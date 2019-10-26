/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

void TimerISR() {
    TimerFlag = 1;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; // inputs

    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines

    // Initializes the LCD display
    LCD_init();

    // Starting at position 1 on the LCD screen, writes "Hello World"
//    LCD_DisplayString(1, "Hello World");

    unsigned char num = 0;

    //need timer
    TimerSet(1000);
    TimerOn();

    /* Insert your solution below */
    while (1) {
	
	while(!TimerFlag){}
	    TimerFlag = 0;

	if(PINA == 0x01) {
            num = num + 1;
	    LCD_WriteData(num + '0');
	}
	else if(PINA == 0x02) {
	    num = num - 1;
	    LCD_WriteData(num + '0');
	}
	else if(PINA == 0xFE || PINA == 0xFD){
	    num = 0;
	    LCD_WriteData(0 + '0');
	}	
    }
    return 1;
}
