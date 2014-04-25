/*
 * GameOver.cpp
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

#include "GameOver.h"
#include "Utils.h"
#include "Constants.h"
using namespace cocos2d;
bool GameOver::init(){
	if (!CCLayer::init()) {
			return false;
		}
		return true;
}
void GameOver::trigger(int scorr,int bestt){
	curScore = scorr;
	bestScore = bestt;
	CCLabelTTF *GAMEOVER = CCLabelTTF::create("GAME OVER",FONT_MAIN,Utils::getScaledFontSize(125));
	GAMEOVER->setColor(ccColor3B {255,15,15});
	CCString *tmpCurrScoreStr = CCString::createWithFormat("SCORE:%d",curScore);
	CCString *tmpbestScoreStr = CCString::createWithFormat("BEST:%d",bestScore);
	CCString *tmpNewRecotd = CCString::createWithFormat("NEW RECORD:%d",curScore);
	scoreBoardBg = CCSprite::create("scoreBoardBG.png");
	CCLabelTTF *currscor= CCLabelTTF::create(tmpCurrScoreStr->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
	CCLabelTTF *bestScoree = CCLabelTTF::create(tmpbestScoreStr->getCString(),FONT_MAIN,Utils::getScaledFontSize(75));
				//menu
				CCSprite *carryOn = CCSprite::createWithSpriteFrameName("onPaused.png");
				CCSprite *carryOff = CCSprite::createWithSpriteFrameName("offPaused.png");
				CCMenuItemSprite *carryOnBtn = CCMenuItemSprite::create(carryOn,carryOff,this,menu_selector(GameOver::playGame));
				Utils::scaleButton(carryOnBtn,4);
				CCMenu *menu = CCMenu::create(carryOnBtn,NULL);
			Utils::scaleSprite(scoreBoardBg,1.1,1,true);
			scoreBoardBg->setPosition(Utils::getCorrectPosition(0.5,0.5));
			GAMEOVER->setPosition(Utils::getCorrectPosition(0.5,0.65));
			currscor->setPosition(Utils::getCorrectPosition(0.5,0.55));
			bestScoree->setPosition(Utils::getCorrectPosition(0.5,0.5));
			menu->setPosition(Utils::getCorrectPosition(0.5,0.35));
			this->addChild(scoreBoardBg,-1);
			this->addChild(GAMEOVER);
			this->addChild(currscor);
			this->addChild(bestScoree);
			this->addChild(menu);
}

void GameOver::playGame(){
		CCDirector::sharedDirector()->replaceScene(Game::scene());
}
