#ifndef PIECE_H
#define PIECE_H


#include "Object.h"
#include "magicNumbers.h"
#include <string>

using namespace std;

class Piece: public Object
{
private:
	char type;
	int currentCell_ID;

	double rotationAngle_XX;
	double rotationAngle_ZZ;

public:
	Piece();
	Piece(char t);

	int getCurrentCell();
	double get_XX_Angle();
	double get_ZZ_Angle();

	void set_XX_Angle(double ang);
	void set_ZZ_Angle(double ang);
	void setCurrentCellID(int i);
	void moveToCell(int cellID);

	void draw();

};




#endif