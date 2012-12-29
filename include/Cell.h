#ifndef CELL_H
#define CELL_H

#include <sstream>
#include "Patch.h"
#include "Piece.h"
#include "magicNumbers.h"

class Cell
{
private:

    int id;
    Patch* shape;
    Piece* piece;

public:

    Cell();
    Cell(Patch* patch);
    Cell(string encoding);
    ~Cell();

    int getID();
    Piece * getPiece();
    void setID(int i);
    void setID(int lin, int col);
    void setPosition(int id);
    void setPiece(Piece* p);
    unsigned int getRow();
    unsigned int getCol();
    string toString();

    void draw();
    
    bool operator==(Cell &cell);
};

#endif