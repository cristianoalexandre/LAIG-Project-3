#ifndef GAMESCENE_H
#define	GAMESCENE_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFobject.h"
#include "CGFshader.h"
#include "DemoShader.h"

#include "LineAnimation.h"
#include "PolyLineAnimation.h"
#include "PieceAnimation.h"

#include "Cylinder.h"
#include "Triangle.h"
#include "Sphere.h"

#include "TorusHitbox.h"
#include "Piece.h"
#include "Model.h"

#include <math.h>
#include <vector>

static vector<PolyLineAnimation*> allPolyAnimations;

class GameScene : public CGFscene
{
public:
    void init();
    void display();
    void update(long t);
    void drawModel_box();
    ~GameScene();

private:
    static const long update_time = 30;

    /** Lights declaration */
    CGFlight * light0;
    CGFlight * light1;
    CGFlight * light2;
    CGFlight * light3;

    GLuint cena;

    /** Appearances declaration */
    CGFappearance* materialAppearance;
    CGFappearance* textureAppearance;
    CGFappearance* tentAppearance;

    /** Primitives declaration */
    Piece* p;
    TorusHitbox* torus;

    /** Shaders declaration */
    DemoShader * shader1;
    Model * model1;
};

#endif	/* GAMESCENE_H */