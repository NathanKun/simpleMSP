/**
 * exercice 4 : lire la valeur du capteur de luminosité 
 * et afficher Jour/nuit sur l’afficheur en fonction d’un seuil prédéfini dans le programme.
 *
 * HE Junyang
 *
 * 检测亮度，自己设定一个阀值，大于阀值显示JOUR，小于阀值显示NUIT
 */
#include <msp430.h> 
/*#include "ADC.h"*/
#include "Afficheur.h"
#include "simpleMSP.h" // 引入库

#define N_ADC_MIN 282 // obtenu par experiment，亮度最低时的数字信号的大小
#define N_ADC_MAX 1010 // obtenu par experiment，亮度最高时
#define SEUIL 50

/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    /*
	// quand INCH = 0001(binaire) = 1(dec), on selectionne A1
	unsigned char voie = 1;*/
	
	// la sortie de ADC
	unsigned int N_ADC; // 转换成的数字信号存到这

	// pourcentage de la luminosite
	uint8_t percentage = 0; // 亮度百分比

	// double A1input = 0;

	// positionner p1.1 a 0 comme un input
	/*P1DIR &= ~(0x02);*/
	directionPin(P11, INPUT); // 将P1.1设为输入方向

	/*
    // initialiser ADC10 et l'afficheur
    ADC_init();*/
    Aff_Init(); // 初始化显示器


    while (1){
    	/*
        	ADC_Demarrer_conversion(voie);
        	N_ADC = ADC_Lire_resultat();
        */

    	N_ADC = analogRead(A1); // 读取A1的模拟型号，转换成数字信号，并存到N_ADC变量中
		 // A1即是P1.1针脚，拓展版的光敏电阻接到P1.1和P1.3上，详情参照拓展版电路图。

        // A1input = N_ADC * vcc / 1023;
        percentage = ((unsigned long)N_ADC - N_ADC_MIN) * 100 / (N_ADC_MAX - N_ADC_MIN); // 计算当前亮度百分比

        if(percentage > SEUIL) Aff_4carac("Jour"); // 亮度大于阀值显示JOUR，否则显示NUIT
        else Aff_4carac("Nuit");

        // attendre 0.2s
    	__delay_cycles(200000);
    }


}
