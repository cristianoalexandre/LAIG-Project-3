#include "Play.h"

Play::Play()
{
}

Play::Play(int srcCellRow, int srcCellCol, int destCellRow, int destCellCol, Piece piece)
{
    //srcCell = Cell(srcCellRow, srcCellCol);
    //destCell = Cell(destCellRow, destCellCol);
    this->piece = piece;
}

unsigned int Play::getSrcCellRow()
{
    return srcCell.getRow();
}

unsigned int Play::getSrcCellCol()
{
    return srcCell.getCol();
}

unsigned int Play::getDestCellRow()
{
    return destCell.getRow();
}

unsigned int Play::getDestCellCol()
{
    return destCell.getCol();
}

string Play::toString()
{
    return string();
}

unsigned int Play::type()
{
    return GENERIC;
}