/*
 * Defines classes for the different tabs we use
 *
 *
 *
 */
#ifndef ANIMATORWINDOWS_H
#define ANIMATORWINDOWS_H
#include <Animator.h>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QSlider>
#include <QLCDNumber>
#include <string>

class AbstractWindow
{
protected:
	Animator* gfx;
	QWidget* window;
public:
	AbstractWindow(Animator *);
	virtual ~AbstractWindow() = 0;
	virtual void transitionTo() = 0;
	virtual void transitionFrom() = 0;
	virtual QWidget* createWindow() = 0;
};

class FreeFormSlider: public QSlider
{
	Q_OBJECT
private:
	int id;
public:
	FreeFormSlider(int,Qt::Orientation, QWidget*);
signals:
	void sendUpdate(int, int);
public slots:
	void detectUpdate(int);	
};

class FreeForm: public AbstractWindow
{
private:
	FreeFormSlider* sldAngle[NUM_ANGLES];
	QLCDNumber* lcdAngle[NUM_ANGLES];
public:
	FreeForm(Animator*);
	~FreeForm();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();
};

class MotionForm: public QObject, public AbstractWindow
{
	Q_OBJECT
private:
	QTableWidget* tbl;
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
