#include "Game.h"

Game::Game()
{
    player1 = NULL;
    player2 = NULL;
}

Game::Game(Player * player1, Player * player2)
{
    this->player1 = player1;
    this->player2 = player2;
}

Game::~Game()
{
}

void Game::viewReplay()
{
}

void Game::makePlay(Play* newPlay)
{

}

void Game::parseMsg(string msg)
{
    switch (lastMessageType)
    {
    case READY:
        parseReadyMsg(msg);
        break;
    case SELECT:
        parseSelectMsg(msg);
        break;
    case PLAY:
        parsePlayMsg(msg);
        break;
    case CHECK:
        parseCheckMsg(msg);
        break;
    case CHECKMATE:
        parseCheckMateMsg(msg);
        break;
    case DRAW:
        parseDrawMsg(msg);
        break;
    default:
        cerr << "Unknown message type - Aborting." << endl;
        exit(-1);
    }
}

bool Game::parseCheckMsg(string msg)
{
    return (msg == "yes");
}

bool Game::parseCheckMateMsg(string msg)
{
    return (msg == "yes");
}

bool Game::parseDrawMsg(string msg)
{
    return (msg == "yes");
}

bool Game::parseReadyMsg(string msg)
{
    return (msg == "yes");
}

Board * Game::parsePlayMsg(string msg)
{
    ;
}

vector <Cell*> Game::parseSelectMsg(string msg)
{
    return vector<Cell*>();
}

void Game::changePlayer()
{
    if (currentPlayer == player1)
        currentPlayer = player2;
    else
        currentPlayer = player1;
}