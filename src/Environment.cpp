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

	wallTexture2 = new CGFappearance("../textures/brick_wall.jpg", GL_REPEAT, GL_REPEAT);
	floorTexture2 = new CGFappearance("../textures/stone_floor.jpg", GL_REPEAT, GL_REPEAT);
	ceilingTexture2 = new CGFappearance("../textures/red_iron.jpg", GL_REPEAT, GL_REPEAT);
	tableTopTexture2 = new CGFappearance("../textures/red.jpg", GL_REPEAT, GL_REPEAT);
	tableLegTexture2 = new CGFappearance("../textures/black.jpg", GL_REPEAT, GL_REPEAT);
	cylinderTexture2 = new CGFappearance("../textures/stainless_steel.jpg", GL_REPEAT, GL_REPEAT);
	sphereTexture2 = new CGFappearance("../textures/cast_iron_grey.jpg", GL_REPEAT, GL_REPEAT);

	wallTexture3 = new CGFappearance("../textures/marble.jpg", GL_REPEAT, GL_REPEAT);
	floorTexture3 = new CGFappearance("../textures/pavement.jpg", GL_REPEAT, GL_REPEAT);
	ceilingTexture3 = new CGFappearance("../textures/wall_texture_white.jpg", GL_REPEAT, GL_REPEAT);
	tableTopTexture3 = new CGFappearance("../textures/mahogany.jpg", GL_REPEAT, GL_REPEAT);
	tableLegTexture3 = new CGFappearance("../textures/stainless_steel.jpg", GL_REPEAT, GL_REPEAT);
	cylinderTexture3 = new CGFappearance("../textures/cast_iron_grey.jpg", GL_REPEAT, GL_REPEAT);
	sphereTexture3 = new CGFappearance("../textures/fur.png", GL_REPEAT, GL_REPEAT);
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
			wallTexture = wallTexture;
			ceilingTexture = ceilingTexture;
			floorTexture = floorTexture;
			cylinderTexture = cylinderTexture;
			sphereTexture = sphereTexture;
			tableTopTexture = tableTopTexture;
			tableLegTexture = tableLegTexture;
			break;
		};
	case 1:
		{
			wallTexture = wallTexture2;
			ceilingTexture = ceilingTexture2;
			floorTexture = floorTexture2;
			cylinderTexture = cylinderTexture2;
			sphereTexture = sphereTexture2;
			tableTopTexture = tableTopTexture2;
			tableLegTexture = tableLegTexture2;
			break;
		};
	case 2:
		{
			wallTexture = wallTexture3;
			ceilingTexture = ceilingTexture3;
			floorTexture = floorTexture3;
			cylinderTexture = cylinderTexture3;
			sphereTexture = sphereTexture3;
			tableTopTexture = tableTopTexture3;
			tableLegTexture = tableLegTexture3;
			break;
		};

	}
}