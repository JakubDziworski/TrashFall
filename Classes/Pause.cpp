/*
 * Pause.cpp
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Pause.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

bool Pause::init(){
	if (!CCLayer::init()) {
		return false;
	}
	SpriteWithText *pause = SpriteWithText::createWithSpriteFrameNamee("onButton.png","PAUSED",ccColor3B{0,0,0});
	CCSprite *resumeOn = CCSprite::createWithSpriteFrameName("onPaused.png");
	CCSprite *resumeOff = CCSprite::createWithSpriteFrameName("offPaused.png");
	CCMenuItemSprite *resumeBtn = CCMenuItemSprite::create(resumeOn,resumeOff,this,menu_selector(Pause::toggle));
	Utils::scaleButton(resumeBtn,2);
	CCMenu *menu = CCMenu::create(resumeBtn,NULL);
	pause->setPosition(ccp(384,1000));
	menu->setPosition(ccp(384,586));
	paused = false;
	this->setVisible(false);
	this->addChild(menu);
	this->addChild(pause);
	return true;
}
void Pause::toggle(){
	paused = !paused;
	Game *g = Utils::getGame();
	this->setVisible(paused);
	if(!paused){
		g->setTouchEnabled(true);
		g->resumeSchedulerAndActions();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else{
		g->setTouchEnabled(false);
		g->pauseSchedulerAndActions();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	if(g->getChildren())
	for(int i=0;i<g->getChildren()->count();i++){
		CCNode *n = (CCNode *) g->getChildren()->objectAtIndex(i);
		if(!paused) n->resumeSchedulerAndActions();
		else n->pauseSchedulerAndActions();
	}
}

