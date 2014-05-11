/*
 * GameOver.cpp
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

#include "GameOver.h"
#include "Utils.h"
#include "Constants.h"
#include "MainMenu.h"
#include "ITouchDisablable.h"
#include "StatsRecords.h"
#include "AchievmentPopUp.h"
#include "AchvList.h"
#include "SimpleAudioEngine.h"
#include "LoadingNode.h"
#include "JniURL.h"
#include "JniAdManager.h"

using namespace CocosDenshion;
using namespace cocos2d;
bool GameOver::init(){
	if (!CCLayer::init()) {
			return false;
		}
		visiblu=false;
		return true;
}
void GameOver::trigger(int scorr,int missedAmount){
	visiblu = true;
	CCUserDefault *usrDefault = CCUserDefault::sharedUserDefault();
	curScore = scorr;
	const float accurancy = (float)scorr/(float)(scorr+missedAmount)*100;
	bestScore = usrDefault->getIntegerForKey(HIGH_SCORE,0);
	int totalCollected = usrDefault->getIntegerForKey(STAT_COLLECTED,0)+scorr;
	int sessionsOver = usrDefault->getFloatForKey(STAT_SESOVER,0)+1;
	float totalAccurancy = (usrDefault->getFloatForKey(STAT_ACCURANCY,0)*(float)(sessionsOver-1)+accurancy)/(float)sessionsOver;
	usrDefault->setIntegerForKey(STAT_COLLECTED,totalCollected);
	usrDefault->setIntegerForKey(STAT_SESOVER,sessionsOver);
	usrDefault->setFloatForKey(STAT_ACCURANCY,totalAccurancy);
	if (sessionsOver == 100) {
			AchievmentPopUp * ach = AchievmentPopUp::createWithSpriteFrameNameee(ACH_HARDCORE.c_str(), usrDefault,true);
			if(ach){
			ach->activate();
			Utils::getBackground()->addChild(ach);
			}
	}
	anim = Animated::create();
	anim->initAnim(0,0,1,0.05f,0.2f,0,0.2f);
	//
	Game *g = Utils::getGame();
				g->pauseSchedulerAndActions();
				g->setTouchEnabled(false);
				g->setKeypadEnabled(false);
				this->setKeypadEnabled(true);
	//
	CCLabelBMFont *GAMEOVER = CCLabelBMFont::create("GAME OVER","font.fnt");
	Utils::scaleSprite(GAMEOVER,10,1,false);
	GAMEOVER->setColor(ccColor3B { 255, 15, 15 });
	GAMEOVER->setPosition(Utils::getCorrectPosition(0.5,0.68));
	//
	scoreBoardBg = CCSprite::createWithSpriteFrameName("scoreBoardBG.png");
	Utils::scaleSprite(scoreBoardBg,1.1,1,true);
	scoreBoardBg->setPosition(Utils::getCorrectPosition(0.5, 0.5));
	//
	SpriteWithText *tip = SpriteWithText::createWithSpriteFrameNamee("onButton.png", Utils::losujTIP().c_str(), ccColor3B{ 1, 1, 1 });
	tip->setTextSize(0.25f);
	tip->setTextMaxInLine(0.93f*this->getContentSize().width);
    Utils::scaleSprite(tip, 1.1F,1,true);
	tip->setPosition(Utils::getCorrectPosition(0.5f, 0.13f));
	//
	SpriteWithText *rateMEon = SpriteWithText::createWithSpriteFrameNamee("offButton.png", "REVIEW", ccColor3B{ 1, 1, 1 });
	SpriteWithText *rateMEoff = SpriteWithText::createWithSpriteFrameNamee("onButton.png", "REVIEW", ccColor3B{ 1, 1, 1 });
	CCMenuItemSprite *rateBtn = CCMenuItemSprite::create(rateMEon,rateMEoff,this,menu_selector(GameOver::rateME));
	Utils::scaleSprite(rateBtn, 2.5f, 1, true);
	CCSprite *carryOn = CCSprite::createWithSpriteFrameName("goBackOn.png");
					CCSprite *carryOff = CCSprite::createWithSpriteFrameName("goBackOff.png");
					CCMenuItemSprite *carryOnBtn = CCMenuItemSprite::create(carryOn,carryOff,this,menu_selector(GameOver::playGame));
					Utils::scaleButton(carryOnBtn,4);
					menu = CCMenu::create(carryOnBtn,rateBtn,NULL);
					menu->setPosition(Utils::getCorrectPosition(0.5,0.37));
					menu->setTouchEnabled(false);
					menu->alignItemsVertically();
	CCString *accStr = CCString::createWithFormat("ACCURANCY:%.1f\%%",accurancy);
	CCLabelBMFont *accurancyLab= CCLabelBMFont::create(accStr->getCString(),"font.fnt");
	anim->addChild(scoreBoardBg,-1);
	anim->addChild(GAMEOVER,1);
	anim->addChild(menu,1);
	anim->addChild(tip, 1);
	Utils::scaleSprite(accurancyLab,15,1,false);
	accurancyLab->setPosition(Utils::getCorrectPosition(0.5,0.52));
	anim->addChild(accurancyLab,1);
	if(scorr > bestScore){
		CCString *tmpNewRecotd = CCString::createWithFormat("NEW RECORD:%d",curScore);
		CCLabelBMFont *newRecord= CCLabelBMFont::create(tmpNewRecotd->getCString(),"font.fnt");
		Utils::scaleSprite(newRecord,15,1,false);
		newRecord->setColor(ccColor3B{255,20,15});
		newRecord->setPosition(Utils::getCorrectPosition(0.5,0.57));
		anim->addChild(newRecord);
		usrDefault->setIntegerForKey(HIGH_SCORE,scorr);
	}
	else{
	CCString *tmpCurrScoreStr = CCString::createWithFormat("SCORE:%d",curScore);
	CCString *tmpbestScoreStr = CCString::createWithFormat("BEST:%d",bestScore);
	CCLabelBMFont *currscor= CCLabelBMFont::create(tmpCurrScoreStr->getCString(),"font.fnt");
	CCLabelBMFont *bestScoree = CCLabelBMFont::create(tmpbestScoreStr->getCString(),"font.fnt");
	Utils::scaleSprite(currscor,15,1,false);
	Utils::scaleSprite(bestScoree,15,1,false);
	currscor->setPosition(Utils::getCorrectPosition(0.5,0.62));
	bestScoree->setPosition(Utils::getCorrectPosition(0.5,0.57));
	anim->addChild(currscor,1);
	anim->addChild(bestScoree,1);
	}
	anim->startAnimIn();
	anim->setPosition(Utils::getCorrectPosition(0,1));
	this->addChild(anim);
	this->schedule(schedule_selector(GameOver::enableTouchAfterWait),0.1f,0,1.4f);
	showAd();
}

void GameOver::lateMainMenu(float float1) {
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}

void GameOver::enableTouchAfterWait(float dt) {
	menu->setTouchEnabled(true);
}
void GameOver::playGame(cocos2d::CCObject* pObject){
	anim->unscheduleAllSelectors();
	anim->stopAllActions();
	anim->startAnimOut();
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	Utils::getBackground()->wywalChmuriIslonce();
	this->scheduleOnce(schedule_selector(GameOver::latePlayGame),timeToHideBgItemz);
}
void GameOver::latePlayGame(float){
	CCDirector::sharedDirector()->replaceScene(Game::scene());
}
void GameOver::keyBackClicked() {
	anim->unscheduleAllSelectors();
	anim->stopAllActions();
	anim->startAnimOut();
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	Utils::getBackground()->wywalChmuriIslonce();
	this->scheduleOnce(schedule_selector(GameOver::lateMainMenu), timeToHideBgItemz);
}

bool GameOver::isVisiblee() {
	return visiblu;
}

void GameOver::rateME(cocos2d::CCObject*) {
	openURLJNI("http://www.google.pl");
}
