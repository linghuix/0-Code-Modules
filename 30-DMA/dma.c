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

#include "dma.h"


/* 定义 DMA 初始化结构体 DMA_InitStructure */
DMA_InitTypeDef DMA_InitStructure;


/**
  * @brief  DMA1配置通道4函数，单次循环，用于串口的数据的间断发送。从内存中将数据搬运到外设串口1
  * @param  无
  * @retval 无
  */
void DMA1_Config(void)	{

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                                  /* 开启 DMA1  时钟 */
  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;                   //* DMA1的源——外设地址 

    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&Send_Buffer;                           //* 数据内存地址

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                                  //*从内存搬运到外设地址
    
	//@attention 传输数据大小为16位，但是这里设置为8位，所以注意需要大小需要乘以二
    DMA_InitStructure.DMA_BufferSize = (BufferSize*2);

    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                    //* 外设地址寄存器不变;

    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                             //内存地址寄存器递增;
    
    /*@attention
    *虽然Send_Buffer[i] = 0x07DEF是16位的，但串口只能发送8位二进制，这里写16位的话会抛弃前8位，
    *所以这里填8位，串口可以收到7D和EF两个数据.注意在右对齐的情况下，发送的顺序是EF，然后是7D
    */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;                 //内存数据宽度为8位;

    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                                 //设置DMA1通道优先级

    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                        //DMA1 通道不设置为内存到内存传输;  

	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                                       //单循环模式，再次启动需要重新配置

    DMA_Init(DMA1_Channel4, &DMA_InitStructure);                                        //写入配置数据，进行初始化.串口1对应的通道是4

	DMA_Cmd(DMA1_Channel4,DISABLE);                                                     //DMA_Cmd(DMA1_Channel4,ENABLE);主程序控制

    //DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);                                   /* 开启DMA传输完成中断 */

}

/**
  * @brief  DMA2配置通道5，循环转换用于ADC的数据从外设搬运到内存。
  * @param  无
  * @retval 无
  */
void DMA2_Config(void)
{
		/* 开启 DMA2  时钟 */
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

	//写入配置数据，进行初始化.ADC 对应DMA2通道为5
    DMA_Init(DMA2_Channel5, &DMA_InitStructure);

	DMA_Cmd(DMA2_Channel5,ENABLE);
	
    /* 开启DMA2传输完成中断 */
    //DMA_ITConfig(DMA2_Channel5, DMA_IT_TC, ENABLE);

}
