/*	Partner 1 Name & E-mail: Justin Gafford jgaff001@ucr.edu
 *	Partner 2 Name & E-mail: Rick Lee rlee037@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #4 Exercise #2
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum states {start, init, check, increm, decrem, wait, wait2, reset} state;
	
#define pin1 (PINA & 0x01)
#define pin2 (PINA & 0x02)

void increm_decrem() {
	switch(state) {
		case start:
			state = init;
			break;
		case init:
			state = check;
			break;
		case check:
			if (!pin1 && !pin2) {
				state = check;
			}
			else if (!pin1 && pin2) {
				state = decrem;
			}
			else if (pin1 && !pin2) {
				state = increm;
			}
			else if (pin1 && pin2) {
				state = reset;
			}
			break;
		case increm:
			state = wait;
			break;
		case decrem:
			state = wait2;
			break;
		case wait:
			if (pin1 && pin2) {
				state = reset;
			}
			else if (!pin1) {
				state = check;
			}
			else if (pin1) {
				state = wait;
			}
			break;
		case wait2:
			if (pin1 && pin2) {
				state = reset;
			}
			else if (!pin2) {
				state = check;
			}
			else if (pin2) {
				state = wait2;
			}
			break;
		case reset:
			state = check;
			break;
		default:
			state = start;
			break;
	}
	switch(state) {
		case init:
			PORTC = 0x07;
			break;
		case check:
			break;
		case increm:
			if (PORTC < 9) {
				PORTC = PORTC + 1;
			}
			break;
		case decrem:
			if (PORTC > 0) {
				PORTC = PORTC - 1; 
			}
			break;
		case wait:
			break;
		case wait2:
			break;
		case reset:
			PORTC = 0x00;
			break;
		default:
			break;
	}
}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF; //inputs
	DDRC = 0xFF; PORTC = 0x00; //outputs
	PORTC = 0x00;
	
	state = start;
	
	while(1) {
		increm_decrem();	
	}
}
