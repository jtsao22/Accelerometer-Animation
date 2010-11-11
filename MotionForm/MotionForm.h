/*
 * Defines a class for Group 2's EE180D free form animation widget
 *
 *
 *
 */
#ifndef MOTIONFORM_H
#define MOTIONFORM_H
#include <QCoin.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoComposeRotation.h>
#include <QTableWidget>
#include <QLabel>


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
#define NUM_ANGLES 6
#define NUM_PARAMS 4

class MotionForm: public QCoin
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
	QTableWidget* tbl;
    QWidget *mainWindow;

public:
	MotionForm(QWidget *main, QTableWidget* newTbl, QWidget* parent = 0);
public slots:
	void updateMotion(void);
    void updateWithFile(void);
    void resetParams(void);
signals:

};
#endif
