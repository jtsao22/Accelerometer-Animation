#ifndef ColorForm_H
#define ColorForm_H
#include <AbstractWindow.h>
#include <QTableWidget>
#include <QPushButton>
#include <QTextEdit>

/*
 * Additional Inherited Members from AbstractWindow:
 *
 * protected:
 * 	Animator* gfx = Pointer to Animator class containing 3D animation, see Animator.h
 * 	QWidget* window = Pointer to Qt window that is represented by ColorForm
 * 	QString label = String containing label for ColorForm as it will appear in the GUI
 *
 * public:
 * 	QString getLabel() = Function that returns label
 * 
 */

class ColorForm: public QObject, public AbstractWindow
{
	Q_OBJECT
private:
//Add private data here
	QTableWidget* tbl;
	QPushButton* goButton;

public:
	ColorForm(Animator*);
	~ColorForm();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();

public slots:
	void updateColors();
};
#endif
