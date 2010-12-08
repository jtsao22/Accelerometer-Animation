/*
 * Defines a class for Group 2's EE180D free form animation widget
 *
 *
 *
 */
#ifndef GENERALFORM_H
#define GENERALFORM_H
#include <QCoin.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/engines/SoCalculator.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/engines/SoComposeRotation.h>
#include <QTableWidget>


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
#define NUM_PARAMS 1

class GeneralForm: public QCoin
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

public:
	GeneralForm(QTableWidget* newTbl, QWidget* parent = 0);
public slots:
	void updateMotion(void);
signals:

};
#endif
