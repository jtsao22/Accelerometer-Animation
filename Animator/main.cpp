#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QApplication>
#include <Animator.h>
#include <QTabWidget>

int main(int argc, char ** argv)
{

	QApplication app(argc,argv);

	QWidget*  mainWindow =  new QWidget;
	mainWindow->resize(1024,768);
	SoQt::init(mainWindow);
	
	Animator* gfx = new Animator(mainWindow);
//	gfx->show();

   SoQt::show(mainWindow);
  	SoQt::mainLoop();

	delete gfx;
	delete mainWindow;
  	SoQt::done();

  	return 0;
}
