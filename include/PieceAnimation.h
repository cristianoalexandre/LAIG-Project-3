#ifndef PIECEANIMATION_H
#define PIECEANIMATION_H


#include "Piece.h"
#include <iostream>
#include <math.h>

using namespace std;

class PieceAnimation
{
private:
    Piece* piece;

    int initialCell;
    int endCell;

    double ZZ_angularIncrement;
    double XX_angularIncrement;

    double XX_final;
    double ZZ_final;

    double totalAnimationTime;

    static unsigned int mili_secs;

public:

    PieceAnimation();

    void setPiece(Piece* p);
    void setMovement(int end, int outDir, int inDir);


    void update();

    static void setMiliSecs(unsigned int mSecs);
    static unsigned int getMiliSecs();
};




#endif


