#ifndef __func_CAN_H
#define __func_CAN_H

#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "epos.h"


//void CAN_SetMsg(uint32_t StdId, uint32_t low_4byte, uint32_t high_4byte);
void CAN_SetMsg(uint32_t ID, uint32_t low, uint32_t high);

#endif
