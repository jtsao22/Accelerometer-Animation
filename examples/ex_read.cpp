#include<Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include<Inventor/SoInput.h>
#include<Inventor/SoDB.h>
#include<Inventor/nodes/SoSeparator.h>
#include<stdlib.h>
#include <QPushButton>
#include <QApplication>
#include <QFont>
#include <QWidget>
#include <QSlider>
#include <QLCDNumber>
#include <QFileDialog>
/*
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoRotation.h>
*/

int main(int argc, char** argv)
{
  QApplication app(argc,argv);
  QWidget*  mainWindow =  new QWidget;
  mainWindow->resize(800,600);

  SoQt::init(mainWindow);


  QPushButton* quit = new QPushButton("Quit",mainWindow);
  quit->setFont(QFont("Times",18,QFont::Bold));
  quit->setGeometry(10,40,180,40);
  QObject::connect(quit,SIGNAL(clicked()),&app,SLOT(quit()));
  
  QSlider* slider = new QSlider(Qt::Horizontal,mainWindow);
  slider->setRange(0,99);
  slider->setValue(0);
  slider->setGeometry(10,100,180,40);

  QLCDNumber* lcd = new QLCDNumber(2,mainWindow);
  QObject::connect(slider,SIGNAL(valueChanged(int)),lcd,SLOT(display(int)));
  lcd->setGeometry(10,160,180,40);


  QWidget* gfx = new QWidget(mainWindow);
  gfx->setGeometry(200,10,540,380);
 
  QString fileName = QFileDialog::getOpenFileName(mainWindow, QObject::tr("Select Scene Graph"),
                                                ".",
                                                QObject::tr("Open Inventor Scene Graphs (*.vi)"));



  //Read data from file

   SoInput sceneInput;
   if (!sceneInput.openFile(fileName.toAscii().data()))
	{
		fprintf(stderr,"Cannot open file\n");
      exit(1);
	}

   SoSeparator* root = SoDB::readAll(&sceneInput);
   if (root == NULL)
	{
		fprintf(stderr,"Problem reading file\n");
		exit(1);
	}
	root->ref();
	sceneInput.closeFile();
  //Got data from file


  SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(gfx);
  eviewer->setSceneGraph(root);
  eviewer->show();

  mainWindow->show();

  SoQt::mainLoop();

  root->unref();
  delete eviewer;
  delete quit;
  delete slider;
  delete lcd;
  delete gfx;
  delete mainWindow;
  //SoQt::done();
  return 0;
}
