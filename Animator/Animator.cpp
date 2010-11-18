#include <Animator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCamera.h>
#include <FreeForm.h>
#include <MotionForm.h>
#include <ColorForm.h>

void Animator::defineWindows()
{
	//Total number of windows
   num_windows = 3;
   windows = new AbstractWindow*[num_windows];

   //Create FreeForm tab with index 0
   windows[0] = new FreeForm(this);

   //Create MotionForm tab with index 1
   windows[1] = new MotionForm(this);

   //Create MotionForm tab with index 1
   windows[2] = new ColorForm(this);

}

Animator::Animator(QWidget * parent):QCoin(parent)
{

	//Create the scene graph
	createSceneGraph();
	//Create GUI elements
  	setGeometry(VIEWER_X,VIEWER_Y,VIEWER_WIDTH,VIEWER_HEIGHT);
	tabs = new QTabWidget(parent);
	tabs->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Define the windows
	defineWindows();	

	//Insert windows into tab
	for(int i = 0; i < num_windows; i++)
	{
		tabs->addTab(windows[i]->createWindow(),windows[i]->getLabel());
	}

	//Call transition function to start at the tab first inserted into tabs
	currentTab = -1;
	tabSwitch(0);
	connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(tabSwitch(int)));


	//Set initial camera position
	SoCamera* cam = getViewer()->getCamera();
	cam->position.setValue(1,-4,-20);
	cam->orientation.setValue(SbVec3f(0,1,0),M_PI);
	viewAll();
	show();
}

Animator::~Animator()
{
	/*
	//Doing the following causes a segmentation fault on close for some reason
	delete tabs;
	*/
	for(int i = 0; i < num_windows; i++)
	{
		delete windows[i];
	}
	delete [] windows;
}


void Animator::tabSwitch(int newTab)
{
	if (currentTab != newTab && newTab >= 0 && newTab < num_windows)
	{
		//Transition from
		if (currentTab >= 0 && currentTab < num_windows)
			windows[currentTab]->transitionFrom();
		//Transition to
		windows[newTab]->transitionTo();
		currentTab = newTab;
	}
}
void Animator::setAngle(int angleIndex,int newAngle)
{
   angle[angleIndex]->rotation.setValue(angleAxis[angleIndex],newAngle*M_PI/180);
}

void Animator::show()
{
	QCoin::show();
	tabs->show();
}

void Animator::createSceneGraph()
{
	//Create scene graph
	SoSeparator* root = new SoSeparator;
	setRoot(root);
	
	//Set the time
	//time = new SoElapsedTime;

	//Create the angles
   angleAxis[0].setValue(0,0,1);
	angleAxis[1].setValue(1,0,0);
	angleAxis[2].setValue(0,-1,0);
	angleAxis[3].setValue(1,0,0);
	angleAxis[4].setValue(0,-1,0);
	angleAxis[5].setValue(1,0,0);
	for(int i = 0; i < NUM_ANGLES; i++)
	{
		angle[i] = new SoRotation;	
		angleCalc[i] = new SoCalculator;
		angleCompRot[i] = new SoComposeRotation;
		angleTime[i] = new SoElapsedTime;
		angleCalc[i]->a.connectFrom(&(angleTime[i]->timeOut));
		angleCompRot[i]->axis = angleAxis[i];
		angleCompRot[i]->angle.connectFrom(&(angleCalc[i]->oa));
		angle[i]->rotation.connectFrom(&(angleCompRot[i]->rotation));
		angleCalc[i]->expression = "oa=0;";
     	angle[i]->rotation.enableConnection(0);
	}

	//Define temp pointers
	SoRotation* tempRotation;
	SoTranslation* tempTranslation;
	SoCylinder* tempCylinder;

	//Make some colors
   colors[0] = new SoMaterial;
   colors[0]->ambientColor.setValue(.3, .3, .31);
   colors[0]->diffuseColor.setValue(.6, .6, .62);
   colors[0]->specularColor.setValue(.78, .8, .83);
   colors[0]->shininess = 1;

   colors[1] = new SoMaterial;
   colors[1]->ambientColor.setValue(.51, .5, .5);
   colors[1]->diffuseColor.setValue(.6, .61, .6);
   colors[1]->specularColor.setValue(.4, .4, .42);
   colors[1]->shininess = .5;


	//Create the body
	body = new SoSeparator;
	body->addChild(colors[1]);
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
	arm->addChild(colors[1]);
	arm->addChild(new SoSphere);
	arm->addChild(angle[0]);
	arm->addChild(angle[1]);

	//Create upper arm
	tempTranslation = new SoTranslation;
	tempTranslation->translation.setValue(SbVec3f(0,-2*UPPERARM_LENGTH /3.0,0));
	arm->addChild(tempTranslation);
	arm->addChild(colors[0]);
	tempCylinder = new SoCylinder;
	tempCylinder->radius = UPPERARM_RADIUS;
	tempCylinder->height = UPPERARM_LENGTH;
   arm->addChild(angle[2]);
	arm->addChild(tempCylinder);

   // Create elbow
   tempTranslation = new SoTranslation;
   tempTranslation->translation.setValue(SbVec3f(0,-2*UPPERARM_LENGTH/3.0, 0));
   arm->addChild(tempTranslation);
   arm->addChild(colors[1]);
   arm->addChild(new SoSphere);
   arm->addChild(angle[3]);

   //Create forearm
   tempTranslation = new SoTranslation;
   tempTranslation->translation.setValue(SbVec3f(0, -2*UPPERARM_LENGTH/3.0, 0));
   arm->addChild(tempTranslation);
   arm->addChild(colors[0]);
   arm->addChild(angle[4]);
   tempCylinder = new SoCylinder;
   tempCylinder->radius = FOREARM_RADIUS;
   tempCylinder->height = FOREARM_LENGTH;
   arm->addChild(tempCylinder);

   // Create wrist 
   tempTranslation = new SoTranslation;
   tempTranslation->translation.setValue(SbVec3f(0,-2*UPPERARM_LENGTH/3.0, 0));
   arm->addChild(tempTranslation);
   arm->addChild(angle[5]);
   arm->addChild(colors[1]);
   arm->addChild(new SoSphere);

   // Add four main fingers
   tempTranslation = new SoTranslation;
   tempTranslation->translation.setValue(SbVec3f(-1,-0.4*UPPERARM_LENGTH, 0));
   arm->addChild(tempTranslation);
   arm->addChild(colors[0]);

   for(int i = 0; i < 4; i++)
   {
      tempTranslation = new SoTranslation;
      tempTranslation->translation.setValue(SbVec3f(0.4,0, 0));
		arm->addChild(tempTranslation);
	   //arm->addChild(colors[0]);
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

}

float Animator::getAngle(int angleIndex)
{
	SbVec3f axisRead;
	float angleRead;
	angle[angleIndex]->rotation.getValue(axisRead,angleRead);
	return angleRead;
}

void Animator::enableAngle(int angleIndex, bool enable)
{
	angle[angleIndex]->rotation.enableConnection(enable);
}

void Animator::setAngleExpr(int angleIndex, std::string expr)
{
	angleCalc[angleIndex]->expression = expr.c_str();
}
SoMaterial* Animator::getMaterial(int color)
{
	return colors[color];
}
void Animator::setAngleSpeed(int angleIndex, double speed)
{
	angleTime[angleIndex]->speed = speed;
}
