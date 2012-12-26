#ifndef PRIMITIVE_H
#define	PRIMITIVE_H

#include "Object.h"

#include <iostream>
#include <string>

using namespace std;

typedef struct
{
    float x;
    float y;
} Vertex2D;

typedef struct
{
    float x;
    float y;
    float z;
} Vertex3D;

class Primitive: public Object
{
private:
    string id;
public:

    virtual int addValues(string attr, string val)
    {
        return 0;
    };

    virtual void draw()
    {
    };
};

#endif	/* FIGURE_H */

