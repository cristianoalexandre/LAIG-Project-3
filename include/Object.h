#ifndef OBJECT_H
#define OBJECT_H

#include "CGFobject.h"
#include "CGFappearance.h"

#include <stdio.h>
#include <iostream>

#define NUM_COORD 3
#define X 0
#define Y 1
#define Z 2

class Object: public CGFobject{

private:
	double pos_x;
	double pos_y;
	double pos_z;

	double ang_XY;
	double ang_XZ;
	double ang_ZY;

	double orientation_vector[NUM_COORD];
	double up_vector[NUM_COORD];

	CGFappearance * appearance;

	bool animate;

public:
	Object();
	~Object();

	void setPos_x(double x);
	void setPos_y(double y);
	void setPos_z(double z);
	void setAnimated(bool anim);
	void setRotationAngleOnZZaxis(double ang);
	void setRotationAngleOnYYaxis(double ang);
	void setRotationAngleOnXXaxis(double ang);
	void setUpVector(double vector[NUM_COORD]);
	void setOrientationVector(double vector[NUM_COORD]);

	double getPos_x();
	double getPos_y();
	double getPos_z();
	double getAng_XZ();
	double getAng_XY();
	double getAng_ZY();
	double* getUpVector();
	double* getOrientationVector();

	bool getAnimated();
	CGFappearance* getTexture();


	void updateToPosition(double x, double y, double z);
	void updatePosition(double delta_x, double delta_y, double delta_z);

	void applyTransforms();
	virtual void draw(); //virtual trouble
	virtual void setTexture(CGFappearance * appearance);

};



#endif