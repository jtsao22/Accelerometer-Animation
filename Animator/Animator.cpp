#include <Animator.h>
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
#include <QFileDialog>
#include <QPushButton>
#include <QApplication>
#include <QFont>
#include <QWidget>
#include <Animator.h>
#include <QTableWidget>
#include <QStringList>
#include <QTextEdit>


// DEFINES

#define UPPERARM_RADIUS 1
#define UPPERARM_LENGTH 3

#define FOREARM_RADIUS 1
#define FOREARM_LENGTH 3

#define FINGER_RADIUS 0.2
#define FINGER_LENGTH 1.5

#define THUMB_RADIUS 0.23
#define THUMB_LENGTH 1.0

#define COL_WIDTH 50
#define ROW_HEIGHT 20

#define TAB_WIDTH 290
#define TAB_HEIGHT 748

#define VIEWER_WIDTH 720
#define VIEWER_HEIGHT 540


Animator::Animator(QWidget * parent):QCoin(parent)
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

	//Create GUI elements
  	setGeometry(300,10,VIEWER_WIDTH,VIEWER_HEIGHT);
	tabs = new QTabWidget(parent);
	tabs->setGeometry(10,10,TAB_WIDTH,TAB_HEIGHT);

	//Create FreeForm Tab
   //Create sliders and LCD's
	windows[0] = new QWidget;
	windows[0]->setGeometry(10,10,TAB_WIDTH,TAB_HEIGHT);
   for(int i = 0; i< NUM_ANGLES; i++)
   {
      sldAngle[i]= new QSlider(Qt::Horizontal,windows[0]);
      sldAngle[i]->setValue(0);
      sldAngle[i]->setGeometry(10,100*i+60,180,40);
      lcdAngle[i] = new QLCDNumber(3,windows[0]);
      lcdAngle[i]->setGeometry(10,100*i+10,180,40);
      //QObject::connect(sldAngle[i],SIGNAL(valueChanged(int)),lcdAngle[i],SLOT(display(int)));
   	sldAngle[i]->setRange(0,360);
   }
/*
   sldAngle[0]->setRange(0,120);
   sldAngle[1]->setRange(-45,180);
   sldAngle[2]->setRange(-40,90);
   sldAngle[3]->setRange(0,145);
   sldAngle[4]->setRange(0,160);
   sldAngle[5]->setRange(-90,60);
*/



	//Create MotionForm tab
	windows[1] =  new QWidget;
	windows[1]->setGeometry(10,10,TAB_WIDTH,TAB_HEIGHT);

	//Create table
	int i,j;
	QTableWidgetItem* tempItem;
	tbl = new QTableWidget(NUM_ANGLES,NUM_PARAMS,windows[1]);
	QStringList hLbls, vLbls;
	hLbls << "a" << "b" << "p" << "w";
	vLbls << "0" << "1" << "2" << "3" << "4" << "5";
	tbl->setHorizontalHeaderLabels(hLbls);
	tbl->setVerticalHeaderLabels(vLbls);
	for(j = 0;j<NUM_PARAMS;j++)
	{
  		tbl->setColumnWidth(j,COL_WIDTH);
	}
	for(i = 0;i<NUM_ANGLES;i++)
	{
   	tbl->setRowHeight(i,ROW_HEIGHT);
		for(j = 0;j<NUM_PARAMS;j++)
		{
			tempItem = new QTableWidgetItem("0");
			tbl->setItem(i,j,tempItem);
		}
	}
   tbl->setGeometry(10,10,(0.5+NUM_PARAMS)*COL_WIDTH,(2+NUM_ANGLES)*ROW_HEIGHT); 

	goButton = new QPushButton("Go",windows[1]);
  	goButton->setFont(QFont("Times",18,QFont::Bold));
  	goButton->setGeometry(10,200,180,40);

   // Button for loading to file
   fileButton = new QPushButton("Use File Data", windows[1]);
   fileButton->setFont(QFont("Times",18,QFont::Bold));
   fileButton->setGeometry(10,250,180,40);

   // Button for resetting
   resetButton = new QPushButton("Reset", windows[1]);
   resetButton->setFont(QFont("Times",18,QFont::Bold));
   resetButton->setGeometry(10,300,180,40);

   // Create Label for messages
   txtEdit = new QTextEdit((QWidget*) windows[1]);
   txtEdit->setReadOnly(1);
   txtEdit->setGeometry(10,350,180,40);
   txtEdit->show();

	/*

  	// Register goButton click
   QObject::connect(goButton,SIGNAL(clicked()),this,SLOT(updateMotion()));
	// Register fileButton click
  	QObject::connect(fileButton, SIGNAL(clicked()), this, SLOT(updateWithFile()));
  	// Register resetButton click
  	QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetParams()));

	*/
	//Insert windows into tab
	tabs->addTab(windows[0],"Free Form");
	tabs->addTab(windows[1],"Motion Form");
	currentTab = -1;
	tabSwitch(0);
	connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(tabSwitch(int)));
	show();
}

