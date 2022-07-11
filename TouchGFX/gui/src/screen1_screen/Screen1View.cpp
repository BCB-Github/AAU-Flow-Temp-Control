#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>

/* Variables to store the Set Value of volume, temp and flow */
int volSV = 0;
int tempSV = 20;
int flowSV = 700;

/* Variables to store the state of the pause/stop/enable buttons */
int limitVolState = 0;
int tempStartState = 0;
int tempStopState = 0;
int flowStartState = 0;
int flowStopState = 0;

int i = 1; // integer to animate circle progress

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    printTempSV();
    printFlowSV();
    printVolSV();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

/* The following functions update present and setpoint values of Temperature and Flow on Screen 1, also total flow */
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

/* The functions update the graphs */
void Screen1View::updateGraphTemp(float DP)
{
	graphTemp.addDataPoint(DP);
}

void Screen1View::updateGraphFlow(float DP)
{
	graphFlow.addDataPoint(DP);
}

/* The following functions are called from buttons on the screen */

void Screen1View::incrementTemp()
{
	if (tempSV != 100) {
		tempSV++;
		printTempSV();
	}
}

void Screen1View::decrementTemp()
{
	if (tempSV != 0) {
		tempSV--;
		if ((tempSV == 9) | (tempSV == 99))
		{ background.invalidate(); }
		printTempSV();
	}
}

void Screen1View::incrementFlow()
{
	if (flowSV != 10000) {
		flowSV += 100;
		printFlowSV();
	}
}

void Screen1View::decrementFlow()
{
	if (flowSV != 0) {
	flowSV -= 100;
	if ((flowSV == 900) | (flowSV == 9900))
	{ background.invalidate(); }
	printFlowSV();
	}
}

void Screen1View::incrementVol()
{
	if (volSV !=100) {
		volSV++;
		printVolSV();
	}
}

void Screen1View::decrementVol()
{
	if (volSV != 0) {
		volSV--;
		if ((volSV == 9) | (volSV == 99))
		{ background.invalidate(); }
		printVolSV();
	}
}

void Screen1View::startPauseTempControl()
{
	if (tempStartState == 0)
	{
		startPauseTemp.setBitmaps(Bitmap(BITMAP_PAUSE_ID), Bitmap(BITMAP_PAUSE_ID));
		startPauseTemp.setPosition(443, 42, 30, 30);
		startPauseTemp.invalidate();
		tempStartState = 1;

	    stopTemp.setBitmaps(Bitmap(BITMAP_STOP_ID), Bitmap(BITMAP_STOP_ID));
	    stopTemp.setPosition(443, 89, 30, 30);
	    stopTemp.invalidate();
	    tempStopState = 1;
	} else {
		startPauseTemp.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
		startPauseTemp.setPosition(443, 42, 30, 30);
		startPauseTemp.invalidate();
		tempStartState = 0;
	}
}

void Screen1View::stopTempControl()
{
	if (tempStopState == 1)
	{
		tempStartState = 0;
		startPauseTemp.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
		startPauseTemp.setPosition(443, 42, 30, 30);
		startPauseTemp.invalidate();
	    stopTemp.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
	    stopTemp.setPosition(443, 89, 30, 30);
	    stopTemp.invalidate();
	}
}

void Screen1View::startPauseFlowControl()
{
	if (flowStartState == 0)
	{
		startPauseFlow.setBitmaps(Bitmap(BITMAP_PAUSE_ID), Bitmap(BITMAP_PAUSE_ID));
		startPauseFlow.setPosition(443, 170, 30, 30);
		startPauseFlow.invalidate();
		flowStartState = 1;

	    stopFlow.setBitmaps(Bitmap(BITMAP_STOP_ID), Bitmap(BITMAP_STOP_ID));
	    stopFlow.setPosition(443, 217, 30, 30);
	    stopFlow.invalidate();
	    flowStopState = 1;
	} else {
		startPauseFlow.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
		startPauseFlow.setPosition(443, 170, 30, 30);
		startPauseFlow.invalidate();
		flowStartState = 0;
	}
}

void Screen1View::stopFlowControl()
{
	if (flowStopState == 1)
	{
		flowStartState = 0;
		startPauseFlow.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
		startPauseFlow.setPosition(443, 170, 30, 30);
		startPauseFlow.invalidate();
		stopFlow.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
		stopFlow.setPosition(443, 217, 30, 30);
		stopFlow.invalidate();
	}
}

void Screen1View::limitVol()
{
	if (limitVolState == 0)
	{
	    toggleVol.setBitmaps(Bitmap(BITMAP_ENABLED_ID), Bitmap(BITMAP_ENABLED_ID));
	    toggleVol.setPosition(226, 195, 30, 30);
		toggleVol.invalidate();
		limitVolState = 1;

	} else {
	    toggleVol.setBitmaps(Bitmap(BITMAP_DISABLED_ID), Bitmap(BITMAP_DISABLED_ID));
	    toggleVol.setPosition(226, 195, 30, 30);
		toggleVol.invalidate();
		limitVolState = 0;
	}
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

void Screen1View::printTempSV()
{
	if (tempSV < 10)
	{
		SPTemp.setXY(377, 70);
	}	else {
		SPTemp.setXY(370, 70);
	}
	Unicode::snprintf(SPTempBuffer, SPTEMP_SIZE, "%d", tempSV);
	SPTemp.resizeToCurrentText();
	SPTemp.invalidate();
}

void Screen1View::printFlowSV()
{
	if (flowSV < 1000)
	{
		SPFlow.setXY(380, 189);
	}	else {
		SPFlow.setXY(374, 189);
	}
	Unicode::snprintf(SPFlowBuffer, SPFLOW_SIZE, "%d", flowSV);
	SPFlow.resizeToCurrentText();
	SPFlow.invalidate();
}

void Screen1View::printVolSV()
{
	if (volSV < 10)
	{
		SPVol.setXY(168, 198);
	}	else {
		SPVol.setXY(162, 198);
	}
	Unicode::snprintf(SPVolBuffer, SPVOL_SIZE, "%d", volSV);
	SPVol.resizeToCurrentText();
	SPVol.invalidate();
}
