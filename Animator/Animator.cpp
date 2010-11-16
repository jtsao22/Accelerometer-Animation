#include <Animator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTranslation.h>
#include <FreeForm.h>
#include <MotionForm.h>

void Animator::defineWindows()
{
	//Total number of windows
   num_windows = 2;
   windows = new AbstractWindow*[num_windows];

   //Create FreeForm tab with index 0
   windows[0] = new FreeForm(this);

   //Create MotionForm tab with index 1
   windows[1] = new MotionForm(this);

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
	root = new SoSeparator;
  	setRoot(root);

	//Set the time
	time = new SoElapsedTime;

	//Create the angles
   angleAxis[0].setValue(0,0,1);
	angleAxis[1].setValue(-1,0,0);
	angleAxis[2].setValue(0,1,0);
	angleAxis[3].setValue(-1,0,0);
	angleAxis[4].setValue(0,1,0);
	angleAxis[5].setValue(-1,0,0);
	for(int i = 0; i < NUM_ANGLES; i++)
	{
		angle[i] = new SoRotation;	
		angleCalc[i] = new SoCalculator;
		angleCompRot[i] = new SoComposeRotation;
		angleCalc[i]->a.connectFrom(&(time->timeOut));
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
   SoMaterial *silver = new SoMaterial;
   silver->ambientColor.setValue(.3, .3, .31);
   silver->diffuseColor.setValue(.6, .6, .62);
   silver->specularColor.setValue(.78, .8, .83);
   silver->shininess = 1;

   SoMaterial *gray = new SoMaterial;
   gray->ambientColor.setValue(.51, .5, .5);
   gray->diffuseColor.setValue(.6, .61, .6);
   gray->specularColor.setValue(.4, .4, .42);
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
   arm->addChild(angle[2]);
	arm->addChild(tempCylinder);

   // Create elbow
   tempTranslation = new SoTranslation;
   tempTranslation->translation.setValue(SbVec3f(0,-2*UPPERARM_LENGTH/3.0, 0));
   arm->addChild(tempTranslation);
   arm->addChild(gray);
   arm->addChild(new SoSphere);
   arm->addChild(angle[3]);

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
   arm->addChild(angle[5]);
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
