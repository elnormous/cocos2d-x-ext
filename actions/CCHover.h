#pragma once

#include <CCActionInterval.h>

class Hover: public cocos2d::ActionInterval
{
public:

    static Hover* create(float duration, float distance);
	
	bool initWithDuration(float duration, float distance);
	
	virtual void startWithTarget(cocos2d::Node* target) override;
	virtual void update(float time) override;
	virtual void stop(void) override;
	
private:
	float _distance;
	cocos2d::Point _startPos;
};
