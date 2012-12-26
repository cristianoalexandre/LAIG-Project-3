#include "Game.h"

Game::Game()
{
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
    return false;
}

bool Game::parseCheckMateMsg(string msg)
{
    return false;
}

bool Game::parseDrawMsg(string msg)
{
    return false;
}

Board* Game::parsePlayMsg(string msg)
{
    return new Board();
}

bool Game::parseReadyMsg(string msg)
{
    return false;
}

vector <Cell*> Game::parseSelectMsg(string msg)
{
    return vector<Cell*>();
}