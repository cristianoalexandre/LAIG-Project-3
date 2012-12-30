#ifndef PLAYER_H
#define	PLAYER_H

#include <string>
#include <sstream>

#define HUMAN 0
#define CPU_EASY 1
#define CPU_MEDIUM 2
#define CPU_HARD 3

using namespace std;

class Player
{
private:
	string color; /* black or white */
	int type;
public:
	Player();
	Player(string color);
	Player(string color, int type);
	
	string getName();
	string getColor();
		
	string toString();
};

#endif	/* PLAYER_H */

