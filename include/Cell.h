#ifndef CELL_H
#define	CELL_H

class Cell
{
public:
	unsigned int row;
	unsigned int col;
	
	Cell() {};
	Cell(unsigned int row, unsigned int col) {this->row = row; this->col = col;}
};

#endif	/* CELL_H */

