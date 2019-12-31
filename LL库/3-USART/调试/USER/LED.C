
#include "LED.h"

/*
 * @brief：LED_GPIO_Config —— 配置LED用到的PA8,PD2,PC12口, and set it.
 * @param	无
 * @retval	无
 */
void LED_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	 GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOC的外设时钟*/	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_13); 	

}

