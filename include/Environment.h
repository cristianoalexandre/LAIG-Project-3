#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include "Patch.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Sphere.h"

class Environment
{
private:

	Plane* wall1;
	Plane* wall2;
	Plane* wall3;
	Plane* wall4;
	Plane* floor;
	Plane* ceiling;

	Patch* curvedSurface1;

	Cylinder* torusSupport;
	Sphere* emitterSphere;

	CGFappearance* wallTexture;
	CGFappearance* floorTexture;
	CGFappearance* ceilingTexture;

	CGFappearance* cylinderTexture;
	CGFappearance* sphereTexture;
	CGFappearance* tableTopTexture;
	CGFappearance* tableLegTexture;

	CGFappearance* wallTexture2;
	CGFappearance* floorTexture2;
	CGFappearance* ceilingTexture2;

	CGFappearance* cylinderTexture2;
	CGFappearance* sphereTexture2;
	CGFappearance* tableTopTexture2;
	CGFappearance* tableLegTexture2;

	CGFappearance* wallTexture3;
	CGFappearance* floorTexture3;
	CGFappearance* ceilingTexture3;

	CGFappearance* cylinderTexture3;
	CGFappearance* sphereTexture3;
	CGFappearance* tableTopTexture3;
	CGFappearance* tableLegTexture3;


public:

	Environment();

	void activateTextureSet(int i);
	void draw();

};


#endif