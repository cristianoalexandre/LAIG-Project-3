#include "Cylinder.h"
#include "CGFappearance.h"

Cylinder::Cylinder()
{
    topTexture = NULL;
    bottomTexture = NULL;
    circularTexture = NULL;
}

Cylinder::~Cylinder()
{
}

Cylinder::Cylinder(float bRadius, float tRadius, float h, int slcs, int stcks)
{
    this->baseRadius = bRadius;
    this->topRadius = tRadius;
    this->height = h;
    this->slices = slcs;
    this->stacks = stcks;
    topTexture = NULL;
    bottomTexture = NULL;
    circularTexture = NULL;
    quadricTop = gluNewQuadric();
    quadricCircular = gluNewQuadric();
    quadricBottom = gluNewQuadric();

    gluQuadricTexture(quadricTop, true);
    gluQuadricTexture(quadricBottom, true);
    gluQuadricTexture(quadricCircular, true);
}

void Cylinder::setBaseRadius(float bRad)
{
    this->baseRadius = bRad;
}

void Cylinder::setTopRadius(float tRad)
{
    this->topRadius = tRad;
}

void Cylinder::setHeight(float h)
{
    this->height = h;
}

void Cylinder::setSlices(int slcs)
{
    this->slices = slcs;
}

void Cylinder::setStacks(int stcks)
{
    this->stacks = stcks;
}

void Cylinder::draw()
{
    if (circularTexture != NULL)
        circularTexture->apply();
    gluCylinder(quadricCircular, this->baseRadius, this->topRadius, this->height, this->slices, this->stacks);

    if (bottomTexture != NULL)
        bottomTexture->apply();

    //Base circle
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(180, 0, 1, 0);
    gluDisk(quadricBottom, 0.0, this->baseRadius, this->slices, 1);
    glPopMatrix();

    if (topTexture != NULL)
        topTexture->apply();

    //Top Circle
    glPushMatrix();
    glTranslatef(0.0, 0.0, this->height);
    gluDisk(quadricTop, 0.0, this->topRadius, this->slices, 1);
    glPopMatrix();
}

int Cylinder::addValues(string attr, string val)
{
    if (attr == "base")
    {
        setBaseRadius(atof(val.c_str()));
    }
    else
    {
        if (attr == "top")
        {
            setTopRadius(atof(val.c_str()));
        }
        else
        {
            if (attr == "height")
            {
                setHeight(atof(val.c_str()));
            }
            else
            {
                if (attr == "slices")
                {
                    setSlices(atoi(val.c_str()));
                }
                else
                {
                    if (attr == "stacks")
                    {
                        setStacks(atoi(val.c_str()));
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void Cylinder::setTopTexture(CGFappearance* appearance)
{
    topTexture = appearance;
}

void Cylinder::setCircularTexture(CGFappearance* appearance)
{
    circularTexture = appearance;
}

void Cylinder::setBottomTexture(CGFappearance* appearance)
{
    bottomTexture = appearance;
}

void Cylinder::setTexture(CGFappearance* appearance)
{
    setTopTexture(appearance);
    setBottomTexture(appearance);
    setCircularTexture(appearance);
}