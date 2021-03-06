#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QPushButton>
#include <QApplication>
#include <QFont>
#include <QWidget>
//#include <QSlider>
//#include <QLCDNumber>
#include <MotionForm.h>
//#include <QFileDialog>
#include <QTableWidget>
#include <QStringList>
#include <QTextEdit>


#define COL_WIDTH 50
#define ROW_HEIGHT 20

int main(int argc, char ** argv)
{

	QApplication app(argc,argv);

	QWidget*  mainWindow =  new QWidget;
	mainWindow->resize(1024,768);
	SoQt::init(mainWindow);

	//Create table
	int i,j;
	QTableWidgetItem* tempItem;
	QTableWidget* tbl = new QTableWidget(NUM_ANGLES,NUM_PARAMS,mainWindow);
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

	QPushButton* goButton = new QPushButton("Go",mainWindow);
  	goButton->setFont(QFont("Times",18,QFont::Bold));
  	goButton->setGeometry(10,200,180,40);

    // Button for loading to file
    QPushButton *fileButton = new QPushButton("Use File Data", mainWindow);
    fileButton->setFont(QFont("Times",18,QFont::Bold));
    fileButton->setGeometry(10,250,180,40);

    // Button for resetting
    QPushButton *resetButton = new QPushButton("Reset", mainWindow);
    resetButton->setFont(QFont("Times",18,QFont::Bold));
    resetButton->setGeometry(10,300,180,40);
	MotionForm* gfx = new MotionForm(tbl, mainWindow);
	//MotionForm* gfx = new MotionForm(mainWindow, tbl, mainWindow);
  	gfx->setGeometry(225,10,800,600);
	
	QObject::connect(goButton,SIGNAL(clicked()),gfx,SLOT(updateMotion()));

    // Register fileButton click
    QObject::connect(fileButton, SIGNAL(clicked()), gfx, SLOT(updateWithFile()));

    // Register resetButton click
    QObject::connect(resetButton, SIGNAL(clicked()), gfx, SLOT(resetParams()));

//  	mainWindow->show();

    SoQt::show(mainWindow);
  	SoQt::mainLoop();

	delete goButton;
	delete tbl;
    delete fileButton;
//  	delete gfx;
  	delete mainWindow;
  	SoQt::done();

  	return 0;
}
