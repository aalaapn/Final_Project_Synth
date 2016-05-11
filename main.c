/*Include Board stuff*/
#include <Board_Accelerometer.h>
#include <Board_Magnetometer.h>
#include <Board_Buttons.h>
#include <Board_LED.h>
#include <Board_DAC.h>
#include <fsl_debug_console.h>
#include "board.h"
//#include  <stdlib.h>
//#include <arm_math.h>
#include <math.h>
//#include <Board_Audio.h>
//#include <mbed.h>
//#include "fsl_ftm_driver.h"
//#include "fsl_ftm_hal.h"
#include "fsl_os_abstraction.h"
//#include "fsl_cmp_driver.h"
#include "fsl_dac_driver.h"
#include "fsl_dac_hal.h"
//#include "fsl_dac_common.h"
//#include "fsl_buffer_driver.h"
#define PI (3.141592653589793)
/*Include Standard Libraries*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include "fsl_sai_driver.h"
/*Define Constants*/
#define DAC_TEST_BUFF_SIZE  (16U)

//volatile uint32_t g_dacInstance = 0U;
//static uint16_t g_dacBuffDat[DAC_TEST_BUFF_SIZE];
extern void DAC_TEST_FillBuffDat(uint16_t *buffPtr, uint32_t buffLen);
//static dac_state_t MyDacStateStructForBufferOneTimeScan;
static uint32_t MyDacIsrCounterBuffStart = 0U;
static uint32_t MyDacIsrCounterBuffUpper = 0U;
static uint32_t MyDacIsrCounterBuffWatermark = 0U;
volatile uint32_t g_dacInstance = 0U;
static uint16_t g_dacBuffDat[DAC_TEST_BUFF_SIZE];
static void DAC_ISR_Buffer(void);
extern void DAC_TEST_FillBuffDat(uint16_t *buffPtr, uint32_t buffLen);
uint32_t instance;
uint8_t buffLen = 1U;
uint16_t *buffPtr;

ACCELEROMETER_STATE astate;
MAGNETOMETER_STATE mstate;
uint32_t a=1;
uint32_t b=2;
uint32_t c=3;

int averagerax(int numAve){
	int sumStates;
	int divisor;
	ACCELEROMETER_STATE astate;
	divisor=numAve;
	sumStates = 0;
	for(numAve; numAve!=0; numAve--){
		Accelerometer_GetState(&astate);
		sumStates=(sumStates+astate.x);
	}
	sumStates=sumStates/divisor;
	return sumStates;
}

int averageray(int numAve){
	int sumStates;
	int divisor;
	ACCELEROMETER_STATE astate;
	divisor=numAve;
	sumStates = 0;
	for(numAve; numAve!=0; numAve--){
		Accelerometer_GetState(&astate);
		sumStates=(sumStates+astate.y);
	}
	sumStates=sumStates/divisor;
	return sumStates;
}

int averageraz(int numAve){
	int sumStates;
	int divisor;
	ACCELEROMETER_STATE astate;
	divisor=numAve;
	sumStates = 0;
	for(numAve; numAve!=0; numAve--){
		Accelerometer_GetState(&astate);
		sumStates=(sumStates+astate.z);
	}
	sumStates=sumStates/divisor;
	return sumStates;
}

int averagermx(int numAve){
	int sumStates;
	int divisor;
	MAGNETOMETER_STATE mstate;
	divisor=numAve;
	sumStates = 0;
	for(numAve; numAve!=0; numAve--){
		Magnetometer_GetState(&mstate);
		sumStates=(sumStates+mstate.x);
	}
	sumStates=sumStates/divisor;
	return sumStates;
}

int averagermy(int numAve){
	int sumStates;
	int divisor;
	MAGNETOMETER_STATE mstate;
	divisor=numAve;
	sumStates = 0;
	for(numAve; numAve!=0; numAve--){
		Magnetometer_GetState(&mstate);
		sumStates=(sumStates+mstate.y);
	}
	sumStates=sumStates/divisor;
	return sumStates;
}

