/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen2ViewBase::Screen2ViewBase() :
    flexButtonCallback(this, &Screen2ViewBase::flexButtonCallbackHandler)
{

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 480, 272);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    flexButton1.setBoxWithBorderPosition(0, 0, 124, 27);
    flexButton1.setBorderSize(5);
    flexButton1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(1, 68, 135), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButton1.setPosition(24, 245, 124, 27);
    flexButton1.setAction(flexButtonCallback);

    textArea1.setXY(41, 249);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_OWHL));

    add(__background);
    add(box1);
    add(flexButton1);
    add(textArea1);
}

void Screen2ViewBase::setupScreen()
{

}

void Screen2ViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &flexButton1)
    {
        //Interaction1
        //When flexButton1 clicked change screen to Screen1
        //Go to Screen1 with screen transition towards West
        application().gotoScreen1ScreenSlideTransitionWest();
    }
}
