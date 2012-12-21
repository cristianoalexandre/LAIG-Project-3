#ifndef OBJECT_H
#define OBJECT_H

#include "CGFobject.h"
#include "CGFappearance.h"
#include "Point.h"

#include <cstdio>
#include <iostream>

#define NUM_COORD 3
#define X 0
#define Y 1
#define Z 2

class Object : public CGFobject
{
private:
    
    Point3D pos;
    
    double angXY;
    double angXZ;
    double angZY;

    double orientationVector[NUM_COORD];
    double upVector[NUM_COORD];

    CGFappearance * appearance;

    bool animate;

public:
    Object();
    ~Object();

    void setPosX(double x);
    void setPosY(double y);
    void setPosZ(double z);
    void setAnimated(bool anim);
    void setRotationAngleOnZZaxis(double ang);
    void setRotationAngleOnYYaxis(double ang);
    void setRotationAngleOnXXaxis(double ang);
    void setUpVector(double vector[NUM_COORD]);
    void setOrientationVector(double vector[NUM_COORD]);

    double getPosX();
    double getPosY();
    double getPosZ();
    double getAngXZ();
    double getAngXY();
    double getAngZY();
    double* getUpVector();
    double* getOrientationVector();

    bool getAnimated();
    CGFappearance* getTexture();

    void updateToPosition(double x, double y, double z);
    void updatePosition(double delta_x, double delta_y, double delta_z);

    void applyTransforms();
    virtual void draw();
    virtual void setTexture(CGFappearance * appearance);
};



#endif