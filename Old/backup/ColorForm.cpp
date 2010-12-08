#include <ColorForm.h>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <Inventor/nodes/SoMaterial.h>

//ColorForm Constructor: Most likely you do not need to modify this
ColorForm::ColorForm(Animator * newGfx):AbstractWindow(newGfx,"Color Form"){}

//ColorForm Destructor: Delete all dynamically allocated data here
ColorForm::~ColorForm()
{
	delete tbl;
	delete goButton;
	delete saveButton;
	delete loadButton;
	delete txtEdit;
}

//ColorForm createWindow: Create the Qt here by placing subwidgets as children to the widget pointed to by window
QWidget* ColorForm::createWindow()
{
	//Create ColorForm Tab
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Define widget here
	//Create table
	tblRows = 12;
	tblCols = 3;
	int i,j;
	QTableWidgetItem* tempItem;
	tbl = new QTableWidget(tblRows,tblCols,window);
	QStringList hLbls, vLbls;
	hLbls << "R/Val" << "G" << "B";
	vLbls << "0 Am" << "0 Df" << "0 Sp";
	vLbls << "0 Em" << "0 Sh" << "0 Tr";
	vLbls << "1 Am" << "1 Df" << "1 Sp";
	vLbls << "1 Em" << "1 Sh" << "1 Tr";
	tbl->setHorizontalHeaderLabels(hLbls);
	tbl->setVerticalHeaderLabels(vLbls);
	for(j = 0;j<tblCols;j++)
	{
  		tbl->setColumnWidth(j,COL_WIDTH);
	}
	for(i = 0;i<tblRows;i++)
	{
   	tbl->setRowHeight(i,ROW_HEIGHT);
		for(j = 0;j<tblCols;j++)
		{
			tempItem = new QTableWidgetItem("0");
			tbl->setItem(i,j,tempItem);
		}
	}
   tbl->setGeometry(3,10,4.7*COL_WIDTH,(2+tblRows)*ROW_HEIGHT); 

	//Button for updating color
	txtEdit = new QTextEdit(window);
   txtEdit->setReadOnly(1);
  	txtEdit->setGeometry(5,300,185,40);

	//Button for updating color
	goButton = new QPushButton("Go",window);
  	goButton->setFont(QFont("Times",18,QFont::Bold));
  	goButton->setGeometry(5,350,185,40);

	//Button for updating color
	loadButton = new QPushButton("Load",window);
  	loadButton->setFont(QFont("Times",18,QFont::Bold));
  	loadButton->setGeometry(5,400,185,40);

	//Button for updating color
	saveButton = new QPushButton("Save",window);
  	saveButton->setFont(QFont("Times",18,QFont::Bold));
  	saveButton->setGeometry(5,450,185,40);
	
	QObject::connect(goButton,SIGNAL(clicked()),this,SLOT(updateColor()));
	QObject::connect(loadButton,SIGNAL(clicked()),this,SLOT(loadColor()));
	QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(saveColor()));

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

void ColorForm::updateColor()
{
   double a[3], d[3], s[3], e[3], sh, tr;
	SoMaterial* mat;
	int i;
	//Do limbs
	for(i=0;i<3;i++)
	{
   	a[i] = tbl->item(0,i)->text().toDouble();
   	d[i] = tbl->item(1,i)->text().toDouble();
   	s[i] = tbl->item(2,i)->text().toDouble();
   	e[i] = tbl->item(3,i)->text().toDouble();
	}
  	sh = tbl->item(4,0)->text().toDouble();
  	tr = tbl->item(5,0)->text().toDouble();
	mat = gfx->getMaterial(0);
	mat->ambientColor.setValue(a[0],a[1],a[2]);
	mat->diffuseColor.setValue(d[0],d[1],d[2]);
	mat->specularColor.setValue(s[0],s[1],s[2]);
	mat->emissiveColor.setValue(e[0],e[1],e[2]);
	mat->shininess.setValue(sh);
	mat->transparency.setValue(tr);

	//Do joints
	for(i=0;i<3;i++)
	{
   	a[i] = tbl->item(6,i)->text().toDouble();
   	d[i] = tbl->item(7,i)->text().toDouble();
   	s[i] = tbl->item(8,i)->text().toDouble();
   	e[i] = tbl->item(9,i)->text().toDouble();
	}
  	sh = tbl->item(10,0)->text().toDouble();
  	tr = tbl->item(11,0)->text().toDouble();
	mat = gfx->getMaterial(1);
	mat->ambientColor.setValue(a[0],a[1],a[2]);
	mat->diffuseColor.setValue(d[0],d[1],d[2]);
	mat->specularColor.setValue(s[0],s[1],s[2]);
	mat->emissiveColor.setValue(e[0],e[1],e[2]);
	mat->shininess.setValue(sh);
	mat->transparency.setValue(tr);
	
}

void ColorForm::loadColor()
{
 	int row = 0;
   int col = 0;
   QString filename = QFileDialog::getOpenFileName(window,"Select Color File",".","Color Files (*.col)");
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
		 if ((row % 6) <= 3)
		 {
       	if(col == tblCols)
       	{
           col = 0;
           row++;
       	}
		 }
		 else
		 {
			if (col == 1)
			{
				col = 0;
				row++;
			}
		 }
       if(row > tblRows)
       {
           txtEdit->setText("File is corrupt");
			  file.close();
           return;
       }
       in >> token;
   }
   file.close();
	updateColor();

}

void ColorForm::saveColor()
{
   QString filename = QFileDialog::getSaveFileName(window,"Enter file name to save",".","Text Files (*.col)");
   if (!filename.endsWith(".col"))
      filename.append(".col");
   QFile file(filename.toAscii().data());
 // Create file
   if(!file.open( QIODevice::WriteOnly))
   {
       txtEdit->setText("Error: Problem Opening file");
       return;
   }
   QTextStream out(&file);
   int i, j;
   for(i = 0; i < tblRows; i++)
   {
      for(j = 0; j < tblCols; j++)
      {
         out << tbl->item(i,j)->text() << " ";
			if ((i % 6) > 3)
				break;
      }
      out << "\n";
   }

   file.close();
   txtEdit->setText("File successfully written");


}
