#ifndef PLAYER_H
#define	PLAYER_H

#include <string>

using namespace std;

class Player
{
private:
    string name;
    string color; /* black or white */
public:
    Player();
    Player(string name, string color);
    string getName();
    string getColor();
};

#endif	/* PLAYER_H */

