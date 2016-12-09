/**
 * Programme qui fasse clignoter la led rouge à une fréquence de 4Hz ou de 2Hz, 
 * à chaque fois que l’on appuie sur le bouton poussoir la fréquence doit changer.
 *
 * HE Junyang
 *
 * 闪红灯，2Hz或4Hz，按S2来改变频率
 */

#include <msp430.h>
#include "simpleMSP.h" // 引入库

/*
 * main.c
 */

unsigned int cycles = 1; // 周期

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    initPorts(); // 初始化全部针
    /*
    P1OUT = 0x00;
     */
    directionPin(P10, OUTPUT); // 将P10设置为输出方向
    /*
    P1DIR |= BIT0;
    P1DIR &= ~(BIT3);
    P1REN |= BIT3;
    P1OUT |= BIT3;
	 */
    enableS2(); // 将S2无脑启用

    /*P1IE |= BIT3;
    P1IES |= BIT3;*/
    interruptPin(P13, ENABLE, FALLING_EDGE); // 将P13即按钮S2中断开启，检测下降沿
    /*P1IFG &= ~(BIT3);*/
    clearFlag(P13); // 清除P13触发旗帜

    __enable_interrupt(); // 全局启用中断

    while (1) {
    	/*P1OUT ^= BIT0;*/
    	reverseOutput(P10); // 反向P10输出电平，0变1或1变0
    	if ( cycles == 1) { // 周期设为1时每0.125秒执行一次（4Hz），否则0.25秒执行一次（2Hz）
        	__delay_cycles(125000);
    	} else {
        	__delay_cycles(250000);
    	}
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) { // 按钮S2中断函数
	if (cycles == 1) {
		cycles = 2;
	} else {
		cycles = 1;
	}
	/*P1IFG &= ~(BIT3);*/
    clearFlag(P13);
}
