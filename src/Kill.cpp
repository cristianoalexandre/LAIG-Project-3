#include "Kill.h"


Kill::Kill() : Play() {};


Kill::Kill(int srcCellRow, int srcCellCol, int destCellRow, int destCellCol, Piece* piece)
		:Play(srcCellRow, srcCellCol, destCellRow, destCellCol, piece){};

unsigned int Kill::type(){

	return -1;
}