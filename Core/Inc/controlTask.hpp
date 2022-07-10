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

// Give the class the structs defined in userStructs.h
typedef struct PassDataMeas* PassDataMeas_Handle;
typedef struct PassDataSV* PassDataSVHandle;


// Define the controlClass
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
	void measurementUpdate(PassDataMeas_Handle passDataMeas);
	void systemUpdateSV(PassDataSVHandle passDataSVHandle);
	//void controlSystemUpdateSV(ControlClass* ControlClass, float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV){
	void controlLoop(float controlMeas);
	void systemRun();
} ControlClass;


/// Declare the functions that will be used in C++ Languge - also declared in .h header file
/* ANSI C prototypes */
///
extern ControlClass* controlVarUpdate(ControlClass*, int changeVar);
extern int controlGetVar(ControlClass*, char* varName);
extern void controlMeasurementUpdate(ControlClass*, PassDataMeas_Handle modelMeasPassData);
extern void controlSystemRun(ControlClass*);
extern void controlSystemPassData(ControlClass*);
//extern void controlSystemUpdateSV(ControlClass* ControlClass, float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV, float newVolumeSV);
extern void controlSystemUpdateSV(ControlClass* ControlClass, PassDataSVHandle passDataSVHandle);




}
#endif // C code wrapper
#endif /* APPLICATION_USER_CORE_CONTROLTASK_HPP_ */
