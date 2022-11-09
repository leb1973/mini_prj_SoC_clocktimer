/*
 * Photo.h
 *
 *  Created on: 2022. 11. 6.
 *      Author: kccistc
 */

#ifndef SRC_HW_PHOTO_H_
#define SRC_HW_PHOTO_H_

#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

#define CHANNEL_1 1

#define OUTPUT 0x00
#define INPUT  0xff
#define ON      1
#define OFF      0

#define INTERRUPT_0   0
#define INTERRUPT_1   1
#define INTERRUPT_2   2

XGpio GPIO_Interrupt;

typedef struct _interruptInst {
   int interruptNum;
}interruptInst;

void interrupt_MakeInst(interruptInst *INTERRUPT,int interruptNum);
void interrupt_init();
int interrupt_GetState(interruptInst *INTERRUPT);


#endif /* SRC_HW_PHOTO_H_ */
