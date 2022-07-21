#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>

/* Variables to store the Set Value of volume, temp and flow */
int tempSetValue = 20;
int flowSetValue = 700;

/* Variables to store the state of the pause/stop/enable buttons */
int enableMotorState = 0;
int tempStartState = 0;
int tempStopState = 0;
int flowStartState = 0;
int flowStopState = 0;
int graphState = 0;

extern int timeEstimate;

extern int volSetValue;
extern int data3DaysFlow[1000];
extern int data3DaysTemp[1000];
extern int daysDataCount;
extern int daysLoops;
extern int data3MinsFlow[1000];
extern int data3MinsTemp[1000];
extern int minsDataCount;
extern int minsLoops;

int i = 1; // integer to animate circle progress

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    printTempSV();
    printFlowSV();

    setTempIcons();
    setFlowIcons();

    if (graphState == 1) {
    	setSpanDays();
    } else {
    	setSpanMinutes();
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

void Screen1View::updateTime(float time)
{
	int hours = (int)time/3600;
	int minutes = (int)time/60 - hours*60;
	int seconds = (int)time % 60;

	if (hours<10) {
		Unicode::snprintf(hoursElapsedBuffer, HOURSELAPSED_SIZE, "0%d", hours);
	} else {
		Unicode::snprintf(hoursElapsedBuffer, HOURSELAPSED_SIZE, "%d", hours);
	}

	if (minutes<10) {
		Unicode::snprintf(timeElapsedBuffer1, TIMEELAPSEDBUFFER1_SIZE, "0%d", minutes);
	} else {
		Unicode::snprintf(timeElapsedBuffer1, TIMEELAPSEDBUFFER1_SIZE, "%d", minutes);
	}

	if (seconds<10) {
		Unicode::snprintf(timeElapsedBuffer2, TIMEELAPSEDBUFFER2_SIZE, "0%d", seconds);
	} else {
		Unicode::snprintf(timeElapsedBuffer2, TIMEELAPSEDBUFFER2_SIZE, "%d", seconds);
	}
	hoursElapsed.resizeToCurrentText();
	hoursElapsed.invalidate();
	timeElapsed.resizeToCurrentText();
	timeElapsed.invalidate();
	//background.invalidate();
}

/* The functions update the graphs */
void Screen1View::updateGraphTemp(float DP)
{
	if (graphState == 0) {
	graphTemp.addDataPoint(DP);
	}
}

void Screen1View::updateGraphFlow(float DP)
{
	if (graphState == 0) {
	graphFlow.addDataPoint(DP);
	}
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
		enableMotorState = 1;
		Unicode::snprintf(sysStateWildcardBuffer, SYSSTATEWILDCARD_SIZE, "Running");
		calcETA();

		presenter->switchMotorState(enableMotorState);
	} else {
		flowStartState = 0;
		Unicode::snprintf(sysStateWildcardBuffer, SYSSTATEWILDCARD_SIZE, "Paused");
	}
	setFlowIcons();
}

void Screen1View::stopFlowControl()
{
	if (flowStopState == 1)
	{
		flowStartState = 0;
		flowStopState = 0;
		enableMotorState = 0;
		Unicode::snprintf(sysStateWildcardBuffer, SYSSTATEWILDCARD_SIZE, "Standby");
		circleProgress.setValue(100);
		presenter->switchMotorState(enableMotorState);
	}
	setFlowIcons();
}



/*void Screen1View::enableMotor()
{

	}
}*/

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





void Screen1View::setTempIcons()
{
	if (tempStopState == 1) {
    	stopTemp.setBitmaps(Bitmap(BITMAP_STOP_ID), Bitmap(BITMAP_STOP_ID));
    	stopTemp.setWidthHeight(30, 30);
    	stopTemp.invalidate();
    	} else {
    	    stopTemp.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
    	    stopTemp.setWidthHeight(30, 30);
    	    stopTemp.invalidate();
    	}
    if (tempStartState == 1) {
		startPauseTemp.setBitmaps(Bitmap(BITMAP_PAUSE_ID), Bitmap(BITMAP_PAUSE_ID));
		startPauseTemp.setWidthHeight(30, 30);
		startPauseTemp.invalidate();
    	} else {
    		startPauseTemp.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
    		startPauseTemp.setWidthHeight(30, 30);
    		startPauseTemp.invalidate();
    	}

}

void Screen1View::setFlowIcons()
{
	if (flowStopState == 1) {
    	stopFlow.setBitmaps(Bitmap(BITMAP_STOP_ID), Bitmap(BITMAP_STOP_ID));
    	stopFlow.setWidthHeight(30, 30);
    	stopFlow.invalidate();
    	} else {
    		stopFlow.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
    		stopFlow.setWidthHeight(30, 30);
    		stopFlow.invalidate();
    	}
    if (flowStartState == 1) {
    	startPauseFlow.setBitmaps(Bitmap(BITMAP_PAUSE_ID), Bitmap(BITMAP_PAUSE_ID));
    	startPauseFlow.setWidthHeight(30, 30);
    	startPauseFlow.invalidate();
    	} else {
    		startPauseFlow.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
    		startPauseFlow.setWidthHeight(30, 30);
    		startPauseFlow.invalidate();
    	}

}

void Screen1View::resetFlowIcons()
{
	startPauseFlow.setBitmaps(Bitmap(BITMAP_START_ID), Bitmap(BITMAP_START_ID));
	startPauseFlow.setWidthHeight(30, 30);
	startPauseFlow.invalidate();
	stopFlow.setBitmaps(Bitmap(BITMAP_STOPDIS_ID), Bitmap(BITMAP_STOPDIS_ID));
	stopFlow.setWidthHeight(30, 30);
	stopFlow.invalidate();
	flowStartState = 0;
}

void Screen1View::setSpanDays()
{
	graphState = 1;
	graphTemp.clear();
	graphTemp.dataCounterReset();
	graphFlow.clear();
	graphFlow.dataCounterReset();
	if (daysLoops == 0) {
		for (int x = 0; x<daysDataCount; x++) {
			graphTemp.addDataPointScaled(data3DaysTemp[x]);
			graphFlow.addDataPoint(data3DaysFlow[x]);
		}
	} else {
		int k = daysDataCount+1;
		for (int y = 0; y<1000; y++) {
			if (k == 1000) {k=0;}
			graphTemp.addDataPointScaled(data3DaysTemp[k]);
			graphFlow.addDataPoint(data3DaysFlow[k]);
			k += 1;
		}
	}
}

void Screen1View::setSpanMinutes()
{
	graphState = 0;
	graphTemp.clear();
	graphTemp.dataCounterReset();
	graphFlow.clear();
	graphFlow.dataCounterReset();
	if (minsLoops == 0) {
		for (int x = 0; x<minsDataCount; x++) {
			graphTemp.addDataPointScaled(data3MinsTemp[x]);
			graphFlow.addDataPoint(data3MinsFlow[x]);
		}
	} else {
		int k = minsDataCount+1;
		for (int y = 0; y<1000; y++) {
			if (k == 1000) {k=0;}
			graphTemp.addDataPointScaled(data3MinsTemp[k]);
			graphFlow.addDataPoint(data3MinsFlow[k]);
			k += 1;
		}
	}
}

void Screen1View::calcETA()
{
	timeEstimate = volSetValue*60*1000 / flowSetValue;
}
