#include <MotionForm.h>
#include <QStringList>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QString>

//MotionForm
MotionForm::MotionForm(Animator * newGfx):AbstractWindow(newGfx,"Motion Form"){}

MotionForm::~MotionForm()
{
	delete tbl;
	delete txtEdit;
	delete goButton;
	delete fileButton;
	delete saveButton;
	delete resetButton;
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
	hLbls << "a" << "b" << "p" << "f";
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

   // Button for saving to file
   saveButton = new QPushButton("Save to File", window);
   saveButton->setFont(QFont("Times",18,QFont::Bold));
   saveButton->setGeometry(10,350,180,40);

   // Button for resetting
   resetButton = new QPushButton("Reset", window);
   resetButton->setFont(QFont("Times",18,QFont::Bold));
   resetButton->setGeometry(10,400,180,40);

	return window;
}

void MotionForm::transitionTo()
{  
	// Register goButton click
	QObject::connect(goButton, SIGNAL(clicked()), this, SLOT(updateMotion()));
	// Register fileButton click
  	QObject::connect(fileButton, SIGNAL(clicked()), this, SLOT(updateWithFile()));
	// Register saveButton click
  	QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
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
	saveButton->disconnect();
	resetButton->disconnect();
	for(int i = 0; i < NUM_ANGLES; i++)
  	{
		gfx->enableAngle(i,0);
   }
}    

void MotionForm::updateMotion(void)
{
  	double a,b, mean, amp, p, f;
  	std::stringstream expression;
	for(int i = 0; i < NUM_ANGLES; i++)
	{
   	a = tbl->item(i,0)->text().toDouble();
   	b = tbl->item(i,1)->text().toDouble();
   	p = tbl->item(i,2)->text().toDouble();
   	f = tbl->item(i,3)->text().toDouble();
   	mean = (a+b)/2;
   	amp = (b-a)/2;
   	mean *= M_PI/180;
   	amp *= M_PI/180;
   	p *= M_PI/180;
   	f *= 2*M_PI;
   	expression << "oa=" << mean << "+" << amp << "*cos(" << p << "+" << f << "*a);";
		gfx->setAngleExpr(i,expression.str());
	}	
}

void MotionForm::updateWithFile(void)
{
   int row = 0;
   int col = 0;
	QString filename = QFileDialog::getOpenFileName(window,"Select Motion File",".","Motion Files (*.mot)");
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
			  file.close();
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

void MotionForm::saveFile(void)
{
	QString filename = QFileDialog::getSaveFileName(window,"Enter file name to save",".","Motion Files (*.mot)");
	if (!filename.endsWith(".txt"))
		filename.append(".txt");
   QFile file(filename.toAscii().data());
 // Create file
   if(!file.open( QIODevice::WriteOnly))
   {
       txtEdit->setText("Error: Problem Opening file");
       return;
   }
   QTextStream out(&file);
	int i, j;
	for(i = 0; i < NUM_ANGLES; i++)
	{
		for(j = 0; j < NUM_PARAMS; j++)
		{
			out << tbl->item(i,j)->text() << " ";
		}
		out << "\n";
	}
		
	file.close();
	txtEdit->setText("File successfully written");	
}
