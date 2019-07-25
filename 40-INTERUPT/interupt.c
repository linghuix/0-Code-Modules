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
  
#include "interupt.h"
#include "stdio.h"
#include "dma.h"
#include "delay.h"


/*****************  global variable 全局变量  ***************************************************/
char code[5];
u8 jj = 0;



/**
  * @brief  中断函数。
  * @param  None
  * @retval None
  */
void ReadData(void)
{

    /*检查指定的TIM中断发生与否*/
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
    {
        /*清除TIMx的中断待处理位*/
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 

        // 重新填充单次循环的DMA数据大小
        DMA_Cmd(DMA1_Channel4,DISABLE);
        DMA_InitStructure.DMA_BufferSize = BufferSize*2;
        DMA_Init(DMA1_Channel4, &DMA_InitStructure);
        DMA_Cmd(DMA1_Channel4,ENABLE);

        //启动串口1的DMA请求
        USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
        Delay(0x0ffff);
    }
}
