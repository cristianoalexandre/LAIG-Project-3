#ifndef CELL_H
#define CELL_H

#include "Object.h"
#include "Patch.h"
#include "magicNumbers.h"

class Cell: public Object
{
private:
	int id;
	Patch* shape;

public:
	Cell();
	Cell(Patch* patch);
	~Cell();

	int getID();
	void setID(int i);
	void setPosition(int id);
	unsigned int getRow();
	unsigned int getCol();

	void draw();
};

#endif