
/*	Partner 1 Name & E-mail: Justin Gafford jgaff001@ucr.edu
 *	Partner 2 Name & E-mail: Rick Lee rlee037@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #4 Exercise #1
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
enum states {Init, pb0_on,buttonpress_pb1,pb1_on,buttonpress_pb0} state;
	
#define buttonPressed (PINA & 0x01)

void statetransistion () {
	switch(state) {
	case Init:
		state = pb0_on;
		break;
	case pb0_on:
		if (buttonPressed) {
			state = buttonpress_pb1;
		}
		else {
			state = pb0_on;
		}
		break;
	case buttonpress_pb1:
		if (buttonPressed) {
			state = buttonpress_pb1;
		}
		else {
			state = pb1_on;
		}
		break;
	case pb1_on:
		if(buttonPressed) {
			state = buttonpress_pb0;
		}
		else {
			state = pb1_on;
		}
		break;
	case buttonpress_pb0:
		if(buttonPressed) {
			state = buttonpress_pb0;
		}
		else {
			state = pb0_on;
		}
		break;
	default:
		state = Init;
		break;
	}
	switch(state) {
		case pb0_on:
			PORTB = 0x01;
			break;
		case buttonpress_pb1:
			PORTB = 0x02;
			break;
		case pb1_on:
			PORTB = 0x02;
			break;
		case buttonpress_pb0:
			PORTB = 0x01;
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
	state = Init;
	while (1)
	{
		statetransistion();
	}
}

