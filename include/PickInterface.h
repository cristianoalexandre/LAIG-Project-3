#ifndef PickInterface_H
#define PickInterface_H

#include "CGFinterface.h"
#include "GameScene.h"
#include "CGFapplication.h"


class PickInterface: public CGFinterface {

private:

	GameScene* game_scene;
	GLUI_Panel *varPanel;

public:
	void setScene(GameScene* s);

	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]); 

	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);

	virtual void processKeyboard(unsigned char key, int x, int y);
	virtual void processMouse(int button, int state, int x, int y);	
};


#endif
