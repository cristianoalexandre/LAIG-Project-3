#include "Game.h"

Game::Game()
{
    player1 = NULL;
    player2 = NULL;
    board = NULL;
    socket = NULL;
}

Game::Game(Player * player1, Player * player2)
{
    this->player1 = player1;
    this->player2 = player2;
    board = new Board();
    socket = new Socket("localhost", 60001);
}

Game::~Game()
{
    delete board;
    delete socket;
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
    lastMessageType = NONE;
    return (msg == "yes");
}

bool Game::parseCheckMateMsg(string msg)
{
    lastMessageType = NONE;
    return (msg == "yes");
}

bool Game::parseDrawMsg(string msg)
{
    lastMessageType = NONE;
    return (msg == "yes");
}

bool Game::parseReadyMsg(string msg)
{
    lastMessageType = NONE;
    return (msg == "yes");
}

bool Game::parsePlayMsg(string msg)
{
    return true;
}

vector <Cell*> Game::parseSelectMsg(string msg)
{
    vector <string> cellsStr = stringExplode(msg, ",");

    vector <Cell*> cells;

    for (vector <string>::iterator it = cellsStr.begin(); it != cellsStr.end(); it++)
    {
        cells.push_back(new Cell(*it));
    }

    return cells;
}

void Game::changePlayer()
{
    if (currentPlayer == player1)
        currentPlayer = player2;
    else
        currentPlayer = player1;
}

void Game::draw()
{
    board->draw();
}

void Game::sendSelectMsg(Cell& srcCell)
{
    ostringstream msg;

    msg << "select(" << board->toString() << "," <<
            srcCell.getPiece()->toLongString() << "," << srcCell.toString() << ".\n";

    socket->sendMsg(msg.str());
    lastMessageType = SELECT;
}

void Game::sendCheckMsg()
{
    ostringstream msg;

    msg << "search_check(" << board->toString() << "," << currentPlayer->getColor() << ".\n";

    socket->sendMsg(msg.str());
    lastMessageType = CHECK;
}

void Game::sendCheckMateMsg()
{
    ostringstream msg;

    msg << "search_checkmate(" << board->toString() << "," << currentPlayer->getColor() << ".\n";

    socket->sendMsg(msg.str());
    lastMessageType = CHECKMATE;
}

void Game::sendDrawMsg()
{
    ostringstream msg;

    msg << "search_draw(" << board->toString() << ".\n";
}

void Game::playCycle()
{
    
}