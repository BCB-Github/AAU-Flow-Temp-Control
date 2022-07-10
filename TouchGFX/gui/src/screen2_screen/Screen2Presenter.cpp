#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{

}

void Screen2Presenter::deactivate()
{

}
void Screen2Presenter::updateTempWildcard(float temp)
{
	//view.updateTempWildcard(temp); // Give the view the analog value
}

void Screen2Presenter::setPVTempS2(float newTempPV)
{
	view.updateTempPVS2(newTempPV);
}

void Screen2Presenter::setPVFlowS2(float newFlowPV)
{
	view.updateFlowPVS2(newFlowPV);
}

void Screen2Presenter::setPressureS2(float newPressure)
{
	view.updatePressureS2(newPressure);
}

void Screen2Presenter::setRpmS2(float newRpm)
{
	view.updateRpmS2(newRpm);
}

void Screen2Presenter::setTestVal1(float newTestVal1)
{
	view.updateTestVal1(newTestVal1);
}

void Screen2Presenter::setTestVal2(float newTestVal2)
{
	view.updateTestVal2(newTestVal2);
}

void Screen2Presenter::setDutyCycle(int newDutyCycle)
{
	view.updateDutyCycle(newDutyCycle);
}


