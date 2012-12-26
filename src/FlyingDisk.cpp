#include "FlyingDisk.h"

FlyingDisk::FlyingDisk()
{

	setPos_x(0.0);
	setPos_y(4.0);
	setPos_z(10.0);
	setRotationAngleOnXXaxis(0.0);
	setRotationAngleOnYYaxis(0.0);
	setRotationAngleOnZZaxis(0.0);

	setAnimated(false);
	/** Defines control points */
	GLfloat control_points[][3] = {
		{-3 + 0.3, 0, 3},
		{-3 / 2, 0, 3 + 1.5},
		{3 / 2, 0, 3 + 1.5},
		{3 - 0.3, 0, 3},

		{-3 - 1.5, 0, 3 / 2},
		{-3 / 2, 5, 3 / 2},
		{3 / 2, 5, 3 / 2},
		{3 + 1.5, 0, 3 / 2},

		{-3 - 1.5, 0, -3 / 2},
		{-3 / 2, 5, -3 / 2},
		{3 / 2, 5, -3 / 2},
		{3 + 1.5, 0, -3 / 2},

		{-3 + 0.3, 0, -3},
		{-3 / 2, 0, -3 - 1.5},
		{3 / 2, 0, -3 - 1.5},
		{3 - 0.3, 0, -3}
	};

	topPart = new Patch(3, 3, 20, 20, control_points, 16, 3);
	disk = new Cylinder(9, 9, 0.5, 255, 10);
	
	diskBottomAppearance = new CGFappearance("../textures/disk_down.png",GL_CLAMP,GL_CLAMP);
	diskTopAppearance = new CGFappearance("../textures/disk_up.png", GL_CLAMP,GL_CLAMP);
	topAppearance = new CGFappearance("../textures/top.png", GL_CLAMP,GL_CLAMP);
	
	topPart->setTexture(topAppearance);
	disk->setBottomTexture(diskBottomAppearance);
	disk->setTopTexture(diskTopAppearance);
}

FlyingDisk::~FlyingDisk()
{
	delete topPart;
	delete disk;
	delete diskBottomAppearance;
	delete diskTopAppearance;
	delete topAppearance;
}

void FlyingDisk::draw()
{
	glPushMatrix();
	glScalef(0.2,0.2,0.2);
	topPart->draw();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	disk->draw();
	glPopMatrix();
	glPopMatrix();
}