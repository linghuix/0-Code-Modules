/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  * 1. 本程序主要存放引脚的配置，针对GPIO以及其他复用功能TIME，ADC，USART，CAN...
  * 2. “事件控制”，“重映射”，“调试IO配置”，“外部中断”，时需要开启AFIO
  *
  ******************************************************************************
  */
#include "gpio.h"

void GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStructure;


/** @addtogroup GPIOA 配置
  * @{
  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);                //添加PA口时钟线

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;     //配置PA0-2号引脚，模式推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

    GPIO_Init(GPIOA,&GPIO_InitStructure);                               //初始化，写入


    /*********串口GPIO端口配置***********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                           /* 配置串口1 （USART1 Tx (PA.09)）*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                          /* 配置串口1 USART1 Rx (PA.10)*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*********串口GPIO端口配置END*********/
    
    
    /*********将PA3设置为ADC模拟输入*********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*********将PA3设置为ADC模拟输入 END*********/

/**
  * @}
  */



/** @addtogroup GPIOB 配置
  * @{
  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                //“事件控制”“重映射”“调试IO配置”“外部中断”时需要开启AFIO

    /* @attention
     * 启用PB3和PB4为普通引脚，PB3和PB4默认为JTAG模式
     *  改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）*/
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);           // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能

    GPIO_Init(GPIOB,&GPIO_InitStructure);                               //初始化，写入
    
    
 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;     //添加PB口时钟线,配置PB0-2号引脚，模式推挽输出       
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(GPIOB,&GPIO_InitStructure); 

/**
  * @}
  */

}

