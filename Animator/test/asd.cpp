#include <asd.h>

//asd Constructor: Most likely you do not need to modify this
asd::asd(Animator * newGfx):AbstractWindow(newGfx,"asdf"){}

//asd Destructor: Delete all dynamically allocated data here
asd::~asd()
{

}

//asd createWindow: Create the Qt here by placing subwidgets as children to the widget pointed to by window
QWidget* asd::createWindow()
{
	//Create asd Tab
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Define widget here

	return window;
}
//asd transitionTo: Place code here that should run every time the user switches to this tab
void asd::transitionTo()
{

}

//asd transitionFrom: Place code here that should run every time the user switches away from this tab
void asd::transitionFrom()
{

}