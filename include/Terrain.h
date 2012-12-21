#ifndef TERRAIN_H
#define	TERRAIN_H

#include "Plane.h"

class Terrain : Object
{
private:
    Plane * plane;

public:
    Terrain();
    ~Terrain();
    void draw();
};

#endif	/* TERRAIN_H */

