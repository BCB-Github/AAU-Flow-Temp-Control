#include <gui/screen2_screen/Screen2View.hpp>

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

void Screen2View::updateTestVal1(float newVal1)
{
	Unicode::snprintfFloat(testVal1Buffer, TESTVAL1_SIZE, "%f", newVal1);
	testVal1.resizeToCurrentText();
	testVal1.invalidate();
	box1.invalidate();
}

void Screen2View::updateTestVal2(float newVal2)
{
	Unicode::snprintfFloat(testVal2Buffer, TESTVAL2_SIZE, "%f", newVal2);
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
