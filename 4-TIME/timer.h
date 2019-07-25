#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"


/************ 进入中断标志位****************************/
extern __IO uint32_t flag;


/*****************  function declaration *******************************************/

void TIME_NVIC_Configuration(void);

void TIME3_Configuration(void);
void TIME2_Configuration(void);
void TIM_interrupt(void);

#endif/* __TIMER_H */

