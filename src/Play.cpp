#include "Play.h"

Play::Play()
{
}

Play::Play(int srcCellRow, int srcCellCol, int destCellRow, int destCellCol, Piece piece)
{
    srcCell = Cell(srcCellRow, srcCellCol);
    destCell = Cell(destCellRow, destCellCol);
    this->piece = piece;
}

unsigned int Play::getSrcCellRow()
{
    return srcCell.row;
}

unsigned int Play::getSrcCellCol()
{
    return srcCell.col;
}

unsigned int Play::getDestCellRow()
{
    return destCell.row;
}

unsigned int Play::getDestCellCol()
{
    return destCell.col;
}

string Play::toString()
{
    return string();
}

unsigned int Play::type()
{
    return GENERIC;
}