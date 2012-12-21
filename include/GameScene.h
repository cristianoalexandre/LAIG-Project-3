#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "Plane.h"
#include "Patch.h"
#include "Tent.h"
#include "Terrain.h"

#include "CGFscene.h"
#include "CGFappearance.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFobject.h"
#include "CGFshader.h"
#include "DemoShader.h"

#include "LineAnimation.h"
#include "PolyLineAnimation.h"

#include "Cylinder.h"
#include "Triangle.h"
#include "Sphere.h"

#include "Game.h"

#include <math.h>
#include <vector>

static vector<PolyLineAnimation*> allPolyAnimations;

class GameScene : public CGFscene
{
public:
    void init();
    void display();
    void update(long t);
    ~GameScene();

private:
    static const long update_time = 30;

    /** Game-related objects */
    Game toruschess;

    /** Lights declaration */
    CGFlight * light0;

    GLuint scene;

    /** Appearances declaration */
    CGFappearance* materialAppearance;
    CGFappearance* textureAppearance;
    CGFappearance* tentAppearance;

    /** Primitives declaration */


    /** Shaders declaration */
};

#endif	/* LAIGSCENE_H */