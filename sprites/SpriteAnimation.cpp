//
//  SpriteAnimation.cpp
//  DwarfForest
//
//  Created by Elviss Strazdins on 30.03.2013.
//  Copyright (c) 2013 Bool Games. All rights reserved.
//
#include "SpriteAnimation.h"

USING_NS_CC;
using namespace std;

class FrameParser : public SAXDelegator
{
public:
    SpriteFrameCache* _cache;
    vector<string> _keys;
    Vector<SpriteFrame*> _frames;
    
    bool _key = false;
    
public:
    FrameParser()
    {
        _cache = SpriteFrameCache::getInstance();
    }
    
    ~FrameParser()
    {
    }
    
    Vector<SpriteFrame*> getFrames(const std::string& fileName)
    {
        SAXParser parser;
        
        parser.init("UTF-8");
        parser.setDelegator(this);
        
        parser.parse(fileName);
        
        return _frames;
    }
    
    void startElement(void *ctx, const char *name, const char **atts)
    {
        CC_UNUSED_PARAM(ctx);
        CC_UNUSED_PARAM(atts);
        const std::string sName(name);
        
        _key = (sName == "key");
    }
    
    void endElement(void *ctx, const char *name)
    {
        CC_UNUSED_PARAM(ctx);
        const std::string sName((char*)name);
        
        if (sName != "key" && !_keys.empty())
        {
            _keys.pop_back();
        }
        
        _key = false;
    }
    
    void textHandler(void *ctx, const char *ch, int len)
    {
        CC_UNUSED_PARAM(ctx);
        
        const std::string text = std::string((char*)ch,len);
        
        if (_key)
        {
            if (_keys.size() == 1 && _keys.front() == "frames")
            {
                SpriteFrame* frame = _cache->getSpriteFrameByName(text);
                _frames.pushBack(frame);
            }
            
            _keys.push_back(text);
        }
    }
};

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
	
	_animation = AnimationCache::getInstance()->getAnimation(plist);
	
	if (!_animation)
	{
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile(plist);
		
		FrameParser parser;
        Vector<SpriteFrame*> animFrames = parser.getFrames(plist);
		
		_animation = Animation::createWithSpriteFrames(animFrames, delay);
		
		AnimationCache::getInstance()->addAnimation(_animation, plist);
	}
	
    if (_animation->getFrames().empty())
    {
        return false;
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
