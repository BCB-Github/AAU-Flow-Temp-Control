/*
 * controlTask.hpp
 *
 *  Created on: Jul 6, 2022
 *      Author: barlo
 */

#ifndef APPLICATION_USER_CORE_CONTROLTASK_HPP_
#define APPLICATION_USER_CORE_CONTROLTASK_HPP_




//extern "C" {float controlTaskFuncH(void);}

#ifdef __cplusplus
extern "C" {

typedef class ControlClass {
private:
	/*SV stands for Set value -i.e control Reference*/
	float pressure;
	float pressureSV;
	float flow;
	float flowSV;
	float temp;
	float tempSV;
	float volume;
	float volumeSV;
	float motorRPM;
	float time;
	int systemStatusSV;
	int systemStatus;

	int timeStart;
	int timeStop;
	int testTimeSV;
	int testTime;

	float kp;
	float ki;
	float u;
	float u_old;


public:
	ControlClass(); // constructor
	int getVar(char* varName);
	void changeVar(int changeVariable);
	void measurementUpdate(float pressureRead, float flowRead, float tempRead, float volumeRead, float motorRPMRead);
	void systemUpdateSV(float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV, float newVolumeSV);
	//void controlSystemUpdateSV(ControlClass* ControlClass, float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV){
	void controlLoop(float controlMeas);
	void statusUpdate(int i);
	void systemRun();
} ControlClass;


/// Declare the functions that will be used in C++ Languge - also declared in .h header file
/* ANSI C prototypes */
///
extern ControlClass* controlVarUpdate(ControlClass*, int changeVar);
extern int controlGetVar(ControlClass*, char* varName);
extern void controlMeasurementUpdate(ControlClass*, float pressureRead, float flowRead, float tempRead, float volumeRead, float motorRPMRead);
extern void controlSystemRun(ControlClass*, int systemStatus);
extern void controlSystemPassData(ControlClass*);
extern void controlSystemUpdateSV(ControlClass* ControlClass, float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV, float newVolumeSV);




}

#endif // C code wrapper
#endif /* APPLICATION_USER_CORE_CONTROLTASK_HPP_ */
