#ifndef ReadMATLAB_H
#define ReadMATLAB_H
#include <AbstractWindow.h>
#include <QTextEdit>
#include <QPushButton>

/*
 * Additional Inherited Members from AbstractWindow:
 *
 * protected:
 *    Animator* gfx = Pointer to Animator class containing 3D animation, see Animator.h
 *    QWidget* window = Pointer to Qt window that is represented by ReadMATLAB
 *    QString label = String containing label for ReadMATLAB as it will appear in the GUI
 *
 * public:
 *    QString getLabel() = Function that returns label
 * 
 */

class ReadMATLAB: public QObject, public AbstractWindow
{
	Q_OBJECT
private:
//Add private data here
    QTextEdit* txtEdit;
    QPushButton *fileButton;

public:
	ReadMATLAB(Animator*);
	~ReadMATLAB();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();

//Add additional public data here

signals:
//Add signals here

public slots:
//Add slots here
    void updateWithFile(void);
    void change_velocity(int speed);

};
#endif
