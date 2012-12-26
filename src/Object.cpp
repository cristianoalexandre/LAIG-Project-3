#include "Object.h"

Object::Object(){

	setPos_x(0.0);
	setPos_y(0.0);
	setPos_z(0.0);
	ang_XY = 0;
	ang_XZ = 0;
	setAnimated(false);
}

Object::~Object(){
}

void Object::setPos_x(double x){

	this->pos_x = x;
}

void Object::setPos_y(double y){

	this->pos_y = y;
}

void Object::setPos_z(double z){

	this->pos_z = z;
}

void Object::setAnimated(bool anim){

	this->animate = anim;
}

void Object::setRotationAngleOnZZaxis(double ang){

	this->ang_XY = ang;
}

void Object::setRotationAngleOnXXaxis(double ang){

	this->ang_ZY = ang;
}

void Object::setRotationAngleOnYYaxis(double ang){

	
	this->ang_XZ = ang;
	
}

void Object::setOrientationVector(double vector[NUM_COORD]){

	this->orientation_vector[X] = vector[X];
	this->orientation_vector[Y] = vector[Y];
	this->orientation_vector[Z] = vector[Z];
}

double Object::getPos_x(){

	return this->pos_x;
}

double Object::getPos_y(){

	return this->pos_y;
}

double Object::getPos_z(){

	return this->pos_z;
}

double Object::getAng_XZ(){

	return this->ang_XZ;
}

double Object::getAng_XY(){

	return this->ang_XY;
}

double Object::getAng_ZY(){

	return this->ang_ZY;
}

double* Object::getOrientationVector(){

	return this->orientation_vector;
}

bool Object::getAnimated(){

	return this->animate;
}

CGFappearance* Object::getTexture(){

	return this->appearance;
}

void Object::updateToPosition(double x, double y, double z){

	setPos_x(x);
	setPos_y(y);
	setPos_z(z);
}

void Object::updatePosition(double delta_x, double delta_y, double delta_z){

	setPos_x(this->pos_x + delta_x);
	setPos_y(this->pos_y + delta_y);
	setPos_z(this->pos_z + delta_z);
}

void Object::applyTransforms(){

	glTranslated(this->pos_x, this->pos_y, this->pos_z);
	double px,py,pz;
	px = getPos_x();
	py = getPos_y();
	pz = getPos_z();

	updateToPosition(0,0,0);
	if(ang_XY != 0 && ang_ZY != 0){
		if(ang_XZ != 0){
			glRotatef(-this->ang_XZ ,0,1,0); //the - is there so that the rotation is CLOCKWISE
		}
		glRotatef(ang_XY,0,0,1);
	}else{
		if(ang_XY != 0){
			glRotatef(this->ang_XY,0,0,1); 
		}
		if(ang_ZY != 0){
			glRotatef(this->ang_ZY,1,0,0); 
		}
		if(ang_XZ != 0){
			glRotatef(-this->ang_XZ ,0,1,0); //the - is there so that the rotation is CLOCKWISE
		}
	}

	updateToPosition(px,py,pz);
	
	
}

void Object::setTexture(CGFappearance* appearance){

	this->appearance = appearance;
}

void Object::draw()
{
	if (appearance != NULL)
	{
		appearance->apply();
	}
}