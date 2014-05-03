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
	this->setVisible(false);
	this->addChild(menuMainMenu);
	this->addChild(menuContinue);
	this->addChild(pause);
	return true;
}
void Pause::toggle(int skor,int mis){
	paused = !paused;
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	Game *g = Utils::getGame();
	this->setVisible(paused);
	if(!paused){
		g->setTouchEnabled(true);
		g->resumeSchedulerAndActions();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else{
		curscore = skor;
		missedAmount = mis;
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

void Pause::goToMainMenu(){
	if(curscore > 3){
	CCUserDefault *dane = CCUserDefault::sharedUserDefault();
	dane->setIntegerForKey(STAT_COLLECTED,dane->getIntegerForKey(STAT_COLLECTED)+curscore);
	int sessionsOver=dane->getIntegerForKey(STAT_SESOVER)+1;
	dane->setIntegerForKey(STAT_SESOVER,sessionsOver);
	if(dane->getIntegerForKey(HIGH_SCORE) < curscore)
	dane->setIntegerForKey(HIGH_SCORE,curscore);
	const float accurancy = (float)curscore/(float)(curscore+missedAmount)*100;
	dane->setFloatForKey(STAT_ACCURANCY,(dane->getFloatForKey(STAT_ACCURANCY,0)*(float)(sessionsOver-1)+accurancy)/(float)sessionsOver);
	if (sessionsOver == 100) {	//DOOOOOOO ZMIANY
				AchievmentPopUp * ach = AchievmentPopUp::createWithSpriteFrameNameee(ACH_HARDCORE.c_str(), dane);
				ach->activate();
				Utils::getBackground()->addChild(ach);
		}
	}
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
