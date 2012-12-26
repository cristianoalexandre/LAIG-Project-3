#include "Board.h"



Board::Board(){

	
	for(int i = 0; i < 8; i++){

		this->whitePieces.push_back(new Piece('P'));
		this->blackPieces.push_back(new Piece('P'));
	}

	for(int i = 0; i < 2; i++){

		this->whitePieces.push_back(new Piece('H'));
		this->blackPieces.push_back(new Piece('H'));
		this->whitePieces.push_back(new Piece('R'));
		this->blackPieces.push_back(new Piece('R'));
		this->whitePieces.push_back(new Piece('B'));
		this->blackPieces.push_back(new Piece('B'));
	}

	this->whitePieces.push_back(new Piece('Q'));
	this->blackPieces.push_back(new Piece('Q'));
	this->whitePieces.push_back(new Piece('K'));
	this->blackPieces.push_back(new Piece('K'));


	this->torus_sensors = new TorusHitbox();

	//string initial_positions;

}


void Board::draw(){

	torus_sensors->draw();
}