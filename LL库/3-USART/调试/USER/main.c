/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 *��Ȩ���У�����ؾ���
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
	
	/*����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
	LED_GPIO_Config();

	USART_init();
	
	printf("\r\n this is a printf Interrupt demo \r\n");
	printf("\r\n ��ӭʹ�ÿ�����STM32 ������ \r\n");
	printf("\r\n***************����ʵ��--�����ж�ʵ��**************** \r\n");
	printf("\r\n����:�ڳ����ն�����һϵ���ַ���ע�⣬����Ҫ�س���β\r\n");
	printf("\r\n     ��Ƭ�����յ�����֮��ֱ�Ӱ�ԭ����ӡ���� \r\n");
	printf("\r\n�뿪ʼ�����ַ���: \r\n");
	
	USART_Receive_IT(&husart1, usart1_Rxmsg, 1);
	USART_Receive_IT(&husart2, usart2_Rxmsg, 3);
	USART_Receive_IT(&husart3, usart3_Rxmsg, 4);
	
	while(1)
	{
		//��ȡ����Ĵ��������ݣ�Ȼ���࣬����д�����š�ʵ�ֵ��ݵĲ�ͣ��˸
	  GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))));
		Delay(4000000);
		
  }
}
