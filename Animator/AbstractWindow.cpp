#include <AbstractWindow.h>

//AbstractWindow
AbstractWindow::AbstractWindow(Animator* newGfx, QString newLabel)
{
	gfx = newGfx;
	label = newLabel;
}

AbstractWindow::~AbstractWindow(){}

QString AbstractWindow::getLabel()
{
	return label;
}
