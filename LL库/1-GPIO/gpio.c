/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  * 1. ��������Ҫ������ŵ����ã����GPIO�Լ��������ù���TIME��ADC��USART��CAN...
  * 2. ���¼����ơ�������ӳ�䡱��������IO���á������ⲿ�жϡ���ʱ��Ҫ����AFIO
  *
  ******************************************************************************
  */
#include "gpio.h"

void GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStructure;


/** @addtogroup GPIOA ����
  * @{
  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);                //���PA��ʱ����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;     //����PA0-2�����ţ�ģʽ�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

    GPIO_Init(GPIOA,&GPIO_InitStructure);                               //��ʼ����д��


    /*********����GPIO�˿�����***********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                           /* ���ô���1 ��USART1 Tx (PA.09)��*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                          /* ���ô���1 USART1 Rx (PA.10)*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*********����GPIO�˿�����END*********/
    
    
    /*********��PA3����ΪADCģ������*********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*********��PA3����ΪADCģ������ END*********/

/**
  * @}
  */



/** @addtogroup GPIOB ����
  * @{
  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                //���¼����ơ�����ӳ�䡱������IO���á����ⲿ�жϡ�ʱ��Ҫ����AFIO

    /* @attention
     * ����PB3��PB4Ϊ��ͨ���ţ�PB3��PB4Ĭ��ΪJTAGģʽ
     *  �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_Disable SWJ ��ȫ���ã�JTAG+SW-DP��*/
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);           // �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_JTAGDisable ��JTAG-DP ���� + SW-DP ʹ��

    GPIO_Init(GPIOB,&GPIO_InitStructure);                               //��ʼ����д��
    
    
 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;     //���PB��ʱ����,����PB0-2�����ţ�ģʽ�������       
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(GPIOB,&GPIO_InitStructure); 

/**
  * @}
  */

}

