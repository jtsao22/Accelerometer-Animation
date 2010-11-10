/*
 * Defines a class for Group 2's EE180D free form animation widget
 *
 *
 *
 */
#ifndef FREEFORM_H
#define FREEFORM_H
#include <QCoin.h>
#include <Inventor/nodes/SoRotation.h>


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

class FreeForm: public QCoin
{
	Q_OBJECT
private:
	SoSeparator* root;
	SoSeparator* body;
	SoSeparator* arm;
	SoRotation* angle[6];
	SbVec3f angleAxis[6];

public:
	FreeForm(QWidget* parent = 0);
public slots:
	void setAngle0(int);
	void setAngle1(int);
	void setAngle2(int);
	void setAngle3(int);
	void setAngle4(int);
   void setAngle5(int);

signals:

};
#endif
