/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #1
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
    DDRA = 0x00; PORTA = 0x0FF;  
    DDRB = 0xFF; PORTB = 0x00;
    PORTC = 0x0F;

    unsigned char cntavail = 0x00;

    while(1) {
        if(cntavail & 0x0F) {
	    PORTC = cntavail;
        }
    }
}  
