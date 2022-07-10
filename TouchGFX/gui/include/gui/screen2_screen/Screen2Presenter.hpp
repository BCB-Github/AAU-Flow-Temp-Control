#ifndef SCREEN2PRESENTER_HPP
#define SCREEN2PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <stdio.h>
#include <stdlib.h>


using namespace touchgfx;

class Screen2View;

class Screen2Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen2Presenter(Screen2View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void updateTempWildcard(float temp);

    virtual ~Screen2Presenter() {};

    void setPVTempS2(float newTempPV);
    void setPVFlowS2(float newFlowPV);
    void setPressureS2(float newPressure);
    void setRpmS2(float newRpm);

    void setTestVal1(float newTestVal1);
    void setTestVal2(float newTestVal2);
    void setDutyCycle(int newDutyCycle);

    virtual void deactivate();


private:
    Screen2Presenter();

    Screen2View& view;
};

#endif // SCREEN2PRESENTER_HPP
