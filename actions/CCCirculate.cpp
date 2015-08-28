#include "CCCirculate.h"

USING_NS_CC;

Circulate* Circulate::create(float duration, const cocos2d::Point& center)
{
    Circulate* action = new Circulate();
    action->initWithDuration(duration, center);
    action->autorelease();
	
    return action;
}

bool Circulate::initWithDuration(float duration, const cocos2d::Point& center)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _center = center;
		
        return true;
    }
	
    return false;
}

void Circulate::startWithTarget(cocos2d::Node* target)
{
	CCActionInterval::startWithTarget(target);
    _startPos = target->getPosition();
    _radius = _startPos.distance(_center);
}

void Circulate::update(float time)
{
	if (_target)
    {
    	// use start position
		_target->setPosition(
			Point(_center.x - _radius * cosf(M_PI * 2.0f * time),
				_center.y + _radius * sinf(M_PI * 2.0f * time)));
    }
}
