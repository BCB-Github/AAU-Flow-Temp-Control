#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>

/* Variables to store the Set Value of volume, temp and flow */
int volSetValue = 0;
int tempSetValue = 20;
int flowSetValue = 700;

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

    setTempIcons();
    setFlowIcons();

    if (limitVolState == 1)
    {
	    toggleVol.setBitmaps(Bitmap(BITMAP_ENABLED_ID), Bitmap(BITMAP_ENABLED_ID));
	    toggleVol.setPosition(226, 195, 30, 30);
		toggleVol.invalidate();
    }

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
	Unicode::snprintfFloat(nowVolBuffer, NOWVOL_SIZE, "%.2f", newVal);
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
	if (tempSetValue != 100) {
		tempSetValue++;
		printTempSV();
	}
}

void Screen1View::decrementTemp()
{
	if (tempSetValue != 0) {
		tempSetValue--;
		if ((tempSetValue == 9) | (tempSetValue == 99))
		{ background.invalidate(); }
		printTempSV();
	}
}

void Screen1View::incrementFlow()
{
	if (flowSetValue != 10000) {
		flowSetValue += 100;
		printFlowSV();
	}
}

void Screen1View::decrementFlow()
{
	if (flowSetValue != 0) {
	flowSetValue -= 100;
	if ((flowSetValue == 900) | (flowSetValue == 9900))
	{ background.invalidate(); }
	printFlowSV();
	}
}

void Screen1View::incrementVol()
{
	if (volSetValue !=100) {
		volSetValue++;
		printVolSV();
	}
}

void Screen1View::decrementVol()
{
	if (volSetValue != 0) {
		volSetValue--;
		if ((volSetValue == 9) | (volSetValue == 99))
		{ background.invalidate(); }
		printVolSV();
	}
}

void Screen1View::startPauseTempControl()
{
	if (tempStartState == 0)
	{
		tempStartState = 1;
	    tempStopState = 1;
	} else {
		tempStartState = 0;
	}
	setTempIcons();
}

void Screen1View::stopTempControl()
{
	if (tempStopState == 1)
	{
		tempStartState = 0;
	    tempStopState = 0;
	}
	setTempIcons();
}

void Screen1View::startPauseFlowControl()
{
	if (flowStartState == 0)
	{
		flowStartState = 1;
	    flowStopState = 1;
	} else {
		flowStartState = 0;
	}
	setFlowIcons();
}

void Screen1View::stopFlowControl()
{
	if (flowStopState == 1)
	{
		flowStartState = 0;
		flowStopState = 0;
	}
	setFlowIcons();
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
	if (tempSetValue < 10)
	{
		SPTemp.setXY(377, 70);
	}	else {
		SPTemp.setXY(370, 70);
	}
	Unicode::snprintf(SPTempBuffer, SPTEMP_SIZE, "%d", tempSetValue);
	SPTemp.resizeToCurrentText();
	SPTemp.invalidate();
}

void Screen1View::printFlowSV()
{
	if (flowSetValue < 1000)
	{
		SPFlow.setXY(380, 189);
	}	else {
		SPFlow.setXY(374, 189);
	}
	Unicode::snprintf(SPFlowBuffer, SPFLOW_SIZE, "%d", flowSetValue);
	SPFlow.resizeToCurrentText();
	SPFlow.invalidate();
}

void Screen1View::printVolSV()
{
	if (volSetValue < 10)
	{
		SPVol.setXY(168, 198);
	}	else {
		SPVol.setXY(162, 198);
	}
	Unicode::snprintf(SPVolBuffer, SPVOL_SIZE, "%d", volSetValue);
	SPVol.resizeToCurrentText();
	SPVol.invalidate();
}



void Screen1View::setTempIcons()
{
	int16_t xyStop[2] = {stopTemp.getX(), stopTemp.getY()};
	int16_t xyStart[2] = {startPauseTemp.getX(), startPauseTemp.getY()};

    if (tempStopState == 1) {
    	stopTemp.setBitmaps(Bitmap(BITMAP_STOP_ID), Bitmap(BITMAP_STOP_ID));
    	stopTemp.setPosition(xyStop[0], xyStop[1], 30, 30);
    	stopTemp.invalidate();
    	} else {
    	    stopTemp.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
    	    stopTemp.setPosition(xyStop[0], xyStop[1], 30, 30);
    	    stopTemp.invalidate();
    	}
    if (tempStartState == 1) {
		startPauseTemp.setBitmaps(Bitmap(BITMAP_PAUSE_ID), Bitmap(BITMAP_PAUSE_ID));
		startPauseTemp.setPosition(xyStart[0], xyStart[1], 30, 30);
		startPauseTemp.invalidate();
    	} else {
    		startPauseTemp.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
    		startPauseTemp.setPosition(xyStart[0], xyStart[1], 30, 30);
    		startPauseTemp.invalidate();
    	}

}

void Screen1View::setFlowIcons()
{
	int16_t xyStop[2] = {stopFlow.getX(), stopFlow.getY()};
	int16_t xyStart[2] = {startPauseFlow.getX(), startPauseFlow.getY()};

    if (flowStopState == 1) {
    	stopFlow.setBitmaps(Bitmap(BITMAP_STOP_ID), Bitmap(BITMAP_STOP_ID));
    	stopFlow.setPosition(xyStop[0], xyStop[1], 30, 30);
    	stopFlow.invalidate();
    	} else {
    		stopFlow.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
    		stopFlow.setPosition(xyStop[0], xyStop[1], 30, 30);
    		stopFlow.invalidate();
    	}
    if (flowStartState == 1) {
    	startPauseFlow.setBitmaps(Bitmap(BITMAP_PAUSE_ID), Bitmap(BITMAP_PAUSE_ID));
    	startPauseFlow.setPosition(xyStart[0], xyStart[1], 30, 30);
    	startPauseFlow.invalidate();
    	} else {
    		startPauseFlow.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
    		startPauseFlow.setPosition(xyStart[0], xyStart[1], 30, 30);
    		startPauseFlow.invalidate();
    	}

}

void Screen1View::resetFlowIcons()
{
	int16_t xyStop[2] = {stopFlow.getX(), stopFlow.getY()};
	int16_t xyStart[2] = {startPauseFlow.getX(), startPauseFlow.getY()};

	startPauseFlow.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
	startPauseFlow.setPosition(xyStart[0], xyStart[1], 30, 30);
	startPauseFlow.invalidate();
	stopFlow.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
	stopFlow.setPosition(xyStop[0], xyStop[1], 30, 30);
	stopFlow.invalidate();
	flowStartState = 0;
}
