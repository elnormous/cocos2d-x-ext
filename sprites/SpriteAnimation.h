//
//  SpriteAnimation.h
//  DwarfForest
//
//  Created by Elviss Strazdins on 30.03.2013.
//  Copyright (c) 2013 Bool Games. All rights reserved.
//

#pragma once


class SpriteAnimation: public cocos2d::Sprite
{
public:
	static SpriteAnimation* create(const std::string& plist, float delay = 0.02f);
	
	SpriteAnimation();
    virtual ~SpriteAnimation();
	
	bool init(const std::string& plist, float delay = 0.02f);
	
	virtual void play(bool repeat = true);
	virtual void stop();
	virtual bool isPlaying();
    
    float getDelay() const;
    void setDelay(float delay);
    
    void setAliasTexParameters();
    void setAntiAliasTexParameters();
	
private:
	CC_DISALLOW_COPY_AND_ASSIGN(SpriteAnimation);
	
	cocos2d::Animate* _action;
	cocos2d::RepeatForever* _repeatAction;
	
	cocos2d::Animation* _animation;
	
	cocos2d::Action* _currentAction;
};
