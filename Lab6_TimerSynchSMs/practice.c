/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #nah
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

// Internal variables

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
    // AVR timer/counter controller register TCCR1
    TCCR1B = 0x0B; // see notes

    // AVR output compare register OCR1A
    OCR1A = 125;

    // Initialize avr counter
    TCNT1 = 0;

    _avr_timer_cntcurr = _avr_timer_M;
    // TimerISR will be called every _avr_timer_cntcurr milliseconds

    // Enable global interrupts
    SREG |= 0x80;
}

void TimerOff() {
    TCCR1B = 0x00;
}

void TimerISR() {
    TimerFlag = 1;
}

// We dont touch this man
ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
} 

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00; //outputs

    TimerSet(1000);
    TimerOn();
    unsigned char tmpB = 0x00;
    while(1) {
        // synchSM calls
        tmpB = ~tmpB;
        PORTB = tmpB;
        while (!TimerFlag); // Wait 1 sec
        TimerFlag = 0;
    }
    return 1;
}
