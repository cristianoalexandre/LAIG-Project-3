#include <GL/glew.h>

#include "GameScene.h"
#include "Patch.h"
#include "FlyingDisk.h"

unsigned int LineAnimation::mili_secs = 0;
unsigned int PieceAnimation::mili_secs = 0;

int Ring::numberExistingRings = 0;

PieceAnimation* animP;

void updateTransforms(int dummy)
{
	animP->update();
	glutTimerFunc(PieceAnimation::getMiliSecs(), updateTransforms, dummy);
}

void GameScene::init()
{
	/** Enables lighting computations */
	glEnable(GL_LIGHTING);

	/** Sets up some lighting parameters */
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);

	/** Lights initialization */
	initCGFLights();

	/** Defines a default normal */
	glNormal3f(0, 0, 1);

	/** Materials initialization */
	materialAppearance = new CGFappearance();
	textureAppearance = new CGFappearance("../textures/pyramid.jpg", GL_REPEAT, GL_REPEAT);
	tentAppearance = new CGFappearance("../textures/tent.jpg", GL_REPEAT, GL_REPEAT);

	/** Object initialization */
	/*torus = new Board();
	p = new Piece("rook", "white");
	p->moveToCell(20);
	//model1 = new Model("../models/whitePawn.obj");

	animP = new PieceAnimation();
	animP->setPiece(p);
	animP->setMovement(32, 1, 1);
	
	/** Game declaration */
        
        player1 = new Player("white");
        player2 = new Player("black",CPU_EASY);
        
	game = new Game(player1, player2);

	/** Animation initialization */
	//PieceAnimation::setMiliSecs(10);
	//glutTimerFunc(PieceAnimation::getMiliSecs(), updateTransforms, 0);
	//setUpdatePeriod(PieceAnimation::getMiliSecs());

	/** Shaders declaration*/

}

void GameScene::display()
{
	/** Clear image and depth buffer everytime we update the scene */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3,0.3,0.3,1.0);

	/** Initialize Model-View matrix as identity (no transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/** Defines the background color */

	/** Apply transformations corresponding to the camera position relative to the origin */
	CGFscene::activeCamera->applyView();

	/** Draw axis */
	axis.draw();

	/** Draw lights */
	light0->draw();
	light1->draw();
	light2->draw();
	light3->draw();
	light4->draw();
	light5->draw();
	light6->draw();
	light7->draw();

	/** Setting the cullface and frontface */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/** Draw objects */
        game->draw();
	/**glPushMatrix();
		glScaled(SCALING_FACTOR, SCALING_FACTOR, SCALING_FACTOR);
		//torus->draw();
		glutSolidTorus(TORUS_INNER_RADIUS, TORUS_OUTER_RADIUS-TORUS_INNER_RADIUS,50,50);
		glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();*/

	//torus->draw();
	//p->draw();
	glutSwapBuffers();
}

void GameScene::update(long t)
{
	//updateTransforms(30);
}

GameScene::~GameScene()
{
	delete light0;
	delete light1;
	delete light2;
	delete light3;
	delete light4;
	delete light5;
	delete light6;
	delete light7;
        delete game;
}

void GameScene::initCGFLights()
{
	float light0_pos[4] = {-10.0, 12.0, -10.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();

	float light1_pos[4] = {10.0, -12.0, -10.0, 1.0};
	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->enable();

	float light2_pos[4] = {-10.0, 12.0, 10.0, 1.0};
	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->enable();

	float light3_pos[4] = {10.0, -12.0, 10.0, 1.0};
	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->enable();

	float light4_pos[4] = {-10.0, -12.0, -10.0, 1.0};
	light4 = new CGFlight(GL_LIGHT4, light4_pos);
	light4->enable();

	float light5_pos[4] = {-10.0, -12.0, 10.0, 1.0};
	light5 = new CGFlight(GL_LIGHT5, light5_pos);
	light5->enable();

	float light6_pos[4] = {10.0, 12.0, -10.0, 1.0};
	light6 = new CGFlight(GL_LIGHT6, light6_pos);
	light6->enable();

	float light7_pos[4] = {10.0, 12.0, 10.0, 1.0};
	light7 = new CGFlight(GL_LIGHT7, light7_pos);
	light7->enable();
}