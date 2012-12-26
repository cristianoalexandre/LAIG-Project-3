#include "Ring.h"


Ring::Ring(){

	this->front = new Strip();
	this->back = new Strip();
	
	numberExistingRings++;
	this->ringID = numberExistingRings;
}

void Ring::attributeCellIDs(){

	front->getTop()->setID((ringID*10) +1);
	front->getMiddleTop()->setID((ringID*10) +2);
	front->getMiddleBottom()->setID((ringID*10) +3);
	front->getBottom()->setID((ringID*10) +4);

	back->getTop()->setID((ringID*10) +8);
	back->getMiddleTop()->setID((ringID*10) +7);
	back->getMiddleBottom()->setID((ringID*10) +6);
	back->getBottom()->setID((ringID*10) +5);
}

void Ring::draw(){

	glPushMatrix();
		front->draw();
		glRotatef(180,0,1,0);
		back->draw();
	glPopMatrix();
}