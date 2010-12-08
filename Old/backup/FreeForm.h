/*
 * Defines classes for the different tabs we use
 *
 *
 *
 */
#ifndef FREEFORM_H
#define FREEFORM_H
#include <AbstractWindow.h>
#include <QSlider>
#include <QLCDNumber>

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
#endif
