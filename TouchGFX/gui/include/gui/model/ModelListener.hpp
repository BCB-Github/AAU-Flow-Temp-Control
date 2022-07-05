#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void setSVTemp(int newTempSV) {}
	virtual void setSVFlow(int newFlowSV) {}
	virtual void setPVTemp(float newTempPV) {}
	virtual void setPVFlow(float newFlowPV) {}
	virtual void setTotalFlow(float newTotalFlow) {}

	virtual void runProgress() {}

	virtual void addDatapointTemp(int newDP) {}
	virtual void addDatapointFlow(int newDP) {}

	virtual void setTestVal1(float newTestVal1) {}
	virtual void setTestVal2(float newTestVal2) {}
	virtual void setDutyCycle(int newDutyCycle) {}




protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
