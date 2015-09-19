#include "CCHover.h"

USING_NS_CC;

Hover* Hover::create(float duration, float distance)
{
    Hover* action = new Hover();
    action->initWithDuration(duration, distance);
    action->autorelease();
	
    return action;
}

bool Hover::initWithDuration(float duration, float distance)
{
    if (ActionInterval::initWithDuration(duration))
    {
		_distance = distance;
		
        return true;
    }
	
    return false;
}

void Hover::startWithTarget(cocos2d::Node* target)
{
	ActionInterval::startWithTarget(target);
    _startPos = target->getPosition();
}

void Hover::update(float time)
{
	if (_target)
    {
		_target->setPositionY(_startPos.y + _distance * sinf(M_PI * 2.0f * time));
    }
}

void Hover::stop(void)
{
	_target->setPosition(_startPos);
	
	ActionInterval::stop();
}
