/*
 * InterfaceFunctions.c
 *
 *  Created on: Jul 6, 2022
 *      Author: jakob
 *      Create user function prototypes for interacting with the Interface
 */

#include "main.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "math.h"


#include "UserFunctionsJMK.h"

//extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern osSemaphoreId_t myBinarySem01Handle;

uint16_t uhADCxConvertedValue[10] = {0};

unsigned int tvar;
float tresult, increase;
int toutput;

void checkButton(QueueHandle_t queueIn, int *valuePointer, QueueHandle_t queueOut, int increment)
{
	if (xQueueReceive(queueIn, &tvar, 0)==pdTRUE)
		{
			if ((increment>0) & (*valuePointer < 2000))
			{
				*valuePointer = *valuePointer + increment;
			}
			if ((increment<0) & (*valuePointer > 0))
			{
				*valuePointer = *valuePointer + increment;
			}
			xQueueSend(queueOut, valuePointer, 0);
		}
}

void graphSine(float frequency, float *basePointer, QueueHandle_t graphQ, int nDataPoints)
{
	  tresult = (sin((*basePointer)*2*PI)*nDataPoints/2);
	  toutput = (int)tresult + nDataPoints/2;
	  xQueueSend(graphQ,&toutput,0);
	  increase = frequency/20;
	  *basePointer = *basePointer + increase;
}
