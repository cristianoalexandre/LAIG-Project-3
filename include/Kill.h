#ifndef KILL_H
#define KILL_H

#include "Play.h"

using namespace std;

class Kill : public Play
{
private:

public:
	Kill();
	Kill(int srcCellRow, int srcCellCol, int destCellRow, int destCellCol, Piece* piece);

	unsigned int type();
};

#endif /* KILL_H */