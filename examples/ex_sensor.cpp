#include <Inventor/SoDB.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoFieldSensor.h>

// Callback that reports whenever the viewer's position changes.
static void
cameraChangedCB(void *data, SoSensor *)
{
   SoCamera *viewerCamera = (SoCamera *)data;

   SbVec3f cameraPosition = viewerCamera->position.getValue();
   printf("Camera position: (%g,%g,%g)\n",
            cameraPosition[0], cameraPosition[1],
            cameraPosition[2]); 
}

int main(int argc, char **argv)
{
   if (argc != 2) {
      fprintf(stderr, "Usage: %s filename.iv\n", argv[0]);
      exit(1);
   }

   QWidget* myWindow = SoQt::init(argv[0]);
   if (myWindow == NULL) exit(1);

   SoInput inputFile;
   if (inputFile.openFile(argv[1]) == FALSE) {
      fprintf(stderr, "Could not open file %s\n", argv[1]);
      exit(1);
   }
   
   SoSeparator *root = SoDB::readAll(&inputFile);
   root->ref();

   SoQtExaminerViewer *myViewer =
            new SoQtExaminerViewer(myWindow);
   myViewer->setSceneGraph(root);
   myViewer->setTitle("Camera Sensor");
   myViewer->show();

   // Get the camera from the viewer, and attach a 
   // field sensor to its position field:
   SoCamera *camera = myViewer->getCamera();
   SoFieldSensor *mySensor = 
            new SoFieldSensor(cameraChangedCB, camera);
   mySensor->attach(&camera->position);

   SoQt::show(myWindow);
   SoQt::mainLoop();
}
