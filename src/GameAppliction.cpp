
#ifndef CGF_NO_SHADERS
#include <GL/glew.h>
#endif
#include "GameApplication.h"
#include <GL/glut.h>
#include <GL/glui.h>

#include <stdlib.h>
using namespace std;


#ifdef _WIN32
	#include <Windows.h>
#endif

#define CG_GLAPP_DISPLAY_MODE GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA
#define CG_GLAPP_INIT_WIDTH 1200
#define CG_GLAPP_INIT_HEIGHT 650
#define CG_GLAPP_INIT_POSX 100
#define CG_GLAPP_INIT_POSY 50
#define CG_GLAPP_REDBITS 8
#define CG_GLAPP_BLUEBITS 8
#define CG_GLAPP_GREENBITS 8


void GameApplication::init(int* argc, char** argv) {

	try {
		glutInit(argc, argv);
		glutInitDisplayMode(CG_GLAPP_DISPLAY_MODE);

		CGFapplication::width = CG_GLAPP_INIT_WIDTH;
		CGFapplication::height = CG_GLAPP_INIT_HEIGHT;
		glutInitWindowSize(CGFapplication::width, CGFapplication::height);
		glutInitWindowPosition(CG_GLAPP_INIT_POSX, CG_GLAPP_INIT_POSY);

		CGFapplication::app_window = glutCreateWindow(argv[0]);

		glutDisplayFunc(CGFapplication::display);
		GLUI_Master.set_glutIdleFunc(CGFapplication::gluiIdleFunction);
		GLUI_Master.set_glutReshapeFunc(CGFapplication::reshape);

		environmentInit();

#ifndef CGF_NO_SHADERS
		glewInit();
#endif
	}
	catch(std::exception&) {
		throw GLexception("CGFapplication::init falhou na execucao");
	}

	return;
}


GameApplication::GameApplication(){
	CGFapplication();
}
