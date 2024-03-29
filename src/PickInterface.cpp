#include "PickInterface.h"

// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

void PickInterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void PickInterface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void PickInterface::processHits (GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
		{
			printf("%d ",selected[i]);
			game_scene->selectedCellID = selected[i];
		}
		printf("\n");
	}
	else
		printf("Nothing selected while picking \n");	
}

void PickInterface::setScene(GameScene* s){

	this->game_scene = s;
}

void PickInterface::processKeyboard(unsigned char key, int x, int y)
{
	// Uncomment below if you would like to process the default keys (e.g. 's' for snapshot, 'Esc' for exiting, ...)
	CGFinterface::processKeyboard(key, x, y);
}

void PickInterface::initGUI()
{
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	varPanel = addPanel("Options", 1);

	addButtonToPanel(varPanel, "Undo", 2);
	addButtonToPanel(varPanel,"Replay",3);
	addColumnToPanel(varPanel);

	GLUI_Panel* textureChoice = addPanelToPanel(varPanel,"Choose Textures",1);
	GLUI_RadioGroup* textures = addRadioGroupToPanel(textureChoice,0,4);

	addRadioButtonToGroup(textures,"Wood");
	addRadioButtonToGroup(textures,"Glass");
	addRadioButtonToGroup(textures,"Metal");
	addColumnToPanel(varPanel);

	GLUI_Panel* difficulty = addPanelToPanel(varPanel,"Dificuldade",1);
	GLUI_RadioGroup* levels = addRadioGroupToPanel(difficulty,0,5);

	addRadioButtonToGroup(levels,"Begginer");
	addRadioButtonToGroup(levels,"Experienced");
	addRadioButtonToGroup(levels,"Hardcore Geek");
	addColumnToPanel(varPanel);

	GLUI_Panel* environmentChoice = addPanelToPanel(varPanel,"Choose Environment",1);
	GLUI_RadioGroup* environments = addRadioGroupToPanel(environmentChoice,0,6);

	addRadioButtonToGroup(environments,"Regular");
	addRadioButtonToGroup(environments,"Colourful");
	addRadioButtonToGroup(environments,"Idiotic");
	addColumnToPanel(varPanel);



}

void PickInterface::processGUI(GLUI_Control *ctrl)
{
	switch (ctrl->user_id)
	{
		case 1:
		{			
			break;
		};
		case 2:
		{		
			cout << "pressed undo button" << endl;
			break;
		};
		case 3:
		{
			cout << "pressed replay button" << endl;
			break;
		};
		case 4:
		{	
			game_scene->stopDrawing = true;
			switch(ctrl->get_int_val())
			{
			case 0:
				{
					game_scene->activateTexture(0);
					cout << "wood" << endl;
					break;
				};
			case 1:
				{
					game_scene->activateTexture(1);
					cout << "glass" << endl;
					break;
				};
			case 2:
				{
					game_scene->activateTexture(2);
					cout << "metal" << endl;
					break;
				};
			}
			game_scene->stopDrawing = false;
			break;
		};
		case 5:
		{
			game_scene->stopDrawing = true;
			switch(ctrl->get_int_val())
			{
			case 0:
				{
					cout << "Begginer" << endl;
					break;
				};
			case 1:
				{
					cout << "Experienced" << endl;
					break;
				};
			case 2:
				{
					cout << "Hardcore Geek" << endl;
					break;
				};
			}
			game_scene->stopDrawing = false;
			break;
		};
		case 6:
		{
			switch(ctrl->get_int_val())
			{
			case 0:
				{
					cout << "Regular" << endl;
					game_scene->getEnvironment()->activateTextureSet(0);
					break;
				};
			case 1:
				{
					cout << "Colourful" << endl;
					game_scene->getEnvironment()->activateTextureSet(1);
					break;
				};
			case 2:
				{
					game_scene->getEnvironment()->activateTextureSet(2);
					cout << "Idiotic" << endl;
					break;
				};
			}
			break;
		};
	};
}
