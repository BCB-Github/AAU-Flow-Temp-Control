#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen1Presenter() {};

    void updateSetPoints();
    void setPVTemp(float newTempPV);
    void setPVFlow(float newFlowPV);
    void setTotalFlow(float newTotalFlow);

    void setTimeElapsed(float time);
    void resetFlowControl();
    void switchMotorState(int state);

    void addDatapointTemp(float newDP);
    void addDatapointFlow(float newDP);

    void runProgress();

    void sendPressureError();
    void sendSaturationError();

private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
