#ifndef TORUS_H
#define TORUS_H

#include "Primitive.h"

class Torus: public Primitive
{
private:
	float innerRadius;
	float outerRadius;
	int slices;
	int loops;

public:
	Torus();
	Torus(float iRadius, float oRadius, int slcs, int loops);
	virtual ~Torus();

	void setInnerRadius(float irad);
	void setOuterRadius(float oRad);
	void setSlices(int slcs);
	void setLoops(int loop);
	void draw();

	virtual int addValues(string attr, string val);

};

#endif