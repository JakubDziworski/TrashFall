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
using namespace cocos2d;
bool GameOver::init(){
	if (!CCLayer::init()) {
			return false;
		}
		return true;
}
void GameOver::trigger(int scorr,int bestt){
	curScore = scorr;
	bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(HIGH_SCORE,0);
	//
	Game *g = Utils::getGame();
				g->pauseSchedulerAndActions();
				g->setKeypadEnabled(false);
				this->setKeypadEnabled(true);
				g->setTouchEnabled(false);
	//
	CCLabelTTF *GAMEOVER = CCLabelTTF::create("GAME OVER", FONT_MAIN,Utils::getScaledFontSize(125));
	GAMEOVER->setColor(ccColor3B { 255, 15, 15 });
	GAMEOVER->setPosition(Utils::getCorrectPosition(0.5,0.65));
	//
	scoreBoardBg = CCSprite::create("scoreBoardBG.png");
	Utils::scaleSprite(scoreBoardBg,1.1,1,true);
	scoreBoardBg->setPosition(Utils::getCorrectPosition(0.5,0.5));
	//
	CCSprite *carryOn = CCSprite::createWithSpriteFrameName("onPaused.png");
					CCSprite *carryOff = CCSprite::createWithSpriteFrameName("offPaused.png");
					CCMenuItemSprite *carryOnBtn = CCMenuItemSprite::create(carryOn,carryOff,this,menu_selector(GameOver::playGame));
					Utils::scaleButton(carryOnBtn,4);
					CCMenu *menu = CCMenu::create(carryOnBtn,NULL);
					menu->setPosition(Utils::getCorrectPosition(0.5,0.37));
	this->addChild(scoreBoardBg,-1);
	this->addChild(GAMEOVER);
	this->addChild(menu);
	if(scorr > bestScore){
		CCString *tmpNewRecotd = CCString::createWithFormat("NEW RECORD:%d",curScore);
		CCLabelTTF *newRecord= CCLabelTTF::create(tmpNewRecotd->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
		newRecord->setColor(ccColor3B{255,15,15});
		newRecord->setPosition(Utils::getCorrectPosition(0.5,0.5));
		this->addChild(newRecord);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(HIGH_SCORE,scorr);
		return;
	}
	CCString *tmpCurrScoreStr = CCString::createWithFormat("SCORE:%d",curScore);
	CCString *tmpbestScoreStr = CCString::createWithFormat("BEST:%d",bestScore);
	CCLabelTTF *currscor= CCLabelTTF::create(tmpCurrScoreStr->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
	CCLabelTTF *bestScoree = CCLabelTTF::create(tmpbestScoreStr->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
	currscor->setPosition(Utils::getCorrectPosition(0.5,0.55));
	bestScoree->setPosition(Utils::getCorrectPosition(0.5,0.5));
	this->addChild(currscor);
	this->addChild(bestScoree);
}

void GameOver::playGame(){
		CCDirector::sharedDirector()->replaceScene(Game::scene());
}
void GameOver::keyBackClicked() {
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}
