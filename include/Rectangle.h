#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Primitive.h"

#include <iostream>


class Rectangle: public Primitive
{
private:
	Vertex2D bottomLeftVertex;
	Vertex2D upperRightVertex;

public:
	Rectangle();
	Rectangle(Vertex2D downLeftVertex, Vertex2D upRightVertex);
	virtual ~Rectangle();
	
	void setDownLeftX(float x);
	void setDownLeftY(float y);

	void setUpRightX(float x);
	void setUpRightY(float y);

	virtual int addValues(string attr, string val);
	
	void draw();
};


#endif

