#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int k = 0; k < 8; k++)
        {
            setCellContent(i, k, NULL);
        }
    }

    this->pieces.push_back(new Piece("rook", "black"));
    setCellContent(7, 0, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("rook", "black"));
    setCellContent(7, 7, (*(pieces.rbegin())));

    this->pieces.push_back(new Piece("rook", "white"));
    setCellContent(0, 0, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("rook", "white"));
    setCellContent(0, 7, (*(pieces.rbegin())));

    this->pieces.push_back(new Piece("bishop", "white"));
    setCellContent(0, 2, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("bishop", "black"));
    setCellContent(7, 2, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("bishop", "white"));
    setCellContent(0, 5, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("bishop", "black"));
    setCellContent(7, 5, (*(pieces.rbegin())));

    this->pieces.push_back(new Piece("knight", "white"));
    setCellContent(2, 0, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("knight", "black"));
    setCellContent(5, 0, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("knight", "white"));
    setCellContent(2, 7, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("knight", "black"));
    setCellContent(5, 7, (*(pieces.rbegin())));

    this->pieces.push_back(new Piece("queen", "white"));
    setCellContent(2, 3, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("queen", "black"));
    setCellContent(5, 3, (*(pieces.rbegin())));

    this->pieces.push_back(new Piece("king", "white"));
    setCellContent(2, 4, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("king", "black"));
    setCellContent(5, 4, (*(pieces.rbegin())));

    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(1, 0, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(6, 0, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(1, 1, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(6, 1, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(2, 2, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(5, 2, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(3, 3, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(4, 3, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(3, 4, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(4, 4, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(3, 5, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(5, 5, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(1, 6, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(6, 6, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "white"));
    setCellContent(6, 7, (*(pieces.rbegin())));
    this->pieces.push_back(new Piece("pawn", "black"));
    setCellContent(1, 7, (*(pieces.rbegin())));

    this->torus_sensors = new TorusHitbox();
}

void Board::draw()
{

    torus_sensors->draw();

    for (int i = 0; i < pieces.size(); i++)
    {
        pieces.at(i)->draw();
    }
}

void Board::setCellContent(int lin, int col, Piece* piece)
{
    board[abs(lin - 7)][col] = piece;

    if (piece != NULL)
        piece->setCell(lin, col);
}

Piece * Board::findPiece(Piece& pieceToFind)
{
    for (vector<piecePtr>::iterator it = pieces.begin(); it != pieces.end(); it++)
    {
        if ((*(*it)) == pieceToFind)
        {
            return (*it);
        }
    }
}