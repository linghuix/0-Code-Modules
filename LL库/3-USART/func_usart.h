#ifndef __func_USART_H
#define	__func_USART_H

#include "usart.h"


/*****************  function declaration �ṹ������********************************************/




/*****************  function declaration ��������********************************************/

void USART_Receive_IT(USART_handle *husart, uint8_t *data, uint8_t size);
void USART_IT(USART_handle *husart);
void USART_Rx_callback(USART_handle *husart);
/**
  * @attention
  *     ʹ�����º�������Ҫ����MICRO-LIB��
  */
int fputc(int ch, FILE *f);
int fgetc(FILE *f);


#endif /* __USART1_H */

