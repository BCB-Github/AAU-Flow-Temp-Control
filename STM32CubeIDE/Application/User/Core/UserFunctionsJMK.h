/*
 * InterfaceFunctions.h
 *
 *  Created on: Jul 7, 2022
 *      Author: jakob
 */

#ifndef APPLICATION_USER_CORE_USERFUNCTIONSJMK_H_
#define APPLICATION_USER_CORE_USERFUNCTIONSJMK_H_


/* Functions */
void checkButton(QueueHandle_t queueIn, int *valuePointer, QueueHandle_t queueOut, int increment);
void graphSine(float frequency, float *basePointer, QueueHandle_t graphQ, int nDataPoints);
/*void PollingInit();
void pollingRoutine();*/
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif /* APPLICATION_USER_CORE_USERFUNCTIONSJMK_H_ */
// yellow
