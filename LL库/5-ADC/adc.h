#ifndef __ADC_H
#define __ADC_H	
#include "stm32f10x.h"
 

/*****************  functions declaration ��������********************************************/
/*
#define ADC_CH0  0 //ͨ��0
#define ADC_CH1  1 //ͨ��1
#define ADC_CH2  2 //ͨ��2
#define ADC_CH3  3 //ͨ��3	   
*/

void ADC3_GPIO_Config(void); 
void ADC2_GPIO_Config(void); 
void ADC1_GPIO_Config(void); 
void ADC_Config(ADC_TypeDef * ADC,uint8_t ADC_Channel);
 
#endif 
