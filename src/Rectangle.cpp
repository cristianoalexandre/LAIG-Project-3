#include "Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

Rectangle::Rectangle(Point2D downLeftVertex, Point2D upRightVertex)
{

    this->bottomLeftVertex = downLeftVertex;
    this->upperRightVertex = upRightVertex;
}

void Rectangle::setDownLeftX(float x)
{
    this->bottomLeftVertex.x = x;
}

void Rectangle::setDownLeftY(float y)
{
    this->bottomLeftVertex.y = y;
}

void Rectangle::setUpRightX(float x)
{
    this->upperRightVertex.x = x;
}

void Rectangle::setUpRightY(float y)
{
    this->upperRightVertex.y = y;
}

void Rectangle::draw()
{

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glEnable(GL_NORMALIZE);
    glTexCoord2i(0, 0);
    glVertex3f(this->bottomLeftVertex.x, this->bottomLeftVertex.y, 0);
    glTexCoord2i(1, 0);
    glVertex3f(this->upperRightVertex.x, this->bottomLeftVertex.y, 0);
    glTexCoord2i(1, 1);
    glVertex3f(this->upperRightVertex.x, this->upperRightVertex.y, 0);
    glTexCoord2i(0, 1);
    glVertex3f(this->bottomLeftVertex.x, this->upperRightVertex.y, 0);
    glEnd();
}
