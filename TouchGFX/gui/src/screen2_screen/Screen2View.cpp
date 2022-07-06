#include <gui/screen2_screen/Screen2View.hpp>
#include "string.h"

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}
void Screen2View::updateTempWildcard(float temp) {
	//memset(&adcFrameRateTexAreaBuffer, 0, ADCFRAMERATETEXAREA_SIZE);
	//Unicode::snprintfFloat(adcFrameRateTexAreaBuffer, ADCFRAMERATETEXAREA_SIZE, "%f", value);

 //   touchgfx::TextAreaWithOneWildcard textArea3;
/*
     static const uint16_t TEXTAREA2_SIZE = 6;
   // touchgfx::Unicode::UnicodeChar textArea3Buffer[TEXTAREA3_SIZE];
    memset(&textArea2Buffer, 0, TEXTAREA2_SIZE);
	Unicode::snprintfFloat(textArea2Buffer, TEXTAREA2_SIZE, "%f", temp);
    textArea2.setWildcard(textArea2Buffer);
	textArea2.resizeToCurrentText();
	textArea2.invalidate();
	*/

}


void Screen2View::updateTestVal1(float newVal1)
{
	//Unicode::snprintfFloat(testVal1Buffer, TESTVAL1_SIZE, "%f", newVal1);
	//testVal1.resizeToCurrentText();
	//testVal1.invalidate();
    //static const uint16_t TEXTAREA2_SIZE = 6;
  // touchgfx::Unicode::UnicodeChar textArea3Buffer[TEXTAREA3_SIZE];
    //memset(&testVal1Buffer, 0, TESTVAL1_SIZE);
	Unicode::snprintfFloat(testVal1Buffer, TESTVAL1_SIZE, "%.2f", newVal1);
	//testVal1.setWildcard(testVal1Buffer);
    testVal1.resizeToCurrentText();
	testVal1.invalidate();
	box1.invalidate();

}

void Screen2View::updateTestVal2(uint16_t newVal2)
{
	Unicode::snprintfFloat(testVal2Buffer, TESTVAL2_SIZE, "%5.f", newVal2);
	testVal2.resizeToCurrentText();
	testVal2.invalidate();
	box1.invalidate();
}

void Screen2View::updateDutyCycle(int newDuty)
{
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", newDuty);
	textArea2.resizeToCurrentText();
	textArea2.invalidate();
	box1.invalidate();
}

void Screen2View::incrementDuty()
{
	presenter->askForDutyUp();
}

void Screen2View::decrementDuty()
{
	presenter->askForDutyDown();
}


