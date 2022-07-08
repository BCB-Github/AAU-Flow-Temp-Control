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
    virtual void updateTempWildcard(float temp);
    

    void updateTestVal1(float newVal1);
    void updateTestVal2(float newVal2);
    void updateDutyCycle(int newDuty);

    void incrementDuty();
    void decrementDuty();

protected:
};

#endif // SCREEN2VIEW_HPP
