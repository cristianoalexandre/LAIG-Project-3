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
    float light0_pos[4] = {-4.0, 20.0, 5.0, 1.0};
    light0 = new CGFlight(GL_LIGHT0, light0_pos);
    light0->enable();

    float light1_pos[4] = {8.0, 20.0, 5.0, 1.0};
    light1 = new CGFlight(GL_LIGHT1, light1_pos);
    light1->enable();

    float light2_pos[4] = {-4.0, 20.0, 10.0, 1.0};
    light2 = new CGFlight(GL_LIGHT2, light2_pos);
    light2->enable();

    float light3_pos[4] = {8.0, 20.0, 10.0, 1.0};
    light3 = new CGFlight(GL_LIGHT3, light3_pos);
    light3->enable();

    /** Defines a default normal */
    glNormal3f(0, 0, 1);


    /** Materials initialization */
    materialAppearance = new CGFappearance();
    textureAppearance = new CGFappearance("../textures/pyramid.jpg", GL_REPEAT, GL_REPEAT);
    tentAppearance = new CGFappearance("../textures/tent.jpg", GL_REPEAT, GL_REPEAT);

    /** Object initialization */
    torus = new Board();
    p = new Piece();
    p->moveToCell(20);
    //model1 = new Model("../models/rook.obj");

    /*PieceAnimation::setMiliSecs(10);
    animP = new PieceAnimation();
    animP->setPiece(p);
    animP->setMovement(32, 1, 1);

    glutTimerFunc(PieceAnimation::getMiliSecs(), updateTransforms, 0);*/
    //setUpdatePeriod(PieceAnimation::getMiliSecs());
    /** Shaders declaration*/

}

void GameScene::display()
{
    /** Clear image and depth buffer everytime we update the scene */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /** Initialize Model-View matrix as identity (no transformation */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /** Apply transformations corresponding to the camera position relative to the origin */
    CGFscene::activeCamera->applyView();

    /** Draw axis */
    //axis.draw();

    /** Draw lights */
    light0->draw();
    light1->draw();
    light2->draw();
    light3->draw();

    /** Setting the cullface and frontface */
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /** Draw objects */

    //glutSolidTorus(3,5,50,50);
    glPushMatrix();
		glScaled(SCALING_FACTOR, SCALING_FACTOR, SCALING_FACTOR);
		torus->draw();
    //glutSolidTorus(1.5, 2.5, 50, 50);
    glPopMatrix();

    p->draw();
    /*glPushMatrix();
		glScalef(5,5,5);
		model1->draw();
    glPopMatrix();*/

    glutSwapBuffers();
}

void GameScene::update(long t)
{
    //updateTransforms(30);
}

GameScene::~GameScene()
{
    delete light0;
}