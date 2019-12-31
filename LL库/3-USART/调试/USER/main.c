/******************** 尚学科技 **************************
 * 实验平台：开拓者STM32开发板
 * 库版本  ：ST3.5.0
 * 作者    ：尚学科技团队 
 * 淘宝    ：http://shop102218275.taobao.com/
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *版权所有，盗版必究。
**********************************************************************************/
#include "stm32f10x.h"
#include "func_usart.h"
#include "LED.h"
#include "delay.h"
#include "stdio.h"


/**
  * @brief  main
  * @param  none
  * @retval ?none
  */
int main(void)
{	
	
	/*设置NVIC中断分组2:2位抢占优先级，2位响应优先级*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
	LED_GPIO_Config();

	USART_init();
	
	printf("\r\n this is a printf Interrupt demo \r\n");
	printf("\r\n 欢迎使用开拓者STM32 开发板 \r\n");
	printf("\r\n***************串口实验--接受中断实验**************** \r\n");
	printf("\r\n描述:在超级终端敲入一系列字符，注意，必须要回车结尾\r\n");
	printf("\r\n     单片机接收到数据之后直接按原样打印出来 \r\n");
	printf("\r\n请开始输入字符串: \r\n");
	
	USART_Receive_IT(&husart1, usart1_Rxmsg, 1);
	USART_Receive_IT(&husart2, usart2_Rxmsg, 3);
	USART_Receive_IT(&husart3, usart3_Rxmsg, 4);
	
	while(1)
	{
		//读取输出寄存器的数据，然后反相，重新写进引脚。实现灯泡的不停闪烁
	  GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))));
		Delay(4000000);
		
  }
}
