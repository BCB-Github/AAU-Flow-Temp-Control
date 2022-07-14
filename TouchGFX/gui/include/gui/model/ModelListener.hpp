#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include <stdio.h>
#include <stdlib.h>


class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}
    virtual void updateTempWildcard(float  temp) {}; // curly brackets so semi colon

    void bind(Model* m)
    {
        model = m;
    }

	virtual void setPVTemp(float newTempPV) {}
	virtual void setPVFlow(float newFlowPV) {}
	virtual void setTotalFlow(float newTotalFlow) {}
	virtual void setPVTempS2(float newTempPV) {}
	virtual void setPVFlowS2(float newFlowPV) {}
	virtual void setPressureS2(float newPressure) {}
	virtual void setRpmS2(float newRpm) {}

	virtual void runProgress() {}

	virtual void addDatapointTemp(float newDP) {}
	virtual void addDatapointFlow(float newDP) {}

	virtual void setTestVal1(float newTestVal1) {}
	virtual void setTestVal2(float newTestVal2) {}
	virtual void setDutyCycle(int newDutyCycle) {}

	virtual void resetFlowControl() {}


protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
