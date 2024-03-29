#ifndef PIECE_H
#define PIECE_H


#include "Object.h"
#include "magicNumbers.h"
#include "Model.h"
#include <string>
#include <sstream>
#include "stringcase.hpp"
#include "DemoShader.h"

using namespace std;

class Piece : public Object
{
private:
	string type;
	string color;
	int currentCell_ID;
	bool dead;

	double rotationAngle_XX;
	double rotationAngle_ZZ;

	Model * model;
	DemoShader* bounce;

	bool selected;
	int frameCounter;

public:
	Piece();
	Piece(string type, string color);
	Piece(const char shortEncoding);
	~Piece();

	string getType();
	string getColor();
	int getCurrentCell();
	double get_XX_Angle();
	double get_ZZ_Angle();

	int getCurrentLin();
	int getCurrentCol();

	void initModel();

	bool getSelected();
	void setSelected(bool sel);
	void set_XX_Angle(double ang);
	void set_ZZ_Angle(double ang);
	void setCurrentCellID(int i);
	void moveToCell(int cellID);
	void setCellID(int lin, int col);
	string toShortString();
	string toLongString();
	void die();
	void live();
    bool isDead();

	void draw();

	bool operator ==(Piece &piece);
};

#endif