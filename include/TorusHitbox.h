#ifndef TORUSHITBOX_H
#define TORUSHITBOX_H


#include "Ring.h"

class TorusHitbox: public Object {

private:

	Ring* ring1;
	Ring* ring2;
	Ring* ring3;
	Ring* ring4;
	Ring* ring5;
	Ring* ring6;
	Ring* ring7;
	Ring* ring8;


public:
	TorusHitbox();
	void draw();
};

#endif