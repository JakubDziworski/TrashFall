/*
 * Pause.cpp
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */
 
#include "Pause.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "StatsRecords.h"
#include "AchievmentPopUp.h"
#include "AchvList.h"
#include "Constants.h"
#include "LoadingNode.h"
#include "JniAdManager.h"
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
	CCSprite *goBackOn = CCSprite::createWithSpriteFrameName("goBackOn.png");
	CCSprite *goBackOff = CCSprite::createWithSpriteFrameName("goBackOff.png");
	CCMenuItemSprite *restartBtn = CCMenuItemSprite::create(goBackOn, goBackOff, this, menu_selector(Pause::restartGame));
	CCMenuItemSprite *resumeBtn = CCMenuItemSprite::create(resumeOn,resumeOff,this,menu_selector(Pause::toggle));
	CCMenuItemSprite *mainMenuBtn = CCMenuItemSprite::create(mainMenuOn,mainMenuOff,this,menu_selector(Pause::goToMainMenu));
	Utils::scaleButton(restartBtn,2.1f);
	Utils::scaleButton(resumeBtn,2.1);
	Utils::scaleButton(mainMenuBtn,1.7);
	Utils::scaleSprite(pause,1.1,1,true);
	CCMenu *menuContinue = CCMenu::create(restartBtn,resumeBtn,NULL);
	menuContinue->alignItemsHorizontally();
	CCMenu *menuMainMenu = CCMenu::create(mainMenuBtn,NULL);
	pause->setPosition(Utils::getCorrectPosition(0.5,0.8));
	menuContinue->setPosition(Utils::getCorrectPosition(0.5,0.5));
	menuMainMenu->setPosition(Utils::getCorrectPosition(0.5,0.26));
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
	if(paused==false){
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
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	anim->unscheduleAllSelectors();
	anim->stopAllActions();
	anim->startAnimOut();
	Utils::getGame()->saveBeforLeaving();
	Utils::getBackground()->wywalChmuriIslonce();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->scheduleOnce(schedule_selector(Pause::lateGoToMenu), timeToHideBgItemz);
}
void Pause::lateGoToMenu(float dt){
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
void Pause::restartGame(cocos2d::CCObject*){
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	anim->unscheduleAllSelectors();
	anim->stopAllActions();
	anim->startAnimOut();
	Utils::getGame()->saveBeforLeaving();
	Utils::getBackground()->wywalChmuriIslonce();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->scheduleOnce(schedule_selector(Pause::lateRestartGame), timeToHideBgItemz);
}
void Pause::lateRestartGame(float){

	CCDirector::sharedDirector()->replaceScene(Game::scene());
}
