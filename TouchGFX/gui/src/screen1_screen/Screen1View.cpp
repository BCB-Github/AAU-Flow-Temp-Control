#include <gui/screen1_screen/Screen1View.hpp>

int i = 1;

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

/* The following functions update present and setpoint values of Temperature and Flow on Screen 1, also total flow */
void Screen1View::updateTempSV(int newVal)
{
	Unicode::snprintf(SPTempBuffer, SPTEMP_SIZE, "%d", newVal);
	SPTemp.resizeToCurrentText();
	SPTemp.invalidate();
	background.invalidate();
}

void Screen1View::updateFlowSV(int newVal)
{
	Unicode::snprintf(SPFlowBuffer, SPFLOW_SIZE, "%d", newVal);
	SPFlow.resizeToCurrentText();
	SPFlow.invalidate();
	background.invalidate();
}

void Screen1View::updateTempPV(float newVal)
{
	Unicode::snprintfFloat(nowTempBuffer, NOWTEMP_SIZE, "%f", newVal);
	nowTemp.resizeToCurrentText();
	nowTemp.invalidate();
	background.invalidate();
}

void Screen1View::updateFlowPV(float newVal)
{
	Unicode::snprintfFloat(nowFlowBuffer, NOWFLOW_SIZE, "%f", newVal);
	nowFlow.resizeToCurrentText();
	nowFlow.invalidate();
	background.invalidate();
}

void Screen1View::updateTotalFlow(float newVal)
{
	Unicode::snprintfFloat(nowVolBuffer, NOWVOL_SIZE, "%f", newVal);
	nowVol.resizeToCurrentText();
	nowVol.invalidate();
	background.invalidate();
}

/* The next functions update the graphs */
void Screen1View::updateGraphTemp(int DP)
{
	graphTemp.addDataPoint(DP);
}

void Screen1View::updateGraphFlow(int DP)
{
	graphFlow.addDataPoint(DP);
}

/* The following functions are called from the up/down buttons */

void Screen1View::incrementTemp()
{
	presenter->askForTempUp();
}

void Screen1View::decrementTemp()
{
	presenter->askForTempDown();
}

void Screen1View::incrementFlow()
{
	presenter->askForFlowUp();
}

void Screen1View::decrementFlow()
{
	presenter->askForFlowDown();
}

/* This function is used to animate the progress circle */
void Screen1View::running()
{
	int currentValue = circleProgress.getValue();

	if (currentValue == 100)
	{
		circleProgress.setStartEndAngle(0,-360);
		i = -1;
	}
	if (currentValue == 0)
	{
		circleProgress.setStartEndAngle(0,360);
		i = 1;
	}

	circleProgress.setValue(currentValue+i);
}
