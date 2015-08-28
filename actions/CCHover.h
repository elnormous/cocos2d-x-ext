#pragma once

#include <CCActionInterval.h>

class Hover: public cocos2d::ActionInterval
{
public:

    static Hover* create(float duration, float distance);
	
	bool initWithDuration(float duration, float distance);
	
	virtual void startWithTarget(cocos2d::Node* target);
	virtual void update(float time);
	virtual void stop(void);
	
private:
	float _distance;
	cocos2d::Point _startPos;
};
