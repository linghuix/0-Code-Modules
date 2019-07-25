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

#include "dma.h"


/* ���� DMA ��ʼ���ṹ�� DMA_InitStructure */
DMA_InitTypeDef DMA_InitStructure;


/**
  * @brief  DMA1����ͨ��4����������ѭ�������ڴ��ڵ����ݵļ�Ϸ��͡����ڴ��н����ݰ��˵����贮��1
  * @param  ��
  * @retval ��
  */
void DMA1_Config(void)	{

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                                  /* ���� DMA1  ʱ�� */
  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;                   //* DMA1��Դ���������ַ 

    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&Send_Buffer;                           //* �����ڴ��ַ

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                                  //*���ڴ���˵������ַ
    
	//@attention �������ݴ�СΪ16λ��������������Ϊ8λ������ע����Ҫ��С��Ҫ���Զ�
    DMA_InitStructure.DMA_BufferSize = (BufferSize*2);

    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                    //* �����ַ�Ĵ�������;

    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                             //�ڴ��ַ�Ĵ�������;
    
    /*@attention
    *��ȻSend_Buffer[i] = 0x07DEF��16λ�ģ�������ֻ�ܷ���8λ�����ƣ�����д16λ�Ļ�������ǰ8λ��
    *����������8λ�����ڿ����յ�7D��EF��������.ע�����Ҷ��������£����͵�˳����EF��Ȼ����7D
    */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;                 //�ڴ����ݿ��Ϊ8λ;

    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                                 //����DMA1ͨ�����ȼ�

    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                        //DMA1 ͨ��������Ϊ�ڴ浽�ڴ洫��;  

	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                                       //��ѭ��ģʽ���ٴ�������Ҫ��������

    DMA_Init(DMA1_Channel4, &DMA_InitStructure);                                        //д���������ݣ����г�ʼ��.����1��Ӧ��ͨ����4

	DMA_Cmd(DMA1_Channel4,DISABLE);                                                     //DMA_Cmd(DMA1_Channel4,ENABLE);���������

    //DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);                                   /* ����DMA��������ж� */

}

/**
  * @brief  DMA2����ͨ��5��ѭ��ת������ADC�����ݴ�������˵��ڴ档
  * @param  ��
  * @retval ��
  */
void DMA2_Config(void)
{
		/* ���� DMA2  ʱ�� */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC3->DR;
	
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;
	
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

    DMA_InitStructure.DMA_BufferSize = 1;
    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;
    
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

	//д���������ݣ����г�ʼ��.ADC ��ӦDMA2ͨ��Ϊ5
    DMA_Init(DMA2_Channel5, &DMA_InitStructure);

	DMA_Cmd(DMA2_Channel5,ENABLE);
	
    /* ����DMA2��������ж� */
    //DMA_ITConfig(DMA2_Channel5, DMA_IT_TC, ENABLE);

}
