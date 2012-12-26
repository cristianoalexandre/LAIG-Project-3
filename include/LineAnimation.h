#ifndef LINEANIMATION_H
#define LINEANIMATION_H

#include "Object.h"
#include "Animation.h"

#include <vector>
#include <iostream>
#include <map>
#include <math.h>

using namespace std;


typedef pair<vector<double>*,vector<double>*> ctrlPointsPair;

class LineAnimation: public Animation
{
private:
	double delta_x;
	double delta_y;
	double delta_z;

	double total_delta_x; 
	double total_delta_y;
	double total_delta_z;

	double obj_ini_postion_x;
	double obj_ini_postion_y;
	double obj_ini_postion_z;

	double obj_end_postion_x;
	double obj_end_postion_y;
	double obj_end_postion_z;

	Object* animatedObject;

	double total_animation_time;
	double total_animation_distance;

	ctrlPointsPair* controlPoints;

	static unsigned int mili_secs;

public:
	LineAnimation();
	~LineAnimation();

	LineAnimation(Object* obj, ctrlPointsPair* ctrlP);
	LineAnimation(Object* obj, ctrlPointsPair* ctrlP, double total_time, double total_distance);

	void setDelta_x(double dx);
	void setDelta_y(double dy);
	void setDelta_z(double dz);

	void setObj_ini_position_x(double ini_x);
	void setObj_ini_position_y(double ini_y);
	void setObj_ini_position_z(double ini_z);

	void setTotalAnimationTime(double s);
	void setTotalAnimationDistance(double d);
	void setAnimatedObject(Object* obj);
	void setControlPoints(ctrlPointsPair* cps);

	double getDelta_x() const;
	double getDelta_y() const;
	double getDelta_z() const;

	double getTotal_delta_x() const; 
	double getTotal_delta_y() const;
	double getTotal_delta_z() const;

	double getObj_ini_postion_x() const;
	double getObj_ini_postion_y() const;
	double getObj_ini_postion_z() const;

	double getObj_end_postion_x() const;
	double getObj_end_postion_y() const;
	double getObj_end_postion_z() const;

	double getTotalAnimationTime() const;
	double getTotalAnimationDistance() const;

	Object* getAnimatedObject() const;
	ctrlPointsPair* getControlPoints() const;

	void checkDeltas(double delt_x, double delt_y, double delt_z);

	void init();
	void animate();
	void initValues();
	
	int updateObjectPosition(); 

	static unsigned int getMiliSecs();
	static void setMiliSecs(unsigned int mSecs);
};



#endif