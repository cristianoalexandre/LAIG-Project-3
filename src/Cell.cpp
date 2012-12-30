#include "Cell.h"

Cell::Cell()
{
	this->shape = NULL;
	this->piece = NULL;
}

Cell::Cell(Patch* eval)
{
	this->shape = eval;
	this->piece = NULL;
}

Cell::~Cell()
{
	delete shape;
	delete piece;
}

Cell::Cell(string encoding)
{
	if (encoding == "")
	{
		cerr << "Trying to create a cell from an empty string!" << endl;
		exit(-1);
	}
	
	string linStr = string(1,encoding[5]);
	string colStr = string(1,encoding[7]);
	
	cout << "Creating cell(" << linStr << "," << colStr << ")" << endl;

	setID(atoi(linStr.c_str()),atoi(colStr.c_str()));

	cout << "Cell created." << endl;
}

int Cell::getID()
{
	return this->id;
}

void Cell::setID(int i)
{
	this->id = i;
	setPosition(i);
}

void Cell::setID(int lin, int col)
{
	id = col + 1;
	id *= 10;
	id += abs(lin - 8);

	if (id % 10 == 0
			|| id < 11
			|| id > 88)
	{
		cerr << "Cell::setID() - Invalid ID!";
		exit(-1);
	}
}

void Cell::draw()
{
	this->shape->draw();
	if (this->piece != NULL)
	{
		this->piece->draw();
	}
}

void Cell::setPiece(Piece* p)
{
	this->piece = p;
	piece->setCurrentCellID(this->id);
}

void Cell::setPosition(int i)
{
	int outerSection = i / 10;
	int innerSection = i % 10;

	switch (outerSection)
	{

	case 1:
	{

		break;
	}
	case 2:
	{

		break;
	}
	case 3:
	{

		break;
	}
	case 4:
	{

		break;
	}
	case 5:
	{

		break;
	}
	case 6:
	{

		break;
	}
	case 7:
	{

		break;
	}
	case 8:
	{

		break;
	}
	}

	switch (innerSection)
	{

	case 1:
	{

		break;
	}
	case 2:
	{

		break;
	}
	case 3:
	{

		break;
	}
	case 4:
	{

		break;
	}
	case 5:
	{

		break;
	}
	case 6:
	{

		break;
	}
	case 7:
	{

		break;
	}
	case 8:
	{

		break;
	}
	}
}

unsigned int Cell::getCol()
{
	int col = id / 10;

	if (col == 0)
	{
		cerr << "getCol(): Invalid ID! - " << id;
		exit(-1);
	}

	return col - 1;
}

unsigned int Cell::getRow()
{
	int lin = id % 10;

	if (lin == 0)
	{
		cerr << "getRow(): Invalid ID! - " << id;
		exit(-1);
	}

	return abs(lin - 8);
}

string Cell::toString()
{
	ostringstream sout;
	
	sout << "cell(" << getRow() << "," << getCol() << ")";
	return sout.str();
}

bool Cell::operator ==(Cell& cell)
{
	return (getCol() == cell.getCol() && getRow() == cell.getRow());
}

Piece * Cell::getPiece()
{
	return piece;
}