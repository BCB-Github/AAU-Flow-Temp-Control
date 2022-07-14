#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "userStructs.h"
extern float temp;

#include "queue.h"

/* I use SV for Set Value and PV for Present Value */
unsigned int placeholder;
float tempDP = 0;
float flowDP = 0;
float tempPV = 0;
float flowPV = 0;
float flowTot = 0;
float pressurePV = 0;
float rpmPV = 0;

extern PassDataMeas modelMeasPassData;
extern int tempStartState;
extern int flowStartState;

float testVal1 = 0;
float testVal2 = 0;
int duty = 0;

extern "C"
{
/* The Queues used to update values */
	xQueueHandle updatePVTempQ;
	xQueueHandle updatePVFlowQ;
	xQueueHandle updateTotalFlowQ;
	xQueueHandle updatePressureQ;
	xQueueHandle updateRpmQ;

/* The Queues used to send datapoints to graphs */
	xQueueHandle dataTempQ;
	xQueueHandle dataFlowQ;


/* Queues used to update test values on screen 2 */
	xQueueHandle updateTest1Q;
	xQueueHandle updateTest2Q;

	xQueueHandle updateDutyQ;

}

Model::Model() : modelListener(0)
{
	/* Creating the queues */

	updatePVTempQ = xQueueGenericCreate(1, sizeof(float), 0);
	updatePVFlowQ = xQueueGenericCreate(1, sizeof(float), 0);
	updateTotalFlowQ = xQueueGenericCreate(1, sizeof(float), 0);
	updatePressureQ = xQueueGenericCreate(1, sizeof(float), 0);
	updateRpmQ = xQueueGenericCreate(1, sizeof(float), 0);

	dataTempQ = xQueueGenericCreate(16, sizeof(float), 0);
	dataFlowQ = xQueueGenericCreate(16, sizeof(float), 0);

	updateTest1Q = xQueueGenericCreate(1, sizeof(float), 0);
	updateTest2Q = xQueueGenericCreate(1, sizeof(float), 0);

	updateDutyQ = xQueueGenericCreate(1, sizeof(int), 0);

}

void Model::tick()
{

	/* The following five if statements check whether new Present Values have been sent to the queues */
	if (xQueueReceive(updatePVTempQ, &tempPV, 0)==pdTRUE)
	{
		modelListener->setPVTemp(tempPV);
		modelListener->setPVTempS2(tempPV);
		modelListener->addDatapointTemp(tempPV);
	}
	if (xQueueReceive(updatePVFlowQ, &flowPV, 0)==pdTRUE)
	{
		modelListener->setPVFlow(flowPV);
		modelListener->setPVFlowS2(flowPV);
		modelListener->addDatapointFlow(flowPV);
	}
	if (xQueueReceive(updateTotalFlowQ, &flowTot, 0)==pdTRUE)
	{
		modelListener->setTotalFlow(flowTot);
	}
	if (xQueueReceive(updatePressureQ, &pressurePV, 0)==pdTRUE)
	{
		modelListener->setPressureS2(pressurePV);
	}
	if (xQueueReceive(updateRpmQ, &rpmPV, 0)==pdTRUE)
	{
		modelListener->setRpmS2(rpmPV);
	}

	if ((flowStartState == 1) | (tempStartState == 1))
		{
			modelListener->runProgress();
			if ((flowStartState == 1) & (tempStartState == 1))
			{
				modelListener->runProgress();
			}
		}


	if (xQueueReceive(updateTest1Q, &testVal1, 0)==pdTRUE)
		{
			modelListener->setTestVal1(testVal1);
		}
	if (xQueueReceive(updateTest2Q, &testVal2, 0)==pdTRUE)
		{
			modelListener->setTestVal2(testVal2);
		}
	if (xQueueReceive(updateDutyQ, &duty, 0)==pdTRUE)
		{
			modelListener->setDutyCycle(duty);
		}

	if (flowStartState == 2) {
		modelListener->resetFlowControl();
	}
}


void Model::updateWildcards() {

}
