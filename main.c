#include <msp430.h> 
#include "simpleMSP.h"
#include "Afficheur.h"
/*
 * main.c
 */
void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	initPorts();
	Aff_Init();

	/*
	interruptPin(P10, ENABLE);
	interruptPin(P13, ENABLE);
	interruptPin(P15, ENABLE, FALLING_EDGE);
	interruptPin(P15, ENABLE, RISING_EDGE);
	interruptPin(P17, ENABLE, RISING_EDGE);
	interruptPin(P17, ENABLE, FALLING_EDGE);
	interruptPin(P23, ENABLE);
	interruptPin(P27, ENABLE);*/

	/*
	selectPin(P10, 0);
	selectPin(P11, 1);
	selectPin(P12, 2);
	selectPin(P13, 3);
	selectPin(P14, 0);
	selectPin(P15, 1);
	selectPin(P16, 2);
	selectPin(P17, 3);
	selectPin(P20, 0);
	selectPin(P21, 1);
	selectPin(P22, 2);
	selectPin(P23, 3);
	selectPin(P24, 0);
	selectPin(P25, 1);
	selectPin(P26, 2);
	selectPin(P27, 3);*/



	/*
	enableS2();
	directionPin(P10, OUTPUT);
	*/
	int time = 0;
	while (1) {
		/*
		if (digitalRead(P13) == HIGH) {
			digitalWrite(P10, LOW);
			digitalWrite(P16, HIGH);
		} else {
			digitalWrite(P10, HIGH);
			digitalWrite(P16, LOW);
		}*/
		Aff_valeur(time);
		time++;
		__delay_cycles(1000000);
	}
}
