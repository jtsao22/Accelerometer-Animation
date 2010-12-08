#ifndef ANIMATEFORM_H
#define ANIMATEFORM_H
#include <AbstractWindow.h>
#include <QTextEdit>
#include <QPushButton>
#include <QTimer>
#include <QStringList>

/*
 * Additional Inherited Members from AbstractWindow:
 *
 * protected:
 *    Animator* gfx = Pointer to Animator class containing 3D animation, see Animator.h
 *    QWidget* window = Pointer to Qt window that is represented by AnimateForm
 *    QString label = String containing label for AnimateForm as it will appear in the GUI
 *
 * public:
 *    QString getLabel() = Function that returns label
 * 
 */

//enum AnimateState { STOPPED, PLAYING, PAUSED };

class AnimateForm: public QObject, public AbstractWindow
{
	Q_OBJECT
private:
//Add private data here
	QTextEdit* txtEdit;
	QPushButton *loadButton;
	QPushButton *playButton;
	QPushButton *stopButton;
	QTimer* timer;
	QStringList script;
	//AnimateState state;
	int scriptLine;
	bool doSoft;
	int parse(QString line);
	
public:
	AnimateForm(Animator*);
	~AnimateForm();
	void transitionTo();
	void transitionFrom();
	QWidget* createWindow();

//Add additional public data here

signals:
//Add signals here

public slots:
//Add slots here
	void loadFile();
	void loop();
	void playPress();
	void stopPress();
};
#endif
