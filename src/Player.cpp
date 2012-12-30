#include "Player.h"

Player::Player()
{
    
}

Player::Player(string color)
{
    this->color = color;
    type = HUMAN;
}

Player::Player(string color, int type)
{
    this->color = color;
    this->type = type;
}

string Player::getColor()
{
    return color;
}

string Player::toString()
{
    ostringstream sout;
    
    sout << color << ",";
    
    if (type == HUMAN)
        sout << "human";
    else
        sout <<  type ;
    
    return sout.str();
}

int Player::getType()
{
	return type;
}