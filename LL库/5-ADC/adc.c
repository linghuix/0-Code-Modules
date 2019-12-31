/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "adc.h"


/**
  * @brief  ADCͨ����ģʽ���á�ʵ�ֵ���ѭ��ADC����
  * @param  ADC1-3��ADCͨ��ADC_Channel_x
  * @retval ��
  *  @attention
  *     1.��Ҫ��ǰ���ú����ŵĹ���
  *     2.������Ҫȡ������ʱ�Ӵ���ע��
  */
void  ADC_Config(ADC_TypeDef * ADC,uint8_t ADC_Channel)
{
	ADC_InitTypeDef ADC_InitStructure; 

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);                   
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);

    /*72M/6=12,ADC���ʱ�䲻�ܳ���14M*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  

    /*������ ADC1 ��ȫ���Ĵ�������ΪĬ��ֵ*/
    ADC_DeInit(ADC); 

    //����ģʽΪ����ģʽ
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	

    /*ģ��ת�������ڵ�ͨ��ģʽ*/
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	

    /*ģ��ת������������ת��ģʽ*/
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

    //���ⲿ����,�ڲ��������
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	

    //�������ת������
    /*����û�в����ⲿ���������������������(��ʲôʱ�򴥷���ʲôʱ�򴥷�)*/
    //ADC_SoftwareStartConvCmd(ADC, ENABLE);		

    /*ADC�����Ҷ���*/
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

    /*˳����й���ת����ADCͨ������Ŀ*/
    ADC_InitStructure.ADC_NbrOfChannel = 1;

    /*����ADC_InitStruct��ָ���Ĳ�����ʼ������ADC�ļĴ���*/   
    ADC_Init(ADC, &ADC_InitStructure);

    /*ʹ��ָ����ADC*/
    ADC_Cmd(ADC, ENABLE);

    /* ʹ��ָ����ADC DMAͨ�� */
    //ADC_DMACmd(ADC, ENABLE);	 �����������ʹ��

    /*����ָ����ADC��У׼�Ĵ���*/
    ADC_ResetCalibration(ADC);

    /*�ȴ��������*/
    while(ADC_GetResetCalibrationStatus(ADC));

    /*��ʼָ��ADC��У׼*/
    ADC_StartCalibration(ADC);
    /*�ȴ�У׼���*/
    while(ADC_GetCalibrationStatus(ADC));

    /*ADCͨ��0,�������˳��ֵΪ1,����ʱ��Ϊ239.5����*/
    ADC_RegularChannelConfig(ADC, ADC_Channel, 1, ADC_SampleTime_239Cycles5 );	

    /* ʹ��ָ����ADC DMAͨ�� */
    //ADC_DMACmd(ADC, ENABLE);	
}