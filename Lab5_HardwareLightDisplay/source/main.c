/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {

    DDRA = 0x00; PORTA = 0xFF; //inputs 
    DDRB = 0xFF; PORTB = 0x00; //outputs

    unsigned char led = 0x00;
    unsigned char button = 0x00;
    
    while (1) {
	// if PA0 is 1
	// PB1PB0 = 01
	// else
	// PB1PB0 = 10
        // 1.) Read inputs
        button = ~PINA & 0x01; // button is connected to A0
        // 2.) Perform computation
        if (button) { // True if button is pressed
		led = (led & 0xFC) | 0x01;
	}
	else {
		led = (led & 0xFC) | 0x02;
	}
	// 3.) Write output
	PORTB = led;
    }
    return 1;
}
