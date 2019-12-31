
#include "func_can.h" 
/*
 * 函数名：CAN_SetMsg
 * 描述  ：CAN通信报文内容设置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */  
/*
void CAN_SetMsg(uint32_t StdId, uint8_t IDE, uint32_t *p)
{     
  int i;
    
    TxMessage.StdId = StdId;                         
  //TxMessage.ExtId=0x1314;                                                                     //使用的扩展ID
    
  TxMessage.IDE = (IDE==0)? CAN_ID_STD:CAN_ID_EXT;                  //扩展模式
  TxMessage.RTR=CAN_RTR_DATA;                                                                   //发送的是数据
  TxMessage.DLC=8;                                                                                      //数据长度为2字节
  
    for(i = 0;i<TxMessage.DLC;i++){
        TxMessage.Data[i]=p[i];
    }
}*/

//TxMessage.Data[0]为低地址
void CAN_SetMsg(uint32_t ID, uint32_t low, uint32_t high){
    
    
    uint32_t tmp;
    uint8_t mail;
    int i;
    
    //low = 0x0EFEFABCD;
    //high = 0x0ABCDEFAD;
    
    TxMessage.StdId = ID;                        
    
	TxMessage.IDE = CAN_ID_STD;               //扩展模式
	TxMessage.RTR = CAN_RTR_DATA;             //发送的是数据
	TxMessage.DLC = 8;                        //数据长度为8字节

    tmp = low;                              //0-cs，1,2-Index  ,3-Sub
    for(i=0;i<4;i++){
        TxMessage.Data[i] = low;
        low = low>>8;
    }
    
    tmp = high;
    
    for(i=4;i<8;i++){
        TxMessage.Data[i] = tmp;
        tmp = tmp>>8;
    }
    mail = CAN_Transmit(CAN1, &TxMessage);
    
    i= 50;
    while(CAN_TransmitStatus(CAN1, mail) != CANTXOK && --i>0){};    //发送不成功的话，等待
    
    //CAN_Transmit(CAN1, &TxMessage);
}
