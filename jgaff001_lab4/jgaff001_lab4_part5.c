/*	Partner 1 Name & E-mail: Justin Gafford jgaff001@ucr.edu
 *	Partner 2 Name & E-mail: Rick Lee rlee037@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #4 Exercise #5
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum states {start, init, pass,wait,wait2} state;
	
#define X (PINA & 0x01)
#define Y (PINA & 0x02)
#define hashtag (PINA & 0x04)
#define lock (PINA & 0x80)

unsigned char correct[] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01};
unsigned char temp = 0;



void oof() {
	while(1) {
		if(PINA == correct[temp]) {
			temp++;
			break;
		}
		else if (temp != 0 && PINA == correct[temp -1]) {
			break;
		}
		else {
			temp = 0;
		}
		break;
	}
}

void keypad () {
	switch(state) {
		case start:
			state = init;
			break;
		case init:
			state = pass;
			break;
		case pass:
			if(temp ==7) {
				state = wait;
				temp = 0;
			}
			else {
				oof();
			}
			break;
		case wait:
			state = wait2;
			break;
		case wait2:
			if (!hashtag && !X && !Y && lock) {
				state = init;
			}
			else if (hashtag && !X && !Y && !lock) {
				state = pass;
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
			break;
		case pass:
			break;
		case wait:
			if (PORTB == 0) {
				PORTB = 1;
			}
			else {
				PORTB = 0;
			}
			break;
		case wait2:
			break;
		default:
			break;
	}
}
int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //inputs
	DDRB = 0xFF; PORTB = 0x00; //outputs
	
	PORTB = 0x00;
	state = start;
    while (1) 
    {
		keypad();
    }
}