Animator::~Animator()
{
	int i;
	/*
	//Doing the following causes a segmentation fault on close for some reason
	delete tabs;
	for(i = 0; i < NUM_TABS; i++)
	{
		delete windows[i];
	}*/
	delete tbl;
	delete goButton;
	delete fileButton;
	delete txtEdit;
	for(i = 0; i < NUM_ANGLES; i++)
	{
		delete sldAngle[i];
		delete lcdAngle[i];
	}
}

void Animator::updateMotion(void)
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
		angleCalc[i]->expression = expression.str().c_str();		
	}	
}

void Animator::updateWithFile(void)
{
    int row = 0;
    int col = 0;
	 QString filename = QFileDialog::getOpenFileName(this,"Select Parameter File",".","Text Files (*.txt)");
    QFile file(filename.toAscii().data());
    QString token;
    
    
    // Check if file exists
    if(!file.exists())
    {
        txtEdit->setText("File does not exists");
        return;
    }
    
    // Open file
    if(!file.open( QIODevice::ReadOnly))
    {
        txtEdit->setText("Error: Problem Opening file");
        return;
    }
    else
        txtEdit->setText("File opened Successfully!");

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
            txtEdit->setText("File is corrupt");
            return;
        }
        in >> token;
    }
    file.close();

    // Do you guys want this to animate right away?
    // If so: uncomment next line:
    updateMotion();

}

void Animator::resetParams(void)
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

void Animator::tabSwitch(int newTab)
{
	int i;
	SbVec3f axisRead;
	float angleRead;

	if (currentTab != newTab)
	{
		switch(currentTab)
		{
			case 0:
				for(i = 0; i<NUM_ANGLES; i++)
				{
					sldAngle[i]->disconnect();
				}

				break;
			case 1:
				goButton->disconnect();
				fileButton->disconnect();
				resetButton->disconnect();
				for(i = 0; i < NUM_ANGLES; i++)
         	{
      		angle[i]->rotation.enableConnection(0);
         	}

				break;
		}
	}
	switch(newTab)
	{
		case 0:
   		QObject::connect(sldAngle[0],SIGNAL(valueChanged(int)),this,SLOT(setAngle0(int)));
   		QObject::connect(sldAngle[1],SIGNAL(valueChanged(int)),this,SLOT(setAngle1(int)));
   		QObject::connect(sldAngle[2],SIGNAL(valueChanged(int)),this,SLOT(setAngle2(int)));
   		QObject::connect(sldAngle[3],SIGNAL(valueChanged(int)),this,SLOT(setAngle3(int)));
   		QObject::connect(sldAngle[4],SIGNAL(valueChanged(int)),this,SLOT(setAngle4(int)));
   		QObject::connect(sldAngle[5],SIGNAL(valueChanged(int)),this,SLOT(setAngle5(int)));
			for(i = 0; i < NUM_ANGLES; i++)
			{
      		QObject::connect(sldAngle[i],SIGNAL(valueChanged(int)),lcdAngle[i],SLOT(display(int)));
				angle[i]->rotation.getValue(axisRead,angleRead);//can someone find a way of doing this without reading the axis?
				sldAngle[i]->setValue(180*angleRead/M_PI);
			}			
			break;

		case 1:
   		// Register goButton click
		   QObject::connect(goButton,SIGNAL(clicked()),this,SLOT(updateMotion()));
			// Register fileButton click
   		QObject::connect(fileButton, SIGNAL(clicked()), this, SLOT(updateWithFile()));
   		// Register resetButton click
   		QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetParams()));
				   
			for(i = 0; i < NUM_ANGLES; i++)
   		{
      		angle[i]->rotation.enableConnection(1);
   		}


			break;
	}
	currentTab = newTab;
}
void Animator::setAngle0(int newAngle)
{
   angle[0]->rotation.setValue(angleAxis[0],newAngle*M_PI/180);
}
void Animator::setAngle1(int newAngle)
{
   angle[1]->rotation.setValue(angleAxis[1],newAngle*M_PI/180);
}

void Animator::setAngle2(int newAngle)
{
   angle[2]->rotation.setValue(angleAxis[2],newAngle*M_PI/180);
}

void Animator::setAngle3(int newAngle)
{
   angle[3]->rotation.setValue(angleAxis[3],newAngle*M_PI/180);
}

void Animator::setAngle4(int newAngle)
{
   angle[4]->rotation.setValue(angleAxis[4],newAngle*M_PI/180);
}

void Animator::setAngle5(int newAngle)
{
   angle[5]->rotation.setValue(angleAxis[5],newAngle*M_PI/180);
}
void Animator::show()
{
	QCoin::show();
/*	for(int i = 0; i < NUM_TABS; i++)
	{
		windows[i]->show();
	}
*/
	tabs->show();
}
