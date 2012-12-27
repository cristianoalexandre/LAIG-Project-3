#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Primitive.h"

class Triangle: public Primitive
{
private:
	Vertex3D left;
	Vertex3D right;
	Vertex3D top;
public:
	Triangle();
	Triangle(Vertex3D left, Vertex3D right, Vertex3D top);
	virtual ~Triangle();

	void setLeftX(float x);
	void setLeftY(float y);
	void setLeftZ(float z);

	void setRightX(float x);
	void setRightY(float y);
	void setRightZ(float z);

	void setTopX(float x);
	void setTopY(float y);
	void setTopZ(float z);

	void draw();

	virtual int addValues(string attr, string val);
};

#endif