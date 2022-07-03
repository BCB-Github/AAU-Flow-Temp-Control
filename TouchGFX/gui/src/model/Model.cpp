#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

unsigned int placeholder;
int tempSV = 0;
int flowSV = 0;
int tempDP = 0;
int flowDP = 0;
float tempPV = 0;
float flowPV = 0;
float flowTotal = 0;

int loopRunning = 1;

float testVal1 = 0;
float testVal2 = 0;

extern "C"
{
/* The Queues used to update values and trigger updates on screen 1 */
	xQueueHandle updateSVTempQ;
	xQueueHandle updateSVFlowQ;
	xQueueHandle updatePVTempQ;
	xQueueHandle updatePVFlowQ;
	xQueueHandle updateTotalFlowQ;

	xQueueHandle tempUpQ;
	xQueueHandle tempDownQ;
	xQueueHandle flowUpQ;
	xQueueHandle flowDownQ;

	xQueueHandle dataTempQ;
	xQueueHandle dataFlowQ;

	xQueueHandle runningQ;

/* Queues used to update test values on screen 2 */
	xQueueHandle updateTest1Q;
	xQueueHandle updateTest2Q;

}

Model::Model() : modelListener(0)
{
	/* Creating the queues */
	updateSVTempQ = xQueueGenericCreate(1, sizeof(int), 0);
	updateSVFlowQ = xQueueGenericCreate(1, sizeof(int), 0);
	updatePVTempQ = xQueueGenericCreate(1, sizeof(float), 0);
	updatePVFlowQ = xQueueGenericCreate(1, sizeof(float), 0);
	updateTotalFlowQ = xQueueGenericCreate(1, sizeof(float), 0);
	tempUpQ = xQueueGenericCreate(1, sizeof(unsigned int), 0);
	tempDownQ = xQueueGenericCreate(1, sizeof(unsigned int), 0);
	flowUpQ = xQueueGenericCreate(1, sizeof(unsigned int), 0);
	flowDownQ = xQueueGenericCreate(1, sizeof(unsigned int), 0);
	runningQ = xQueueGenericCreate(1, sizeof(int), 0);

	dataTempQ = xQueueGenericCreate(16, sizeof(int), 0);
	dataFlowQ = xQueueGenericCreate(16, sizeof(int), 0);

	updateTest1Q = xQueueGenericCreate(1, sizeof(float), 0);
	updateTest2Q = xQueueGenericCreate(1, sizeof(float), 0);
}

void Model::tick()
{
	if (xQueueReceive(updateSVTempQ, &tempSV, 0)==pdTRUE)
	{
		modelListener->setSVTemp(tempSV);
	}
	if (xQueueReceive(updateSVFlowQ, &flowSV, 0)==pdTRUE)
	{
		modelListener->setSVFlow(flowSV);
	}
	if (xQueueReceive(updatePVTempQ, &tempPV, 0)==pdTRUE)
	{
		modelListener->setPVTemp(tempPV);
	}
	if (xQueueReceive(updatePVFlowQ, &flowPV, 0)==pdTRUE)
	{
		modelListener->setPVFlow(flowPV);
	}
	if (xQueueReceive(updateTotalFlowQ, &flowTotal, 0)==pdTRUE)
	{
		modelListener->setTotalFlow(flowPV);
	}
	xQueueReceive(runningQ, &loopRunning, 0);
	if (loopRunning == 1)
		{
			modelListener->runProgress();
		}

	if (xQueueReceive(updateTest1Q, &testVal1, 0)==pdTRUE)
		{
			modelListener->setTestVal1(testVal1);
		}
	if (xQueueReceive(updateTest2Q, &testVal2, 0)==pdTRUE)
		{
			modelListener->setTestVal2(testVal2);
		}

	while (xQueueReceive(dataTempQ, &tempDP, 0)==pdTRUE)
	{
		modelListener->addDatapointTemp(tempDP);
	}
	while (xQueueReceive(dataFlowQ, &flowDP, 0)==pdTRUE)
	{
		modelListener->addDatapointFlow(flowDP);
	}
}

void Model::increaseTemp()
{
	xQueueSend(tempUpQ,&placeholder,0);
}

void Model::decreaseTemp()
{
	xQueueSend(tempDownQ,&placeholder,0);
}

void Model::increaseFlow()
{
	xQueueSend(flowUpQ,&placeholder,0);
}

void Model::decreaseFlow()
{
	xQueueSend(flowDownQ,&placeholder,0);
}
