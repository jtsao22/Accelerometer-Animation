#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/SoOutput.h>

// DEFINES
#define UPPER_ARM_RADIUS 1
#define UPPER_ARM_HEIGHT 3
#define FOREARM_RADIUS 1
#define FOREARM_HEIGHT 3

int main(int argc, char ** argv)
{
	SoQt::init(argc,argv,argv[0]);

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

  //Write scene graph to outputfile

  SoOutput out;
  out.openFile("scene_graph.vi");
  SoWriteAction writeAction(&out);
  //writeAction.getOutput()->setBinary(TRUE); //Default is FALSE
  writeAction.apply(arm);
  out.closeFile();

  arm->unref();
//  SoQt::done();
  return 0;
}
