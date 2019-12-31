/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "func_usart.h"
#include <stdarg.h>


/**
  * @brief  �ض���c�⺯��printf��USART1,��printf����
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f){
    
    USART_SendData(USART1, (unsigned char) ch);                     /* ��Printf���ݷ������� */
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
    return (ch);
}


/**
  * @brief  ���ض���c�⺯��scanf��USART1, ��scanf����
  * @param  None
  * @retval None
  */
int fgetc(FILE *f){

    while( USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);     //�ȴ�������������
    return (int) USART_ReceiveData(USART1);
}


/**
  * @brief  ���жϷ��ͺ���
  * @param  husart  ���ڷ������ݽṹ��
  * @retval None    
  */
void USART_Tran_IT(USART_handle *husart){
    
    if(husart->Txuse && husart->TxMsg.num == 0){return;}
    
    husart->Txuse = 1;          //���ձ�־
    
    //���������ж�
    USART_ITConfig(husart->USART, USART_IT_RXNE, ENABLE);
    
    //װ��� 1 ������
    husart->USART->DR = husart->TxMsg.message[0];
    
    return;
}


/**
  * @brief  ���жϷ��͵Ļص��������������жϺ����е���
  * @param  None
  * @retval None
  */
void USART_Tran_IT_callback(USART_handle *husart){
    
    return;
}

/**
  * @brief  ���жϽ��պ���������һ�����������ݣ����ս�������ûص������������ݴ���
  * @param  husart  ���ڽ������ݽṹ��
  * @retval None    
  */
void USART_Receive_IT(USART_handle *husart, uint8_t *data, uint8_t size){
    
    if(husart->Rxuse && size == 0){return;}
    
    husart->Rxuse = 1;          //���ձ�־
    husart->RxMsg.index = 0;      //�±���㿪ʼ
		husart->RxMsg.num = size;
		husart->RxMsg.message = data;
    
    //���������ж�
    USART_ITConfig(husart->USART, USART_IT_RXNE, ENABLE);
    
    return;
}


/**
  * @brief  ���жϽ��յķ��������������жϺ����е��á�
  * @param  None
  * @retval None
  */
void USART_IT(USART_handle *husart){
    
    if(husart->USART == USART1){ 				//��������
			
        if(husart->Rxuse && husart->RxMsg.index+1 <= husart->RxMsg.num ){
            //װ��� index+1 ������
            husart->RxMsg.message[husart->RxMsg.index] = husart->USART->DR;
            husart->RxMsg.index++;
            
            //�������
            if(husart->RxMsg.index == husart->RxMsg.num){
                //�ر��ж�
                USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
                husart->Rxuse = 0;
                USART_Rx_callback(husart);
            }
        }
        else if(husart->Txuse && husart->TxMsg.index+1 <= husart->TxMsg.num ){        //��������
            //��������
            printf("%s,%d",__FILE__,__LINE__);
        }
    }
		else if(husart->USART == USART2){			//��������
			
        if(husart->Rxuse && husart->RxMsg.index+1 <= husart->RxMsg.num ){
            //װ��� index+1 ������
            husart->RxMsg.message[husart->RxMsg.index] = husart->USART->DR;
            husart->RxMsg.index++;
            
            //�������
            if(husart->RxMsg.index == husart->RxMsg.num){
                //�ر��ж�
                USART_ITConfig(husart->USART, USART_IT_RXNE, DISABLE);
                husart->Rxuse = 0;
                USART_Rx_callback(husart);
            }
        }
        else if(husart->Txuse && husart->TxMsg.index+1 <= husart->TxMsg.num ){        //��������
            //��������
            printf("%s,%d",__FILE__,__LINE__);
        }
    }
		else if(husart->USART == USART3){			//��������
			
        if(husart->Rxuse && husart->RxMsg.index+1 <= husart->RxMsg.num ){
            //װ��� index+1 ������
            husart->RxMsg.message[husart->RxMsg.index] = husart->USART->DR;
            husart->RxMsg.index++;
            
            //�������
            if(husart->RxMsg.index == husart->RxMsg.num){
                //�ر��ж�
                USART_ITConfig(husart->USART, USART_IT_RXNE, DISABLE);
                husart->Rxuse = 0;
                USART_Rx_callback(husart);
            }
        }
        else if(husart->Txuse && husart->TxMsg.index+1 <= husart->TxMsg.num ){        //��������
            //��������
            printf("%s,%d",__FILE__,__LINE__);
        }
    }
		
}


//���ս���
uint8_t data[4];
void USART_Rx_callback(USART_handle *husart){
	
    uint8_t i;
	
	if(husart->USART == USART1){
		
		for(i=0;i<1;i++){
			data[i]=usart1_Rxmsg[i];
			printf("%c\r\n",data[i]);
		}
	
		USART_Receive_IT(&husart1, usart1_Rxmsg, 1);
	}
	else if(husart->USART == USART2){
		
		for(i=0;i<3;i++){
			data[i]=usart2_Rxmsg[i];
			printf("%X\r\n",data[i]);
		}

		USART_Receive_IT(&husart2, usart2_Rxmsg, 3);
	}
	else if(husart->USART == USART3){
		
		for(i=0;i<4;i++){
			data[i]=usart3_Rxmsg[i];
			printf("%d\r\n",data[i]);
		}

		USART_Receive_IT(&husart3, usart3_Rxmsg, 4);
	}
	
}
