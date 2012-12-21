#include "Object.h"

Object::Object()
{
    setPosX(0.0);
    setPosY(0.0);
    setPosZ(0.0);
    angXY = 0;
    angXZ = 0;
    setAnimated(false);
}

Object::~Object()
{
}

void Object::setPosX(double x)
{
    pos.x = x;
}

void Object::setPosY(double y)
{
    pos.y = y;
}

void Object::setPosZ(double z)
{
    pos.z = z;
}

void Object::setAnimated(bool anim)
{
    this->animate = anim;
}

void Object::setRotationAngleOnZZaxis(double ang)
{

    this->angXY = ang;
}

void Object::setRotationAngleOnXXaxis(double ang)
{

    this->angZY = ang;
}

void Object::setRotationAngleOnYYaxis(double ang)
{


    this->angXZ = ang;

}

void Object::setOrientationVector(double vector[NUM_COORD])
{
    this->orientationVector[X] = vector[X];
    this->orientationVector[Y] = vector[Y];
    this->orientationVector[Z] = vector[Z];
}

double Object::getPosX()
{
    return pos.x;
}

double Object::getPosY()
{
    return pos.y;
}

double Object::getPosZ()
{
    return pos.z;
}

double Object::getAngXZ()
{
    return this->angXZ;
}

double Object::getAngXY()
{
    return this->angXY;
}

double Object::getAngZY()
{
    return this->angZY;
}

double* Object::getOrientationVector()
{
    return this->orientationVector;
}

bool Object::getAnimated()
{
    return this->animate;
}

CGFappearance* Object::getTexture()
{
    return this->appearance;
}

void Object::updateToPosition(double x, double y, double z)
{
    setPosX(x);
    setPosY(y);
    setPosZ(z);
}

void Object::updatePosition(double delta_x, double delta_y, double delta_z)
{
    setPosX(getPosX() + delta_x);
    setPosY(getPosY() + delta_y);
    setPosZ(getPosZ() + delta_z);
}

void Object::applyTransforms()
{
    glTranslated(getPosX(), getPosY(), getPosZ());
    double px, py, pz;
    px = getPosX();
    py = getPosY();
    pz = getPosZ();

    updateToPosition(0, 0, 0);
    if (angXY != 0 && angZY != 0)
    {
        if (angXZ != 0)
        {
            glRotatef(-this->angXZ, 0, 1, 0); //the - is there so that the rotation is CLOCKWISE
        }
        glRotatef(angXY, 0, 0, 1);
    }
    else
    {
        if (angXY != 0)
        {
            glRotatef(this->angXY, 0, 0, 1);
        }
        if (angZY != 0)
        {
            glRotatef(this->angZY, 1, 0, 0);
        }
        if (angXZ != 0)
        {
            glRotatef(-this->angXZ, 0, 1, 0); //the - is there so that the rotation is CLOCKWISE
        }
    }

    updateToPosition(px, py, pz);
}

void Object::setTexture(CGFappearance* appearance)
{
    this->appearance = appearance;
}

void Object::draw()
{
    if (appearance != NULL)
    {
        appearance->apply();
    }
}