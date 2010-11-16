#include <ColorForm.h>

//ColorForm Constructor: Most likely you do not need to modify this
ColorForm::ColorForm(Animator * newGfx):AbstractWindow(newGfx,"Color Form"){}

//ColorForm Destructor: Delete all dynamically allocated data here
ColorForm::~ColorForm()
{
	delete tbl;
	delete goButton;
}

//ColorForm createWindow: Create the Qt here by placing subwidgets as children to the widget pointed to by window
QWidget* ColorForm::createWindow()
{
	//Create ColorForm Tab
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Define widget here
	//Create table
	int i,j;
	QTableWidgetItem* tempItem;
	tbl = new QTableWidget(6,3,window);
	QStringList hLbls, vLbls;
	hLbls << "Red" << "Green" << "Blue";
	vLbls << "Limb Am" << "Limb Df" << "Limb Sp";
	vLbls << "Joint Am" << "Joint Df" << "Joint Sp";
	tbl->setHorizontalHeaderLabels(hLbls);
	tbl->setVerticalHeaderLabels(vLbls);
	for(j = 0;j<3;j++)
	{
  		tbl->setColumnWidth(j,COL_WIDTH);
	}
	for(i = 0;i<6;i++)
	{
   	tbl->setRowHeight(i,ROW_HEIGHT);
		for(j = 0;j<3;j++)
		{
			tempItem = new QTableWidgetItem("0.5");
			tbl->setItem(i,j,tempItem);
		}
	}
   tbl->setGeometry(3,10,4.7*COL_WIDTH,8*ROW_HEIGHT); 

	//Button for updating color
	goButton = new QPushButton("Go",window);
  	goButton->setFont(QFont("Times",18,QFont::Bold));
  	goButton->setGeometry(5,200,185,40);
	
	QObject::connect(goButton,SIGNAL(clicked()),this,SLOT(updateColors()));

	return window;
}
//ColorForm transitionTo: Create any Qt/Coin connections or enable Coin engines for Coin connections made in createWindow
void ColorForm::transitionTo()
{

}

//ColorForm transitionFrom: Remove Qt/Coin connections or disable Coin engines that should not be present when leaving the ColorForm tab
void ColorForm::transitionFrom()
{

}

void ColorForm::updateColors()
{
   double a[3], d[3], s[3];
	int i;
	//Do limbs
	for(i=0;i<3;i++)
	{
   	a[i] = tbl->item(0,i)->text().toDouble();
   	d[i] = tbl->item(1,i)->text().toDouble();
   	s[i] = tbl->item(2,i)->text().toDouble();
	}
	gfx->setMaterial(0,a,d,s);

	//Do joints
	for(i=0;i<3;i++)
	{
   	a[i] = tbl->item(3,i)->text().toDouble();
   	d[i] = tbl->item(4,i)->text().toDouble();
   	s[i] = tbl->item(5,i)->text().toDouble();
	}
	gfx->setMaterial(1,a,d,s);
	
}
