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
#include "MainMenu.h"
#include "StatsRecords.h"
#include "AchievmentPopUp.h"
#include "AchvList.h"
#include "Constants.h"
#include "LoadingNode.h"
using namespace CocosDenshion;
using namespace cocos2d;

bool Pause::init(){
	if (!CCLayer::init()) {
		return false;
	}
	SpriteWithText *pause = SpriteWithText::createWithSpriteFrameNamee("onButton.png","PAUSED",ccColor3B{0,0,0});
	SpriteWithText *mainMenuOn = SpriteWithText::createWithSpriteFrameNamee("onButton.png","MENU",ccColor3B{0,0,0});
	SpriteWithText *mainMenuOff = SpriteWithText::createWithSpriteFrameNamee("offButton.png","MENU",ccColor3B{0,0,0});
	CCSprite *resumeOn = CCSprite::createWithSpriteFrameName("onPaused.png");
	CCSprite *resumeOff = CCSprite::createWithSpriteFrameName("offPaused.png");
	CCMenuItemSprite *resumeBtn = CCMenuItemSprite::create(resumeOn,resumeOff,this,menu_selector(Pause::toggle));
	CCMenuItemSprite *mainMenuBtn = CCMenuItemSprite::create(mainMenuOn,mainMenuOff,this,menu_selector(Pause::goToMainMenu));
	Utils::scaleButton(resumeBtn,2);
	Utils::scaleButton(mainMenuBtn,1.7);
	Utils::scaleSprite(pause,1.1,1,true);
	CCMenu *menuContinue = CCMenu::create(resumeBtn,NULL);
	CCMenu *menuMainMenu = CCMenu::create(mainMenuBtn,NULL);
	pause->setPosition(Utils::getCorrectPosition(0.5,0.8));
	menuContinue->setPosition(Utils::getCorrectPosition(0.5,0.5));
	menuMainMenu->setPosition(Utils::getCorrectPosition(0.5,0.3));
	paused = false;
	anim = Animated::create();
	anim->addChild(menuMainMenu);
	anim->addChild(menuContinue);
	anim->addChild(pause);
	anim->setPosition(Utils::getCorrectPosition(0,1));
	anim->initAnim(0,0,1,0,0.2f,0,0.2f,0,0,0);
	this->addChild(anim);
	return true;
}
void Pause::toggle(cocos2d::CCObject*){
	paused = !paused;
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	Game *g = Utils::getGame();
	if(!paused){
		anim->unscheduleAllSelectors();
		anim->stopAllActions();
		anim->startAnimOut();
		g->setTouchEnabled(true);
		g->resumeSchedulerAndActions();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else{
		anim->unscheduleAllSelectors();
		anim->stopAllActions();
		anim->startAnimIn();
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

void Pause::goToMainMenu(cocos2d::CCObject*){
	anim->unscheduleAllSelectors();
	anim->stopAllActions();
	anim->startAnimOut();
	Utils::getGame()->saveBeforLeaving();
	LoadingNode *node = LoadingNode::create();
	this->addChild(node);
	this->scheduleOnce(schedule_selector(Pause::lateGoToMenu),0.45f);
}
void Pause::lateGoToMenu(float dt){
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
