/*
 * switch.c
 *
 *  Created on: 2022. 11. 5.
 *      Author: kccistc
 */
#include "switch.h"

void switch_init()
{
   XGpio_Initialize(&GPIO_Switch,XPAR_AXI_GPIO_0_DEVICE_ID);
   XGpio_SetDataDirection(&GPIO_Switch, CHANNEL_1, 0xff);
}

void switch_MakeInst(switchInst *SWITCH, int switchNum)
{
   SWITCH -> switchNum = switchNum;
}

int switch_GetState(switchInst *SWITCH)
{
   return (XGpio_DiscreteRead(&GPIO_Switch, CHANNEL_1) & (1 << SWITCH -> switchNum));
}
