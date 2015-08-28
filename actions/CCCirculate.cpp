#include "CCHover.h"

USING_NS_CC;

Circulate* Circulate::create(float duration, const cocos2d::Point& center)
{
    Hover* action = new Hover();
    action->initWithDuration(duration, radius, center);
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
    _radius = _startPos.distance(target);
}

void Circulate::update(float time)
{
	if (_target)
    {
    	// use start position
		_target->setPosition(
			Point(center.x - _radius * cosf(M_PI * 2.0f * time),
				center.y + _radius * sinf(M_PI * 2.0f * time)));
    }
}
