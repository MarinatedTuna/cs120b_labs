/*	Author: jvega008
 *  Partner(s) Name: Joseph Tibog, Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "io.h"
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;


void TimerOn(){
	TCCR1B = 0x0B;


	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;
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


enum States {init,wait, press_sub, press_add, reset} state;
unsigned char tmp = 0x00;
void sm_tick(){
	switch(state) {
		case init:
			state = wait;
			break;
		case wait:
			if((~PINA & 0x03) == 0x03) {
				state = reset;
			}
			else if ((~PINA & 0x01) == 0x01) {
				state = press_add;
			}
			else if ((~PINA & 0x02) == 0x02) {
				state = press_sub;
			}
			break;
		case press_add:
			state = wait;
			break;
		case press_sub:
			state = wait;
			break;
		case reset: 
			state = wait;
			break;
		default:
			state = init;
			break;
		}
		switch(state) {
			case init: 
				break;
			case wait:
				break;
			case press_add:
				if(tmp < 9) {
					tmp++;
				}
				break;
			case press_sub:
			    if(tmp > 0) {
					tmp--;
				}
				break;
			case reset:
				tmp = 0x00;
				break;
			default:
				break;
         }
}


int main(void) {
    
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    TimerSet(25);
    TimerOn();



    state = init;
    tmp = 0x00;
    LCD_init();
    
    while (1) {
		sm_tick();
		LCD_Cursor(1);
		LCD_WriteData(tmp + '0');	
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
