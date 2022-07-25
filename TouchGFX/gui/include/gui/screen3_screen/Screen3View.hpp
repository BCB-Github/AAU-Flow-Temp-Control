#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void incrementVol();
    void decrementVol();
    void limitVol();
    void printVolSV();
    void updateGraphVol(float DP);
    void updateVol(float Vol);

    void updateTimeS3(float time);
    void setTimeEstimate();
    void calcETA(float Vol);

    void incrementDigit1();
    void decrementDigit1();
    void incrementDigit2();
    void decrementDigit2();
    void incrementDigit3();
    void decrementDigit3();

    void printInput1();
    void printInput2();
    void printInput3();

    void enableCorrection();
    void printFactor();

protected:
};

#endif // SCREEN3VIEW_HPP
