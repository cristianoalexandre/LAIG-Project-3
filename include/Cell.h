#ifndef CELL_H
#define CELL_H


#include "Patch.h"
#include "Piece.h"
#include "magicNumbers.h"

class Cell
{
private:

	int id;
	Patch* shape;
	
	Piece* piece;

public:

	Cell();
	Cell(Patch* patch);
	~Cell();

	int getID();
	void setID(int i);
	void setPosition(int id);
	void setPiece(Piece* p);
	unsigned int getRow();
	unsigned int getCol();

	void draw();
};

#endif