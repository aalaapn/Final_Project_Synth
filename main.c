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
		while(Buttons_GetState()==0){
			LED_Off(0);
			LED_Off(1);
			LED_Off(2);
		}
		while(Buttons_GetState()==1){
			LED_Off(0);
			LED_Off(1);
			LED_Off(2);
			LED_On(0);
		  i=0;
			while(i<2000){
				Accelerometer_GetState(&astate);
				i=i+5;
				j=100*tan(40*i)+1000;
				if(fmod(i,3)==0){
				k=i*20;
				}
				else{
				k=i*500;
				}
				debug_printf("DAC_DRV_Output: %d\r\n", fmod(i,3));
				DAC_DRV_Output(instance, k);
	  }
		}
		while(Buttons_GetState()==2){
			LED_Off(0);
			LED_Off(1);
			LED_Off(2);
			LED_On(1);
			 i=0;
			while(i<100){
				Accelerometer_GetState(&astate);
				i=i+1;
				j=1000*sin(400*i)+1000;
				k=i*500;
				debug_printf("DAC_DRV_Output: %d\r\n", k);
				DAC_DRV_Output(instance, k);
	  }
		}
		while(Buttons_GetState()==3){
			LED_Off(0);
			LED_Off(1);
			LED_Off(2);
			LED_On(2);
			 i=0;
			while(i<10){
				Accelerometer_GetState(&astate);
				i=i+1;
				j=2000*sin(400*i)+2000;
				k=j;
				debug_printf("DAC_DRV_Output: %d\r\n", k);
				DAC_DRV_Output(instance, k);
	  }
		}
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
		
		//LED_Off(0);
		//Accelerometer_GetState(&astate);
		//Magnetometer_GetState(&mstate);
		//debug_printf("%5d %5d %5d %5d %5d %5d\r\n", astate.x, astate.y, astate.z, mstate.x, mstate.y, mstate.z);
		//debug_printf("%" PRIu32 "\r\n", LED_GetCount());
		//DAC_TEST_NormalMode(2);
	}
}

