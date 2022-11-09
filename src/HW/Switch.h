/*
 * switch.h
 *
 *  Created on: 2022. 11. 5.
 *      Author: kccistc
 */

#ifndef SRC_HW_SWITCH_H_
#define SRC_HW_SWITCH_H_

#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

#define CHANNEL_1 1

#define OUTPUT 0x00
#define INPUT  0xff
#define ON      1
#define OFF      0

#define SWITCH_0   0
#define SWITCH_1   1
#define SWITCH_2   2
#define SWITCH_3   3
#define SWITCH_4   4  // Setting mode <-> Clock mode


XGpio GPIO_Switch;

typedef struct _switchInst {
   int switchNum;
}switchInst;

void switch_MakeInst(switchInst *SWITCH,int switchNum);
void switch_init();
int switch_GetState(switchInst *SWITCH);
#endif /* SRC_HW_SWITCH_H_ */
