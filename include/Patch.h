#ifndef PATCH_H
#define	PATCH_H

#include "Object.h"
#include "CGFappearance.h"

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef GLfloat vec3[3];
typedef GLfloat vec2[2];

class Patch : public Object
{
private:
    vec3 * control_points;
    vec2 * texture_points;
    int * divisions;
    int order_u;
    int order_v;
    int stride_u;
    int stride_v;

public:
    Patch();
    Patch(GLint order_u, GLint order_v, GLint divisions_u, GLint divisions_v, GLfloat control_points[][3], int lin, int col);
    ~Patch();

    void draw();
};

#endif	/* PATCH_H */

