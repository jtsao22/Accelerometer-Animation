#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoSeparator.h>

int main(int , char **argv)
{
   // Initialize Inventor and Qt
   QWidget* myWindow = SoQt::init(argv[0]);  
   if (myWindow == NULL) exit(1);     

   SoSeparator *root = new SoSeparator;
   root->ref();
   SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
   root->addChild(myCamera);
   root->addChild(new SoDirectionalLight);

   // This transformation is modified to rotate the cone
   SoRotationXYZ *myRotXYZ = new SoRotationXYZ;
   root->addChild(myRotXYZ);

   SoMaterial *myMaterial = new SoMaterial;
   myMaterial->diffuseColor.setValue(1.0, 0.0, 0.0);   // Red
   root->addChild(myMaterial);
   root->addChild(new SoCone);

   // An engine rotates the object. The output of myCounter 
   // is the time in seconds since the program started.
   // Connect this output to the angle field of myRotXYZ
   myRotXYZ->axis = SoRotationXYZ::X;     // rotate about X axis
   SoElapsedTime *myCounter = new SoElapsedTime;
   myRotXYZ->angle.connectFrom(&myCounter->timeOut);

   SoQtRenderArea *myRenderArea = new SoQtRenderArea(myWindow);
   myCamera->viewAll(root, myRenderArea->getViewportRegion());
   myRenderArea->setSceneGraph(root);
   myRenderArea->setTitle("Engine Spin");
   myRenderArea->show();

   SoQt::show(myWindow);
   SoQt::mainLoop();
}
