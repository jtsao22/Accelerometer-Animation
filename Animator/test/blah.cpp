#include <blah.h>

//blah Constructor: Most likely you do not need to modify this
blah::blah(Animator * newGfx):AbstractWindow(newGfx,"wtry"){}

//blah Destructor: Delete all dynamically allocated data here
blah::~blah()
{

}

//blah createWindow: Create the Qt here by placing subwidgets as children to the widget pointed to by window
QWidget* blah::createWindow()
{
	//Create blah Tab
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Define widget here

	return window;
}
//blah transitionTo: Place code here that should run every time the user switches to this tab
void blah::transitionTo()
{

}

//blah transitionFrom: Place code here that should run every time the user switches away from this tab
void blah::transitionFrom()
{

}