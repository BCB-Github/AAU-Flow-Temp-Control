#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

Screen3Presenter::Screen3Presenter(Screen3View& v)
    : view(v)
{

}

void Screen3Presenter::activate()
{

}

void Screen3Presenter::deactivate()
{

}

void Screen3Presenter::addDatapointVol(float VolDP)
{
	view.updateGraphVol(VolDP);
	view.updateVol(VolDP);
}

void Screen3Presenter::setTimeElapsedS3(float time)
{
	view.updateTimeS3(time);
}

