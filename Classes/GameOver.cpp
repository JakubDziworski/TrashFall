/*
 * GameOver.cpp
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

#include "GameOver.h"
#include "Utils.h"
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
	CCString *tmpCurrScoreStr = CCString::createWithFormat("SCORE:%d",curScore);
	CCString *tmpbestScoreStr = CCString::createWithFormat("BEST:%d",bestScore);
			CCString *tmpNewRecotd = CCString::createWithFormat("NEW RECORD:%d",curScore);
			scoreBoardBg = CCSprite::create("scoreBoardBG.png");
			currentScore = SpriteWithText::createWithSpriteFrameNamee("offButton.png",tmpCurrScoreStr->getCString(),ccColor3B{0,0,0});
			highScore = SpriteWithText::createWithSpriteFrameNamee("offButton.png",tmpbestScoreStr->getCString(),ccColor3B{0,0,0});
			newScoreSet = SpriteWithText::createWithSpriteFrameNamee("offButton.png",tmpNewRecotd->getCString(),ccColor3B{255,30,30});
			CCSprite *carryOn = CCSprite::createWithSpriteFrameName("onPaused.png");
				CCSprite *carryOff = CCSprite::createWithSpriteFrameName("offPaused.png");
				CCMenuItemSprite *carryOnBtn = CCMenuItemSprite::create(carryOn,carryOff,this,menu_selector(GameOver::playGame));
				Utils::scaleButton(carryOnBtn,4);
				CCMenu *menu = CCMenu::create(carryOnBtn,NULL);
			Utils::scaleSprite(scoreBoardBg,1.1,1,true);
			Utils::scaleSprite(currentScore,1.1,1,true);
			Utils::scaleSprite(highScore,1.1,1,true);
			Utils::scaleSprite(newScoreSet,1.1,1,true);


			menu->setPosition(Utils::getCorrectPosition(0.5,0.5));
			const float bgHeight = carryOnBtn->getContentSize().height*carryOnBtn->getScaleY();
			const float offset = bgHeight/4+Utils::getcorrectValue(bgHeight/16,false);
			float pos=Utils::getcorrectValue(0.5+(bgHeight/2-bgHeight/16-offset/2)/Utils::sreensSize().height,false);
			scoreBoardBg->setPosition(Utils::getCorrectPosition(0.5,0.5));
			currentScore->setPosition(ccp(Utils::getcorrectValue(0.5),pos));
			pos+=offset;
			highScore->setPosition(ccp(Utils::getcorrectValue(0.5),pos));
			pos+=offset;
			menu->setPosition(Utils::getcorrectValue(0.5),pos);
			this->addChild(scoreBoardBg,-1);
			this->addChild(highScore);
			this->addChild(currentScore);
}
