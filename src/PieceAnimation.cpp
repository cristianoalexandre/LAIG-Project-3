#include "PieceAnimation.h"



PieceAnimation::PieceAnimation(){
	this->piece = NULL;
	this->totalAnimationTime = 2;
}

void PieceAnimation::setPiece(Piece* p){

	this->piece = p;
}

void PieceAnimation::setMovement(int end, int outerDir, int innerDir){//dir = 0 -> move down; dir = 1 -> move up

	if(this->piece == NULL){
		cout << "PIECE IS NULL; CANNOT SET MOVEMENT\nPRESS ENTER TO EXIT" << endl;
		cin.get();
		exit(1);
	}

	this->initialCell = this->piece->getCurrentCell();
	this->endCell = end;

	int iniRing, endRing, iniRingCell, endRingCell, tmp;

	iniRing = this->initialCell/10;
	endRing = this->endCell/10;
	iniRingCell = this->initialCell%10;
	endRingCell = this->endCell%10;
	

	if(iniRing > endRing){

		switch(outerDir){
		case 0:
			{
				tmp = abs(endRing - iniRing);
				break;
			}
		case 1:
			{
				tmp =  -8 + abs(endRing - iniRing);
				break;
			}
		default:
			{
				cout << "UNRECOGNIZED DIRECTION WHEN INITIALIZING MOVEMENT\nPRESS ENTER TO EXIT" << endl;
				cin.get();
				exit(1);
				break;
			}
		}
		this->ZZ_angularIncrement = (tmp*45)/(totalAnimationTime/mili_secs*1000);
	}else{

		if(iniRing == endRing){
			this->ZZ_angularIncrement = 0;
		}else{

			switch(outerDir){
			case 0:
				{
					tmp = 8 - (endRing - iniRing);
					break;
				}
			case 1:
				{
					tmp =  (endRing - iniRing)*-1;
					break;
				}
			default:
				{
					cout << "UNRECOGNIZED DIRECTION WHEN INITIALIZING MOVEMENT\nPRESS ENTER TO EXIT" << endl;
					cin.get();
					exit(1);
					break;
				}
			}
			this->ZZ_angularIncrement = (tmp*45)/(totalAnimationTime/mili_secs*1000);
		}

	}



	if(iniRingCell > endRingCell){

		switch(innerDir){
		case 0:
			{
				tmp = endRingCell - iniRingCell;
				break;
			}
		case 1:
			{
				tmp =  8 - abs(endRingCell - iniRingCell);
				break;
			}
		default:
			{
				cout << "UNRECOGNIZED DIRECTION WHEN INITIALIZING MOVEMENT\nPRESS ENTER TO EXIT" << endl;
				cin.get();
				exit(1);
				break;
			}
		}

		this->XX_angularIncrement = (tmp*45)/(totalAnimationTime/mili_secs*1000);
	}else{
		if(iniRingCell == endRingCell){
			this->XX_angularIncrement = 0;
		}else{

			switch(innerDir){
			case 0:
				{
					tmp = (endRingCell - iniRingCell)*-1;
					break;
				}
			case 1:
				{
					tmp =  endRingCell - iniRingCell;
					break;
				}
			default:
				{
					cout << "UNRECOGNIZED DIRECTION WHEN INITIALIZING MOVEMENT\nPRESS ENTER TO EXIT" << endl;
					cin.get();
					exit(1);
					break;
				}
			}
			this->XX_angularIncrement = (tmp*45)/(totalAnimationTime/mili_secs*1000);
		}

	}


	this->ZZ_final = -22.5;

	while(endRing > 1){

		this->ZZ_final -= 45;
		endRing--;
	}

	this->XX_final = 22.5;

	while(endRingCell > 1){

		this->XX_final += 45;
		endRingCell--;
	}

}

void PieceAnimation::update(){

	if(XX_angularIncrement != 0){
		if(fabs(piece->get_XX_Angle() + XX_angularIncrement) >= fabs(XX_final)){
	
			piece->set_XX_Angle(this->XX_final);
			this->XX_angularIncrement = 0;
		}else{
			this->piece->set_XX_Angle(piece->get_XX_Angle() + XX_angularIncrement);
		}
	}

	if(ZZ_angularIncrement != 0){
		if(fabs(piece->get_ZZ_Angle() + ZZ_angularIncrement) >= fabs(ZZ_final)){
	
			piece->set_ZZ_Angle(this->ZZ_final);
			this->ZZ_angularIncrement = 0;
		}else{
			this->piece->set_ZZ_Angle(piece->get_ZZ_Angle() + ZZ_angularIncrement);
		}
	}
}

void PieceAnimation::setMiliSecs(unsigned int mSecs){

	mili_secs = mSecs;
}

unsigned int PieceAnimation::getMiliSecs(){

	return mili_secs;
}