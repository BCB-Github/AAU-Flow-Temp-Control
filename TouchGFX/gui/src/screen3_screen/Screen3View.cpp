#include <gui/screen3_screen/Screen3View.hpp>
#include <BitmapDatabase.hpp>

int volSetValue = 0;
int limitVolState = 0;
int volInput[3] = {0};
int enableCorrectionState = 0;
float correctionFactor = 1;

extern int flowSetValue;
int timeEstimate = 0;

Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();

    printVolSV();
    setTimeEstimate();
    printInput1();
    printInput2();
    printInput3();
    printFactor();
    if (limitVolState == 1)
    {
	    toggleVol.setBitmaps(Bitmap(BITMAP_ENABLED_ID), Bitmap(BITMAP_ENABLED_ID));
	    toggleVol.setWidthHeight(30, 30);
		toggleVol.invalidate();
    }
    if (enableCorrectionState == 1)
    {
	    applyCalibration.setBitmaps(Bitmap(BITMAP_ENABLED_ID), Bitmap(BITMAP_ENABLED_ID));
	    applyCalibration.setWidthHeight(30, 30);
	    applyCalibration.invalidate();
    }
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::incrementVol()
{
	if (volSetValue !=100) {
		volSetValue++;
		printVolSV();
	}

}

void Screen3View::decrementVol()
{
	if (volSetValue != 0) {
		volSetValue--;
		if ((volSetValue == 9) | (volSetValue == 99))
		{ box1.invalidate(); }
		printVolSV();
	}
}

void Screen3View::limitVol()
{
	if (limitVolState == 0)
	{
	    toggleVol.setBitmaps(Bitmap(BITMAP_ENABLED_ID), Bitmap(BITMAP_ENABLED_ID));
	    toggleVol.setWidthHeight(30, 30);
		toggleVol.invalidate();
		limitVolState = 1;

	} else {
	    toggleVol.setBitmaps(Bitmap(BITMAP_DISABLED_ID), Bitmap(BITMAP_DISABLED_ID));
	    toggleVol.setWidthHeight(30, 30);
		toggleVol.invalidate();
		limitVolState = 0;
	}
}

void Screen3View::printVolSV()
{
	if (volSetValue < 10)
	{
		SPVol.setXY(28, 62);
	}	else {
		SPVol.setXY(21, 62);
	}
	Unicode::snprintf(SPVolBuffer, SPVOL_SIZE, "%d", volSetValue);
	SPVol.resizeToCurrentText();
	SPVol.invalidate();
}

void Screen3View::updateGraphVol(float DP)
{
	graphVol.addDataPoint(DP);
	Unicode::snprintfFloat(currentVolBuffer, CURRENTVOL_SIZE, "%.2f", DP);
	currentVol.resizeToCurrentText();
	currentVol.invalidate();
	box1.invalidate();
}

void Screen3View::updateVol(float Vol)
{
	Unicode::snprintfFloat(currentVolBuffer, CURRENTVOL_SIZE, "%.2f", Vol);
	currentVol.resizeToCurrentText();
	currentVol.invalidate();
	box1.invalidate();
	calcETA(Vol);
	setTimeEstimate();
}

void Screen3View::updateTimeS3(float time) {
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
	//box1.invalidate();
}

void Screen3View::setTimeEstimate()
{
	int hours = timeEstimate/3600;
	int minutes = timeEstimate/60 - hours*60;
	int seconds = timeEstimate%60;

	if (hours<10) {
		Unicode::snprintf(hoursETABuffer, HOURSETA_SIZE, "0%d", hours);
	} else {
		Unicode::snprintf(hoursETABuffer, HOURSETA_SIZE, "%d", hours);
	}

	if (minutes<10) {
		Unicode::snprintf(timeETABuffer1, TIMEETABUFFER1_SIZE, "0%d", minutes);
	} else {
		Unicode::snprintf(timeETABuffer1, TIMEETABUFFER1_SIZE, "%d", minutes);
	}

	if (seconds<10) {
		Unicode::snprintf(timeETABuffer2, TIMEETABUFFER2_SIZE, "0%d", seconds);
	} else {
		Unicode::snprintf(timeETABuffer2, TIMEETABUFFER2_SIZE, "%d", seconds);
	}
	hoursETA.invalidate();
	timeETA.invalidate();
}

void Screen3View::calcETA(float Vol)
{
	timeEstimate = (int)(((float)volSetValue-Vol)*60*1000 / (float)flowSetValue);
}

void Screen3View::incrementDigit1()
{
	if (volInput[0] != 9) {
		volInput[0]++;
		printInput1();
	}
}

void Screen3View::decrementDigit1()
{
	if (volInput[0] != 0) {
		volInput[0]--;
		printInput1();
	}
}

void Screen3View::incrementDigit2()
{
	if (volInput[1] != 9) {
		volInput[1]++;
		printInput2();
	}
}

void Screen3View::decrementDigit2()
{
	if (volInput[1] != 0) {
		volInput[1]--;
		printInput2();
	}
}

void Screen3View::incrementDigit3()
{
	if (volInput[2] != 9) {
		volInput[2]++;
		printInput3();
	}
}

void Screen3View::decrementDigit3()
{
	if (volInput[2] != 0) {
		volInput[2]--;
		printInput3();
	}
}

void Screen3View::printInput1()
{
	Unicode::snprintf(volInput1Buffer, VOLINPUT1_SIZE, "%d", volInput[0]);
	volInput1.resizeToCurrentText();
	volInput1.invalidate();
}

void Screen3View::printInput2()
{
	Unicode::snprintf(volInput2Buffer, VOLINPUT2_SIZE, "%d", volInput[1]);
	volInput2.resizeToCurrentText();
	volInput2.invalidate();
}

void Screen3View::printInput3()
{
	Unicode::snprintf(volInput3Buffer, VOLINPUT3_SIZE, "%d", volInput[2]);
	volInput3.resizeToCurrentText();
	volInput3.invalidate();
}

void Screen3View::enableCorrection()
{
	if (enableCorrectionState == 0)
	{
		applyCalibration.setBitmaps(Bitmap(BITMAP_ENABLED_ID), Bitmap(BITMAP_ENABLED_ID));
		applyCalibration.setWidthHeight(30, 30);
		applyCalibration.invalidate();
		enableCorrectionState = 1;
		float volMeasured = volInput[0]*10 + volInput[1] + volInput[2]*0.1;
		if (volSetValue != 0) {
			correctionFactor = volMeasured/volSetValue;
		}
		printFactor();

	} else {
		applyCalibration.setBitmaps(Bitmap(BITMAP_DISABLED_ID), Bitmap(BITMAP_DISABLED_ID));
		applyCalibration.setWidthHeight(30, 30);
		applyCalibration.invalidate();
		enableCorrectionState = 0;
		correctionFactor = 1;
		printFactor();
	}
}

void Screen3View::printFactor()
{
	Unicode::snprintfFloat(calibrationFactorBuffer, CALIBRATIONFACTOR_SIZE, "%.2f", correctionFactor);
	calibrationFactor.resizeToCurrentText();
	calibrationFactor.invalidate();
}
