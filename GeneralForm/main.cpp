#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QPushButton>
#include <QApplication>
#include <QFont>
#include <QWidget>
//#include <QSlider>
//#include <QLCDNumber>
#include <GeneralForm.h>
//#include <QFileDialog>
#include <QTableWidget>
#include <QStringList>


#define COL_WIDTH 200
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
	hLbls << "Expression: oa(a)";
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
			tempItem = new QTableWidgetItem("oa=0;");
			tbl->setItem(i,j,tempItem);
		}
	}
   tbl->setGeometry(10,10,(0.5+NUM_PARAMS)*COL_WIDTH,(2+NUM_ANGLES)*ROW_HEIGHT); 

	QPushButton* goButton = new QPushButton("Go",mainWindow);
  	goButton->setFont(QFont("Times",18,QFont::Bold));
  	goButton->setGeometry(10,200,180,40);


	GeneralForm* gfx = new GeneralForm(tbl, mainWindow);
  	gfx->setGeometry(225,10,800,600);
	
	QObject::connect(goButton,SIGNAL(clicked()),gfx,SLOT(updateMotion()));

  	mainWindow->show();

  	SoQt::mainLoop();

	delete goButton;
	delete tbl;
//  	delete gfx;
  	delete mainWindow;
  	SoQt::done();

  	return 0;
}
