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

    unsigned char led_output = 0x00;
    unsigned char door_sensor = 0x00;
    unsigned char light_sensor = 0x00;

    while(1) {
    // Read input
        door_sensor = PINA & 0x01;
        light_sensor = (PINA & 0x02) >> 1;
        if((light_sensor != 0x01) & (door_sensor != 0x01)) {
            led_output = 0x00;
        }
        else if((light_sensor != 0x01) & (door_sensor == 0x01)) {
	    led_output = 0x80;
        }
        else if((light_sensor == 0x01) & (door_sensor != 0x01)) {
	    led_output = 0x00;
	}
	else if((light_sensor == 0x01) & (door_sensor == 0x01)) {
	    led_output = 0x00;
	}
        else {
	    led_output = 0x00;
	}
	// Write output
	PORTB = led_output;
	PORTB = PORTB >> 7;
    }
    return 0;
}  
