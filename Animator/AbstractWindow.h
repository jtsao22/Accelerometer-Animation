/*
 * Defines classes for the different tabs we use
 *
 *
 *
 */
#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H
#include <Animator.h>
#include <QString>
#include <QWidget>

class Animator;

class AbstractWindow
{
protected:
	Animator* gfx;
	QWidget* window;
	QString label;
public:
	AbstractWindow(Animator *, QString);
	virtual ~AbstractWindow() = 0;
	virtual void transitionTo() = 0;
	virtual void transitionFrom() = 0;
	virtual QWidget* createWindow() = 0;
	QString getLabel();
};

#endif
