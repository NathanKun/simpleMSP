/**
 * Exercice 2 : On souhaite réaliser un chronomètre digital affichant les 1/10 de seconde. 
 * Nous supposons le DCO (SMCLK) réglé à 1MHz.
 * a) Déterminer la meilleure configuration du prédiviseur, 
 * mode de comptage et TACCR0 afin d’obtenir une période de timer de 100ms.
 * b) Ecrire en C une fonction de configuration du timer.
 * c) Ecrire l’application afin de réaliser l’application chronomètre en y intégrant une fonction void 
 * afficheTime(char min, char sec, char sec10) permettant d’afficher le chronomètre sur l’afficheur. 
 * Comme il n’y a que 4 digits sur l’afficheur, nous nous limiterons à l’affichage suivant : M.SS.D
 * 
 * Remarque : un chronomètre dispose d’un bouton de déclenchement et d’arrêt. 
 * Il y a souvent un bouton de remise à zéro. Comme sur la Launchpad, 
 * il n’y a que le bouton S2 d’accessible, le premier appui déclenchera la mise à zéro 
 * et le démarrage simultané du chronomètre et le second appui figera le chronomètre sur la valeur mesurée.
 *
 * HE Junyang
 *
 * 做一个计时器，显示为；分.秒秒.十分之一秒，按钮S2按一下停止，再按清除并重新开始计时。
 */

#include <msp430.h> 
#include "Afficheur.h"
#include "simpleMSP.h" // 引入库

volatile char min, sec, sec10; // 用于显示的三个时间变量
volatile uint8_t is_stop = 1; // 是否停止，1停，0走

/**
 * 显示时间
 */
void afficheTime (char min, char sec, char sec10) {
	Aff_valeur(convert_Hex_Dec(min*1000 + sec*10 + sec10)); // 分钟第四位，乘1000，秒第二位，乘10
}

/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    initPorts(); // 初始化全部针
	
    // configuration des I/O
    /*P1DIR &= ~BIT3;
    P1OUT |= BIT3;
    P1REN |= BIT3;
    P1IE |= BIT3;
    P1IES |= BIT3;*/

    enableS2(); // 启用按钮S2
    interruptPin(P13, ENABLE, FALLING_EDGE); // 启用P13（按钮S2）的中断，检测下降沿

    // configuration de timer
    /*BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;*/
    timer_init(); // 初始化计时器
    /*
    TA0CTL = MC_1 | TASSEL_2 | ID_1; // up mode, SMCLK, diviser par 2
    TA0CCR0 = 50000; //100ms
    TA0CTL |= TAIE; // activer interrution de timer
     */

    Aff_Init(); // 初始化显示器


    __enable_interrupt(); // 全局开启中断

    directionPin(P10, OUTPUT); // 将P10设为输出模式
    is_stop = 1;
	while(1){ // 停止时亮灯，计时时关灯
		if(is_stop == 1) 
			digitalWrite(P10, HIGH); // 将P10输出设为高电平
		else
			digitalWrite(P10, LOW); // 将P10输出设为低电平
	}
	
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) { // 按钮S2中断时执行的函数
	if(is_stop == 0) {
		is_stop = 1;
		timer_delete(TIMER0); // 删除计时器
	} else if(is_stop == 1){
		is_stop = 0;
		sec10 = sec = min = 0; // 重置变量
		Aff_Efface();
	    Aff_Points(BIT0 | BIT2); // afficher points
	    timer_create(TIMER0, 100000, UP_MODE); // 创建计时器，ccr为100000微秒，Up模式，即100毫秒触发一次
	}
	clearFlag(P13); // 降下P13的触发旗帜
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void my_timer() { // 计时器中断函数
	if(is_stop == 0){
		sec10++; // +0.1s
		if(sec10 == 10) {
			sec10 = 0;
			sec++;
			Aff_Efface(); // avoid some possible display errors.
			Aff_Points(BIT0 | BIT2); // afficher points
		}
		if(sec == 60){
			sec = 0;
			min++;
		}
		if(min == 10){
			min = 0;
		}
		afficheTime (min, sec, sec10); // 显示时间
	}

	clearFlag(TIMER0); // 降下TIMER0的触发旗帜
}
