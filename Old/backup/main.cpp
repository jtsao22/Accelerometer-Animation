#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QApplication>
#include <Animator.h>
#include <QTabWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QMenuBar>
#include <QMainWindow>

int main(int argc, char ** argv)
{

	QApplication app(argc,argv);

	QMainWindow*  mainWindow =  new QMainWindow;
	mainWindow->resize(1024,768);
	
	//Create big text box for no reason
   QTextEdit* txtEdit = new QTextEdit(mainWindow);
   txtEdit->setReadOnly(1);
   txtEdit->setGeometry(240,45,770,50);
	txtEdit->setFont(QFont("Times",18,QFont::Bold));
	txtEdit->setText("EE180D Animator");
	txtEdit->setAlignment(Qt::AlignCenter);
   txtEdit->show();

	//Create an About message box
	QMessageBox* aboutDialog = new QMessageBox;
	aboutDialog->setText("EE180D Animator was programmed by:\n Matthew Miguel, Jason Tsao, and Vikram Balakrishnan\n using Qt and Coin");
	
	//Create a menu bar
	QMenuBar* menuBar = mainWindow->menuBar();

	//Add a menu for generic stuff
	QMenu* mainMenu = menuBar->addMenu("Animator");
	mainMenu->addAction("Quit",&app,SLOT(quit()));

	//Add a menu for help stuff
	QMenu* helpMenu = menuBar->addMenu("Help");
	helpMenu->addAction("About",aboutDialog,SLOT(exec()));

	menuBar->addMenu(mainMenu);
	menuBar->addMenu(helpMenu);


	//Start the GUI
	SoQt::init(mainWindow);
	
	Animator* gfx = new Animator(mainWindow);

   SoQt::show(mainWindow);
  	SoQt::mainLoop();


	//Clean up time
	delete txtEdit;
	delete aboutDialog;
	delete helpMenu;
	delete mainMenu;
	delete menuBar;
	delete gfx;
	delete mainWindow;
  	SoQt::done();

  	return 0;
}
