#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    void updateTempPVS2(float newTempPV);
    void updateFlowPVS2(float newFlowPV);
    void updatePressureS2(float newPressure);
    void updateRpmS2(float newRpm);

    void updateTestVal1(float newVal1);
    void updateTestVal2(float newVal2);
    void updateDutyCycle(int newDuty);
    void printDuty();

    void incrementDuty();
    void decrementDuty();

protected:
};

#endif // SCREEN2VIEW_HPP
