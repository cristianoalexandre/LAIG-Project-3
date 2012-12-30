#include "Game.h"

Game::Game()
{
	player1 = NULL;
	player2 = NULL;
	board = NULL;
	socket = NULL;
	status = PICKING_1;
	firstPickedCell = -1;
	secondPickedCell = -1;
	anim = NULL;
}

Game::Game(Player * player1, Player * player2)
{
	this->player1 = player1;
	this->player2 = player2;
	board = new Board();
	socket = new Socket("localhost", 60010);
	status = PICKING_1;
	firstPickedCell = -1;
	secondPickedCell = -1;
	currentPlayer = player1;
	anim = NULL;
}

Game::~Game()
{
	delete board;
	delete socket;
}

void Game::viewReplay()
{
	stack <Play*> executedPlaysCpy = executedPlays;
	queue <Play*> replayPlays;
	
	while (executedPlaysCpy.empty() == false)
	{
		replayPlays.push(executedPlaysCpy.top());
		executedPlaysCpy.pop();
	}
	
	while (executedPlays.empty() == false)
	{
		undo();
	}
	
	while (replayPlays.empty() == false)
	{
		makePlay(replayPlays.front());
		replayPlays.pop();
	}
}

void Game::undo()
{
	/* Primeiro desfazemos o movimento... */
	Play * play = executedPlays.top();
	executedPlays.pop();
	
	Piece * currentPiece = play->getPiece();
	currentPiece->setCellID(play->getSrcCellRow(),play->getSrcCellCol());
	
	/* E só depois as mortes. */
	
	while (executedPlays.empty() == false && executedPlays.top()->type() == KILL)
	{
		play = executedPlays.top();
		currentPiece = play->getPiece();
		currentPiece->live();
		currentPiece->setCellID(play->getDestCellRow(),play->getDestCellCol());
		
		executedPlays.pop();
	}
}

void Game::makePlay(Play* newPlay)
{
	executedPlays.push(newPlay);

	Piece * currentPiece = newPlay->getPiece();


	if (newPlay->type() == MOVE)
	{
		cout << "Moving to " << newPlay->getDestCellRow() << "," << newPlay->getDestCellCol() << endl;


		anim = new PieceAnimation();
		anim->setPiece(currentPiece);
		anim->setEndCell(newPlay->getDestCell()->getID());
		anim->setMovement(1,1);//ATENCAO a direccao, ainda se tem que calcular isso....

		//currentPiece->setCellID(newPlay->getDestCellRow(),newPlay->getDestCellCol());
		cout << "Finished moving." << endl;
	}
	else if (newPlay->type() == KILL)
	{
		cout << "Killing..." << endl;
		currentPiece->die();
		cout << "Killing completed." << endl;
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

vector <Cell*> Game::parseSelectMsg(string msg)
{
	vector <string> cellsStr = stringExplode(msg, ".");

	vector <Cell*> cells;

	for (int i = 0; i < cellsStr.size()-1; i++)
	{
		cout << cellsStr[i] << endl;
		cells.push_back(new Cell(cellsStr[i]));
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

void Game::sendSelectMsg(Piece *piece)
{
	ostringstream msg;

	Cell newCell;
	newCell.setID(piece->getCurrentCell());
	cout << piece->getCurrentCell() << endl;

	msg << "select(" << board->toString() << "," <<
		piece->toLongString() << "," << newCell.toString() << ").\n";

	cout << msg.str() << endl;
	socket->sendMsg(msg.str());
	lastMessageType = SELECT;
}

void Game::sendCPUPlayMsg()
{
	ostringstream msg;

	msg << "cpu_play(" << board->toString() << "," << currentPlayer->toString() << ").\n";

	cout << msg.str() << endl;
	socket->sendMsg(msg.str());
}

vector <Cell*> Game::parseCPUPlayMsg(string msg)
{
	cout << msg << endl;

	vector <string> cellsStr = stringExplode(msg, ".");

	vector <Cell*> cells;

	for (int i = 0; i < cellsStr.size(); i++)
	{
		cout << cellsStr[i] << endl;
		cells.push_back(new Cell(cellsStr[i]));
	}

	return cells;
}

void Game::sendCheckMsg()
{
	ostringstream msg;

	msg << "search_check(" << board->toString() << "," << currentPlayer->getColor() << ").\n";

	socket->sendMsg(msg.str());
	lastMessageType = CHECK;
}

void Game::sendCheckMateMsg()
{
	ostringstream msg;

	msg << "search_checkmate(" << board->toString() << "," << currentPlayer->getColor() << ").\n";
	
	cout << msg.str() << endl;
	socket->sendMsg(msg.str());
	lastMessageType = CHECKMATE;
}

void Game::sendDrawMsg()
{
	ostringstream msg;

	msg << "search_draw(" << board->toString() << ").\n";

	socket->sendMsg(msg.str());
	lastMessageType = DRAW;
}
void Game::disconnectSocket()
{
	socket->disconnect();
}

void Game::connectSocket()
{
	socket->open("localhost", 60010);
}

void Game::reloadSocket()
{
	disconnectSocket();
	connectSocket();
}