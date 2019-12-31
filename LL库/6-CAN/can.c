/*******************************************************************************
 * 文件名  ：can.c
 * 描述    ：将printf函数重定向到USART1。这样就可以用printf函数将单片机的数据
 *           打印到PC上的超级终端或串口调试助手。         
 * 实验平台：野火STM32开发板
 * 硬件连接：------------------------
 *          |       PB8-CAN-RX       |
 *          |       PB9-CAN-TX       |
 *           ------------------------
 * 库版本  ：ST3.5.0
 * 作者    ：保留
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/

#include "can.h" 

extern   CanTxMsg TxMessage;

/*
 * 描述  ：CAN的GPIO 重映射配置,PB8上拉输入，PB9推挽输出
 * 调用  ：内部调用
 */
static void CAN1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*外设时钟设置*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);              // 重映射IO功能为can

    /* Configure CAN pin: RX */                                 // PB8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Configure CAN pin: TX */                                 // PB9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
}

/*
 * 描述  ：CAN的模式，波特率，中断，过滤器配置
 * 调用  ：内部调用
 */
void CAN1_Configuration(void)
{
    NVIC_InitTypeDef      NVIC_InitStructure;
    CAN_InitTypeDef       CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    
    /* 引脚设定 */
    CAN1_GPIO_Config();
    
    /* 使能时钟 */
    RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

    /* NVIC配置 */
    /*
     * 发送报文中断
     * 接收FIFO报文中断，USB_LP_CAN1_RX0_IRQn
     * 错误中断
     */
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //抢占优先级 1 越小优先级越大
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //子优先级为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* 配置CAN参数 */
    CAN_InitStructure.CAN_TTCM = DISABLE;//MCR-TTCM  关闭时间触发通信模式使能
    CAN_InitStructure.CAN_ABOM = DISABLE;//MCR-ABOM  自动离线管理 
    CAN_InitStructure.CAN_AWUM = DISABLE;//MCR-AWUM  使用自动唤醒模式
    CAN_InitStructure.CAN_NART = DISABLE;//MCR-NART  禁止报文自动重传      DISABLE-自动重传
    CAN_InitStructure.CAN_RFLM = DISABLE;//MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
    CAN_InitStructure.CAN_TXFP = DISABLE;//MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符 
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//正常工作模式

    /* 配置CAN波特率 = 1MBps(36MHz/6/(1+3+2)) */
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;//BTR-SJW 重新同步跳跃宽度 1个时间单元
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;//BTR-TS1 时间段1 占用了3个时间单元
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;//BTR-TS1 时间段2 占用了2个时间单元
    CAN_InitStructure.CAN_Prescaler = 6;    //BTR-BRP 波特率分频器  
    CAN_Init(CAN1, &CAN_InitStructure);

    /* CAN过滤配置 */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    /* 使能中断 */
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}


/*
 * 描述  ：完整配置CAN的功能
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void CAN_init(void)
{
  CAN1_Configuration();
}
