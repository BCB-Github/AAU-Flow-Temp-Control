/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN3VIEWBASE_HPP
#define SCREEN3VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/graph/GraphScroll.hpp>
#include <touchgfx/widgets/graph/GraphElements.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/graph/GraphLabels.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>

class Screen3ViewBase : public touchgfx::View<Screen3Presenter>
{
public:
    Screen3ViewBase();
    virtual ~Screen3ViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void incrementVol()
    {
        // Override and implement this function in Screen3
    }

    virtual void decrementVol()
    {
        // Override and implement this function in Screen3
    }

    virtual void limitVol()
    {
        // Override and implement this function in Screen3
    }

    virtual void incrementDigit1()
    {
        // Override and implement this function in Screen3
    }

    virtual void incrementDigit2()
    {
        // Override and implement this function in Screen3
    }

    virtual void incrementDigit3()
    {
        // Override and implement this function in Screen3
    }

    virtual void decrementDigit1()
    {
        // Override and implement this function in Screen3
    }

    virtual void decrementDigit2()
    {
        // Override and implement this function in Screen3
    }

    virtual void decrementDigit3()
    {
        // Override and implement this function in Screen3
    }

    virtual void enableCorrection()
    {
        // Override and implement this function in Screen3
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  flexDownVol;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  flexUpVol;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  upInput1;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  upInput2;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  upInput3;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  downInput1;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  downInput2;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  downInput3;
    touchgfx::Box box1;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  flexButton1;
    touchgfx::TextArea textArea1;
    touchgfx::GraphScroll<1000> graphVol;
    touchgfx::GraphElementLine graphVolLine1;
    touchgfx::PainterRGB565 graphVolLine1Painter;
    touchgfx::GraphElementGridY graphVolMajorYAxisGrid;
    touchgfx::GraphLabelsY graphVolMajorYAxisLabel;
    touchgfx::TextAreaWithOneWildcard SPVol;
    touchgfx::ScalableImage upVolImg;
    touchgfx::ScalableImage downVolImg;
    touchgfx::TextArea en3;
    touchgfx::ImageButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  toggleVol;
    touchgfx::TextArea lim1;
    touchgfx::TextArea textAreaSP;
    touchgfx::TextAreaWithTwoWildcards timeETA;
    touchgfx::TextArea textArea5;
    touchgfx::TextAreaWithTwoWildcards timeElapsed;
    touchgfx::TextArea textArea4;
    touchgfx::TextAreaWithOneWildcard hoursElapsed;
    touchgfx::TextAreaWithOneWildcard hoursETA;
    touchgfx::TextArea textArea6;
    touchgfx::TextAreaWithOneWildcard currentVol;
    touchgfx::ScalableImage upFirstImg;
    touchgfx::ScalableImage upSecondImg;
    touchgfx::ScalableImage upThirdImg;
    touchgfx::ScalableImage downFirstImg;
    touchgfx::ScalableImage downSecondImg;
    touchgfx::ScalableImage downThirdImg;
    touchgfx::TextArea textArea7;
    touchgfx::TextAreaWithOneWildcard volInput1;
    touchgfx::TextAreaWithOneWildcard volInput2;
    touchgfx::TextAreaWithOneWildcard volInput3;
    touchgfx::TextArea textArea8;
    touchgfx::ImageButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  applyCalibration;
    touchgfx::TextArea textArea9;
    touchgfx::TextArea textArea9_1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t SPVOL_SIZE = 3;
    touchgfx::Unicode::UnicodeChar SPVolBuffer[SPVOL_SIZE];
    static const uint16_t TIMEETABUFFER1_SIZE = 3;
    touchgfx::Unicode::UnicodeChar timeETABuffer1[TIMEETABUFFER1_SIZE];
    static const uint16_t TIMEETABUFFER2_SIZE = 3;
    touchgfx::Unicode::UnicodeChar timeETABuffer2[TIMEETABUFFER2_SIZE];
    static const uint16_t TIMEELAPSEDBUFFER1_SIZE = 3;
    touchgfx::Unicode::UnicodeChar timeElapsedBuffer1[TIMEELAPSEDBUFFER1_SIZE];
    static const uint16_t TIMEELAPSEDBUFFER2_SIZE = 3;
    touchgfx::Unicode::UnicodeChar timeElapsedBuffer2[TIMEELAPSEDBUFFER2_SIZE];
    static const uint16_t HOURSELAPSED_SIZE = 3;
    touchgfx::Unicode::UnicodeChar hoursElapsedBuffer[HOURSELAPSED_SIZE];
    static const uint16_t HOURSETA_SIZE = 3;
    touchgfx::Unicode::UnicodeChar hoursETABuffer[HOURSETA_SIZE];
    static const uint16_t CURRENTVOL_SIZE = 5;
    touchgfx::Unicode::UnicodeChar currentVolBuffer[CURRENTVOL_SIZE];
    static const uint16_t VOLINPUT1_SIZE = 2;
    touchgfx::Unicode::UnicodeChar volInput1Buffer[VOLINPUT1_SIZE];
    static const uint16_t VOLINPUT2_SIZE = 2;
    touchgfx::Unicode::UnicodeChar volInput2Buffer[VOLINPUT2_SIZE];
    static const uint16_t VOLINPUT3_SIZE = 2;
    touchgfx::Unicode::UnicodeChar volInput3Buffer[VOLINPUT3_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen3ViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // SCREEN3VIEWBASE_HPP