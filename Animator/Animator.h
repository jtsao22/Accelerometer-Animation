/*
 * Defines a class for Group 2's EE180D free form animation widget
 *
 *
 *
 */
#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <QCoin.h>
#include <AbstractWindow.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoComposeRotation.h>
#include <QTabWidget>

/*
 * Angles
 * --------------------------------------
 * Angle 0 = Shoulder Lateral Angle
 * Angle 1 = Shoulder Alateral Angle
 * Angle 2 = Shoulder Rotation Angle
 * Angle 3 = Elbow Bending Angle
 * Angle 4 = Elbow Rotation Angle
 * Angle 5 = Wrist Bending Angle
 */

// DEFINES

#define UPPERARM_RADIUS 1
#define UPPERARM_LENGTH 3

#define FOREARM_RADIUS 1
#define FOREARM_LENGTH 3

#define FINGER_RADIUS 0.2
#define FINGER_LENGTH 1.5

#define THUMB_RADIUS 0.23
#define THUMB_LENGTH 1.0

#define COL_WIDTH 40
#define ROW_HEIGHT 20

#define TAB_X 10
#define TAB_Y 50
#define TAB_WIDTH 200
#define TAB_HEIGHT 708

#define VIEWER_X 210
#define VIEWER_Y 100
#define VIEWER_WIDTH 800
#define VIEWER_HEIGHT 600

#define NUM_ANGLES 6
#define NUM_PARAMS 4
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

class AbstractWindow;

class Animator: public QCoin
{
	Q_OBJECT
private:
	SoSeparator* root;
	SoSeparator* body;
	SoSeparator* arm;
	SoRotation* angle[NUM_ANGLES];
	SbVec3f angleAxis[NUM_ANGLES];
	SoCalculator* angleCalc[NUM_ANGLES];
	SoComposeRotation* angleCompRot[NUM_ANGLES];
	SoElapsedTime* time;
	void createSceneGraph();

	//GUI stuff
	QTabWidget* tabs;
	int num_windows;
	AbstractWindow** windows;
	int currentTab;
	void defineWindows();


public:
	Animator(QWidget* parent = 0);
	float getAngle(int);
	void enableAngle(int, bool);
	void setAngleExpr(int, std::string);
	~Animator();
	void show();
public slots:
   void setAngle(int,int);
	void tabSwitch(int);

signals:

};
#endif
