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

#include "Game.h"

#include <math.h>
#include <vector>

static vector<PolyLineAnimation*> allPolyAnimations;

class GameScene : public CGFscene
{
public:
	void init();
	void initCGFLights();
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
	CGFlight * light4;
	CGFlight * light5;
	CGFlight * light6;
	CGFlight * light7;

	/** Appearances declaration */
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFappearance* tentAppearance;

	/** Primitives declaration */
	Piece* p;
	Board* torus;

	/** Shaders declaration */
	DemoShader * shader1;

	/** Game declaration */
        Player * player1;
        Player * player2;
	Game * game;
};

#endif	/* GAMESCENE_H */