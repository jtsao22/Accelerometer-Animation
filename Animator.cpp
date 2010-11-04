#include<Animator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoRotation.h>

// DEFINES

#define UPPERARM_RADIUS 1
#define UPPERARM_LENGTH 3
#define FOREARM_RADIUS 1
#define FOREARM_LENGTH 3

Animator::Animator(QWidget * parent):QCoin(parent)
{
	root = new SoSeparator;
  	setRoot(root);

	//Create the angles
	for(int i = 0; i < 4; i++)
	{
		angle[i] = new SoRotation;	
	}
	angle[0]->rotation.setValue(1,0,0,0);
	angle[1]->rotation.setValue(0,0,1,0);
	angle[2]->rotation.setValue(1,0,0,0);
	angle[3]->rotation.setValue(1,0,0,0);

	//Define temp pointers
	SoRotation* tempRotation;
	SoTranslation* tempTranslation;
	SoCylinder* tempCylinder;

	//Make some colors
	SoMaterial *silver = new SoMaterial;
  	silver->ambientColor.setValue(.2, .2, .2);
  	silver->diffuseColor.setValue(.6, .6, .6);
  	silver->specularColor.setValue(.5, .5, .5);
  	silver->shininess = .5;

	SoMaterial *gray = new SoMaterial;
  	gray->ambientColor.setValue(.5, .5, .5);
  	gray->diffuseColor.setValue(.5, .5, .5);
  	gray->specularColor.setValue(.5, .5, .5);
  	gray->shininess = .5;

	//Create the body
	body = new SoSeparator;
	body->addChild(gray);
	body->addChild(new SoRotation);
   SoRotation* bodyRotation = (SoRotation*) body->getChild(0);
	bodyRotation->rotation.setValue(SbVec3f(0,0,1),M_PI/2);
	body->addChild(new SoCone);
	root->addChild(body);


	//Start the arm
	arm = new SoSeparator;

	//Create shoulder
	arm->addChild(gray);
	arm->addChild(new SoSphere);

	//Create upper arm
	arm->addChild(silver);
	arm->addChild(angle[0]);
	arm->addChild(angle[1]);
	tempTranslation = new SoTranslation;
	tempTranslation->translation.setValue(SbVec3f(1,-UPPERARM_LENGTH /2.0,0));
	tempCylinder = new SoCylinder;
	tempCylinder->radius = UPPERARM_RADIUS;
	tempCylinder->height = UPPERARM_LENGTH;
	arm->addChild(tempCylinder);

	//Elbow
	tempTranslation = new SoTranslation;
	tempTranslation->translation.setValue(SbVec3f(0,-UPPERARM_LENGTH /4.0,0));
	arm->addChild(tempTranslation);
	arm->addChild(new SoSphere);

	root->addChild(arm);

	/*//Create forearm
	arm->addChild(angle[3]);
	arm->addChild(tempTranslation);dd
	SoSeparator* forearm = new SoSeparator;

	forearm->addChild(silver);
	tempCylinder = new SoCylinder;
	tempCylinder->radius = UPPERARM_RADIUS;
	tempCylinder->height = UPPERARM_LENGTH;
	forearm->addChild(tempCylinder);

	tempTranslation->translation.setValue(SbVec3f(0,-FOREARM_LENGTH /4.0,0));
	forearm->addChild(tempTranslation);
	
	forearm->addChild(new SoSphere);	

	tempTranslation->translation.setValue(SbVec3f(0,-FOREARM_LENGTH,0));
*/
	viewAll();
/*
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
*/
}
void Animator::setAngle1(int newAngle)
{
   angle[0]->rotation.setValue(SbVec3f(1,0,0),newAngle*M_PI/180);
}

void Animator::setAngle2(int newAngle)
{
   angle[1]->rotation.setValue(SbVec3f(0,0,1),newAngle*M_PI/180);
}

void Animator::setAngle3(int newAngle)
{
   angle[2]->rotation.setValue(SbVec3f(0,0,1),newAngle*M_PI/180);
}

void Animator::setAngle4(int newAngle)
{
   angle[3]->rotation.setValue(SbVec3f(0,0,1),newAngle*M_PI/180);
}

