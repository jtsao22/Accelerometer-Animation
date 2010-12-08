#!/usr/bin/python
import os;

#Print initial prompt
print 'tabMaker v.1 for EE180D Animator';

#Get class name
className = raw_input('Enter the name of the C++ class representing your new tab: ');
if className == '':
 exit(1);

#Get label name
labelName = raw_input('Enter the label name for the tab as it will appear in the GUI: ');
if labelName == '':
 labelName = className;

#Does it need to be a Q_Object?
while 1:
 qObj = raw_input('Will you need to define your own Qt signals/slots? (y/n): ');
 if qObj == 'y' or qObj == 'Y':
  qObj = 1;
  break;
 elif qObj == 'n' or qObj == 'N':
  qObj = 0;
  break;

#Create Header File
fid = open('{0}.h'.format(className),'w');
if not qObj:
 fid.write('''#ifndef {0}_H
#define {0}_H
#include <AbstractWindow.h>

/*
 * Additional Inherited Members from AbstractWindow:
 *
 * protected:
 * 	Animator* gfx = Pointer to Animator class containing 3D animation, see Animator.h
 * 	QWidget* window = Pointer to Qt window that is represented by {0}
 * 	QString label = String containing label for {0} as it will appear in the GUI
 *
 * public:
 * 	QString getLabel() = Function that returns label
 * 
 */

class {0}: public AbstractWindow
{{
private:
//Add private data here

public:
	{0}(Animator*);
	~{0}();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();

//Add additional public data here
}};
#endif'''.format(className));
else:
 fid.write('''#ifndef {0}_H
#define {0}_H
#include <AbstractWindow.h>

/*
 * Additional Inherited Members from AbstractWindow:
 *
 * protected:
 *    Animator* gfx = Pointer to Animator class containing 3D animation, see Animator.h
 *    QWidget* window = Pointer to Qt window that is represented by {0}
 *    QString label = String containing label for {0} as it will appear in the GUI
 *
 * public:
 *    QString getLabel() = Function that returns label
 * 
 */

class {0}: public QObject, public AbstractWindow
{{
	Q_OBJECT
private:
//Add private data here

public:
	{0}(Animator*);
	~{0}();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();

//Add additional public data here

signals:
//Add signals here

public slots:
//Add slots here

}};
#endif'''.format(className));

fid.close();

#Create Source File
fid = open('{0}.cpp'.format(className),'w');
fid.write('''#include <{0}.h>

//{0} Constructor: Most likely you do not need to modify this
{0}::{0}(Animator * newGfx):AbstractWindow(newGfx,"{1}"){{}}

//{0} Destructor: Delete all dynamically allocated data here
{0}::~{0}()
{{

}}

//{0} createWindow: Create the Qt here by placing subwidgets as children to the widget pointed to by window
QWidget* {0}::createWindow()
{{
	//Create {0} Tab
	window = new QWidget;
	window->setGeometry(TAB_X,TAB_Y,TAB_WIDTH,TAB_HEIGHT);

	//Define widget here

	return window;
}}
//{0} transitionTo: Create any Qt/Coin connections or enable Coin engines for Coin connections made in createWindow
void {0}::transitionTo()
{{

}}

//{0} transitionFrom: Remove Qt/Coin connections or disable Coin engines that should not be present when leaving the {0} tab
void {0}::transitionFrom()
{{

}}'''.format(className,labelName));
fid.close();

#Update project file
print('Updating Animator.pro');
fid = open('Animator.pro','r');
lines = fid.readlines();
fid.close();
for i in range(len(lines)):
 line = lines[i];
 if line[:7] == 'HEADERS':
  lines[i] = lines[i].replace('\n',' {0}.h\n'.format(className));
 elif line[:7] == 'SOURCES':
  lines[i] = lines[i].replace('\n',' {0}.cpp\n'.format(className));
fid = open('Animator.pro','w');
fid.writelines(lines);
fid.close();

#Call qmake
os.system('qmake');

#Print further instructions
print('Please define your new tab in {0}.h and {0}.cpp'.format(className));
print('To complete the integration of your tab into the Animator, modify the defineWindows() function at the top of Animator.cpp as follows');
print('	(1) Increase the value of num_windows to account for your new tab');
print('	(2) Insert your window into the windows array: windows[?] = new {0}(this);'.format(className));
print('	    where ? is a valid integer index not used by any other tab.');
print('	(3) Add #include <{0}.h> to the top of Animator.cpp'.format(className));
print('After this, simply type make to compile and you are good to go!');

