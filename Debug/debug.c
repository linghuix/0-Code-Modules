
#include <debug.c>


/**
  * @brief  重定向c库函数printf到USART1,由printf调用
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f){
    
    USART_SendData(USART1, (unsigned char) ch);                     /* 将Printf内容发往串口 */
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
    return (ch);
}


/**
  * @brief  ：重定向c库函数scanf到USART1, 由scanf调用
  * @param  None
  * @retval None
  */
int fgetc(FILE *f){
    
    while( USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);     //等待串口输入数据
    return (int) USART_ReceiveData(USART1);
}

