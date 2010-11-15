#include <AnimatorWindows.h>
#include <QTextStream>
#include <QTableWidget>
#include <QTextEdit>
#include <QFile>
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

//AbstractWindow
AbstractWindow::AbstractWindow(Animator* newGfx)
{
	gfx = newGfx;
}

AbstractWindow::~AbstractWindow(){}

//FreeFormSlider

FreeFormSlider::FreeFormSlider(int newId, Qt::Orientation o, QWidget * parent): QSlider(o,parent)
{
	id = newId;
	connect(this,SIGNAL(valueChanged(int)),this,SLOT(detectUpdate(int)));
}

void FreeFormSlider::detectUpdate(int newValue)
{
	emit sendUpdate(id,newValue);
}

//FreeForm
FreeForm::FreeForm(Animator * newGfx):AbstractWindow(newGfx){}

void FreeForm::transitionTo()
{
	for(int i = 0; i < NUM_ANGLES; i++)
	{
  		QObject::connect(sldAngle[i],SIGNAL(sendUpdate(int,int)),gfx,SLOT(setAngle(int,int)));
  		QObject::connect(sldAngle[i],SIGNAL(valueChanged(int)),lcdAngle[i],SLOT(display(int)));
		sldAngle[i]->setValue(0.5 + 180*gfx->getAngle(i)/M_PI);
	}			
}

void FreeForm::transitionFrom()
{
	for(int i = 0; i<NUM_ANGLES; i++)
	{
		sldAngle[i]->disconnect();
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
      lcdAngle[i] = new QLCDNumber(3,window);
      lcdAngle[i]->setGeometry(10,100*i+10,180,40);
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
return window;
}

FreeForm::~FreeForm()
{
	for(int i = 0; i < NUM_ANGLES; i++)
	{
		delete sldAngle[i];
		delete lcdAngle[i];
	}
}

//MotionForm
MotionForm::MotionForm(Animator * newGfx):AbstractWindow(newGfx){}

void MotionForm::transitionTo()
{  
	// Register goButton click
	QObject::connect(goButton, SIGNAL(clicked()), this, SLOT(updateMotion()));
	// Register fileButton click
  	QObject::connect(fileButton, SIGNAL(clicked()), this, SLOT(updateWithFile()));
  	// Register resetButton click
  	QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetParams()));
		   
	for(int i = 0; i < NUM_ANGLES; i++)
  	{
		gfx->enableAngle(i,1);
  	}
}  
      
void MotionForm::transitionFrom()
{        
	goButton->disconnect();
	fileButton->disconnect();
	resetButton->disconnect();
	for(int i = 0; i < NUM_ANGLES; i++)
  	{
		gfx->enableAngle(i,0);
   }
}    

QWidget* MotionForm::createWindow()
{
	//Create MotionForm tab
	window =  new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Create table
	int i,j;
	QTableWidgetItem* tempItem;
	tbl = new QTableWidget(NUM_ANGLES,NUM_PARAMS,window);
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

   // Create Label for messages
   txtEdit = new QTextEdit(window);
   txtEdit->setReadOnly(1);
   txtEdit->setGeometry(10,200,180,40);
   txtEdit->show();

	//Button for updating engines
	goButton = new QPushButton("Go",window);
  	goButton->setFont(QFont("Times",18,QFont::Bold));
  	goButton->setGeometry(10,250,180,40);

   // Button for loading to file
   fileButton = new QPushButton("Use File Data", window);
   fileButton->setFont(QFont("Times",18,QFont::Bold));
   fileButton->setGeometry(10,300,180,40);

   // Button for resetting
   resetButton = new QPushButton("Reset", window);
   resetButton->setFont(QFont("Times",18,QFont::Bold));
   resetButton->setGeometry(10,350,180,40);

	return window;
}

MotionForm::~MotionForm()
{
	delete tbl;
	delete txtEdit;
	delete goButton;
	delete fileButton;
	delete resetButton;
}

void MotionForm::updateMotion(void)
{
  	double a,b, mean, amp, p, w;
  	std::stringstream expression;
	for(int i = 0; i < NUM_ANGLES; i++)
	{
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
		gfx->setAngleExpr(i,expression.str());
	}	
}

void MotionForm::updateWithFile(void)
{
   int row = 0;
   int col = 0;
	QString filename = QFileDialog::getOpenFileName(window,"Select Parameter File",".","Text Files (*.txt)");
   QFile file(filename.toAscii().data());
   QString token;
   
   
   // Check if file exists
   if(!file.exists())
   {
       txtEdit->setText("File does not exist");
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

   updateMotion();

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
