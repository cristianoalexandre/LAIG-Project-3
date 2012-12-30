#ifndef PLAY_H
#define	PLAY_H

#include <sstream>
#include <string>

#include "Cell.h"
#include "AuxiliaryFunctions.h"

#define GENERIC 0
#define KILL 1
#define MOVE 2

using namespace std;

class Play
{
protected:
	Cell* srcCell;
	Cell* destCell;
	Piece* piece;
public:

	Play();
	~Play();
	Play(int srcCellRow, int srcCellCol, int destCellRow, int destCellCol, Piece* piece);
	unsigned int getSrcCellRow();
	unsigned int getSrcCellCol();
	unsigned int getDestCellRow();
	unsigned int getDestCellCol();

	Cell* getDestCell();
	Piece* getPiece();

	virtual string toString();
	virtual unsigned int type();
};

#endif	/* PLAY_H */

