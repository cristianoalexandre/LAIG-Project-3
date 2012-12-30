#include "PieceAnimation.h"



PieceAnimation::PieceAnimation(){
	this->piece = NULL;
	this->totalAnimationTime = 2;
	this->initialCell = 0;
	this->endCell = 0;
}

void PieceAnimation::setPiece(Piece* p){

	this->piece = p;
	this->totalAnimationTime = 2;
	this->initialCell = p->getCurrentCell();
}

void PieceAnimation::setEndCell(int end){

	this->endCell = end;
}

void PieceAnimation::setTotalAnimationTime(double time){

	this->totalAnimationTime = time;
}

bool PieceAnimation::isAnimating()
{
	return (ZZ_angularIncrement != 0 || XX_angularIncrement !=0);
}

void PieceAnimation::setMovement(int outerDir, int innerDir){//dir = 0 -> move down; dir = 1 -> move up

	cout << "piece_xx_angle = " << this->piece->get_XX_Angle() << endl;
	cout << "piece_zz_angle = " << this->piece->get_ZZ_Angle() << endl;

	if(this->piece == NULL){
		cout << "PIECE IS NULL; CANNOT SET MOVEMENT\nPRESS ENTER TO EXIT" << endl;
		cin.get();
		exit(1);
	}

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
		this->ZZ_angularIncrement = (tmp*45)/((totalAnimationTime*1000)/PieceAnimation::mili_secs);
		this->total_angle_ZZ = 45*tmp;
	}else{

		if(iniRing == endRing){
			this->ZZ_angularIncrement = 0;
			this->total_angle_ZZ = 0;
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
			this->ZZ_angularIncrement = (tmp*45)/((totalAnimationTime*1000)/PieceAnimation::mili_secs);
			this->total_angle_ZZ = 45*tmp;
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
		this->XX_angularIncrement = (tmp*45)/((totalAnimationTime*1000)/PieceAnimation::mili_secs);
		this->total_angle_XX = 45*tmp;
	}else{
		if(iniRingCell == endRingCell){
			this->XX_angularIncrement = 0;
			this->total_angle_XX = 0;
		}else{

			switch(innerDir){
			case 0:
				{
					tmp = (8 - (endRingCell - iniRingCell)) *-1;
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
			this->XX_angularIncrement = (tmp*45)/((totalAnimationTime*1000)/PieceAnimation::mili_secs);
			this->total_angle_XX = 45*tmp;
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

	
	cout << "xx_final = " << this->XX_final << endl;
	cout << "zz_final = " << this->ZZ_final << endl;

	cout << "piece_xx_angle = " << this->piece->get_XX_Angle() << endl;
	cout << "piece_zz_angle = " << this->piece->get_ZZ_Angle() << endl;

	cout << "total_angle_xx = " << this->total_angle_XX << endl;
	cout << "total_angle_zz = " << this->total_angle_ZZ << endl;

	cout << "inc_xx = " << this->XX_angularIncrement << endl;
	cout << "inc_zz = " << this->ZZ_angularIncrement << endl;


}

void PieceAnimation::update(){

	/*cout << "------------------------UPDATE------------------------" << endl;
	cout << "piece_xx_angle = " << this->piece->get_XX_Angle() << endl;
	cout << "piece_zz_angle = " << this->piece->get_ZZ_Angle() << endl;
	cout << "xx_inc = " << this->XX_angularIncrement << endl;
	cout << "zz_inc = " << this->ZZ_angularIncrement << endl;
	cout << "total_xx = " << this->total_angle_XX << endl;
	cout << "total_zz = " << this->total_angle_ZZ << endl;
	*/
	
	if(XX_angularIncrement != 0){

		double crossZero = this->total_angle_XX * (this->total_angle_XX + XX_angularIncrement) ; //valor anterior * valor actual
		if(crossZero <= 0){
	
			piece->set_XX_Angle(this->XX_final);
			this->XX_angularIncrement = 0;
		}else{
			this->piece->set_XX_Angle(piece->get_XX_Angle() + XX_angularIncrement);
			this->total_angle_XX -= XX_angularIncrement;
		}
	}

	if(ZZ_angularIncrement != 0){

		double crossZero = this->total_angle_ZZ * (this->total_angle_ZZ + ZZ_angularIncrement) ; //valor anterior * valor actual
		if(crossZero <= 0){
	
			piece->set_ZZ_Angle(this->ZZ_final);
			this->ZZ_angularIncrement = 0;
		}else{
			this->piece->set_ZZ_Angle(piece->get_ZZ_Angle() + ZZ_angularIncrement);
			this->total_angle_ZZ -= ZZ_angularIncrement;
		}
	}

	if(ZZ_angularIncrement == 0 && XX_angularIncrement == 0){
		piece->moveToCell(this->endCell);
	}

}

void PieceAnimation::setMiliSecs(unsigned int mSecs){

	mili_secs = mSecs;
}

unsigned int PieceAnimation::getMiliSecs(){

	return mili_secs;
}