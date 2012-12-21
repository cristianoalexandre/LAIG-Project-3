#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

Triangle::Triangle(Point3D left, Point3D right, Point3D top)
{
    this->left = left;
    this->right = right;
    this->top = top;
}

void Triangle::setLeftX(float x)
{
    this->left.x = x;
}

void Triangle::setLeftY(float y)
{
    this->left.y = y;
}

void Triangle::setLeftZ(float z)
{
    this->left.z = z;
}

void Triangle::setRightX(float x)
{
    this->right.x = x;
}

void Triangle::setRightY(float y)
{
    this->right.y = y;
}

void Triangle::setRightZ(float z)
{
    this->right.z = z;
}

void Triangle::setTopX(float x)
{
    this->top.x = x;
}

void Triangle::setTopY(float y)
{
    this->top.y = y;
}

void Triangle::setTopZ(float z)
{
    this->top.z = z;
}

void Triangle::draw()
{
    glBegin(GL_TRIANGLES);
    glTexCoord2i(0, 0);
    glVertex3f(this->left.x, this->left.y, this->left.z);
    glTexCoord2i(1, 0);
    glVertex3f(this->right.x, this->right.y, this->right.z);
    glTexCoord2i(this->top.x, this->top.y);
    glVertex3f(this->top.x, this->top.y, this->top.z);
    glEnd();
}