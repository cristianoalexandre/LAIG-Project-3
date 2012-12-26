#include "Piece.h"


Piece::Piece(){
	this->currentCell_ID = 0;
	this->type = 'U';
}

Piece::Piece(char t){
	this->currentCell_ID = 0;
	this->type = t;
}

int Piece::getCurrentCell(){

	return this->currentCell_ID;
}

double Piece::get_XX_Angle(){

	return this->rotationAngle_XX;
}

double Piece::get_ZZ_Angle(){

	return this->rotationAngle_ZZ;
}

void Piece::set_XX_Angle(double ang){

	this->rotationAngle_XX = ang;
}

void Piece::set_ZZ_Angle(double ang){
	
	this->rotationAngle_ZZ = ang;
}


void Piece::setCurrentCellID(int i){

	this->currentCell_ID = i;

}


void Piece::moveToCell(int cellID){

	int innerSection = cellID%10;
	int outerSection = cellID/10;


	this->rotationAngle_ZZ = -22.5;

	while(outerSection > 1){

		this->rotationAngle_ZZ -= 45;
		outerSection--;
	}

	this->rotationAngle_XX = 22.5;

	while(innerSection > 1){

		this->rotationAngle_XX += 45;
		innerSection--;
	}

	setCurrentCellID(cellID);
}

void Piece::draw(){

	glPushMatrix();
		glRotated(this->rotationAngle_ZZ,0,0,1);
		glTranslated(0, TORUS_OUTER_RADIUS*SCALING_FACTOR +0.75, 0);
		glRotated(this->rotationAngle_XX,1,0,0);
		glTranslated(0, TORUS_INNER_RADIUS*SCALING_FACTOR +0.75, 0);

		//glRotated(this->rotationAngle_ZZ,0,0,1);
		//glTranslated(TORUS_OUTER_RADIUS, this->getPos_y(), this->getPos_z());
		glutSolidSphere(0.75,50,50);
		glTranslated(0,0.5,0);
		glutSolidCube(1);

	glPopMatrix();
}