int averagermz(int numAve){
	int sumStates;
	int divisor;
	MAGNETOMETER_STATE mstate;
	divisor=numAve;
	sumStates = 0;
	for(numAve; numAve!=0; numAve--){
		Magnetometer_GetState(&mstate);
		sumStates=(sumStates+mstate.z);
	}
	sumStates=sumStates/divisor;
	return sumStates;
}

int main(){
	hardware_init();
	Accelerometer_Initialize();
	Magnetometer_Initialize();
	Buttons_Initialize();
	LED_Initialize();
	//DAC_Initialize();
	/*DAC and Buffer configs*/
	dac_converter_config_t userConfigPtr;
	dac_buffer_config_t dacBuffConfigStruct;
	
	volatile uint32_t instance = 0U;
	uint16_t value =1;
	DAC_DRV_StructInitUserConfigNormal(&userConfigPtr);
	DAC_DRV_Init(instance, &userConfigPtr);
	double j;
	double i;
	int ax;
	int ay;
	int az;
	int mx;
	int my;
	int mz;
	uint16_t k;

//	debug_printf("DAC_DRV_Output: %d\r\n", instance);
	
	while(1){
		//LED_SetOut(a);
		//LED_SetOut(b);
		//LED_SetOut(c);
		//LED_SetOut(a);
		//LED_SetOut(b);
		//LED_SetOut(c);
		//LED_On(1);
//		while(Buttons_GetState()==0){
//			LED_Off(0);
//			LED_Off(1);
//			LED_Off(2);
//			i=0;
//			while(i<100){
//				Accelerometer_GetState(&astate);
//				i=i+1;
//				j=abs(astate.y)*cos(i*abs(astate.x));
//				k=j;
//				debug_printf("DAC_DRV_Output: %d\r\n", k);
//				DAC_DRV_Output(instance, k);
//	  }
//		}
//		while(Buttons_GetState()==1){
//			LED_Off(0);
//			LED_Off(1);
//			LED_Off(2);
//			LED_On(0);
//		  i=0;
//			while(i<500){
//				Accelerometer_GetState(&astate);
//				i=i+5;
//				j=10*sin(100*i)+10;
//				k=j;
//				debug_printf("DAC_DRV_Output: %d\r\n", k);
//				DAC_DRV_Output(instance, k);
//	  }
//		}
//		while(Buttons_GetState()==2){
//			LED_Off(0);
//			LED_Off(1);
//			LED_Off(2);
//			LED_On(1);
//			 i=0;
//			while(i<100){
//				Accelerometer_GetState(&astate);
//				i=i+1;
//				j=20*sin(400*i)+20;
//				k=j;
//				debug_printf("DAC_DRV_Output: %d\r\n", k);
//				DAC_DRV_Output(instance, k);
//	  }
//		}
//		while(Buttons_GetState()==3){
//			LED_Off(0);
//			LED_Off(1);
//			LED_Off(2);
//			LED_On(2);
//			 i=0;
//			while(i<100){
//				Accelerometer_GetState(&astate);
//				i=i+1;
//				j=30*sin(300*i)+30;
//				k=j;
//				debug_printf("DAC_DRV_Output: %d\r\n", k);
//				DAC_DRV_Output(instance, k);
//	  }
//		}
//		else{
//		while(i<100000){
//			Accelerometer_GetState(&astate);
//			i=i+.0001;
//			j=500*astate.x*sin(400*i)+3000;
//			k=j;
//			debug_printf("DAC_DRV_Output: %d\r\n", k);
//			DAC_DRV_Output(instance, k);
//	  }
//		LED_Off(1);

//	}
		
		LED_Off(0);
		ax=averagerax(5);
		ay=averageray(5);
		az=averageraz(5);
		mx=averagermx(4);
		my=averagermy(4);
		mz=averagermz(4);
		debug_printf("%5d %5d %5d %5d %5d %5d\r\n", ax, ay, az, mx, my, mz);
		//debug_printf("%" PRIu32 "\r\n", LED_GetCount());
		//DAC_TEST_NormalMode(2);
	}
}

