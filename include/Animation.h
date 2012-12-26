#ifndef ANIMATION_H
#define ANIMATION_H


class Animation
{
private:


public:
	Animation();
	~Animation();


	virtual void init(){}
	virtual int updateObjectPosition(){return 0;}
	virtual void animate(){}
};

#endif