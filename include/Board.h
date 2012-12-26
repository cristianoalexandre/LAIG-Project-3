#ifndef BOARD_H
#define	BOARD_H


#include "TorusHitbox.h"

class Board
{
private:

	string boardState;
	vector<Piece*> whitePieces;
	vector<Piece*> blackPieces;
	TorusHitbox* torus_sensors;

public:

	Board();

	void draw();

};

#endif	/* BOARD_H */

