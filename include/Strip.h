#ifndef STRIP_H
#define STRIP_H


#include "Cell.h"

class Strip: public Object {
	
private:
	Cell* top;
	Cell* middleTop;
	Cell* middleBottom;
	Cell* bottom;

	double delta_z;

public:

	Strip();

	Cell* getTop();
	Cell* getMiddleTop();
	Cell* getMiddleBottom();
	Cell* getBottom();

	void draw();
};

#endif