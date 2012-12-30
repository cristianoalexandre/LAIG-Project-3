#ifndef GAME_H
#define	GAME_H

#include <stack>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>

#include "Socket.h"
#include "Play.h"
#include "AuxiliaryFunctions.h"
#include "Board.h"
#include "Player.h"
#include "Kill.h"
#include "Move.h"
#include "PieceAnimation.h"

using namespace std;

#define READY 0
#define SELECT 1
#define PLAY 2
#define CHECK 3
#define CHECKMATE 4
#define DRAW 5
#define NONE 6

/* GAME STATUS */
#define PICKING_1 1
#define SENDING_SELECT 2
#define WAITING_SELECT 3
#define PICKING_2 4
#define CPU_PLAYING 40
#define PLAYING 5
#define SENDING_DRAW 6
#define WAITING_DRAW 7
#define SENDING_CHECKMATE_2 8
#define WAITING_CHECKMATE_2 9
#define SENDING_CHECK_2 10
#define WAITING_CHECK_2 11
#define CHANGE_PLAYER 19
#define SENDING_CHECKMATE_1 12
#define WAITING_CHECKMATE_1 13
#define SENDING_CHECK_1 14
#define WAITING_CHECK_1 15
#define SEND_CPU_MSG 30
#define WAITING_CPU_ANS 31

/* GAME OVER */
#define GAME_DRAW 16
#define WHITE_WIN 17
#define BLACK_WIN 18

class Game
{
public:
    stack <Play*> executedPlays;
    int lastMessageType;
    Player *player1;
    Player *player2;
    Player *currentPlayer;
    Socket *socket;
    Board *board;
    int status;
    int firstPickedCell;
    int secondPickedCell;
    vector <Cell*> possiblePlays;
	vector <Cell*> cpuPlay;

	PieceAnimation* anim;

    Game();
    Game(Player * player1, Player * player2);
    ~Game();

    void viewReplay();
    void makePlay(Play* newPlay);
    void changePlayer();

    void parseMsg(string msg);

    bool parseReadyMsg(string msg);
    vector <Cell*> parseSelectMsg(string msg);
    vector <Cell*> parseCPUPlayMsg(string msg);
    bool parseCheckMsg(string msg);
    bool parseCheckMateMsg(string msg);
    bool parseDrawMsg(string msg);

    void sendCheckMsg();
    void sendCheckMateMsg();
    void sendDrawMsg();
	void sendSelectMsg(Piece *piece);
	void sendCPUPlayMsg();

    void disconnectSocket();
    void connectSocket();
    void reloadSocket();
    void draw();
    void undo();
};

#endif	/* GAME_H */

