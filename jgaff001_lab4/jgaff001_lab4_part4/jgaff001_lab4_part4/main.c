/*	Partner 1 Name & E-mail: Justin Gafford jgaff001@ucr.edu
 *	Partner 2 Name & E-mail: Rick Lee rlee037@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #4 Exercise #4
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum states {start, init, button, wait, button2, wait2} state;

#define X (PINA & 0x01)
#define Y (PINA & 0x02)
#define hashtag (PINA & 0x04)
#define lock (PINA & 0x80)

void keypad() {
	switch(state) {
		case start:
			state = init;
			break;
		case init:
			if (hashtag && !X && !Y && !lock) {
				state = button;
			}
			else {
				state = init;
			}
			break;
		case button:
			if (hashtag && !X && !Y && !lock) {
				state = button;
			}
			else if (!hashtag && !X && !Y && !lock) {
				state = wait;
			}
			else {
				state = init;
			}
			break;
		case wait:
			if (!hashtag && !X && Y && !lock) {
				state = button2;
			}
			else if (!hashtag && !X && !Y && !lock) {
				state = wait;
			}
			else {
				state = init;
			}
			break;
		case button2:
			state = wait2;
			break;
		case wait2:
			if (!hashtag && !X && !Y && lock) {
				state = init;
			}
			else if (hashtag && !X && !Y && !lock) {
				state = button;
			}
			else {
				state = wait2;
			}
			break;
		default:
			state = start;
			break;
	}
	switch(state) {
		
		case init:
			PORTB = 0x00;
			PORTC = init;
			break;
		case button:
			PORTC = button;
			break;
		case wait:
			PORTC = wait;
			break;
		case button2:
			if (PORTB == 0x00) {
				PORTB = 0x01;
			}
			else {
				PORTB = 0x00;
			}
			PORTC = button2;
			break;
		case wait2:
			PORTC = wait2;
			break;
		default:
			break;
	}
}
int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; //inputs
	DDRB = 0xFF; PORTB = 0x00; //outputs
	DDRC = 0xFF; PORTC = 0x00; //outputs
	PORTB = 0x00;
	
	state = start;
    while (1) 
    {
		keypad();
    }
}



