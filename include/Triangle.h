#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Primitive.h"

class Triangle : public Primitive
{
private:
    Point3D left;
    Point3D right;
    Point3D top;
public:
    Triangle();
    Triangle(Point3D left, Point3D right, Point3D top);
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
};

#endif