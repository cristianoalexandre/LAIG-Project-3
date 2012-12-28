#ifndef PLAYER_H
#define	PLAYER_H

#include <string>

#define HUMAN 0
#define CPU_EASY 1
#define CPU_MEDIUM 2
#define CPU_HARD 3

using namespace std;

class Player
{
private:
	string name;
	string color; /* black or white */
	int type;
public:
	Player();
	Player(string name, string color);
	string getName();
	string getColor();
};

#endif	/* PLAYER_H */

