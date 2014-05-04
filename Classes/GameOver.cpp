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

using namespace CocosDenshion;
using namespace cocos2d;
bool GameOver::init(){
	if (!CCLayer::init()) {
			return false;
		}
		return true;
}
void GameOver::trigger(int scorr,int missedAmount){
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
			ach->activate();
			Utils::getBackground()->addChild(ach);
	}
	anim = Animated::create();
	anim->initAnim(0,0,1,0,0.2f,0,0.1f);
	//
	Game *g = Utils::getGame();
				g->pauseSchedulerAndActions();
				g->setKeypadEnabled(false);
				g->setTouchEnabled(false);
	//
	CCLabelTTF *GAMEOVER = CCLabelTTF::create("GAME OVER", FONT_MAIN,Utils::getScaledFontSize(125));
	GAMEOVER->setColor(ccColor3B { 255, 15, 15 });
	GAMEOVER->setPosition(Utils::getCorrectPosition(0.5,0.68));
	//
	scoreBoardBg = CCSprite::create("scoreBoardBG.png");
	Utils::scaleSprite(scoreBoardBg,1.1,1,true);
	scoreBoardBg->setPosition(Utils::getCorrectPosition(0.5,0.5));
	//
	CCSprite *carryOn = CCSprite::createWithSpriteFrameName("onPaused.png");
					CCSprite *carryOff = CCSprite::createWithSpriteFrameName("offPaused.png");
					CCMenuItemSprite *carryOnBtn = CCMenuItemSprite::create(carryOn,carryOff,this,menu_selector(GameOver::playGame));
					Utils::scaleButton(carryOnBtn,4);
					menu = CCMenu::create(carryOnBtn,NULL);
					menu->setPosition(Utils::getCorrectPosition(0.5,0.37));
					menu->setTouchEnabled(false);
	CCString *accStr = CCString::createWithFormat("ACCURANCY:%.1f\%%",accurancy);
	CCLabelTTF *accurancyLab= CCLabelTTF::create(accStr->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
	anim->addChild(scoreBoardBg,-1);
	anim->addChild(GAMEOVER,1);
	anim->addChild(menu,1);
	accurancyLab->setPosition(Utils::getCorrectPosition(0.5,0.52));
	anim->addChild(accurancyLab,1);
	if(scorr > bestScore){
		CCString *tmpNewRecotd = CCString::createWithFormat("NEW RECORD:%d",curScore);
		CCLabelTTF *newRecord= CCLabelTTF::create(tmpNewRecotd->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
		newRecord->setColor(ccColor3B{255,15,15});
		newRecord->setPosition(Utils::getCorrectPosition(0.5,0.57));
		anim->addChild(newRecord);
		usrDefault->setIntegerForKey(HIGH_SCORE,scorr);
	}
	else{
	CCString *tmpCurrScoreStr = CCString::createWithFormat("SCORE:%d",curScore);
	CCString *tmpbestScoreStr = CCString::createWithFormat("BEST:%d",bestScore);
	CCLabelTTF *currscor= CCLabelTTF::create(tmpCurrScoreStr->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
	CCLabelTTF *bestScoree = CCLabelTTF::create(tmpbestScoreStr->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
	currscor->setPosition(Utils::getCorrectPosition(0.5,0.62));
	bestScoree->setPosition(Utils::getCorrectPosition(0.5,0.57));
	anim->addChild(currscor,1);
	anim->addChild(bestScoree,1);
	}
	anim->startAnimIn();
	anim->setPosition(Utils::getCorrectPosition(0,1));
	this->addChild(anim);
	this->schedule(schedule_selector(GameOver::enableTouchAfterWait),0.1f,0,1.4f);
}
void GameOver::enableTouchAfterWait(float dt){
	menu->setTouchEnabled(true);
	this->setKeypadEnabled(true);
}
void GameOver::playGame(){
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
		CCDirector::sharedDirector()->replaceScene(Game::scene());
}
void GameOver::keyBackClicked() {
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
