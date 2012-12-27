#ifndef PIECE_H
#define PIECE_H


#include "Object.h"
#include "magicNumbers.h"
#include "Model.h"
#include <string>
#include "stringcase.hpp"

using namespace std;

class Piece: public Object
{
private:
	string type;
        string color;
	int currentCell_ID;

	double rotationAngle_XX;
	double rotationAngle_ZZ;
        
        Model * model;

public:
	Piece();
	Piece(string type, string color);
        ~Piece();

        string getType();
        string getColor();
	int getCurrentCell();
	double get_XX_Angle();
	double get_ZZ_Angle();
        
        int getCurrentLin();
        int getCurrentCol();
        
        void initModel();

	void set_XX_Angle(double ang);
	void set_ZZ_Angle(double ang);
	void setCurrentCellID(int i);
	void moveToCell(int cellID);
        void setCell(int lin, int col);

	void draw();
        
        bool operator ==(Piece &piece);
};

#endif