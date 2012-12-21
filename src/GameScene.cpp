#include <GL/glew.h>

#include "GameScene.h"
#include "Patch.h"

unsigned int LineAnimation::mili_secs = 0;

void updateTransforms(int dummy)
{
    for (unsigned int i = 0; i < allPolyAnimations.size(); i++)
    {
        allPolyAnimations[i]->updateObjectPosition();
    }

    glutTimerFunc(LineAnimation::getMiliSecs(), updateTransforms, dummy);
}

void myGlutIdle(void)
{
    /* According to the GLUT specification, the current window is 
       undefined during an idle callback.  So we need to explicitly change
       it if necessary */
    //if ( glutGetWindow() != main_window ) 
    //glutSetWindow(main_window);  
    glutSetWindow(glutGetWindow());

    glutPostRedisplay();

    /****************************************************************/
    /*            This demonstrates GLUI::sync_live()               */
    /*   We change the value of a variable that is 'live' to some   */
    /*   control.  We then call sync_live, and the control          */
    /*   associated with that variable is automatically updated     */
    /*   with the new value.  This frees the programmer from having */
    /*   to always remember which variables are used by controls -  */
    /*   simply change whatever variables are necessary, then sync  */
    /*   the live ones all at once with a single call to sync_live  */
    /****************************************************************/

    //  glui->sync_live();

}

void GameScene::init()
{
    /** Enables lighting computations */
    glEnable(GL_LIGHTING);

    /** Sets up some lighting parameters */
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);

    /** Lights initialization */
    float light0_pos[4] = {5.0, 4.0, 5.0, 1.0};
    light0 = new CGFlight(GL_LIGHT0, light0_pos);
    light0->enable();

    /** Defines a default normal */
    glNormal3f(0, 0, 1);

    /** Materials initialization */
    materialAppearance = new CGFappearance();
    textureAppearance = new CGFappearance("../textures/pyramid.jpg", GL_REPEAT, GL_REPEAT);
    tentAppearance = new CGFappearance("../textures/tent.jpg", GL_REPEAT, GL_REPEAT);

    /** Object initialization */

    /** Shaders declaration */

    /** Set the update period */
    setUpdatePeriod(30);
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
    axis.draw();

    /** Draw lights */
    light0->draw();

    /** Setting the cullface and frontface */
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /** ===== DRAW OBJECTS START ===== */

    /** Draw dynamic objects */

    for (unsigned int i = 0; i < allPolyAnimations.size(); i++)
    {
        allPolyAnimations[i]->animate();
    }

    /** Draw static objects */

    /** ===== DRAW OBJECTS END ===== */

    glutSwapBuffers();
}

void GameScene::update(long t)
{
}

GameScene::~GameScene()
{
    delete light0;
}