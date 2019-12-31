#ifndef __INTERUPT_H
#define	__INTERUPT_H

#include "stm32f10x.h"

/*****************  global variable 全局变量声明 ***************************************************/

extern __IO uint16_t ADC_ConvertedValue;
extern __IO u16 Send_Buffer[BufferSize];
extern __IO float ADC_ConvertedValueLocal; 
extern DMA_InitTypeDef DMA_InitStructure;


/*****************  function declaration 中断函数声明********************************************/

void ReadData(void);
void ReceData(void);

#endif /* __INTERUPT_H */
