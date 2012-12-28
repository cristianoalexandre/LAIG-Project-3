#include "Torus.h"


Torus::Torus(){

}

Torus::~Torus(){
}

Torus::Torus(float iRadius, float oRadius, int slcs, int loops){

	this->innerRadius = iRadius;
	this->outerRadius = oRadius;
	this->slices = slcs;
	this->loops = loops;

}

void Torus::setInnerRadius(float irad){this->innerRadius = irad;}
void Torus::setOuterRadius(float oRad){this->outerRadius = oRad;}
void Torus::setSlices(int slcs){this->slices = slcs;}
void Torus::setLoops(int loop){this->loops = loop;}

void Torus::draw(){

	glutSolidTorus(this->innerRadius, this->outerRadius, this->slices, this->loops);

}


int Torus::addValues(string attr, string val){

	if(attr == "inner"){
		setInnerRadius(atof(val.c_str()));
	}else{
		if(attr == "outer"){
			setOuterRadius(atof(val.c_str()));
		}else{
			if(attr == "slices"){
				setSlices(atoi(val.c_str()));
			}else{
				if(attr == "loops"){
					setLoops(atoi(val.c_str()));
					return 1;
				}
			}
		}
	}
	return 0;
}
