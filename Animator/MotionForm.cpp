#include <MotionForm.h>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <sstream>

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
    delete convertButton;
	delete speedLabel;
	delete speedText;
}

QWidget* MotionForm::createWindow()
{
	//Create MotionForm tab
	window =  new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);
	
	//Create speed stuff
	speedLabel = new QLabel("Speed",window);
	speedLabel->setGeometry(60,180,70,30);
	
	speedText = new QTextEdit("1",window);
	speedText->setGeometry(60,210,70,30);

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
    txtEdit->setGeometry(10,250,180,40);
    txtEdit->show();

	//Button for updating engines
	goButton = new QPushButton("Go",window);
  	goButton->setFont(QFont("Times",18,QFont::Bold));
  	goButton->setGeometry(10,300,180,40);

    // Button for loading to file
    fileButton = new QPushButton("Load", window);
    fileButton->setFont(QFont("Times",18,QFont::Bold));
    fileButton->setGeometry(10,350,180,40);

    // Button for saving to file
    saveButton = new QPushButton("Save", window);
    saveButton->setFont(QFont("Times",18,QFont::Bold));
    saveButton->setGeometry(10,400,180,40);

    // Button for resetting
    resetButton = new QPushButton("Reset", window);
    resetButton->setFont(QFont("Times",18,QFont::Bold));
    resetButton->setGeometry(10,450,180,40);

    // Button for converting from .mot file to .anm
    convertButton = new QPushButton("Convert", window);
    convertButton->setFont(QFont("Times",18, QFont::Bold));
    convertButton->setGeometry(10, 500, 180, 40);

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
    // Register convertButton click
    QObject::connect(convertButton, SIGNAL(clicked()), this, SLOT(convertToAnm()));
		   
	gfx->enableTime(1);
}  
      
void MotionForm::transitionFrom()
{        
    // Disconnect buttons
	goButton->disconnect();
	fileButton->disconnect();
	saveButton->disconnect();
	resetButton->disconnect();
    convertButton->disconnect();
	gfx->enableTime(0);
}    

void MotionForm::updateMotion(void)
{
  	double a,b, mean, amp, p, f;
	std::stringstream expression;
	for(int i = 0; i < NUM_ANGLES; i++)
	{
	    expression.str().clear();
	    expression.str("");
   	    a = tbl->item(i,0)->text().toDouble();
   	    b = tbl->item(i,1)->text().toDouble();
   	    p = tbl->item(i,2)->text().toDouble();
   	    f = tbl->item(i,3)->text().toDouble();

        // Calculate the new mean, amplitude, phase, and frequency
        // and take the appropriate actions
   	    mean = (a+b)/2;
   	    amp = (b-a)/2;
   	    mean *= M_PI/180;
   	    amp *= M_PI/180;
   	    p *= M_PI/180;
   	    f *= 2*M_PI;
   	    expression << mean << "+" << amp << "*cos(" << p << "+" << f <<"*a)";
	    gfx->setAngleExpr(i,expression.str());
	    gfx->setTimeSpeed(speedText->toPlainText().toDouble());
	}	
	gfx->triggerSoft();
}


void MotionForm::updateWithFile(void)
{
    int row = 0;
    int col = 0;

    // Get motion file
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

    // Read in from the file token by token (whitespace separated words)
    in >> token;
    while(token != NULL)
    {
        // Set the tokens into the table;
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

    // Close and update
    file.close();
    updateMotion();

}

void MotionForm::resetParams(void)
{
    // Resets the table to zero and updates
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
    // Get filename to save to
	QString filename = QFileDialog::getSaveFileName(window,"Enter file name to save",".","Motion Files (*.mot)");
	if (!filename.endsWith(".txt"))
		filename.append(".txt");

    // Open file
    QFile file(filename.toAscii().data());
    if(!file.open( QIODevice::WriteOnly))
    {
        txtEdit->setText("Error: Problem Opening file");
        return;
    }

    // Output table values to the file
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

void MotionForm::convertToAnm(void)
{
    // Prompt for file to save to
    QString ask("Enter file name to convert to");
    QString curdir(".");
    QString type("Animator Files (*.anm)");
	QString filename = QFileDialog::getSaveFileName(window, ask,curdir,type, NULL, QFileDialog::DontConfirmOverwrite);
	if (!filename.endsWith(".anm"))
		filename.append(".anm");
    QFile file(filename.toAscii().data());

    QTextStream out(&file);

    // Check if file exists
    if(file.exists())
    {
        // Open file for appending
        txtEdit->setText("File already exists, appending!");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
        {    
            txtEdit->setText("Error: Problem Opening file");
            return;
        }
        out << "\n";
        out << "// Appended by MotionForm Converter";
    }
    else
    {
      // Create file
      if(!file.open( QIODevice::WriteOnly))
      {
          txtEdit->setText("Error: Problem Opening file");
          return;
      }
      out << "// Created by MotionForm Converter";
    }
		
  	double a,b, mean, amp, p, f;
	for(int i = 0; i < NUM_ANGLES; i++)
	{
   	    a = tbl->item(i,0)->text().toDouble();
   	    b = tbl->item(i,1)->text().toDouble();
   	    p = tbl->item(i,2)->text().toDouble();
   	    f = tbl->item(i,3)->text().toDouble();
        // Calculate mean, amplitude, phase, and frequency and set it into a
   	    mean = (a+b)/2;
   	    amp = (b-a)/2;
   	    mean *= M_PI/180;
   	    amp *= M_PI/180;
   	    p *= M_PI/180;
   	    f *= 2*M_PI;
        out << "\n";
        out << "expr " << i << " ";
   	    out << mean << "+" << amp << "*cos(" << p << "+" << f <<"*a)";
	}	
    out << "\n" << gfx->getTimeSpeed();
	file.close();
	txtEdit->setText("File successfully written");	

}
