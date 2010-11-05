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

#define FINGER_RADIUS 0.2
#define FINGER_LENGTH 1.5

#define THUMB_RADIUS 0.23
#define THUMB_LENGTH 1.0

Animator::Animator(QWidget * parent):QCoin(parent)
{
	root = new SoSeparator;
  	setRoot(root);

	//Create the angles
	for(int i = 0; i < 5; i++)
	{
		angle[i] = new SoRotation;	
	}
	angle[0]->rotation.setValue(SbVec3f(-1,0,0),0);
	angle[1]->rotation.setValue(SbVec3f(0,0,1),0);
	angle[2]->rotation.setValue(SbVec3f(0,0,1),0);
	angle[3]->rotation.setValue(SbVec3f(0,1,0),0);
    angle[4]->rotation.setValue(SbVec3f(0,1,0),0);

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
	tempRotation = new SoRotation;
	tempRotation->rotation.setValue(SbVec3f(0,0,1),M_PI/2);
	body->addChild(tempRotation);
	body->addChild(new SoCone);
	root->addChild(body);


	//Start the arm
	arm = new SoSeparator;
	tempTranslation = new SoTranslation;
	tempTranslation->translation.setValue(SbVec3f(1+UPPERARM_RADIUS,0,0));
	arm->addChild(tempTranslation);

	//Create shoulder
	arm->addChild(gray);
	arm->addChild(new SoSphere);
	arm->addChild(angle[0]);
	arm->addChild(angle[1]);

	//Create upper arm
	tempTranslation = new SoTranslation;
	tempTranslation->translation.setValue(SbVec3f(0,-2*UPPERARM_LENGTH /3.0,0));
	arm->addChild(tempTranslation);
	arm->addChild(silver);
	tempCylinder = new SoCylinder;
	tempCylinder->radius = UPPERARM_RADIUS;
	tempCylinder->height = UPPERARM_LENGTH;
	arm->addChild(tempCylinder);

    // Create elbow
    tempTranslation = new SoTranslation;
    tempTranslation->translation.setValue(SbVec3f(0,-2*UPPERARM_LENGTH/3.0, 0));
    arm->addChild(tempTranslation);
    arm->addChild(gray);
    arm->addChild(new SoSphere);
    arm->addChild(angle[3]);
    arm->addChild(angle[2]);

    //Create forearm
    tempTranslation = new SoTranslation;
    tempTranslation->translation.setValue(SbVec3f(0, -2*UPPERARM_LENGTH/3.0, 0));
    arm->addChild(tempTranslation);
    arm->addChild(silver);
    arm->addChild(angle[4]);
    tempCylinder = new SoCylinder;
    tempCylinder->radius = FOREARM_RADIUS;
    tempCylinder->height = FOREARM_LENGTH;
    arm->addChild(tempCylinder);

    // Create wrist 
    tempTranslation = new SoTranslation;
    tempTranslation->translation.setValue(SbVec3f(0,-2*UPPERARM_LENGTH/3.0, 0));
    arm->addChild(tempTranslation);
    arm->addChild(gray);
    arm->addChild(new SoSphere);

    // Add four main fingers
    tempTranslation = new SoTranslation;
    tempTranslation->translation.setValue(SbVec3f(-1,-0.4*UPPERARM_LENGTH, 0));
    arm->addChild(tempTranslation);
    arm->addChild(silver);

    for(int i = 0; i < 4; i++)
    {
        tempTranslation = new SoTranslation;
        tempTranslation->translation.setValue(SbVec3f(0.4,0, 0));
	    arm->addChild(tempTranslation);
	    //arm->addChild(silver);
	    tempCylinder = new SoCylinder;
	    tempCylinder->radius = FINGER_RADIUS;
	    tempCylinder->height = FINGER_LENGTH;
	    arm->addChild(tempCylinder);
    }
    
    //Add Thumb
    tempTranslation = new SoTranslation;
    tempTranslation->translation.setValue(SbVec3f(-4*0.4-0.2,0.5,0));
    arm->addChild(tempTranslation);
    tempRotation = new SoRotation;
    tempRotation->rotation.setValue(SbVec3f(0,0,1),-M_PI/4);
    arm->addChild(tempRotation);
    tempCylinder = new SoCylinder;
    tempCylinder->radius = THUMB_RADIUS;
    tempCylinder->height = THUMB_LENGTH;
    arm->addChild(tempCylinder);

    // Add arm to root
	root->addChild(arm);

	viewAll();
}
void Animator::setAngle1(int newAngle)
{
   angle[0]->rotation.setValue(SbVec3f(-1,0,0),newAngle*M_PI/180);
}

void Animator::setAngle2(int newAngle)
{
   angle[1]->rotation.setValue(SbVec3f(0,0,1),newAngle*M_PI/180);
}

void Animator::setAngle3(int newAngle)
{
   angle[2]->rotation.setValue(SbVec3f(-1,0,0),newAngle*M_PI/180);
}

void Animator::setAngle4(int newAngle)
{
   angle[3]->rotation.setValue(SbVec3f(0,1,0),newAngle*M_PI/180);
}

void Animator::setAngle5(int newAngle)
{
   angle[4]->rotation.setValue(SbVec3f(0,1,0),newAngle*M_PI/180);
}
