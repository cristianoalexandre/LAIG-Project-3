#include "Cell.h"

Cell::Cell()
{

}

Cell::Cell(Patch* eval)
{
    this->shape = eval;
}

Cell::~Cell()
{

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

void Cell::draw()
{

    this->shape->draw();
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
    return -1;
}

unsigned int Cell::getRow()
{
    return -1;
}