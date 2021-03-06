/*
 * controlTask.c
 *
 *  Created on: Jul 6, 2022
 *      Author: barlo
 */
#include "main.h"
#include "cmsis_os.h"
#include "queue.h"
#include "libjpeg.h"
#include "app_touchgfx.h"
#include "controlTask.hpp"
#include "controlTask.h"
#include "userStructs.h" // include the ability to pass measurements

extern int flowStartState;
extern int flowStopState;
int plimit = 5;
int errorPlaceholder = 0;
int saturationErrorSent = 0;
float oldFlow = 0;
float oldFlow2 = 0;
float oldFlow3 = 0;
float T1 = 0.01/60;

extern xQueueHandle pressureErrorQ;
extern xQueueHandle saturationErrorQ;
extern xQueueHandle sendServerErrorQ;
extern xQueueHandle motorSwitchQ;

ControlClass::ControlClass() : pressure(0), pressureSV(0), kp_flow(0.001) , ki_flow(.003){

}; // initialize sampleVar to 0

int ControlClass::getVar(char* varName) {

	return pressure;
}

void ControlClass::changeVar(int changeVariable){
	pressure = changeVariable;
}



ControlClass* controlVarUpdate(ControlClass* ControlClass, int newVar){
	ControlClass->changeVar(newVar);
	return ControlClass;
}

int  controlGetVar(ControlClass* ControlClass, char* varName){
	return ControlClass->getVar(varName);
}

void ControlClass::controlTemp(float controlMeas){

		 static float controlMeasOld;
		 float T = 0.01; // this might not be right

		 u_temp = u_old_temp+ controlMeas * (kp_temp + ki_temp * T) - controlMeasOld * kp_temp;

		 if (u_temp> 5)
		 {
			 u_temp= 5;
		 }
		 else if ( u_temp < 0)
		 {
			  u_temp = 0;
		 }

		 u_old_temp = u_temp;
		 controlMeasOld = controlMeas;



}

void ControlClass::controlFlow(float controlMeas){
	 static int maxVoltageCounter;
		 static float controlMeasOld;
		 float T = 0.01; // this might not be right

		 u_flow = u_old_flow+ controlMeas * (kp_flow + ki_flow * T) - controlMeasOld * kp_flow;

		 if (u_flow > 5)
		 {
			 u_flow= 5;
			 maxVoltageCounter++;
		 }
		 else if( u_flow < 0)
		 {
			 maxVoltageCounter++;
			 u_flow = 0;
		 }
		 else{

			 maxVoltageCounter = 0;
		 }

		 u_old_flow = u_flow;
		 controlMeasOld = controlMeas;
		 if (maxVoltageCounter > 100) {
			 // dvs nu har den k??rt p?? max i et l??nger periode - send en fejl
			 if (saturationErrorSent != 1) {
				 xQueueSend(saturationErrorQ, &errorPlaceholder, 0);
				 errorPlaceholder = 0;
				 xQueueSend(sendServerErrorQ, &errorPlaceholder, 0);
				 saturationErrorSent = 1;
			 }

		 } else {
			 if (saturationErrorSent == 1) {
				 xQueueSend(saturationErrorQ, &errorPlaceholder, 0);
				 saturationErrorSent = 0;
			 }
		 }

}



// Define Class Function
void ControlClass::measurementUpdate(PassDataMeasHandle passDataMeas){//float pressureRead, float flowRead, float tempRead, float volumeRead, float motorRPMRead){
	/*time = HAL_GetTick();
	pressure = pressureRead;
	flow = flowRead;
	temp = tempRead;
	volume = volumeRead;
	motorRPM = motorRPMRead;
	*/
	passDataMeas->volumeMeas[passDataMeas->newestMeasIndex] = volume;
	passDataMeas->timeStart[passDataMeas->newestMeasIndex] = timeStart;
	pressure = passDataMeas->presMeas[passDataMeas->newestMeasIndex];
	temp = passDataMeas->tempMeas[passDataMeas->newestMeasIndex];
	flow = passDataMeas->flowMeas[passDataMeas->newestMeasIndex];
	time = passDataMeas->time[passDataMeas->newestMeasIndex];
}



// Define Linker Function
void controlMeasurementUpdate(ControlClass* ControlClass, PassDataMeas_Handle passDataMeas)
{
	ControlClass->measurementUpdate(passDataMeas);
}



