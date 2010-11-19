/*
 * Defines classes for the different tabs we use
 *
 *
 *
 */
#ifndef MOTIONFORM_H
#define MOTIONFORM_H
#include <AbstractWindow.h>
#include <QTableWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

class MotionForm: public QObject, public AbstractWindow
{
	Q_OBJECT
private:
	QTableWidget* tbl;
	QLabel* speedLabel;
	QTextEdit* speedText;	
	QPushButton* goButton;
	QPushButton* fileButton;
	QPushButton* saveButton;
	QPushButton* resetButton;
   QTextEdit* txtEdit;
public:
	MotionForm(Animator*);
	~MotionForm();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();
public slots:
	void updateMotion(void);
   void updateWithFile(void);
   void saveFile(void);
   void resetParams(void);
};
#endif
