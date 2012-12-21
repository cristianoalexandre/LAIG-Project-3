#ifndef KILL_H
#define KILL_H

#include "Play.h"

using namespace std;

class Kill : public Play
{
private:

public:
	Kill() : Play() {};
	Kill(int srcCellRow, int srcCellCol, int destCellRow, int destCellCol, Piece piece)
		:Play(srcCellRow, srcCellCol, destCellRow, destCellCol, piece){};

	unsigned int type();
};

#endif /* KILL_H */