/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #1
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
    /* Insert DDR and PORT initializations */

    //inputs
    DDRA = 0x00; PORTA = 0xFF;

    //outputs
    DDRC = 0xFF; PORTC = 0x00;

  //  unsigned char store = 0;

    /* Insert your solution below */
    while (1) {
	if(PINA == 1 || PINA == 2){
	    //PA0 or PA1 is 1
	    //PC5 = 1;
	    PINC = PC5;
	    PORTC = PINC;
	}
	if(PINA == 3 || PINA == 4) {
//	    store = PC5 | PC4; //experiment bitwise or
	    PINC = (PC5 + PC4);
	    PORTC = PINC;
	}
	if(PINA == 5 || PINA == 6) {
//	    store = PC5 | PC4 | PC3;
//	    previously 0x00 | (PC5 | PC4 | PC3);
	    PINC = (PC5 + PC4 + PC3);
	    PORTC = PINC;	
	}
	if(PINA == 7 || PINA == 8 || PINA == 9) {
	    PINC = (PC5 + PC4 + PC3 + PC2);
	    PORTC = PINC;
	}
	if(PINA == 10 || PINA == 11 || PINA == 12) {
	    PINC = (PC5 + PC4 + PC3 + PC2 + PC1);
	    PORTC = PINC;
	}
	if(PINA == 13 || PINA == 14 || PINA == 15) {
	    PINC = (PC5 + PC4 + PC3 + PC2 + PC1 + PC0);
	    PORTC = PINC;
	}
    }
    return 1;
}
