#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/SoOutput.h>
#include <gen_scene.h>

int main(int argc, char ** argv)
{
	SoQt::init(argc,argv,argv[0]);

	SoSeparator* root = generateScene();

	//Write scene graph to outputfile

	SoOutput out;
	out.openFile("graph.vi");
	SoWriteAction writeAction(&out);
	writeAction.apply(root);
	out.closeFile();

	root->unref();
  
	return 0;
}

//Define scene graph
SoSeparator* generateScene()
{	
    //create scene root
    SoSeparator* root = new SoSeparator;
    root->ref();

    //model of the Sun

    // diffuse material
    SoMaterial* sunMat = new SoMaterial;
    sunMat->diffuseColor.setValue(1.0f,1.0f,0.3f);
    root->addChild(sunMat);

    // sphere of radius 10
    SoSphere* sun = new SoSphere;
    sun->radius.setValue(10.f);
    root->addChild(sun);

    //model of the Earth
    root->addChild(createPlanet(4.0f,45.f,0.f,SbColor(0.7f,0.7f,1.0f)));

    //model of Mercury
    root->addChild(createPlanet(2.0f,20.f, float(4*M_PI/3),
                                 SbColor(1.0f,0.3f,0.f)));

    //model of Venus
    root->addChild(createPlanet(3.0f,30.f, float(3*M_PI/3),
                                 SbColor(1.0f,0.6f,0.f)));

	 return root;
}

//Define helper functions
SoSeparator* createPlanet(float radius, float distance, float initialAngle, SbColor color)
{
	   SoSeparator *root = new SoSeparator;

		//material of planet
		SoMaterial* material = new SoMaterial;
		material->diffuseColor.setValue(color);
		root->addChild(material);

		//revolution around the Sun
		SoRotationXYZ* rotY = new SoRotationXYZ;
		rotY->axis = SoRotationXYZ::Y;

		// connect engine to rotation node
		SoElapsedTime* counter = new SoElapsedTime;
		counter->speed.setValue(20.f/distance);
		rotY->angle.connectFrom(&counter->timeOut);

		// translation from the Sun
		SoTranslation* trans = new SoTranslation;
		trans->translation.setValue(distance*float(+cos(initialAngle)),0.f,
											 distance*float(-sin(initialAngle)));

		root->addChild(trans);
		root->addChild(rotY);

		//planet geometry
		SoSphere *sphere = new SoSphere;
		sphere->radius.setValue(radius);
		root->addChild(sphere);	

		return root;
}
