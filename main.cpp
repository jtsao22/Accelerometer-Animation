#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QPushButton>
#include <QApplication>
#include <QFont>
#include <QWidget>
#include <QSlider>
#include <QLCDNumber>
#include <Animator.h>
//#include <QFileDialog>




SoSeparator* defineGraph();

int main(int argc, char ** argv)
{

  QApplication app(argc,argv);

  QWidget*  mainWindow =  new QWidget;
  mainWindow->resize(800,600);
  SoQt::init(mainWindow);


  
	//Create sliders and LCD's
	QSlider* sldAngle[4];
	QLCDNumber* lcdAngle[4];
	for(int i = 0; i<4; i++)
	{
 		sldAngle[i]= new QSlider(Qt::Horizontal,mainWindow);
  		sldAngle[i]->setRange(0,360);
 		sldAngle[i]->setValue(0);
  		sldAngle[i]->setGeometry(10,100*i+60,180,40);
  		lcdAngle[i] = new QLCDNumber(3,mainWindow);
  		lcdAngle[i]->setGeometry(10,100*i+10,180,40);
		QObject::connect(sldAngle[i],SIGNAL(valueChanged(int)),lcdAngle[i],SLOT(display(int)));
	}
	Animator* gfx = new Animator(mainWindow);
  	gfx->setGeometry(200,10,540,380);
	QObject::connect(sldAngle[0],SIGNAL(valueChanged(int)),gfx,SLOT(setAngle1(int)));
	QObject::connect(sldAngle[1],SIGNAL(valueChanged(int)),gfx,SLOT(setAngle2(int)));
	QObject::connect(sldAngle[2],SIGNAL(valueChanged(int)),gfx,SLOT(setAngle3(int)));
	QObject::connect(sldAngle[3],SIGNAL(valueChanged(int)),gfx,SLOT(setAngle4(int)));

  //QPushButton* quit = new QPushButton("Quit",mainWindow);
  //quit->setFont(QFont("Times",18,QFont::Bold));
  //quit->setGeometry(10,40,180,40);
  //QObject::connect(quit,SIGNAL(clicked()),&app,SLOT(quit()));

  	mainWindow->show();

  	SoQt::mainLoop();

  	delete gfx;
	for(int i = 0; i < 4; i++)
	{
		delete sldAngle[i];
		delete lcdAngle[i];
	}
  	delete mainWindow;
  	SoQt::done();

  	return 0;
}

