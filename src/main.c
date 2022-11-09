#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"
#include "xgpio.h"
#include "hw/switch.h"
#include "hw/Photo.h"

#define BUZZER_DEV_BASE_ADDR   		 	 0x44A00000
#define BUZZER_DATA_REG        		 	 *(uint32_t *) BUZZER_DEV_BASE_ADDR

#define FND_DEV_BASE_ADDR     		 	 0x44A10000

#define MOTOR_DEV_BASE_ADDR     		 0x44A20000
#define MOTOR_ENABLE_DATA_REG    	 	 *(uint32_t *) (MOTOR_DEV_BASE_ADDR+0)
#define MOTOR_DIR_MODE_DATA_REG   	 	 *(uint32_t *) (MOTOR_DEV_BASE_ADDR+4)
#define MOTOR_MS1_DATA_REG        	  	 *(uint32_t *) (MOTOR_DEV_BASE_ADDR+8)
#define MOTOR_TIME_INTERRUPT_DATA_REG 	 *(uint32_t *) (MOTOR_DEV_BASE_ADDR+12)




#define C4 262   //도
#define D4 294   //레
#define E4 330   //미
#define F4 349   //파
#define G4 392   //솔
#define A4 440   //라
#define B4 494   //시
#define C5 523   //도

int ar[] = {C4, D4, E4, F4, G4, A4, B4, C5, C5, B4, A4, G4, F4, E4, D4, C4};


int main()
{
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");

    switch_init();


    switchInst enableSW;
    switchInst directionSW;
    switchInst ms1SW;
    switchInst photoSW;
    switchInst setting_clock_SW;

    switch_MakeInst(&enableSW, SWITCH_0);
    switch_MakeInst(&directionSW, SWITCH_1);
    switch_MakeInst(&ms1SW, SWITCH_2);
    switch_MakeInst(&photoSW, SWITCH_3);
    switch_MakeInst(&setting_clock_SW, SWITCH_4);

	interrupt_init();

    interruptInst sec_INT;
    interruptInst min_INT;
    interruptInst hour_INT;

    interrupt_MakeInst(&sec_INT,  INTERRUPT_0);
    interrupt_MakeInst(&min_INT,  INTERRUPT_1);
    interrupt_MakeInst(&hour_INT, INTERRUPT_2);

    while (1)
    {

//
//       for (int i=0; i<=sizeof(ar); i++)
//       {
//          BUZZER_DATA_REG = ar[i];
//          sleep(1);
//       }

       printf("%d\n", interrupt_GetState(&sec_INT));
       printf("REG : %ld\n", MOTOR_ENABLE_DATA_REG);


    if(switch_GetState(&enableSW)) MOTOR_ENABLE_DATA_REG = 1;
    if(!switch_GetState(&enableSW)) MOTOR_ENABLE_DATA_REG = 0;


    if(switch_GetState(&directionSW)) MOTOR_DIR_MODE_DATA_REG |= 0x00000001;
    if(!switch_GetState(&directionSW)) MOTOR_DIR_MODE_DATA_REG &= 0x11111110;

    if(switch_GetState(&ms1SW)) MOTOR_MS1_DATA_REG |= 0x00000001;
    if(!switch_GetState(&ms1SW)) MOTOR_MS1_DATA_REG &= 0x11111110;

    if(switch_GetState(&photoSW)) MOTOR_TIME_INTERRUPT_DATA_REG = 1;
	if(!switch_GetState(&photoSW)) MOTOR_TIME_INTERRUPT_DATA_REG = 0;

	if(switch_GetState(&setting_clock_SW))
	{
		if(interrupt_GetState(&sec_INT))
		{
			MOTOR_ENABLE_DATA_REG = 0x01;
		}
		if(interrupt_GetState(&min_INT))
		{
			MOTOR_ENABLE_DATA_REG = 0x02;
		}

		if(interrupt_GetState(&hour_INT))
		{
			MOTOR_ENABLE_DATA_REG = 0x04;
		}

		if(interrupt_GetState(&sec_INT) && interrupt_GetState(&min_INT))
		{
			MOTOR_ENABLE_DATA_REG = 0x03;
		}
		if(interrupt_GetState(&sec_INT) && interrupt_GetState(&hour_INT))
		{
			MOTOR_ENABLE_DATA_REG = 0x05;
		}

		if(interrupt_GetState(&min_INT) && interrupt_GetState(&hour_INT))
		{
			MOTOR_ENABLE_DATA_REG = 0x06;
		}
		if(interrupt_GetState(&sec_INT) && interrupt_GetState(&min_INT) && interrupt_GetState(&hour_INT))
		{
			MOTOR_ENABLE_DATA_REG = 0x07;
			BUZZER_DATA_REG = C4;
			sleep(1);
			BUZZER_DATA_REG = D4;
			sleep(1);
			BUZZER_DATA_REG = E4;
			sleep(1);
			BUZZER_DATA_REG = F4;
			sleep(1);
			BUZZER_DATA_REG = G4;
			sleep(1);
			BUZZER_DATA_REG = A4;
			sleep(1);
			BUZZER_DATA_REG = B4;
			sleep(1);
			BUZZER_DATA_REG = C5;
			sleep(1);

			BUZZER_DATA_REG = 0;
		}
	}



//	if(!switch_GetState(&setting_clock_SW))
//	{
//		if (interrupt_GetState(&sec_INT))
//		{
//			BUZZER_DATA_REG = C4;
//		}
//		else if(interrupt_GetState(&min_INT))
//		{
//			BUZZER_DATA_REG = D4;
//		}
//		else if(interrupt_GetState(&hour_INT))
//		{
//			BUZZER_DATA_REG = E4;
//		}
//	}
//	if(interrupt_GetState(&sec_INT))	MOTOR_ENABLE_DATA_REG = 0x01;

//	if(interrupt_GetState(&min_INT))	MOTOR_ENABLE_DATA_REG = 0x02;

//	if(interrupt_GetState(&hour_INT))	MOTOR_ENABLE_DATA_REG = 0x04;


//	{
//		interrupt_GetState(&sec_INT);
//		interrupt_GetState(&min_INT);
//		interrupt_GetState(&hour_INT);
//	}

    }


    cleanup_platform();
    return 0;
}


