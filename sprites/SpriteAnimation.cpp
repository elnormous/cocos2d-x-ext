//
//  SpriteAnimation.cpp
//  DwarfForest
//
//  Created by Elviss Strazdins on 30.03.2013.
//  Copyright (c) 2013 Bool Games. All rights reserved.
//
#include "SpriteAnimation.h"
#include <algorithm>

USING_NS_CC;
using namespace std;

SpriteAnimation* SpriteAnimation::create(const std::string& plist, float delay)
{
    SpriteAnimation* ret = new SpriteAnimation();
    if (ret && ret->init(plist, delay))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

SpriteAnimation::SpriteAnimation():
	_action(nullptr), _repeatAction(nullptr), _animation(nullptr), _currentAction(nullptr)
{
}

SpriteAnimation::~SpriteAnimation()
{
	if (_action) _action->release();
	if (_repeatAction) _repeatAction->release();
}

bool SpriteAnimation::init(const std::string& plist, float delay)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	string animationName = plist + "_" + to_string(delay);
	_animation = AnimationCache::getInstance()->getAnimation(animationName);
	
	if (!_animation)
	{
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile(plist);
		
		ValueMap values = FileUtils::getInstance()->getValueMapFromFile(plist);
		
		vector<string> frameNames;
		for (const pair<string, Value>& frame : values["frames"].asValueMap())
		{
			frameNames.push_back(frame.first);
		}
		
		sort(frameNames.begin(), frameNames.end());
		
		Vector<SpriteFrame*> animFrames;
		for (const string& frameName : frameNames)
		{
			SpriteFrame* frame = cache->getSpriteFrameByName(frameName);
			animFrames.pushBack(frame);
		}
		
		_animation = Animation::createWithSpriteFrames(animFrames, delay);
		
		AnimationCache::getInstance()->addAnimation(_animation, animationName);
	}
	
	_action = Animate::create(_animation);
	_action->retain();
	
	_repeatAction = RepeatForever::create(_action);
	_repeatAction->retain();
	
	//set the current frame to first frame of animation
	setSpriteFrame(_animation->getFrames().at(0)->getSpriteFrame());
	
	return true;
}

void SpriteAnimation::play(bool repeat)
{
	stop();
		
	//if it is on stage
	if (repeat)
	{
		_currentAction = _repeatAction;
	}
	else
	{
		_currentAction = _action;
	}
	
	runAction(_currentAction);
}

void SpriteAnimation::stop()
{
	if (_currentAction)
	{
		if (!_currentAction->isDone())
		{
			stopAction(_currentAction);
		}
		
		_currentAction = nullptr;
	}
}

bool SpriteAnimation::isPlaying()
{
	return (_currentAction && !_currentAction->isDone());
}

void SpriteAnimation::setAliasTexParameters()
{
    const Vector<AnimationFrame*>& frames = _animation->getFrames();
    
    for (AnimationFrame* frame : frames)
    {
        frame->getSpriteFrame()->getTexture()->setAliasTexParameters();
    }
}

void SpriteAnimation::setAntiAliasTexParameters()
{
    const Vector<AnimationFrame*>& frames = _animation->getFrames();
    
    for (AnimationFrame* frame : frames)
    {
        frame->getSpriteFrame()->getTexture()->setAntiAliasTexParameters();
    }
}
