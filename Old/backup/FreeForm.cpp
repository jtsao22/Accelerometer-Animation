#include <FreeForm.h>

//FreeFormSlider
FreeFormSlider::FreeFormSlider(int newId, Qt::Orientation o, QWidget * parent): QSlider(o,parent)
{
	id = newId;
}

void FreeFormSlider::detectUpdate(int newValue)
{
	emit sendUpdate(id,newValue);
}

//FreeForm
FreeForm::FreeForm(Animator * newGfx):AbstractWindow(newGfx,"Free Form"){}

FreeForm::~FreeForm()
{
	for(int i = 0; i < NUM_ANGLES; i++)
	{
		delete sldAngle[i];
		delete lcdAngle[i];
	}
}

QWidget* FreeForm::createWindow()
{
	//Create FreeForm Tab
   //Create sliders and LCD's
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);
   for(int i = 0; i< NUM_ANGLES; i++)
   {
      sldAngle[i]= new FreeFormSlider(i,Qt::Horizontal,window);
      sldAngle[i]->setValue(0);
      sldAngle[i]->setGeometry(10,100*i+60,180,40);
      lcdAngle[i] = new QLCDNumber(4,window);
      lcdAngle[i]->setGeometry(10,100*i+10,180,40);
   	sldAngle[i]->setRange(-360,720); //Ensures at least 360 degrees up or down to play with when switching from MotionForm
   }
/*
   sldAngle[0]->setRange(0,120);
   sldAngle[1]->setRange(-45,180);
   sldAngle[2]->setRange(-40,90);
   sldAngle[3]->setRange(0,145);
   sldAngle[4]->setRange(0,160);
   sldAngle[5]->setRange(-90,60);
*/
return window;
}

void FreeForm::transitionTo()
{
	for(int i = 0; i < NUM_ANGLES; i++)
	{
		QObject::connect(sldAngle[i],SIGNAL(valueChanged(int)),sldAngle[i],SLOT(detectUpdate(int)));
  		QObject::connect(sldAngle[i],SIGNAL(valueChanged(int)),lcdAngle[i],SLOT(display(int)));
		sldAngle[i]->setValue(((int)(360.5 + 180*(gfx->getAngle(i)/M_PI))) % 360);
  		QObject::connect(sldAngle[i],SIGNAL(sendUpdate(int,int)),gfx,SLOT(setAngle(int,int)));
	}			
}

void FreeForm::transitionFrom()
{
	for(int i = 0; i<NUM_ANGLES; i++)
	{
		sldAngle[i]->disconnect();
	}
}
