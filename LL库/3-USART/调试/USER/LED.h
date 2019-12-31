/******************** 尚学科技 **************************
 * 实验平台：开拓者STM32开发板
 * 库版本  ：ST3.5.0
 * 作者    ：尚学科技团队 
 * 淘宝    ：http://shop102218275.taobao.com/
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *版权所有，盗版必究。
**********************************************************************************/

#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define LED1_OFF GPIO_SetBits(GPIOA,GPIO_Pin_8);    //PA8输出高电平
#define LED1_ON GPIO_ResetBits(GPIOA,GPIO_Pin_8);   //PA8输出低电平
#define LED2_OFF GPIO_SetBits(GPIOD,GPIO_Pin_2);    //PD2输出高电平
#define LED2_ON GPIO_ResetBits(GPIOD,GPIO_Pin_2);   //PD2输出低电平
#define LED3_OFF GPIO_SetBits(GPIOC,GPIO_Pin_12);   //PC12输出高电平
#define LED3_ON GPIO_ResetBits(GPIOC,GPIO_Pin_12);  //PC12输出低电平

void LED_GPIO_Config(void);   /* LED 端口初始化 */

#endif /* __LED_H */
