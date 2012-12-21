#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Primitive.h"

#include <iostream>

class Rectangle : public Primitive
{
private:
    Point2D bottomLeftVertex;
    Point2D upperRightVertex;

public:
    Rectangle();
    Rectangle(Point2D downLeftVertex, Point2D upRightVertex);
    virtual ~Rectangle();

    void setDownLeftX(float x);
    void setDownLeftY(float y);

    void setUpRightX(float x);
    void setUpRightY(float y);

    void draw();
};


#endif

