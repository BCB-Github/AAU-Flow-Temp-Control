/*
 * controlTask.h
 *
 *  Created on: Jul 6, 2022
 *      Author: barlo
 */


#ifndef APPLICATION_USER_CORE_CONTROLTASK_H_
#define APPLICATION_USER_CORE_CONTROLTASK_H_

void controlTaskFunc(void* argument); // Declare the control Task Function


#ifndef __cplusplus // Define the Class for the C compiler
typedef
		struct ControlClass
		ControlClass;

		extern ControlClass* controlVarUpdate(ControlClass*, int changeVar);
		extern int controlGetVar(ControlClass*, char* varName);
		extern void controlMeasurementUpdate(ControlClass*, float pressureRead, float flowRead, float tempRead, float volumeRead, float motorRPMRead);
		extern void controlSystemRun(ControlClass*, int systemStatus);
		extern void controlSystemPassData(ControlClass*);
		extern void controlSystemUpdateSV(ControlClass* ControlClass, float newTempSV, float newFlowSV, float newPressureSV, int newTimeSV, float newVolumeSV);


#endif






#endif /* APPLICATION_USER_CORE_CONTROLTASK_H_ */
