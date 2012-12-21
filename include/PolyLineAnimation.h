#ifndef POLYLINEANIMATION_H
#define POLYLINEANIMATION_H

#define PI 3.14159265

#include "LineAnimation.h"
#include "Animation.h"
#include <math.h>


class PolyLineAnimation: public Animation{

private:
	
	int total_time;
	int current_animation_ind;
	int reset_to_segment;

	bool repeat_animation;
	bool active;
	double total_distance;

	Object* obj;
	vector<LineAnimation*> animSegments;

public:

	PolyLineAnimation();
	~PolyLineAnimation();

	PolyLineAnimation(Object* obj, double tot_time, bool repeat, int reset_ind);

	int getTotalTime();
	int getResetToSegment();
	double getTotalDistance();
	bool getRepeatAnimation();
	bool isAnimationActive();
	Object* getAnimatedObject();
	

	
	void setTotalTime(int totalTime);
	void setResetSegment(int ind);
	void setTotalDistance(double dist);
	void setAnimatedObject(Object* obj);
	void setRepeatAnimation(bool repeat);
	void ActivateAnimation(bool activ);
	void initValues(Object* obj, vector<vector<double>*>* controlPoints, double totalTime);

	void init();
	void reset();
	int updateObjectPosition();
	void rotateObject();
	void animate();

};


#endif