#ifndef GAME_H
#define	GAME_H

#include <stack>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "Socket.h"
#include "Play.h"
#include "AuxiliaryFunctions.h"
#include "Board.h"
#include "Player.h"

using namespace std;

#define READY 0
#define SELECT 1
#define PLAY 2
#define CHECK 3
#define CHECKMATE 4
#define DRAW 5

class Game
{
private:
	stack <Play*> executedPlays;
	int lastMessageType;
	Player *player1;
	Player *player2;
	Player *currentPlayer;
	Socket *socket;

public:
	Game();
	Game(Player * player1, Player * player2);
	~Game();

	void viewReplay();
	void makePlay(Play* newPlay);
	void changePlayer();

	void parseMsg(string msg);

	bool parseReadyMsg(string msg);
	vector <Cell*> parseSelectMsg(string msg);
	Board* parsePlayMsg(string msg);
	bool parseCheckMsg(string msg);
	bool parseCheckMateMsg(string msg);
	bool parseDrawMsg(string msg);
};

#endif	/* GAME_H */

