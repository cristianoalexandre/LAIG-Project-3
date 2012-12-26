#include "LineAnimation.h"

LineAnimation::LineAnimation()
{
    setDelta_x(0.0);
    setDelta_y(0.0);
    setDelta_z(0.0);
    setAnimatedObject(NULL);
    setTotalAnimationTime(1.0);
    setTotalAnimationDistance(0.0);
}

LineAnimation::~LineAnimation()
{
}

void LineAnimation::setDelta_x(double x)
{

    this->delta_x = x;
}

void LineAnimation::setDelta_y(double y)
{

    this->delta_y = y;
}

void LineAnimation::setDelta_z(double z)
{

    this->delta_z = z;
}

void LineAnimation::setObj_ini_position_x(double ini_x)
{

    this->obj_ini_postion_x;
}

void LineAnimation::setObj_ini_position_y(double ini_y)
{

    this->obj_ini_postion_y;
}

void LineAnimation::setObj_ini_position_z(double ini_z)
{

    this->obj_ini_postion_z;
}

void LineAnimation::setMiliSecs(unsigned int mSecs)
{
    LineAnimation::mili_secs = mSecs;
}

void LineAnimation::setTotalAnimationTime(double s)
{

    this->total_animation_time = s;
}

void LineAnimation::setTotalAnimationDistance(double d)
{

    this->total_animation_distance = d;
}

void LineAnimation::setAnimatedObject(Object* obj)
{

    this->animatedObject = obj;
}

void LineAnimation::setControlPoints(ctrlPointsPair* cps)
{

    this->controlPoints = cps;
}

double LineAnimation::getDelta_x() const
{

    return this->delta_x;
}

double LineAnimation::getDelta_y() const
{

    return this->delta_y;
}

double LineAnimation::getDelta_z() const
{

    return this->delta_z;
}

double LineAnimation::getTotal_delta_x() const
{

    return this->total_delta_x;
}

double LineAnimation::getTotal_delta_y() const
{

    return this->total_delta_y;
}

double LineAnimation::getTotal_delta_z() const
{

    return this->total_delta_z;
}

double LineAnimation::getObj_ini_postion_x() const
{

    return this->obj_ini_postion_x;
}

double LineAnimation::getObj_ini_postion_y() const
{

    return this->obj_ini_postion_y;
}

double LineAnimation::getObj_ini_postion_z() const
{

    return this->obj_ini_postion_z;
}

double LineAnimation::getObj_end_postion_x() const
{

    return this->obj_end_postion_x;
}

double LineAnimation::getObj_end_postion_y() const
{

    return this->obj_end_postion_y;
}

double LineAnimation::getObj_end_postion_z() const
{

    return this->obj_end_postion_z;
}

unsigned int LineAnimation::getMiliSecs()
{

    return LineAnimation::mili_secs;
}

double LineAnimation::getTotalAnimationTime() const
{

    return this->total_animation_time;
}

double LineAnimation::getTotalAnimationDistance() const
{

    return this->total_animation_distance;
}

Object* LineAnimation::getAnimatedObject() const
{

    return this->animatedObject;
}

ctrlPointsPair* LineAnimation::getControlPoints() const
{

    return this->controlPoints;
}

void LineAnimation::checkDeltas(double dx, double dy, double dz)
{

    if ((animatedObject->getPos_x() + dx) > obj_end_postion_x)
    {

        setDelta_x(obj_end_postion_x - animatedObject->getPos_x());
    }
    if ((animatedObject->getPos_y() + dy) > obj_end_postion_y)
    {

        setDelta_y(obj_end_postion_y - animatedObject->getPos_y());
    }
    if ((animatedObject->getPos_z() + dz) > obj_end_postion_z)
    {

        setDelta_x(obj_end_postion_z - animatedObject->getPos_z());
    }
}

void LineAnimation::initValues()
{

    //IMEDIATELY AFTER KNOWING THE CONTROL POINTS WE CALCULATE THE OVERALL DESTANCE OF THE ANIMATION
    total_delta_x = controlPoints->second->at(X) - controlPoints->first->at(X);
    total_delta_y = controlPoints->second->at(Y) - controlPoints->first->at(Y);
    total_delta_z = controlPoints->second->at(Z) - controlPoints->first->at(Z);
    double dist_x = (double) powl(total_delta_x, 2.0);
    double dist_y = (double) powl(total_delta_y, 2.0);
    double dist_z = (double) powl(total_delta_z, 2.0);

    total_animation_distance = (double) sqrtl(dist_x + dist_y + dist_z);
}

void LineAnimation::init()
{

    delta_x = (LineAnimation::getMiliSecs() / (total_animation_time * 1000)) * total_delta_x;
    delta_y = (LineAnimation::getMiliSecs() / (total_animation_time * 1000)) * total_delta_y;
    delta_z = (LineAnimation::getMiliSecs() / (total_animation_time * 1000)) * total_delta_z;

    obj_ini_postion_x = this->animatedObject->getPos_x();
    obj_ini_postion_y = this->animatedObject->getPos_y();
    obj_ini_postion_z = this->animatedObject->getPos_z();

    obj_end_postion_x = obj_ini_postion_x + total_delta_x;
    obj_end_postion_y = obj_ini_postion_y + total_delta_y;
    obj_end_postion_z = obj_ini_postion_z + total_delta_z;

}

int LineAnimation::updateObjectPosition()
{

    if (fabs(animatedObject->getPos_x() - obj_ini_postion_x) >= fabs(total_delta_x))
    {
        setDelta_x(0);
    }
    if (fabs(animatedObject->getPos_y() - obj_ini_postion_y) >= fabs(total_delta_y))
    {
        setDelta_y(0);
    }
    if (fabs(animatedObject->getPos_z() - obj_ini_postion_z) >= fabs(total_delta_z))
    {
        setDelta_z(0);
    }

    if (fabs(animatedObject->getPos_x() - obj_ini_postion_x) >= fabs(total_delta_x) &&
            fabs(animatedObject->getPos_y() - obj_ini_postion_y) >= fabs(total_delta_y) &&
            fabs(animatedObject->getPos_z() - obj_ini_postion_z) >= fabs(total_delta_z))
    {
        return 1;
    }
    else
    {
        animatedObject->updatePosition(this->delta_x, this->delta_y, this->delta_z);
        return 0;
    }

}

void LineAnimation::animate()
{

    glPushMatrix();
    this->animatedObject->applyTransforms();
    this->animatedObject->draw();
    glPopMatrix();
}


