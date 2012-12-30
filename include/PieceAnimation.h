#ifndef PIECEANIMATION_H
#define PIECEANIMATION_H


#include "Piece.h"
#include <iostream>

using namespace std;


class PieceAnimation
{

private:
	Piece* piece;
	
	int initialCell;
	int endCell;

	double ZZ_angularIncrement;
	double XX_angularIncrement;

	double total_angle_XX;
	double total_angle_ZZ;

	double XX_final;
	double ZZ_final;
	
	double totalAnimationTime;

	static unsigned int mili_secs;

public:
	
	PieceAnimation();

	void setPiece(Piece* p);
	void setEndCell(int end);
	void setTotalAnimationTime(double time);
	void setMovement(int outDir, int inDir);

	bool isAnimating();

	void update();

	static void setMiliSecs(unsigned int mSecs);
	static unsigned int getMiliSecs();
};




#endif


