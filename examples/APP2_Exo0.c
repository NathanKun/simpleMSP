/**
 * EXERCICE0 Seance 2
 * Il s’agit d’un programme très simple qui recopie simplement l’état
 * des quatre interrupteurs présents sur votre carte d’extension
 * sur les quatre leds rouges situées sur la même carte.
 * La prise en compte des modifications de l’état des interrupteurs doit être instantanée.
 *
 * HE Junyang
 *
 * 用拓展版，四个开关分别控制四个led。
 */

#include <msp430.h> 
#include "simpleMSP.h"

/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    /*
    // tous les pins travaillent en mode normal
    P1SEL=0x00;
    P2SEL=0x00;
    P1SEL2=0x00;
    P2SEL2=0x00;

    // initialiser tous les pins a 0
    P2IN &= 0x00;
    P2OUT &= 0x00;
    */

    initPorts(); // 初始化全部针
    selectPin(P26, 0); // P2.6和P2.7（板子上名字为XIN和XOUT）设为普通输入输出模式，否则这两针默认为特殊的模式
    selectPin(P27, 0);

    /*
    // Pins de 0 a 3 de P2 travaillent comme une entree
    P2DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);
    // Pins de 4 a 7 de P2 travaillent comme une sortie
    P2DIR |= (BIT4 + BIT5 + BIT6 + BIT7);
     */
    directionPin(P20, INPUT); // 将P2.0到P2.3方向设置为输入
    directionPin(P21, INPUT);
    directionPin(P22, INPUT);
    directionPin(P23, INPUT);
    directionPin(P24, OUTPUT); // 将P2.4到P2.7方向设置为输出
    directionPin(P25, OUTPUT);
    directionPin(P26, OUTPUT);
    directionPin(P27, OUTPUT);

    /*
    // avtiver le pull-up pour les pins de 0 a 3 donc 0x0F
    P2REN |= 0x0F;
    // donner une tension a les pins de 0 a 3
    P2OUT |= 0x0F;
     */

    digitalWrite(P20, HIGH); // P2.0到P2.3输出高电平
    digitalWrite(P21, HIGH);
    digitalWrite(P22, HIGH);
    digitalWrite(P23, HIGH);
    pullupPin(P20, ENABLE); // P2.0到P2.3上拉电阻开启
    pullupPin(P21, ENABLE);
    pullupPin(P22, ENABLE);
    pullupPin(P23, ENABLE);
	 // 开关本身并不产生信号，需要有电压和电阻才能产生高或低的信号。
	 
    while(1) {

    	// led et interupteur 1
    	if(digitalRead(P20) == HIGH) // 读取P2.0的输入，若为高电平（开关1）
    		digitalWrite(P24, HIGH); // 将P2.4输出设为高电平（led1）
    	else
    		digitalWrite(P24, LOW); // 将P2.4输出设为低电平（led1）

    	// led et interupteur 2
    	if(digitalRead(P21) == 1) // HIGH == 1
    		digitalWrite(P25, HIGH);
    	else
    		digitalWrite(P25, LOW);

    	// led et interupteur 3
    	if(digitalRead(P22)) // 1 == true, in C
    		digitalWrite(P27, HIGH);
    	else
    		digitalWrite(P27, LOW);

    	// led et interupteur 4
    	if(digitalRead(P23))
    		digitalWrite(P26, HIGH);
    	else
    		digitalWrite(P26, LOW);

    	/*
    	// led et interupteur 1
    	if((P2IN | ~(BIT0)) == ~(BIT0))
    		P2OUT |= BIT4;
    	else
        	P2OUT &= ~(BIT4);

    	// led et interupteur 2
    	if((P2IN | ~(BIT1)) == ~(BIT1))
    		P2OUT |= BIT5;
    	else
    		P2OUT &= ~(BIT5);

    	// led et interupteur 3
    	if((P2IN | ~(BIT2)) == ~(BIT2))
    		P2OUT |= BIT7;
    	else
    		P2OUT &= ~(BIT7);

    	// led et interupteur 4
    	if((P2IN | ~(BIT3)) == ~(BIT3))
    		P2OUT |= BIT6;
    	else
    		P2OUT &= ~(BIT6);
    	*/
    }
}
