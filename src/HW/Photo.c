/*
 * Photo.c
 *
 *  Created on: 2022. 11. 6.
 *      Author: kccistc
 */
#include "Photo.h"

void interrupt_init()
{
   XGpio_Initialize(&GPIO_Interrupt,XPAR_AXI_GPIO_1_DEVICE_ID);
   XGpio_SetDataDirection(&GPIO_Interrupt, CHANNEL_1, 0xff);
}

void interrupt_MakeInst(interruptInst *INTERRUPT,int interruptNum)
{
	INTERRUPT -> interruptNum = interruptNum;
}




int interrupt_GetState(interruptInst *INTERRUPT)
{
   return (XGpio_DiscreteRead(&GPIO_Interrupt, CHANNEL_1) & (1 << INTERRUPT -> interruptNum));
}
