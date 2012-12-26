#ifndef CYLINDER_H
#define CYLINDER_H

#include "Primitive.h"
#include "CGFappearance.h"

class Cylinder : public Primitive
{
private:
    float baseRadius;
    float topRadius;
    float height;
    int slices;
    int stacks;
    CGFappearance * topTexture;
    CGFappearance * bottomTexture;
    CGFappearance * circularTexture;
    GLUquadric* quadricTop;
    GLUquadric* quadricCircular;
    GLUquadric* quadricBottom;
public:
    Cylinder();
    Cylinder(float bRadius, float tRadius, float h, int slcs, int stcks);
    virtual ~Cylinder();

    void setBaseRadius(float bRad);
    void setTopRadius(float tRad);
    void setHeight(float h);
    void setSlices(int slcs);
    void setStacks(int stcks);

    void setTexture(CGFappearance * appearance);
    void setTopTexture(CGFappearance * appearance);
    void setBottomTexture(CGFappearance * appearance);
    void setCircularTexture(CGFappearance * appearance);

    void draw();

    virtual int addValues(string attr, string val);
};

#endif