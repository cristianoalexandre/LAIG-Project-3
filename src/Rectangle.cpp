#include "Rectangle.h"

Rectangle::Rectangle(){
}

Rectangle::~Rectangle(){
}

Rectangle::Rectangle(Vertex2D downLeftVertex, Vertex2D upRightVertex){

	this->bottomLeftVertex = downLeftVertex;
	this->upperRightVertex = upRightVertex; 
}


void Rectangle::setDownLeftX(float x){this->bottomLeftVertex.x = x;}
void Rectangle::setDownLeftY(float y){this->bottomLeftVertex.y = y;}

void Rectangle::setUpRightX(float x){this->upperRightVertex.x = x;}
void Rectangle::setUpRightY(float y){this->upperRightVertex.y = y;}


void Rectangle::draw(){
	
	glBegin(GL_QUADS);
	glNormal3f(0.0,0.0,1.0);
	glEnable(GL_NORMALIZE);
		glTexCoord2i(0, 0);
		glVertex3f(this->bottomLeftVertex.x, this->bottomLeftVertex.y, 0);
		glTexCoord2i(1, 0);
		glVertex3f(this->upperRightVertex.x, this->bottomLeftVertex.y, 0);
		glTexCoord2i(1, 1);
		glVertex3f(this->upperRightVertex.x, this->upperRightVertex.y, 0);
		glTexCoord2i(0, 1);
		glVertex3f(this->bottomLeftVertex.x, this->upperRightVertex.y, 0);
	glEnd();
}

int Rectangle::addValues(string attr, string val){

	if(attr == "x1"){
		setDownLeftX(atof(val.c_str()));
	}else{
		if(attr == "y1"){
			setDownLeftY(atof(val.c_str()));
		}else{
			if(attr == "x2"){
				setUpRightX(atof(val.c_str()));
			}else{
				if(attr == "y2"){
					setUpRightY(atof(val.c_str()));
					return 1;
				}
			}
		}
	}
	return 0;
}