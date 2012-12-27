#include "Piece.h"

Piece::Piece()
{
    this->currentCell_ID = 0;
    this->type = "undefined";
    this->color = "undefined";
    initModel();
}

Piece::Piece(string type, string color)
{
    this->currentCell_ID = 0;
    this->type = type;
    this->color = color;
    initModel();
}

Piece::~Piece()
{
    delete model;
}

void Piece::initModel()
{
    string fileString = "../models/";
    fileString += color;
    fileString += titlecase(type);
    fileString += ".obj";

    cout << "Loading model at " << fileString << endl;
    model = new Model(fileString);
}

int Piece::getCurrentCell()
{
    return this->currentCell_ID;
}

double Piece::get_XX_Angle()
{
    return this->rotationAngle_XX;
}

double Piece::get_ZZ_Angle()
{
    return this->rotationAngle_ZZ;
}

void Piece::set_XX_Angle(double ang)
{
    this->rotationAngle_XX = ang;
}

void Piece::set_ZZ_Angle(double ang)
{
    this->rotationAngle_ZZ = ang;
}

void Piece::setCurrentCellID(int i)
{
    this->currentCell_ID = i;
}

void Piece::moveToCell(int cellID)
{
    int innerSection = cellID % 10;
    int outerSection = cellID / 10;

    this->rotationAngle_ZZ = -22.5;

    while (outerSection > 1)
    {
        this->rotationAngle_ZZ -= 45;
        outerSection--;
    }

    this->rotationAngle_XX = 22.5;

    while (innerSection > 1)
    {
        this->rotationAngle_XX += 45;
        innerSection--;
    }

    setCurrentCellID(cellID);
}

void Piece::draw()
{
    glPushMatrix();
    glRotated(this->rotationAngle_ZZ, 0, 0, 1);
    glTranslated(0, TORUS_OUTER_RADIUS * SCALING_FACTOR + 0.75, 0);
    glRotated(this->rotationAngle_XX, 1, 0, 0);
    glTranslated(0, TORUS_INNER_RADIUS * SCALING_FACTOR + 0.75, 0);

    //glRotated(this->rotationAngle_ZZ,0,0,1);
    //glTranslated(TORUS_OUTER_RADIUS, this->getPos_y(), this->getPos_z());
    /*
    glutSolidSphere(0.75, 50, 50);
    glTranslated(0, 0.5, 0);
    glutSolidCube(1);
     */
    glPushMatrix();
    glScalef(20,20,20);
    model->draw();
    glPopMatrix();

    glPopMatrix();
}

string Piece::getType()
{
    return type;
}

string Piece::getColor()
{
    return color;
}

bool Piece::operator ==(Piece &piece)
{
    return ((this->getType() == piece.getType())
            && (this->getCurrentCell() == piece.getCurrentCell())
            && (this->getColor() == piece.getColor()));
}

int Piece::getCurrentLin()
{
    int lin = currentCell_ID % 10;

    if (lin == 0)
    {
        cerr << "getCurrentLin(): Invalid ID! - " << currentCell_ID;
        exit(-1);
    }

    return abs(lin - 8);
}

int Piece::getCurrentCol()
{
    int col = currentCell_ID / 10;

    if (col == 0)
    {
        cerr << "getCurrentCol(): Invalid ID! - " << currentCell_ID;
        exit(-1);
    }

    return col - 1;
}

void Piece::setCell(int lin, int col)
{
    currentCell_ID = col + 1;
    currentCell_ID *= 10;
    currentCell_ID += abs(lin - 8);

    if (currentCell_ID % 10 == 0
            || currentCell_ID < 11
            || currentCell_ID > 88)
    {
        cerr << "setCell() - Invalid ID!";
        exit(-1);
    }
    
    moveToCell(currentCell_ID);
}