#include <gui/screen2_screen/Screen2View.hpp>
#include "string.h"

/* Variable to store duty cycle percentage */
int dutyPercent = 0;


Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    printDuty();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::updateTempPVS2(float newTempPV)
{
	Unicode::snprintfFloat(textArea5Buffer, TEXTAREA5_SIZE, "%.2f", newTempPV);
	textArea5.resizeToCurrentText();
	textArea5.invalidate();
	box1.invalidate();
}

void Screen2View::updateFlowPVS2(float newFlowPV)
{
	Unicode::snprintfFloat(textArea3Buffer, TEXTAREA3_SIZE, "%.2f", newFlowPV);
	textArea3.resizeToCurrentText();
	textArea3.invalidate();
	box1.invalidate();
}

void Screen2View::updatePressureS2(float newPressure)
{
	Unicode::snprintfFloat(textArea6Buffer, TEXTAREA6_SIZE, "%.2f", newPressure);
	textArea6.resizeToCurrentText();
	textArea6.invalidate();
	box1.invalidate();
}

void Screen2View::updateRpmS2(float newRpm)
{
	Unicode::snprintfFloat(textArea7Buffer, TEXTAREA7_SIZE, "%.0f", newRpm);
	textArea7.resizeToCurrentText();
	textArea7.invalidate();
	box1.invalidate();
}

void Screen2View::updateTestVal1(float newVal1)
{

	Unicode::snprintfFloat(testVal1Buffer, TESTVAL1_SIZE, "%.2f", newVal1);
    testVal1.resizeToCurrentText();
	testVal1.invalidate();
	box1.invalidate();

}

void Screen2View::updateTestVal2(float newVal2)
{
	Unicode::snprintfFloat(testVal2Buffer, TESTVAL2_SIZE, "%.2f", newVal2);
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
	if (dutyPercent != 100)
	{
		dutyPercent += 5;
		printDuty();
	}
}

void Screen2View::decrementDuty()
{
	if (dutyPercent != 0)
	{
		dutyPercent -= 5;
		if ((dutyPercent == 9) | (dutyPercent == 99))
		{ box1.invalidate(); }
		printDuty();
	}
}

void Screen2View::printDuty()
{
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", dutyPercent);
	textArea2.resizeToCurrentText();
	textArea2.invalidate();
}

