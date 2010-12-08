#ifndef blah_H
#define blah_H
#include <AbstractWindow.h>

/*
 * Additional Inherited Members from AbstractWindow:
 *
 * protected:
 *    Animator* gfx = Pointer to Animator class containing 3D animation, see Animator.h
 *    QWidget* window = Pointer to Qt window that is represented by blah
 *    QString label = String containing label for blah as it will appear in the GUI
 *
 * public:
 *    QString getLabel() = Function that returns label
 * 
 */

class blah: public QObject, public AbstractWindow
{
	Q_OBJECT
private:
//Add private data here

public:
	blah(Animator*);
	~blah();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();

//Add additional public data here

signals:
//Add signals here

public slots:
//Add slots here

};
#endif