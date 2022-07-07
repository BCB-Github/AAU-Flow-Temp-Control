/*
 * controlTask.c
 *
 *  Created on: Jul 6, 2022
 *      Author: barlo
 */
#include "main.h"
#include "cmsis_os.h"
#include "libjpeg.h"
#include "app_touchgfx.h"
#include "controlTask.hpp"
#include "controlTask.h"


//float temp;
//uint16_t flow;




ControlClass::ControlClass() : pressure(0), pressureSV(0), kp(0.01) , ki(.3){

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

void ControlClass::controlLoop(float controlMeas){

	 static float controlMeasOld;
	 float T = 0.01;
	 u = u_old+ controlMeas * (kp + ki * T) - controlMeasOld * kp;
	 u_old = u;
	 if (u_old > 5)
	 {
		 u_old = 5;
	 }
	 if( u_old < 0)
	 {
		 u_old = 0;
	 }
	 controlMeasOld = controlMeas;


}



// Define Class Function
void ControlClass::measurementUpdate(float pressureRead, float flowRead, float tempRead, float volumeRead, float motorRPMRead){
	time = HAL_GetTick();
	pressure = pressureRead;
	flow = flowRead;
	temp = tempRead;
	volume = volumeRead;
	motorRPM = motorRPMRead;
}


// Define Linker Function
void controlMeasurementUpdate(ControlClass* ControlClass, float pressureRead, float flowRead, float tempRead, float volumeRead, float motorRPMRead)
{

	ControlClass->measurementUpdate(pressureRead, flowRead, tempRead, volumeRead, motorRPMRead);
}

void ControlClass::statusUpdate(int systemStatusUpdate)
{
	systemStatusSV = systemStatusUpdate;
}

void ControlClass::systemRun(){

	float dutyVoltage;
	// set output To flow
	float ccr1;

	// The idea is we want to make a buffer between the reference set point and the system status
	// Then we can make sure that the ramp up and down work as intended
	if (systemStatusSV == 0){
		// i.e system is set to not run
		switch (systemStatus){
		case 1:
			systemStatus = 0;
			break;
		case 2 : // The system is currently running
			systemStatus = 3; // Set the control to ramp down to zero
			break;
		case 3:
			if (motorRPM < 10) {
		systemStatus = 4;
			}
			break;
		case 4:
			if (motorRPM == 0){
				systemStatus = 5;
			}
			break;
		case 5: // Test Completed - return to standby
			systemStatus = 0;
			break;
		default :
			// if the system status is at zero, do nothing
			break;

		}
	}
	if(systemStatusSV == 1) // 1 means gooOOOO
	{
		if (systemStatus == 0)
		{
			systemStatus = 1;
		}
	}



	// This will be the operation of the control system
	switch (systemStatus) {
	default: // system Standby
		break;
	case 1: // initialize

		// update setValues
		timeStop = 0;
		timeStart = time;
		testTime = 0;
		systemStatus = 2;
		break;

	case 2: // control running high
		testTime = time - timeStart - timeStop ;

		// Idea here is that we run our control
		controlLoop(flowSV - flow);
		if (u > 5)
		{
			u = 5;
		}
		if (u < 0)
		{
			u =0;
		}
		dutyVoltage= u/5;
		// set output To flow
		ccr1 = dutyVoltage*65535;
		TIM1->CCR1=(int)ccr1; // duty%=i/65535



		if (testTime >= testTimeSV){
			// The set time for the test has been passed - Ramp Down
			systemStatus = 3;
		}

		break;

	case 3: // Control Ramp down
		controlLoop(flowSV - flow); // Control the system to zero
	//	if (timeStart >= testTimeSV){ // The test time has been achieved
		//	if (motorRPM < 10) // The motor has stopped
			//{
				// disable pwm output
				systemStatus = 2; // The test has been completed
			//}
		//}
		break;

	case 4: // system paused
		timeStop = time - testTime - timeStart;
		break;
	case 5: //testCompleted
		// Return to Standby
		u = 0;
		u_old = 0;

		systemStatus = 0;
		break;
	}
}




void controlSystemRun(ControlClass* ControlClass, int systemStatus){
	ControlClass->statusUpdate(systemStatus);
	ControlClass->systemRun();

}


// Update the control Set values
void ControlClass::systemUpdateSV(float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV, float newVolumeSV){
	pressureSV = newPressureSV;
	flowSV = newFlowSV;
	tempSV = newTempSV;
	volumeSV = newVolumeSV;
	testTimeSV = newTimeSV;


}

void controlSystemUpdateSV(ControlClass* ControlClass, float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV, float newVolumeSV){
	ControlClass->systemUpdateSV(newTempSV, newFlowSV, newPressureSV, newTimeSV, newVolumeSV);
}



void controlSystemPassData(ControlClass*){

}




/*
extern "C" {float controlTaskFuncH(void){
	int sampleInt = 50;
	//return call_Control_int();
	//return sampleInt;
	return 5;
}
}
*/

ControlClass systemControl;


//extern "C" float controlTaskConverter() {return controlTaskFuncH(); }




