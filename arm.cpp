#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoRotation.h>
#include <QPushButton>
#include <QApplication>
#include <QFont>
#include <QWidget>
#include <QSlider>
#include <QLCDNumber>


// DEFINES

#define UPPER_ARM_RADIUS 1
#define UPPER_ARM_HEIGHT 3
#define FOREARM_RADIUS 1
#define FOREARM_HEIGHT 3

int main(int argc, char ** argv)
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

  // Arm node
  
  SoSeparator * arm = new SoSeparator;
  arm->ref();

  // Define Forearm 
 
  SoTransform *forearm_transform = new SoTransform;
  forearm_transform->translation.setValue(0, 0, 0.0);
  
  SoCylinder *forearm_cylinder = new SoCylinder;
  forearm_cylinder->radius = FOREARM_RADIUS;
  forearm_cylinder->height = FOREARM_HEIGHT;

  // Define Upper Arm
  
  SoTransform *upper_arm_transform = new SoTransform;
  upper_arm_transform->translation.setValue(0,5, 0.0);
  
  SoCylinder *upper_arm_cylinder = new SoCylinder;
  upper_arm_cylinder->radius = UPPER_ARM_RADIUS;
  upper_arm_cylinder->height = UPPER_ARM_HEIGHT;
 
  // Define Elbow joint
  
  SoTransform *elbow_transform = new SoTransform;
  elbow_transform->translation.setValue(0, -2.5, 0);
  elbow_transform->scaleFactor.setValue(1.2, 1.2, 1.2);
  //elbow_transform->rotation.setValue(k

  SoMaterial *silver = new SoMaterial;
  silver->ambientColor.setValue(.2, .2, .2);
  silver->diffuseColor.setValue(.6, .6, .6);
  silver->specularColor.setValue(.5, .5, .5);
  silver->shininess = .5;

  SoSphere *elbow_sphere = new SoSphere;

  // Define Shoulder joint
  
  SoTransform *shoulder_transform = new SoTransform;
  shoulder_transform->translation.setValue(0, 4.5, 0);
  shoulder_transform->scaleFactor.setValue(1.2, 1.2, 1.2);

  SoSphere *shoulder_sphere = new SoSphere;
  
  // Combine forearm and upper arm into arm
  arm->addChild(forearm_transform);
  arm->addChild(forearm_cylinder);
  arm->addChild(upper_arm_transform);
  arm->addChild(upper_arm_cylinder);

  // Add joints
  arm->addChild(elbow_transform);
  arm->addChild(silver);
  arm->addChild(elbow_sphere);
  arm->addChild(shoulder_transform);
  arm->addChild(shoulder_sphere);

  SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(gfx);
  eviewer->setSceneGraph(arm);
  eviewer->show();

  mainWindow->show();

  SoQt::mainLoop();

  delete eviewer;
  arm->unref();
  delete gfx;
  delete mainWindow;
  SoQt::done();

  return 0;
}
