#ifndef SG_H
#define SG_H
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoBaseColor.h>

//Declare scene graph generator function
SoSeparator* generateScene();

//Declare helper functions
SoSeparator* createPlanet(float radius, float distance, float initialAngle, SbColor color);
#endif
