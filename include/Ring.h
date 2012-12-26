#ifndef RING_H
#define RING_H


#include "Strip.h"

class Ring: public Object {

private:

	Strip* front;
	Strip* back;
	
	int ringID;

	static int numberExistingRings;

public:

	Ring();

	static int getNumberExistingRings();
	static void setNumExistingRings(int n);

	void attributeCellIDs();
	void draw();
};

#endif