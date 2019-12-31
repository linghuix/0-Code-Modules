/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "adc.h"


/**
  * @brief  ADC通道和模式配置。实现单个循环ADC采样
  * @param  ADC1-3，ADC通道ADC_Channel_x
  * @retval 无
  *  @attention
  *     1.需要提前配置好引脚的功能
  *     2.根据需要取消开启时钟代码注释
  */
void  ADC_Config(ADC_TypeDef * ADC,uint8_t ADC_Channel)
{
	ADC_InitTypeDef ADC_InitStructure; 

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);                   
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);

    /*72M/6=12,ADC最大时间不能超过14M*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  

    /*将外设 ADC1 的全部寄存器重设为默认值*/
    ADC_DeInit(ADC); 

    //工作模式为独立模式
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	

    /*模数转换工作在单通道模式*/
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	

    /*模数转换工作在连续转换模式*/
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

    //非外部触发,内部软件触发
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	

    //软件启动转换功能
    /*由于没有采用外部触发，软件启动触发功能(想什么时候触发就什么时候触发)*/
    //ADC_SoftwareStartConvCmd(ADC, ENABLE);		

    /*ADC数据右对齐*/
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

    /*顺序进行规则转换的ADC通道的数目*/
    ADC_InitStructure.ADC_NbrOfChannel = 1;

    /*根据ADC_InitStruct中指定的参数初始化外设ADC的寄存器*/   
    ADC_Init(ADC, &ADC_InitStructure);

    /*使能指定的ADC*/
    ADC_Cmd(ADC, ENABLE);

    /* 使能指定的ADC DMA通道 */
    //ADC_DMACmd(ADC, ENABLE);	 在主程序进行使能

    /*重置指定的ADC的校准寄存器*/
    ADC_ResetCalibration(ADC);

    /*等待重置完成*/
    while(ADC_GetResetCalibrationStatus(ADC));

    /*开始指定ADC的校准*/
    ADC_StartCalibration(ADC);
    /*等待校准完成*/
    while(ADC_GetCalibrationStatus(ADC));

    /*ADC通道0,规则采样顺序值为1,采样时间为239.5周期*/
    ADC_RegularChannelConfig(ADC, ADC_Channel, 1, ADC_SampleTime_239Cycles5 );	

    /* 使能指定的ADC DMA通道 */
    //ADC_DMACmd(ADC, ENABLE);	
}