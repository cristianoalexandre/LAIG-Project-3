#include "Torus.h"

Torus::Torus()
{

}

Torus::~Torus()
{
}

Torus::Torus(float iRadius, float oRadius, int slcs, int loops)
{
    this->innerRadius = iRadius;
    this->outerRadius = oRadius;
    this->slices = slcs;
    this->loops = loops;
}

void Torus::setInnerRadius(float irad)
{
    this->innerRadius = irad;
}

void Torus::setOuterRadius(float oRad)
{
    this->outerRadius = oRad;
}

void Torus::setSlices(int slcs)
{
    this->slices = slcs;
}

void Torus::setLoops(int loop)
{
    this->loops = loop;
}

void Torus::draw()
{
    glutSolidTorus(this->innerRadius, this->outerRadius, this->slices, this->loops);
}