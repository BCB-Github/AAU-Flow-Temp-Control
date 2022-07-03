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

void Screen1Presenter::setSVTemp(int newTempSV)
{
	view.updateTempSV(newTempSV);
}

void Screen1Presenter::setSVFlow(int newFlowSV)
{
	view.updateFlowSV(newFlowSV);
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

void Screen1Presenter::addDatapointTemp(int newDP)
{
	view.updateGraphTemp(newDP);
}

void Screen1Presenter::addDatapointFlow(int newDP)
{
	view.updateGraphFlow(newDP);
}

void Screen1Presenter::askForTempUp()
{
	model->increaseTemp();
}

void Screen1Presenter::askForTempDown()
{
	model->decreaseTemp();
}

void Screen1Presenter::askForFlowUp()
{
	model->increaseFlow();
}

void Screen1Presenter::askForFlowDown()
{
	model->decreaseFlow();
}

void Screen1Presenter::runProgress()
{
	view.running();
}
