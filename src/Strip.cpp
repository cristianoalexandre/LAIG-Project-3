#include "Strip.h"

#include "LineAnimation.h"
#include "PolyLineAnimation.h"


Strip::Strip(){

	GLfloat z_bound = 0.75;//z_tot = 1.5;
    GLfloat x_boundSmall = 1.1; //Xsmall_tot = 2.2;
	GLfloat x_boundBig = 1.5; //Xbing_tot = 3;
	GLfloat height = 2;


	this->delta_z = 1.15;
	double delta_z_height = 0.22;

	double first_delta_x = 3.06;
	double second_delta_x = 2.73;
	double third_delta_x = 1.91;
	double fourth_delta_x = 1.10;
	double fifth_delta_x = 0.77;

	double first_delta_x_height = first_delta_x/2 * sinl(22.5 * PI/180);
	double second_delta_x_height = second_delta_x/2 * sinl(22.5 * PI/180);;
	double third_delta_x_height = third_delta_x/2 * sinl(22.5 * PI/180);;
	double fourth_delta_x_height = fourth_delta_x/2 * sinl(22.5 * PI/180);;
	double fifth_delta_x_height = fifth_delta_x/2 * sinl(22.5 * PI/180);;

	double adjust = 0.2;

	

	GLfloat control_points1[][3] = {
		/*{-second_delta_x/2, 0, delta_z/2},
		{0, second_delta_x_height, delta_z/2},
		{second_delta_x/2, 0, delta_z/2},

		{(-first_delta_x +((first_delta_x - second_delta_x)/2))/2, delta_z_height, 0},
        {0, delta_z_height, 0},
		{(first_delta_x -((first_delta_x - second_delta_x)/2))/2, delta_z_height, 0},
		
		{-first_delta_x/2, 0, -delta_z/2},
		{0, first_delta_x_height, -delta_z/2},
		{first_delta_x/2, 0, -delta_z/2}
		*/
		{-second_delta_x/2, 0, delta_z/2},
		{0, 0, delta_z/2},
		{second_delta_x/2, 0, delta_z/2},

		{(-first_delta_x +((first_delta_x - second_delta_x)/2))/2, 0, 0},
		{0, 0, 0},
		{(first_delta_x -((first_delta_x - second_delta_x)/2))/2, 0, 0},
		
		{-first_delta_x/2, 0, -delta_z/2},
		{0, 0, -delta_z/2 },
		{first_delta_x/2, 0, -delta_z/2}
    };


	GLfloat control_points2[][3] = {
		/*{-third_delta_x/2, 0, delta_z/2},
		{0, third_delta_x_height, delta_z/2},
		{third_delta_x/2, 0, delta_z/2},*/

		{-third_delta_x/2, 0, delta_z/2},
		{0, 0, delta_z/2},
		{third_delta_x/2, 0, delta_z/2},

		{(-second_delta_x +((second_delta_x - third_delta_x)/2))/2, 0, 0},
        {0, 0, 0},
		{(second_delta_x -((second_delta_x- third_delta_x)/2))/2, 0, 0},
		
		/*{-second_delta_x/2, 0, -delta_z/2},
		{0, second_delta_x_height, -delta_z/2},
		{second_delta_x/2, 0, -delta_z/2}*/
		{-second_delta_x/2, 0, -delta_z/2},
		{0, 0, -delta_z/2},
		{second_delta_x/2, 0, -delta_z/2}
    };

	GLfloat control_points3[][3] = {
		{-fourth_delta_x/2, 0, delta_z/2},
		{0, 0, delta_z/2},
		{fourth_delta_x/2, 0, delta_z/2},

		{(-third_delta_x +((third_delta_x - fourth_delta_x)/2))/2, 0, 0},
        {0, 0, 0},
		{(third_delta_x -((third_delta_x- fourth_delta_x)/2))/2, 0, 0},
		
		{-third_delta_x/2, 0, -delta_z/2},
		{0, 0, -delta_z/2},
		{third_delta_x/2, 0, -delta_z/2}
    };

	GLfloat control_points4[][3] = {
		{-fifth_delta_x/2, 0, delta_z/2},
		{0, 0, delta_z/2},
		{fifth_delta_x/2, 0, delta_z/2},

		{(-fourth_delta_x +((fourth_delta_x - fifth_delta_x)/2))/2, 0, 0},
        {0, 0, 0},
		{(fourth_delta_x -((fourth_delta_x- fifth_delta_x)/2))/2, 0, 0},
		
		{-fourth_delta_x/2, 0, -delta_z/2},
		{0, 0, -delta_z/2},
		{fourth_delta_x/2, 0, -delta_z/2}
    };

	Patch* eval = new Patch(2, 2, 20, 20, control_points1, 9, 3);
	this->top = new Cell(eval);
	Patch* eval2 = new Patch(2, 2, 20, 20, control_points2, 9, 3);
	this->middleTop = new Cell(eval2);
	Patch* eval3 = new Patch(2, 2, 20, 20, control_points3, 9, 3);
	this->middleBottom = new Cell(eval3);
	Patch* eval4 = new Patch(2, 2, 20, 20, control_points4, 9, 3);
	this->bottom = new Cell(eval4);

}


Cell* Strip::getTop(){

	return this->top;
}

Cell* Strip::getMiddleTop(){

	return this->middleTop;
}

Cell* Strip::getMiddleBottom(){

	return this->middleBottom;
}

Cell* Strip::getBottom(){

	return this->bottom;
}



void Strip::draw() 
{	

	double v = 1.0825; //calculus rounding error adjustment factor
	glPushMatrix();
		//Scalef(v,1,1);
		glTranslatef(0,4,0);
		glPushMatrix();
			glRotatef(22.5,1,0,0);
			glTranslatef(0,0,delta_z/2);
			top->draw();
			glPushMatrix();
				glTranslatef(0,0,delta_z/2);
				glRotatef(45,1,0,0);
				glTranslatef(0,0,delta_z/2);
				middleTop->draw();
				glPushMatrix();
					glTranslatef(0,0,delta_z/2);
					glRotatef(45,1,0,0);
					glTranslatef(0,0,delta_z/2);
					middleBottom->draw();
					glPushMatrix();
						glTranslatef(0,0,delta_z/2);
						glRotatef(45,1,0,0);
						glTranslatef(0,0,delta_z/2);
						bottom->draw();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//glutSolidTorus(1.5,2.5,50,50);

	//glutSolidSphere(11.5,50,50);
}