#include <ReadMATLAB.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <sstream>


//ReadMATLAB Constructor: Most likely you do not need to modify this
ReadMATLAB::ReadMATLAB(Animator * newGfx):AbstractWindow(newGfx,"MATLAB"){}

//ReadMATLAB Destructor: Delete all dynamically allocated data here
ReadMATLAB::~ReadMATLAB()
{
//    delete fileButton;
//    delete txtEdit;
}

//ReadMATLAB createWindow: Create the Qt here by placing subwidgets as children to the widget pointed to by window
QWidget* ReadMATLAB::createWindow()
{
	//Create ReadMATLAB Tab
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Define widget here

    // Create Label for messages
    txtEdit = new QTextEdit(window);
    txtEdit->setReadOnly(1);
    txtEdit->setGeometry(10,200,180,40);
    txtEdit->show();

    // Button for Loading file
    fileButton = new QPushButton("Use File Data", window);
    fileButton->setFont(QFont("Times",18,QFont::Bold));
    fileButton->setGeometry(10,300,180,40);

	return window;
}
//ReadMATLAB transitionTo: Create any Qt/Coin connections or enable Coin engines for Coin connections made in createWindow
void ReadMATLAB::transitionTo()
{
	// Register fileButton click
  	QObject::connect(fileButton, SIGNAL(clicked()), this, SLOT(updateWithFile()));

	for(int i = 0; i < NUM_ANGLES; i++)
  	{
		gfx->enableTime(1);
  	}
}

//ReadMATLAB transitionFrom: Remove Qt/Coin connections or disable Coin engines that should not be present when leaving the ReadMATLAB tab
void ReadMATLAB::transitionFrom()
{
    fileButton->disconnect();
    txtEdit->disconnect();

	for(int i = 0; i < NUM_ANGLES; i++)
  	{
		gfx->enableTime(1);
  	}
}

void ReadMATLAB::updateWithFile(void)
{
	QString filename = QFileDialog::getOpenFileName(window,"Select Animation File",".","Animation Files (*.anm)");
   QFile file(filename.toAscii().data());
   QString line;
   QStringList list;
   
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

   while(!in.atEnd())
   {
       line = in.readLine();
       list = line.split(' ');

       
       if(list[0] != "expr")
       {
           txtEdit->setText(list[0]);
           QTimer::singleShot(2000, this, SLOT(change_velocity(list[0])));
       }
       else
       {
           std::stringstream expression;
           expression <<  list[2].toStdString();
           gfx->setAngleExpr(list[1].toInt(), expression.str());
       }
   }
   file.close();

}

void ReadMATLAB::change_velocity(int speed)
{
    gfx->setTimeSpeed(speed);
}

