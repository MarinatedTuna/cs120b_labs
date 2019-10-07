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
    DDRA = 0x00; PORTA = 0x0F;  
    DDRB = 0xFF; PORTB = 0x00;
    PORTC = 0x00;
    //unsigned char cntavail = 4;

    while(1) {
        if(PORTA == 0x00) {
	   // cntavail = 4;
	   PORTC = 4;  
        }
else	if (PORTA == 0x01 || PORTA == 0x02 || PORTA == 0x04 || PORTA == 0x08) {
	  //  cntavail = 3;
	  PORTC = 3;
	}
else	if (PORTA == 0x03 || PORTA == 0x06 || PORTA == 0x0C || PORTA == 0x0A || PORTA == 0x05 || PORTA == 0x09) {
	PORTC = 2; 
	//   cntavail = 2;
	}
else	if (PORTA == 0x07 || PORTA == 0x0E || PORTA == 0x0D || PORTA == 0x0B) {
	 PORTC = 1;
	 //cntavail = 1;
	}
else 	if (PORTA == 0x0F) {
	PORTC = 0;	 
//   cntavail = 0;
	}
	// If full
	//if(PORTA == 0x0F) {
	//    PORTC = 0x80;
	//}
	//PORTC = 4;
    } 
    return 0; 
}  
