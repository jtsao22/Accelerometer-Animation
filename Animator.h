/*
 * Defines a class for Group 2's EE180D animation widget
 *
 *
 *
 */
#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <QCoin.h>
#include <Inventor/nodes/SoRotation.h>

class Animator: public QCoin
{
	Q_OBJECT
private:
	SoSeparator* root;
	SoSeparator* body;
	SoSeparator* arm;
	SoRotation* angle[4];

public:
	Animator(QWidget* parent = 0);
public slots:
	void setAngle1(int);
	void setAngle2(int);
	void setAngle3(int);
	void setAngle4(int);

signals:

};
#endif
