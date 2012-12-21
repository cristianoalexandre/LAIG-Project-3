#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere: public Primitive
{
private:
	float radius;
	int slices;
	int stacks;

public:
	Sphere();
	Sphere(float radius, int slcs, int stcks);
	virtual ~Sphere();

	void setRadius(float rad);
	void setSlices(int slcs);
	void setStacks(int stcks);
	void draw();

	virtual int addValues(string attr, string val);
};

#endif