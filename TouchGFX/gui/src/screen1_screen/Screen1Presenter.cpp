#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}



void Screen1Presenter::setPVTemp(float newTempPV)
{
	view.updateTempPV(newTempPV);
}

void Screen1Presenter::setPVFlow(float newFlowPV)
{
	view.updateFlowPV(newFlowPV);
}

void Screen1Presenter::setTotalFlow(float newTotalFlow)
{
	view.updateTotalFlow(newTotalFlow);
}

void Screen1Presenter::addDatapointTemp(float newDP)
{
	view.updateGraphTemp(newDP);
}

void Screen1Presenter::addDatapointFlow(float newDP)
{
	view.updateGraphFlow(newDP);
}

void Screen1Presenter::runProgress()
{
	view.running();
}

void Screen1Presenter::switchMotorState(int state)
{
	model->updateMotorState(state);
}

void Screen1Presenter::resetFlowControl()
{
	view.resetFlowIcons();
}
