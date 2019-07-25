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
  
#include "interupt.h"
#include "stdio.h"
#include "dma.h"
#include "delay.h"


/*****************  global variable ȫ�ֱ���  ***************************************************/
char code[5];
u8 jj = 0;



/**
  * @brief  �жϺ�����
  * @param  None
  * @retval None
  */
void ReadData(void)
{

    /*���ָ����TIM�жϷ������*/
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
    {
        /*���TIMx���жϴ�����λ*/
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 

        // ������䵥��ѭ����DMA���ݴ�С
        DMA_Cmd(DMA1_Channel4,DISABLE);
        DMA_InitStructure.DMA_BufferSize = BufferSize*2;
        DMA_Init(DMA1_Channel4, &DMA_InitStructure);
        DMA_Cmd(DMA1_Channel4,ENABLE);

        //��������1��DMA����
        USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
        Delay(0x0ffff);
    }
}
