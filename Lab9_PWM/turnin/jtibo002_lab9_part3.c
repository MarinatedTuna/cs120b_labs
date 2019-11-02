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

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;


void TimerOn(){
	TCCR1B = 0x0B;


	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;

	SREG = 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned long arr[] = {261.63,261.63,440.00,261.63,261.63,493.88,530.00,530.00,261.63,293.66};
unsigned char i = 0;
unsigned char j = 0;
enum States{off, on, play} state;
    void tick(){
	switch(state){
	     case off: 
		if(~PINA == 0x01){
		    while(~PINA == 0x01){}
		    state = on;
		    break;
	        }
		else{
		    state = off;
		    break;
		}
	    case on:
		state = play;
		break;
	    case play:
		break;
	    default:
		state = off;
		break;
        }
	switch(state){
	    case off:
		PWM_off();
		break;
	    case on:
	    	PWM_on();
		i = 0;
		set_PWM(arr[i]);
		state = play;
		i++;
		break;
	    case play:
		set_PWM(arr[i]);
		if(i == 9){
		    state = off;
		    break;
		}
		i++;
		state = play;
		break;
	}
    } 

int main(void) {
		
    DDRB = 0x40; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    TimerSet(50);
    TimerOn();
    while (1) {
        tick();
	while(!TimerFlag){}
	TimerFlag = 0;
    }
    return 1;
}
