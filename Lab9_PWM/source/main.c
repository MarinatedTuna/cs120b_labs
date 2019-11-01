/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #9  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM(double frequency) {
    static double current_frequency;
    
    if (frequency != current_frequency) {
        
        if (!frequency) {
            TCRR3B &= 0x08;
        }
        else {
            TCRR3B |= 0x03;
        }

        if (freqency < 0.954) {
            OCR3A = 0xFFFF;
        }
        else if (frequency > 31250) {
            OCR3A = 0x0000;
        }
        else {
            OCR3A = (short) (8000000 / (128 * frequency)) - 1;
        }

        TCNT3 = 0;
        current_frequency = frequency;
    }
} 

int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {

    }
    return 1;
}
