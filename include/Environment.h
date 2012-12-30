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


public:

	Environment();

	void activateTextureSet(int i);
	void draw();

};


#endif