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



#include "delay.h"
volatile u32 TimingDelay;

/**
  * @brief  ������ʱ�����ʱ�ӳ�ʼ��
  * @param  None
  * @retval None
  */
void SysTick_Init(){
    
    #if defined US_DELAY    
    SysTick_us_Init();
    
    #elif defined MS_DELAY  
    SysTick_ms_Init();
    
    #endif
}


/**
  * @brief  ����ȷ���ӳ�
  * @param  32λ�޷�������
  * @retval None
  */
void Delay(__IO u32 nCount)  //
{
    for(; nCount != 0; nCount--);
} 


/**
  * @brief: ��ȷ�����ӳ�
  * @param:  32λ�޷�������
  * @retval: None
  * @attention: ���ж��ڲ�ʹ��ʱ����Ҫע����ж����ȼ�����ɵĳ����������
  */
void Delay_ms(__IO u32 nTime)
{ 
  TimingDelay = nTime;
  
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                     //ʹ����શ�ʱ��
  
  while(TimingDelay != 0);                                      //�ȴ��жϣ���ʱ��
}


/**
  * @brief ��ȷ΢���ӳ�
  * @param  32λ�޷�������
  * @retval None
  */
void Delay_us(__IO u32 nTime)
{ 
  TimingDelay = nTime;

  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

  while(TimingDelay != 0);
}


/**
  * @brief ʱ�ӳ�ʼ��
  * @param  32λ�޷�������
  * @retval None
  * @attention
  *     SystemCoreClock / 1000      1ms�ж�һ��
  *     SystemCoreClock / 100000    10us�ж�һ��
  *     SystemCoreClock / 1000000   1us�ж�һ��
  *     f = 72000000HZ
  *     time = (72000000/1000) * 1/72000000 = 1ms
  */
void SysTick_ms_Init(void){

while(SysTick_Config( SystemCoreClock/1000));                               //Systick ������ʱn*ms  

SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                                  //SysTick_Config����ʱ�Ѿ��򿪡�ʹ�ö�ʱ��ǰ�ȹر�

}


void SysTick_us_Init(void){ 

while(SysTick_Config( SystemCoreClock/1000000));

SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


/**
  * @brief Systick�жϷ�����
  * @param  None
  * @retval None
  */
void TimingDelay_decrement(void){
    
    if (TimingDelay != 0x00){  TimingDelay--; }
}