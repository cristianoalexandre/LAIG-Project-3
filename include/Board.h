#ifndef BOARD_H
#define	BOARD_H

#include <algorithm>
#include <vector>

#include "TorusHitbox.h"

using namespace std;

typedef Piece* piecePtr;

class Board
{
private:
	string boardState;
	vector <piecePtr> pieces;
	TorusHitbox* torus_sensors;

	piecePtr board [8][8];

public:
	Board();
	Board(string boardStr);

	void draw();
	Piece * findPiece(Piece &pieceToFind);
	Piece * findPieceInCell(int id);
	Piece * findPieceInCell(int lin, int col);
	void setCellContent(int lin, int col, Piece * piece);

	string toString();
};

#endif	/* BOARD_H */