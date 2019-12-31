/*******************************************************************************
 * �ļ���  ��can.c
 * ����    ����printf�����ض���USART1�������Ϳ�����printf��������Ƭ��������
 *           ��ӡ��PC�ϵĳ����ն˻򴮿ڵ������֡�         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�------------------------
 *          |       PB8-CAN-RX       |
 *          |       PB9-CAN-TX       |
 *           ------------------------
 * ��汾  ��ST3.5.0
 * ����    ������
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/

#include "can.h" 

extern   CanTxMsg TxMessage;

/*
 * ����  ��CAN��GPIO ��ӳ������,PB8�������룬PB9�������
 * ����  ���ڲ�����
 */
static void CAN1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*����ʱ������*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);              // ��ӳ��IO����Ϊcan

    /* Configure CAN pin: RX */                                 // PB8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               // ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Configure CAN pin: TX */                                 // PB9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
}

/*
 * ����  ��CAN��ģʽ�������ʣ��жϣ�����������
 * ����  ���ڲ�����
 */
void CAN1_Configuration(void)
{
    NVIC_InitTypeDef      NVIC_InitStructure;
    CAN_InitTypeDef       CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    
    /* �����趨 */
    CAN1_GPIO_Config();
    
    /* ʹ��ʱ�� */
    RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

    /* NVIC���� */
    /*
     * ���ͱ����ж�
     * ����FIFO�����жϣ�USB_LP_CAN1_RX0_IRQn
     * �����ж�
     */
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //��ռ���ȼ� 1 ԽС���ȼ�Խ��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //�����ȼ�Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* ����CAN���� */
    CAN_InitStructure.CAN_TTCM = DISABLE;//MCR-TTCM  �ر�ʱ�䴥��ͨ��ģʽʹ��
    CAN_InitStructure.CAN_ABOM = DISABLE;//MCR-ABOM  �Զ����߹��� 
    CAN_InitStructure.CAN_AWUM = DISABLE;//MCR-AWUM  ʹ���Զ�����ģʽ
    CAN_InitStructure.CAN_NART = DISABLE;//MCR-NART  ��ֹ�����Զ��ش�      DISABLE-�Զ��ش�
    CAN_InitStructure.CAN_RFLM = DISABLE;//MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
    CAN_InitStructure.CAN_TXFP = DISABLE;//MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ�� 
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//��������ģʽ

    /* ����CAN������ = 1MBps(36MHz/6/(1+3+2)) */
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;//BTR-SJW ����ͬ����Ծ��� 1��ʱ�䵥Ԫ
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;//BTR-TS1 ʱ���1 ռ����3��ʱ�䵥Ԫ
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;//BTR-TS1 ʱ���2 ռ����2��ʱ�䵥Ԫ
    CAN_InitStructure.CAN_Prescaler = 6;    //BTR-BRP �����ʷ�Ƶ��  
    CAN_Init(CAN1, &CAN_InitStructure);

    /* CAN�������� */
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

    /* ʹ���ж� */
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}


/*
 * ����  ����������CAN�Ĺ���
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void CAN_init(void)
{
  CAN1_Configuration();
}
