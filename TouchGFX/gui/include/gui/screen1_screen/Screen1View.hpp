#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateTempPV(float newVal);
    void updateFlowPV(float newVal);
    void updateTotalFlow(float newVal);
    void updateTime(float time);
    void setTempIcons();
    void setFlowIcons();
    void resetFlowIcons();

    void updateGraphTemp(float DP);
    void updateGraphFlow(float DP);

    void incrementTemp();
    void decrementTemp();
    void incrementFlow();
    void decrementFlow();


    void startPauseTempControl();
    void stopTempControl();
    void startPauseFlowControl();
    void stopFlowControl();
    //void enableMotor();
    void setSpanDays();
    void setSpanMinutes();
    void calcETA();

    void displayPressureError();

    void running();

    void printTempSV();
    void printFlowSV();


protected:
};

#endif // SCREEN1VIEW_HPP
