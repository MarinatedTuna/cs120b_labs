/*	Author: jvega008
 *  Partner(s) Name: Joseph Tibog, Jenaro Vega
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
   
    void set_PWM(double frequency){
        static double current_frequency;
	if(frequency != current_frequency){
	    if(!frequency){ TCCR3B &= 0x08; }
	    else { TCCR3B |= 0x03; }
	    if(frequency < 0.954) { OCR3A = 0xFFFF; }
	    else if(frequency > 31250) { OCR3A = 0x0000; }
	    else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
	    TCNT3 = 0;
	    current_frequency = frequency;
        }
    }
    void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
    }
    void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
    }
    DDRB = 0x40; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    PWM_on();
    while (1) {
        if(~PINA == 0x01){
	    set_PWM(261.63);
	}
	else if(~PINA == 0x02){
	    set_PWM(293.66);
	}
	else if(~PINA == 0x04){
	    set_PWM(329.63);
	}
	else{
	    PWM_off();
	}
    }
    return 1;
}
