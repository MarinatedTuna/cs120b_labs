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
    PORTC = 0x00;

    unsigned char cntavail = 0x00;
    unsigned char ports = PINA & 0x0F;
    unsigned char one = 0x01;

    while(1) {
        if((ports & 0x01) && 0x01) {
	    cntavail = cntavail + one;  
        }
        if((ports & 0x02) && 0x02) {
            cntavail = cntavail + one;
        }
        if((ports & 0x04) && 0x04) {
            cntavail = cntavail + one;
        }
        if((ports & 0x08) && 0x08) {
            cntavail = cntavail + one;
        }

        // Actually counted what wasn't open so we need to flip it to show number of spaces open
        if(cntavail == 0x04) {
	    cntavail = 0x00;
        }
        else if(cntavail == 0x03) {
	    cntavail = 0x01;
        }
        else if(cntavail == 0x02) {
	    cntavail = 0x02;
	}
        else if(cntavail == 0x01) {
	    cntavail = 0x03;
        }
	else if(cntavail == 0x00) {
	    cntavail = 0x04;
	}
	else {
	    cntavail = 0x04;
	}
	
	PORTC = cntavail;
    } 
    return 0; 
}  
