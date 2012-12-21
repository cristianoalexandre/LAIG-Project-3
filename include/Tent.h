#ifndef TENT_H
#define	TENT_H

#include "Patch.h"

class Tent : Object
{
    private:
        Patch * patch;
        GLfloat height;
        GLfloat z_bound;
        GLfloat x_bound;
    public:
        Tent();
        ~Tent();
        void setTexture(CGFappearance * appearance);
        void draw();
};

#endif	/* TENT_H */

