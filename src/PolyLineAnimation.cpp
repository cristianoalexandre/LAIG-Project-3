
#include "PolyLineAnimation.h"


PolyLineAnimation::PolyLineAnimation(){
	setAnimatedObject(NULL);
	setTotalTime(0);
	setTotalDistance(0);
	ActivateAnimation(false);
	setRepeatAnimation(false);
}

PolyLineAnimation::PolyLineAnimation(Object* obj, double tot_time, bool repeat, int reset_ind){

	setAnimatedObject(obj);
	setTotalTime(tot_time);
	setRepeatAnimation(repeat);
	setResetSegment(reset_ind);
}

PolyLineAnimation::~PolyLineAnimation(){

}

int PolyLineAnimation::getTotalTime(){

	return this->total_time;
}

int PolyLineAnimation::getResetToSegment(){

	return this->reset_to_segment;
}

double PolyLineAnimation::getTotalDistance(){

	return this->total_distance;
}

bool PolyLineAnimation::getRepeatAnimation(){

	return this->repeat_animation;
}

bool PolyLineAnimation::isAnimationActive(){

	return this->active;
}

Object* PolyLineAnimation::getAnimatedObject(){

	return this->obj;
}

void PolyLineAnimation::setTotalTime(int totalTime){

	this->total_time = totalTime;
}

void PolyLineAnimation::setResetSegment(int ind){

	this->reset_to_segment = ind;
}

void PolyLineAnimation::setTotalDistance(double dist){

	this->total_distance = dist;
}

void PolyLineAnimation::setAnimatedObject(Object* ob){

	this->obj = ob;
}

void PolyLineAnimation::setRepeatAnimation(bool repeat){

	this->repeat_animation = repeat;
}

void PolyLineAnimation::ActivateAnimation(bool activ){

	this->active = activ;
}

void PolyLineAnimation::initValues(Object* obj, vector<vector<double>*>* controlPoints, double totalTime){

	setAnimatedObject(obj);
	setTotalTime(totalTime);

	for(unsigned int i = 0; i < controlPoints->size() -1; i++){

		LineAnimation* anim = new LineAnimation();

		ctrlPointsPair* p = new ctrlPointsPair(controlPoints->at(i), controlPoints->at(i+1));
		anim->setControlPoints(p);

		this->animSegments.push_back(anim);
	}
	init();
}

void PolyLineAnimation::init(){

	for(unsigned int i = 0; i < animSegments.size(); i++){
		
		animSegments.at(i)->setAnimatedObject(this->obj);
		animSegments.at(i)->initValues();
		total_distance += animSegments.at(i)->getTotalAnimationDistance();
		
	}
	for(unsigned int i = 0; i < animSegments.size(); i++){

		animSegments.at(i)->setTotalAnimationTime((animSegments.at(i)->getTotalAnimationDistance() * total_time)/total_distance);
		animSegments.at(i)->init();
	}
	this->current_animation_ind = 0;
}

int PolyLineAnimation::updateObjectPosition(){

	if(current_animation_ind >= animSegments.size()){
		return 1;
	}else{

		if(animSegments.at(current_animation_ind)->updateObjectPosition() == 1){
			current_animation_ind++;

			if(current_animation_ind >= animSegments.size()){

				if(this->repeat_animation){
					reset();
					cout << "reset done" << endl;
				}
			}else{
				this->animSegments.at(current_animation_ind)->init();
				
				rotateObject();
				
			}
			
		}	
		if(current_animation_ind == 0 && obj->getAng_XZ() == 0){//to ensure object rotates properly before the first animation stint
			rotateObject();
		}
	}

	return 0;
}

