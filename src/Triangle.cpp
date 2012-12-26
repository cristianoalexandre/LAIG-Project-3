#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

Triangle::Triangle(Vertex3D left, Vertex3D right, Vertex3D top)
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

int Triangle::addValues(string attr, string val)
{

    if (attr == "x1")
    {
        setLeftX(atof(val.c_str()));
    }
    else
    {
        if (attr == "y1")
        {
            setLeftY(atof(val.c_str()));
        }
        else
        {
            if (attr == "z1")
            {
                setLeftZ(atof(val.c_str()));
            }
            else
            {
                if (attr == "x2")
                {
                    setRightX(atof(val.c_str()));
                }
                else
                {
                    if (attr == "y2")
                    {
                        setRightY(atof(val.c_str()));
                    }
                    else
                    {
                        if (attr == "z2")
                        {
                            setRightZ(atof(val.c_str()));
                        }
                        else
                        {
                            if (attr == "x3")
                            {
                                setTopX(atof(val.c_str()));
                            }
                            else
                            {
                                if (attr == "y3")
                                {
                                    setTopY(atof(val.c_str()));
                                }
                                else
                                {
                                    if (attr == "z3")
                                    {
                                        setTopZ(atof(val.c_str()));
                                        return 1;
                                    }
                                    else
                                    {
                                        //printf("ERROR: in Triangle.addValues - unrecognized attribute: %s\n\nPress any key to exit\n", attr);
                                        cin.get();
                                        exit(1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
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