void ControlClass::systemRun(){

	float dutyVoltageFlow;
	float dutyVoltageTemp;
	// set output To flow
	float ccr1;
	// set output to Temp
	float ccr2;

	// The idea is we want to make a buffer between the reference set point and the system status
	// Then we can make sure that the ramp up and down work as intended
	if (systemFlowStatusSV == 0){
		// i.e system is set to not run
		switch (systemFlowStatus){
		case 1:
			systemFlowStatus = 0;
			break;
		case 2 : // The system is currently running
			systemFlowStatus = 3; // Set the control to ramp down to zero
			break;
		case 3:
			if (motorRPM < 100) {
			systemFlowStatus = 5;
			}
			break;
		case 4:
			systemFlowStatus = 3;

			break;
		case 5: // Test Completed - return to standby
			systemFlowStatus = 0;
			break;
		default :
			// if the system status is at zero, do nothing
			break;

		}
	}

	if(systemFlowStatusSV == 1) // 1 means gooOOOO
	{
		if ( systemFlowStatus == 0 )
		{
			systemFlowStatus = 1;
		}
		if (systemFlowStatus == 4)
		{
			systemFlowStatus = 2;
		}
	}

	if (systemFlowStatusSV == 2)
	{
		systemFlowStatus = 4;
	}





	// This will be the operation of the control system
	switch (systemFlowStatus) {
	default: // system Standby
		break;
	case 1: // initialize

		// update setValues
		timeStop = 0;
		timeStart = time;
		testTime = 0;
		systemFlowStatus = 2;
		volume = 0;

		break;

	case 2: // control running high

		// Pressure check
		if (pressure > plimit) {
			systemFlowStatus = 3;
			xQueueSend(pressureErrorQ, &flowStartState, 0);
			errorPlaceholder = 1;
			xQueueSend(sendServerErrorQ, &errorPlaceholder, 0);
			break;
		}

		testTime = time - timeStart - timeStop ;
		// Idea here is that we run our control
		controlFlow(flowSV - flow);



		volume = volume +  	T1/2 * (flow + oldFlow); // - add the volume that had occoured during the loop

		//oldFlow3 = oldFlow2;
		//oldFlow2 = oldFlow;
		oldFlow = flow;
		dutyVoltageFlow= u_flow/5;

		// set output To flow
		ccr1 = dutyVoltageFlow*32767;
		if (dutyVoltageFlow == 0) {ccr1 = 1;}
		TIM12->CCR1=(int)ccr1; // duty%=i/32767

		if (systemVolLimitStatus == 1) {
			if (volume >= volumeSV){
			// The set time for the test has been passed - Ramp Down
			systemFlowStatus = 3;
			}
		}


		break;

	case 3: // Control Ramp down

		 // Control the system to zero
		controlFlow(0-flow);
		dutyVoltageFlow= u_flow/5;

		// set output To flow
		ccr1 = dutyVoltageFlow*32767;
		TIM12->CCR1=(int)ccr1; // duty%=i/32767
		//	if (timeStart >= testTimeSV){ // The test time has been achieved
			if (flow < 100) // The motor has stopped
			{
				// disable pwm output
				systemFlowStatus = 5; // The test has been completed
			}

		break;

	case 4: // system paused
		timeStop = time - testTime - timeStart;
		 // Control the system to zero
		controlFlow(0-flow);
		dutyVoltageFlow= u_flow/5;

		// set output To flow
		ccr1 = dutyVoltageFlow*32767;
		TIM12->CCR1=(int)ccr1; // duty%=i/32767
		break;
	case 5: //testCompleted
		// Return to Standby
		u_old_flow = 0;
		volume = 0;
		TIM12->CCR1=(int)1;
		flowStartState = 2;
		flowStopState = 0;
		systemFlowStatusSV = 0;
		systemFlowStatus = 0;
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7|MCU_ACTIVE_Pin, GPIO_PIN_RESET);
		break;
	}


	/* Temperature control */

	// The idea is we want to make a buffer between the reference set point and the system status
	// Then we can make sure that the ramp up and down work as intended
	if (systemTempStatusSV == 0){
		// i.e system is set to not run
		switch (systemTempStatus){
		case 1:
			systemTempStatus = 0;
			break;
		case 2 : // The system is currently running
			systemTempStatus = 0;
			break;
		case 3:

			systemTempStatus = 0;

			break;

		default :
			// if the system status is at zero, do nothing
			break;

		}
	}

	if(systemTempStatusSV == 1) // 1 means gooOOOO
	{
		if (systemTempStatus == 0)
		{
			systemTempStatus = 1;
		}
	}

	if (systemTempStatusSV == 2)
	{
		systemTempStatus = 3;
	}


	// This will be the operation of the control system
	switch (systemTempStatus) {
	default: // system Standby
		TIM5->CCR4=1;
		break;
	case 1: // initialize

		// update setValues
		systemTempStatus = 2;

		break;

	case 2: // control running high
		// Idea here is that we run our control
		controlTemp(tempSV - temp);
		if (u_temp > 5)
		{
			u_temp = 5;
		}
		if (u_temp < 0)
		{
			u_temp =0;
		}
		dutyVoltageTemp= u_temp/5;

		// set output To temp
		ccr2 = dutyVoltageTemp*32767;
		TIM5->CCR4=(int)ccr2;

		break;

	case 3: // system paused

		// set output To temp
		TIM5->CCR4=1;
		break;

	}
}




void controlSystemRun(ControlClass* ControlClass){
	ControlClass->systemRun();

}


// Update the control Set values
void ControlClass::systemUpdateSV(PassDataSVHandle passDataSVHandle){
	/*
	 * pressureSV = newPressureSV;
	flowSV = newFlowSV;
	tempSV = newTempSV;
	volumeSV = newVolumeSV;
	testTimeSV = newTimeSV;
*/
	flowSV = passDataSVHandle->flowSV;
	tempSV = passDataSVHandle->tempSV;
	volumeSV = passDataSVHandle->volumeSV;
	systemFlowStatusSV = passDataSVHandle->systemFlowStatusSV;
	systemTempStatusSV = passDataSVHandle->systemTempStatusSV;
	systemVolLimitStatus = passDataSVHandle->systemVolLimitStatus;


}

void controlSystemUpdateSV(ControlClass* ControlClass, PassDataSVHandle passDataSVHandle)
{
	ControlClass->systemUpdateSV(passDataSVHandle);
}



void controlSystemPassData(ControlClass*){

}






ControlClass systemControl;


//extern "C" float controlTaskConverter() {return controlTaskFuncH(); }




