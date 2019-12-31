#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>


/*****************  function declaration �ṹ������********************************************/

struct struct_Message{
    uint8_t *message;   //��������ָ��
    uint16_t num;       //���ݰ���С
    uint16_t index;     //�����±꣬��ʼ��ʱΪ 0
};

typedef struct struct_Message USART_Message;

//���ڹ���ṹ��
struct struct_USART_handle{
    USART_TypeDef *USART;   //���ڼĴ����ṹ�壬���ڱ�־���ĸ����ڷ��͵�
    uint8_t RxTx;           //����1���ǽ���0
    uint8_t Rxuse;          //��λ�޷������ݣ�1��ʾ����ʹ�ã�0��ʾδʹ��
    uint8_t Txuse;          //��λ�޷������ݣ�1��ʾ����ʹ�ã�0��ʾδʹ��
    USART_Message RxMsg;     //�ֳ�������ԭ���ǣ�����ʱ����ӽ�����Ϣ�ͻḲ�Ƿ�����Ϣ
    USART_Message TxMsg;     //����ָ��
    
};


typedef struct struct_USART_handle USART_handle;


extern USART_handle husart1;
extern USART_handle husart2;
extern USART_handle husart3;
extern USART_handle husart4;

extern uint8_t usart1_Rxmsg[5];
extern uint8_t usart2_Rxmsg[5];
extern uint8_t usart3_Rxmsg[5];
extern uint8_t usart4_Rxmsg[5];

/*****************  function declaration ��������********************************************/

void USART_init(void);



/**
  * @attention
  *     ʹ�����º�������Ҫ����MICRO-LIB��
  */
int fputc(int ch, FILE *f);
int fgetc(FILE *f);


#endif /* __USART1_H */
