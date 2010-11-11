#include <MotionForm.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoRotation.h>
#include <QTextStream>
#include <QTableWidget>
#include <QTextEdit>
#include <qfile.h>
#include <iostream>
#include <sstream>
//#include <stdio.h>

// DEFINES

#define UPPERARM_RADIUS 1
#define UPPERARM_LENGTH 3

#define FOREARM_RADIUS 1
#define FOREARM_LENGTH 3

#define FINGER_RADIUS 0.2
#define FINGER_LENGTH 1.5

#define THUMB_RADIUS 0.23
#define THUMB_LENGTH 1.0


MotionForm::MotionForm(QWidget *main,QTableWidget* newTbl, QWidget * parent):QCoin(parent)
{
    mainWindow = main;
	tbl = newTbl;
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
	}

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

void MotionForm::updateMotion(void)
{
	int i;
	double a,b, mean, amp, p, w;
	std::stringstream expression;
	for( i = 0; i < NUM_ANGLES; i++)
	{
		expression.str().clear();
		a = tbl->item(i,0)->text().toDouble();
		b = tbl->item(i,1)->text().toDouble();
		p = tbl->item(i,2)->text().toDouble();
		w = tbl->item(i,3)->text().toDouble();
		mean = (a+b)/2;
		amp = (b-a)/2;
		mean *= M_PI/180;
		amp *= M_PI/180;
		p *= M_PI/180;
		w *= M_PI/180;
		expression << "oa=" << mean << "+" << amp << "*cos(" << p << "+" << w << "*a);";
//		printf("%s\n",expression.str().c_str());
		angleCalc[i]->expression = expression.str().c_str();		
	}	
}

void MotionForm::updateWithFile(void)
{
    int row = 0;
    int col = 0;
    QFile file("config.txt");
    QString token;
    
    // Create Label for messages
    QTextEdit *txtedit = new QTextEdit(mainWindow);
    txtedit->setReadOnly(1);
    txtedit->setGeometry(10,350,180,40);
    txtedit->show();
    
    // Check if file exists
    if(!file.exists())
    {
        txtedit->setText("File does not exists");
        return;
    }
    
    // Open file
    if(!file.open( QIODevice::ReadOnly))
    {
        txtedit->setText("Error: Problem Opening file");
        return;
    }
    else
        txtedit->setText("File opened Successfully!");

    QTextStream in(&file);

    in >> token;
    while(token != NULL)
    {
        tbl->item(row,col)->setText(token);
        col++;
        if(col == NUM_PARAMS)
        {
            col = 0;
            row++;
        }

        if(row > NUM_ANGLES)
        {
            txtedit->setText("File is corrupt");
            return;
        }
        in >> token;
    }
    file.close();

    // Do you guys want this to animate right away?
    // If so: uncomment next line:
    // updateMotion();

}

void MotionForm::resetParams(void)
{
    for(int col = 0; col < NUM_PARAMS; col++)
    {
        for(int row = 0; row < NUM_ANGLES; row++)
        {
            tbl->item(row,col)->setText("0");
        }
    }
    updateMotion();
}
