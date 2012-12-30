#include "Piece.h"

Piece::Piece()
{
    this->currentCell_ID = 0;
    this->type = "undefined";
    this->color = "undefined";
    bounce = NULL;
    frameCounter = 0;
    selected = false;
    dead = false;
    initModel();
}

Piece::Piece(string type, string color)
{
    this->currentCell_ID = 0;
    this->type = type;
    this->color = color;
    bounce = new DemoShader("../shaders/bounce.vert", "../shaders/dummyFrag.frag");
    frameCounter = 0;
    selected = false;
    dead = false;
    initModel();
}

Piece::Piece(const char encoding)
{
    currentCell_ID = 0;
    dead = false;

    switch (encoding)
    {
    case 'g':
        type = "king";
        color = "black";
        break;
    case 'u':
        type = "queen";
        color = "black";
        break;
    case 'h':
        type = "knight";
        color = "black";
        break;
    case 'i':
        type = "bishop";
        color = "black";
        break;
    case 'o':
        type = "rook";
        color = "black";
        break;
    case 'a':
        type = "pawn";
        color = "black";
        break;
    case 'k':
        type = "king";
        color = "white";
        break;
    case 'q':
        type = "queen";
        color = "white";
        break;
    case 'n':
        type = "knight";
        color = "white";
        break;
    case 'b':
        type = "bishop";
        color = "white";
        break;
    case 'r':
        type = "rook";
        color = "white";
        break;
    case 'p':
        type = "pawn";
        color = "white";
        break;
    }

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

    if (color == "white")
    {
        bounce->setBaseTexture("../textures/ivory.jpg");
    }
    else
    {
        bounce->setBaseTexture("../textures/black.jpg");
    }
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

bool Piece::getSelected()
{

    return selected;
}

void Piece::setSelected(bool sel)
{

    this->selected = sel;
}

void Piece::draw()
{
    if (dead == false)
    {
        glPushMatrix();
        glRotated(this->rotationAngle_ZZ, 0, 0, 1);
        glTranslated(0, TORUS_OUTER_RADIUS - TORUS_INNER_RADIUS, 0);
        glRotated(this->rotationAngle_XX, 1, 0, 0);
        glTranslated(0, TORUS_INNER_RADIUS, 0);

        //glRotated(this->rotationAngle_ZZ,0,0,1);
        //glTranslated(TORUS_OUTER_RADIUS, this->getPos_y(), this->getPos_z());
        /*
        glutSolidSphere(0.75, 50, 50);
        glTranslated(0, 0.5, 0);
        glutSolidCube(1);
         */

        if (selected)
        {
            glPushMatrix();
            frameCounter++;
            bounce->bind();
            bounce->update(frameCounter);
            model->draw();
            bounce->unbind();
            glPopMatrix();
        }
        else
        {
            frameCounter = 0;
            bounce->bind();
            bounce->update(frameCounter);
            model->draw();
            bounce->unbind();
        }

        glPopMatrix();
    }
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

void Piece::setCellID(int lin, int col)
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

string Piece::toShortString()
{
    if (color == "black")
    {
        if (type == "pawn")
            return "a";
        else if (type == "rook")
            return "o";
        else if (type == "bishop")
            return "i";
        else if (type == "knight")
            return "h";
        else if (type == "queen")
            return "u";
        else if (type == "king")
            return "g";
        else
        {
            cerr << "Problem in Piece::toString - unknown color";
            exit(-1);
        }
    }
    else if (color == "white")
    {
        if (type == "pawn")
            return "p";
        else if (type == "rook")
            return "r";
        else if (type == "bishop")
            return "b";
        else if (type == "knight")
            return "n";
        else if (type == "queen")
            return "q";
        else if (type == "king")
            return "k";
        else
        {
            cerr << "Problem in Piece::toString - unknown color";
            exit(-1);
        }
    }
    else
    {
        cerr << "Problem in Piece::toString - unknown color";
        exit(-1);
    }
}

string Piece::toLongString()
{
    ostringstream sout;

    sout << "piece(" << color << "," << type << ")";
    return sout.str();
}

void Piece::die()
{
    dead = true;
}

void Piece::live()
{
    dead = false;
}

bool Piece::isDead()
{
    return dead;
}