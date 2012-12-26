#ifndef MOVE_H
#define MOVE_H

#include "Play.h"

using namespace std;

class Move : public Play
{
private:

public:
	Move() : Play() {};
	Move(int srcCellRow, int srcCellCol, int destCellRow, int destCellCol, Piece* piece)
		:Play(srcCellRow, srcCellCol, destCellRow, destCellCol, piece){};
	unsigned int type();
};

#endif /* MOVE_H */