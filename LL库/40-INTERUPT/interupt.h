#ifndef __INTERUPT_H
#define	__INTERUPT_H

#include "stm32f10x.h"

/*****************  global variable ȫ�ֱ������� ***************************************************/

extern __IO uint16_t ADC_ConvertedValue;
extern __IO u16 Send_Buffer[BufferSize];
extern __IO float ADC_ConvertedValueLocal; 
extern DMA_InitTypeDef DMA_InitStructure;


/*****************  function declaration �жϺ�������********************************************/

void ReadData(void);
void ReceData(void);

#endif /* __INTERUPT_H */
