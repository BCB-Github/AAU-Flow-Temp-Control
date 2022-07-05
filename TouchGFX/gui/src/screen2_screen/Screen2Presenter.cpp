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

<<<<<<< HEAD
void Screen2Presenter::updateTempWildcard(float temp)
{
	view.updateTempWildcard(temp); // Give the view the analog value
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

void Screen2Presenter::askForDutyUp()
{
	model->increaseDuty();
}

void Screen2Presenter::askForDutyDown()
{
	model->decreaseDuty();
}

=======
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

void Screen2Presenter::askForDutyUp()
{
	model->increaseDuty();
}

void Screen2Presenter::askForDutyDown()
{
	model->decreaseDuty();
}
>>>>>>> refs/remotes/origin/master
