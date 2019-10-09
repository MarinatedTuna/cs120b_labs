/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #3
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
    DDRA = 0x00; PORTA = 0xFF;  
    DDRC = 0xFF; PORTC = 0x00;

    while(1) {

	if(PINA == 0x00) {
	   PORTA = PINA; 
	   PORTC = PC3; //Actually 4 but we have to set it to PC3 which is 3
	}
	if(PINA == 0x01 || PINA == 0x02 || PINA == 0x04 || PINA == 0x08) {
	   PORTA = PINA;
	   PORTC = PC2;
	}
	else if(PINA == 0x03 || PINA == 0x06 || PINA == 0x0C || PINA == 0x0A || PINA == 0x05 || PINA == 0x09) {
	   PORTA = PINA;
	   PORTC = PC1;
	}
	else if(PINA == 0x07 || PINA == 0x0E || PINA == 0x0D || PINA == 0x0B) {
	   PORTA = PINA;
	   PORTC = PC0;
	}
	else if(PINA == 0x0F) {
	   PORTA = PINA;
	   PORTC = PC7 & 0x01;
	}
    } 
    return 0; 
}  
