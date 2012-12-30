#include "Environment.h"


Environment::Environment(){

	float wall_shininess = 200.0; 
	float wall_specular[] = {0.1, 0.1, 0.1, 1.0};	/* specular reflection. */
	float wall_diffuse[] =  {0.5, 0.5, 0.5, 1.0};	/* diffuse reflection. */
	float wall_ambient[] =  {0.6, 0.6, 0.6, 1.0};	/* ambient reflection. */


	wall1 = new Plane(10,10);
	wall2 = new Plane(10,10);
	wall3 = new Plane(10,10);
	wall4 = new Plane(10,10);

	floor = new Plane(10,10);
	ceiling = new Plane(10,10);

	torusSupport = new Cylinder(0.5,0.5,4,20,20);
	emitterSphere = new Sphere(1,30,30);

	//wallTexture = new CGFappearance(wall_ambient, wall_diffuse, wall_specular, wall_shininess);
	wallTexture = new CGFappearance("../textures/wall_texture_white.jpg", GL_REPEAT, GL_REPEAT);
	//wallTexture->setTexture("../textures/wall_texture_white.jpg");

	//ceilingTexture = new CGFappearance(wall_ambient, wall_diffuse, wall_specular, wall_shininess);
	ceilingTexture = new CGFappearance("../textures/ceiling.jpg", GL_REPEAT, GL_REPEAT);
	//ceilingTexture->setTexture("../textures/ceiling.jpg");

	//floorTexture = new CGFappearance(wall_ambient, wall_diffuse, wall_specular, wall_shininess);
	floorTexture = new CGFappearance("../textures/wood_floor.jpg", GL_REPEAT, GL_REPEAT);
	//floorTexture->setTexture("../textures/wood_floor.jpg");

	//cylinderTexture = new CGFappearance(wall_ambient, wall_diffuse, wall_specular, wall_shininess);
	cylinderTexture = new CGFappearance("../textures/mahogany.jpg", GL_REPEAT, GL_REPEAT);
	//cylinderTexture->setTexture("../textures/mahogany.jpg");

	//sphereTexture = new CGFappearance(wall_ambient, wall_diffuse, wall_specular, wall_shininess);
	sphereTexture = new CGFappearance("../textures/black.jpg", GL_REPEAT, GL_REPEAT);
	//sphereTexture->setTexture("../textures/black.jpg");

	//tableTopTexture = new CGFappearance(wall_ambient, wall_diffuse, wall_specular, wall_shininess);
	tableTopTexture = new CGFappearance("../textures/mahogany.jpg", GL_REPEAT, GL_REPEAT);

	//tableLegTexture = new CGFappearance(wall_ambient, wall_diffuse, wall_specular, wall_shininess);
	tableLegTexture = new CGFappearance("../textures/black.jpg", GL_REPEAT, GL_REPEAT);
}

void Environment::draw(){


	glPushMatrix();

		/* WALLS */
		wallTexture->apply();
		glPushMatrix();
			glTranslated(0,-50,0);
			glScaled(150,1,60);
			wall1->draw();
		glPopMatrix();
		glPushMatrix();
			glRotated(-90,0,0,1);
			glTranslated(0,-75,0);
			glScaled(150,1,60);
			wall2->draw();
		glPopMatrix();
		glPushMatrix();
			glRotated(90,0,0,1);
			glTranslated(0,-75,0);
			glScaled(100,1,60);
			wall3->draw();
		glPopMatrix();
		glPushMatrix();
			glRotated(180,0,0,1);
			glTranslated(0,-50,0);
			glScaled(150,1,60);
			wall4->draw();
		glPopMatrix();

		/* FLOOR */
		floorTexture->apply();
		glPushMatrix();
			glRotated(90,1,0,0);
			glTranslated(0,-30,0);
			glScaled(150,1,100);
			floor->draw();
		glPopMatrix();

		/* CEILING */
		ceilingTexture->apply();
		glPushMatrix();
			glRotated(-90,1,0,0);
			glTranslated(0,-30,0);
			glScaled(150,1,100);
			ceiling->draw();
		glPopMatrix();

		
		tableTopTexture->apply();
		glPushMatrix(); //TAMPO DA MESA
			glTranslated(0,0,-10);
			glScaled(20,15,2);
			glutSolidCube(1);
		glPopMatrix();
		tableLegTexture->apply();
		glPushMatrix(); //PERNA DA MESA
			glTranslated(0,0,-20);
			glScaled(1.5,1.5,20);
			glutSolidCube(1);
		glPopMatrix();


		/* Cylinders */
		cylinderTexture->apply();
		glPushMatrix();
			glTranslated(8,5.5,-10);
			torusSupport->draw();
		glPopMatrix();

		glPushMatrix();
			glTranslated(-8,5.5,-10);
			torusSupport->draw();
		glPopMatrix();

		glPushMatrix();
			glTranslated(-8,-5.5,-10);
			torusSupport->draw();
		glPopMatrix();

		glPushMatrix();
			glTranslated(8,-5.5,-10);
			torusSupport->draw();
		glPopMatrix();

		/* Spheres*/
		sphereTexture->apply();
		glPushMatrix();
			glTranslated(8,5.5,-6);
			emitterSphere->draw();
		glPopMatrix();

		glPushMatrix();
			glTranslated(-8,5.5,-6);
			emitterSphere->draw();
		glPopMatrix();

		glPushMatrix();
			glTranslated(-8,-5.5,-6);
			emitterSphere->draw();
		glPopMatrix();

		glPushMatrix();
			glTranslated(8,-5.5,-6);
			emitterSphere->draw();
		glPopMatrix();

		
	glPopMatrix();

}

void Environment::activateTextureSet(int i){

	switch(i){

	case 0:
		{
			wallTexture->setTexture("../textures/wall_texture_white.jpg");
			ceilingTexture->setTexture("../textures/ceiling.jpg");
			floorTexture->setTexture("../textures/wood_floor.jpg");
			cylinderTexture->setTexture("../textures/mahogany.jpg");
			sphereTexture->setTexture("../textures/black.jpg");
			tableTopTexture->setTexture("../textures/mahogany.jpg");
			tableLegTexture->setTexture("../textures/black.jpg");
			break;
		};
	case 1:
		{
			wallTexture->setTexture("../textures/chess3.jpg");
			floorTexture->setTexture("../textures/stone_floor.jpg");
			ceilingTexture->setTexture("../textures/red_iron.jpg");
			tableTopTexture->setTexture("../textures/red.jpg");
			tableLegTexture->setTexture("../textures/black.jpg");
			cylinderTexture->setTexture("../textures/stainless_steel.jpg");
			sphereTexture->setTexture("../textures/cast_iron_grey.jpg");
			break;
		};
	case 2:
		{
			wallTexture->setTexture("../textures/marble.jpg");
			floorTexture->setTexture("../textures/pavement.jpg");
			ceilingTexture->setTexture("../textures/wall_texture_white.jpg");
			tableTopTexture->setTexture("../textures/mahogany.jpg");
			tableLegTexture->setTexture("../textures/stainless_steel.jpg");
			cylinderTexture->setTexture("../textures/cast_iron_grey.jpg");
			sphereTexture->setTexture("../textures/fur.png");
			break;
		};

	}
}