void PolyLineAnimation::rotateObject(){

	int orientation_x;
	int orientation_y;
	int orientation_z;

	if(animSegments.at(current_animation_ind)->getObj_ini_postion_z() < animSegments.at(current_animation_ind)->getObj_end_postion_z()){
		orientation_z = 1;
	}else{
		orientation_z = -1;
	}
	if(animSegments.at(current_animation_ind)->getObj_ini_postion_x() < animSegments.at(current_animation_ind)->getObj_end_postion_x()){
		orientation_x = 1;
	}else{
		orientation_x = -1;
	}
	if(animSegments.at(current_animation_ind)->getObj_ini_postion_y() < animSegments.at(current_animation_ind)->getObj_end_postion_y()){
		orientation_y = 1;
	}else{
		orientation_y = -1;
	}

	double delta_x = fabs(animSegments.at(current_animation_ind)->getTotal_delta_x());
	double delta_y = fabs(animSegments.at(current_animation_ind)->getTotal_delta_y());
	double delta_z = fabs(animSegments.at(current_animation_ind)->getTotal_delta_z());

	double ang_XZ = atan2l(delta_z, delta_x) *180/PI;
	double ang_XY;
	double ang_ZY;

	if(delta_x != 0 || delta_z != 0){//IF BOTH ARE 0, ANGLE DOES NOT CHANGE AS THERE IS ONLY MOVEMENT IN THE YY AXIS DIRECTION

		if(orientation_x < 0 && orientation_z < 0){//angle is calculated from the positive xx axis towards the object's path in the first quadrant
			ang_XZ += 180;							   //these calculations correct the angle in case the object moves to or is in other quadrants
		}else{
			if(orientation_x < 0){
				ang_XZ = ang_XZ + (180 - (2*ang_XZ));
			}
			if (orientation_z < 0){
				ang_XZ = ang_XZ * -1;
			}
		}

		if(delta_x == 0){//IF ONLY DELTA_X IS 0, THEN ANGLE IS EITHER 90 OR -90 DEPENDING ON DIRECTION OF MOVEMENT
			if(animSegments.at(current_animation_ind)->getObj_ini_postion_z() < animSegments.at(current_animation_ind)->getObj_end_postion_z()){
				ang_XZ = 90;
			}else{
				ang_XZ = -90;
			}		
		}else{
			if(delta_z == 0){// IF ONLY DELTA_Z IS 0, THEN ANGLE IS EITHER 0 OR 180 DEPENDING ON DIRECTION OF MOVEMENT
				if(animSegments.at(current_animation_ind)->getObj_ini_postion_x() < animSegments.at(current_animation_ind)->getObj_end_postion_x()){
					ang_XZ = 0;
				}else{
					ang_XZ = 180;
				}
			}
		}
		animSegments.at(current_animation_ind)->getAnimatedObject()->setRotationAngleOnYYaxis(ang_XZ);	
	}
	double delta_w;
	if(delta_y == 0){
		ang_XY = 0;
		ang_ZY = 0;
	}else{
		if(delta_x == 0 && delta_z == 0){
			ang_XY = -90;
			ang_ZY = -90;
		}else{
			if(delta_x == 0){
				delta_w = delta_z;
				ang_ZY = atan2l(delta_y, delta_w) * (180/PI);
				ang_XY = 0;
			}else{
				if(delta_z == 0){
					delta_w = delta_x;
					ang_XY = atan2l(delta_y, delta_w) * (180/PI);
					ang_ZY = 0;
				}else{
					delta_w = sqrtl(powl(delta_x,2.0) + powl(delta_z,2.0));
					ang_XY = atan2l(delta_y, delta_w) * (180/PI);
					ang_ZY = atan2l(delta_y, delta_w) * (180/PI);
				}
			}
			
		}	
	}
	if(orientation_y < 0){
		if(orientation_x < 0 && delta_z == 0){
			ang_XY =  ang_XY *-1;
		}
		ang_XY = ang_XY * -1;
		ang_ZY = ang_ZY * -1;
		
	}else{
		if(orientation_z > 0){
			ang_ZY = ang_ZY *-1;
		}else{
			if(orientation_x < 0){
				ang_XY = ang_XY * -1;
			}
		}
	}
	
	animSegments.at(current_animation_ind)->getAnimatedObject()->setRotationAngleOnXXaxis(ang_ZY);	
	animSegments.at(current_animation_ind)->getAnimatedObject()->setRotationAngleOnZZaxis(ang_XY);	
		
}

void PolyLineAnimation::animate(){

	
	if(current_animation_ind < animSegments.size()){
		animSegments.at(current_animation_ind)->animate();
	}else{
		animSegments.at(animSegments.size() -1)->animate();
	}

}

void PolyLineAnimation::reset(){

	this->current_animation_ind = this->reset_to_segment;

	obj->setPos_x(animSegments.at(current_animation_ind)->getObj_ini_postion_x());
	obj->setPos_y(animSegments.at(current_animation_ind)->getObj_ini_postion_y());
	obj->setPos_z(animSegments.at(current_animation_ind)->getObj_ini_postion_z());

	animSegments.at(current_animation_ind)->init();
	rotateObject();
}
