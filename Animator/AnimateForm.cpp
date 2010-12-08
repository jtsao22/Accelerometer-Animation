#include <AnimateForm.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QRegExp>


//Parsing Rules
int AnimateForm::parse(QString line)
{
	//Return Value
	// 0 = Scan Next Line Immediately
	// 1 = Wait for StepSize before scanning next line
	// 2 = Error occurred, stop animation


	QRegExp regex;
	double stepSize = 0;
        // Disregard comments and empty lines
        if(line.startsWith("//") || line.isEmpty());
	//Angle Expressions
	else if (line.startsWith("expr"))
	{	
		/* Syntax: expr N S
		 * N = index of angle (integer)
		 * S = string expression
		 */
		regex.setPattern("^expr\\s+(\\d+)\\s+(\\S.*)$");
		if (regex.indexIn(line) != -1)
		{
			gfx->setAngleExpr(regex.cap(1).toInt(),regex.cap(2).toStdString());
			doSoft = 1;
		}
		else
		{
			return 2;
		}
	}
	//Step Size Expressions
       	else if(line.startsWith("stepsize"))
       	{
		/* Syntax: stepsize T
		 * T = number of seconds between windows (floating point)
		 */
     		regex.setPattern("^stepsize\\s+(\\d+(\\.\\d+)?)");
       		if(regex.indexIn(line) != -1)
         	{
               		stepSize = regex.cap(1).toDouble();
			//txtEdit->setText("Stepsize = " + regex.cap(1));
               		if(stepSize < 1.0)
               			gfx->setSoftTime(stepSize);
               		else
                 	 	gfx->setSoftTime(1.0);
                	timer->setInterval(stepSize*1000);
            	}	
		else
		{
			return 2;
		}
        }
	else
	{
		/* Dynamic Parameters
		 * Sequence of floating point values or tildes
		 */
		regex.setPattern("^\\s*((?:\\d+(?:\\.\\d+)?|~)(?:\\s+|$))+");
       		if(regex.indexIn(line) != -1)
		{
			//Use regex.cap(N) to get the Nth dynamic parameter as a Q string with N starting from 1

			//Dynamic Parameter 1
			if (!regex.cap(1).startsWith("~"))
				gfx->setTimeSpeed(regex.cap(1).toDouble());

			//txtEdit->setText("Speed = " + regex.cap(1));
		}
		else
		{
			return 2;
		}

		if (doSoft)
			gfx->triggerSoft();
		return 1;
	}
	return 0;
}


//AnimateForm Constructor: Most likely you do not need to modify this
AnimateForm::AnimateForm(Animator * newGfx):AbstractWindow(newGfx,"Animate"){}

//AnimateForm Destructor: Delete all dynamically allocated data here
AnimateForm::~AnimateForm()
{}

//AnimateForm createWindow: Create the Qt here by placing subwidgets as children to the widget pointed to by window
QWidget* AnimateForm::createWindow()
{
	//Create AnimateForm Tab
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);
	
	//Create Timer
	timer = new QTimer(window);
	timer->setInterval(UPDATE_TIME*1000);

	//Set initial status
	//state = STOPPED;

	// Create Label for messages
	txtEdit = new QTextEdit(window);
	txtEdit->setReadOnly(1);
	txtEdit->setGeometry(10,200,180,40);
	txtEdit->show();

	// Button for Loading file
	loadButton = new QPushButton("Load", window);
	loadButton->setFont(QFont("Times",18,QFont::Bold));
	loadButton->setGeometry(10,300,180,40);

	// Button for Playing animation
	playButton = new QPushButton("Play", window);
	playButton->setFont(QFont("Times",18,QFont::Bold));
	playButton->setGeometry(10,350,180,40);

	// Button for Stopping animation
	stopButton = new QPushButton("Stop", window);
	stopButton->setFont(QFont("Times",18,QFont::Bold));
	stopButton->setGeometry(10,400,180,40);


	//Can define Qt connections here because none of these objects have any connections that need to be broken in a tab switch

	// Register loadButton click
	QObject::connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));

	// Register playButton click
	QObject::connect(playButton, SIGNAL(clicked()),this,SLOT(playPress()));

	// Register stopButton click
	QObject::connect(stopButton, SIGNAL(clicked()),this,SLOT(stopPress()));

	//Connect timer signal to loop
	QObject::connect(timer,SIGNAL(timeout()),this,SLOT(loop()));

	return window;
}
//AnimateForm transitionTo: Create any Qt/Coin connections or enable Coin engines for Coin connections made in createWindow
void AnimateForm::transitionTo()
{
	gfx->enableTime(1);
	stopPress();
}

//AnimateForm transitionFrom: Remove Qt/Coin connections or disable Coin engines that should not be present when leaving the AnimateForm tab
void AnimateForm::transitionFrom()
{
	gfx->enableTime(0);
	timer->stop();
}

void AnimateForm::loadFile(void)
{
	QString filename = QFileDialog::getOpenFileName(window,"Select Animation File",".","Animation Files (*.anm)");
	QFile file(filename.toAscii().data());
	QString line;
   
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

	txtEdit->setText("File Opened Successfully");

	QTextStream in(&file);
	
	script.clear();

	while(!in.atEnd())
		 script << in.readLine();
	file.close();
	scriptLine = 0;
}

void AnimateForm::loop()
{
	doSoft = 0;
	int scriptSize = script.size();

	while( scriptLine < scriptSize)
	{	
<<<<<<< HEAD
        // Read script read in by load
		line = script[scriptLine++];
		if (line.startsWith("expr"))
		{	
            // If its an expr line, set the angle expression with the angle
            // number and the expression
			regex.setPattern("^expr\\s+(\\d+)\\s+(\\S.*)$");
			if (regex.indexIn(line) != -1)
			{
				gfx->setAngleExpr(regex.cap(1).toInt(),regex.cap(2).toStdString());
				doSoft = 1;
			}
			else
			{
				txtEdit->setText("Error reading line");
				return;
			}
		}
        // Support comments
        else if(line.startsWith("//"));
        // Disregard empty lines
        else if(line.isEmpty());
        else if(line.startsWith("stepsize"))
        {
            // If stepsize, sets the soft time and timer interval
            regex.setPattern("^stepsize\\s+(\\d+(\\.\\d+)?)");
            if(regex.indexIn(line) != -1)
            {
                step_size = regex.cap(1).toDouble();
                txtEdit->setText("Stepsize = " + regex.cap(1));
                if(step_size < 1.0)
                    gfx->setSoftTime(step_size);
                else
                    gfx->setSoftTime(1.0);
                timer->setInterval(step_size*1000);
            }	
        }
		else if(line.startsWith("~"))
			return;
		else
		{
            // if the line only includes a number, change the speed
			gfx->setTimeSpeed(line.toDouble());
			if (doSoft)
				gfx->triggerSoft();
			return;
=======
		switch (parse(script[scriptLine++]))
		{
			case 2:
				txtEdit->setText("Error parsing line");
				gfx->setTimeSpeed(0);
			case 1:
				return;
>>>>>>> 5d77149fa2e71f0a6749416282caf55a140d1fb5
		}
	}
	stopPress();
}

void AnimateForm::playPress()
{
	timer->start();
	scriptLine = 0;
	loop();
}

void AnimateForm::stopPress()
{
	timer->stop();
	for(int i = 0; i < NUM_ANGLES; i++)
	{
		gfx->setAngleExpr(i,"0");
	}
	txtEdit->setText("Stopped");
	gfx->triggerSoft();
}
