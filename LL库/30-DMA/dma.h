#ifndef __dma_H
#define	__dma_H

#include "stm32f10x.h"

/*****************  macro宏 ***************************************************/

#define BufferSize  52                                                          //定义一行存储的传感器数据

/*****************  function declaration 函数声明********************************************/
void DMA1_Config(void); 
void DMA2_Config(void); 

#endif /* __DMA_H */
