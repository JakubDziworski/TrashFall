/*
 * AchievmentDisplayer.cpp
 *
 *  Created on: 27-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "AchievmentDisplayer.h"
#include "AchievmentPopUp.h"
#include "Constants.h"
#include "Utils.h"
using namespace cocos2d;

bool AchievmentDisplayer::init() {
	if (!CCLayer::init()) {
		return false;
	}
	CCUserDefault *baza = CCUserDefault::sharedUserDefault();
	const float offset = CCSprite::createWithSpriteFrameName("offButton.png")->getContentSize().height+Utils::getcorrectValue(0.005,false);
	float posY = Utils::getcorrectValue(0.9);
	const float posX = Utils::getcorrectValue(0.5,true);
	AchievmentPopUp *achv[achivAmount];
	CCLOG("started creating array");
		achv[0] = AchievmentPopUp::createWithSpriteFrameNameee(ACH_50);
		CCLOG("done ACH_50");
		achv[1] = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100);
		CCLOG("done ACH_100");
		achv[2] = AchievmentPopUp::createWithSpriteFrameNameee(ACH_250);
		achv[3] = AchievmentPopUp::createWithSpriteFrameNameee(ACH_500);
		achv[4] = AchievmentPopUp::createWithSpriteFrameNameee(ACH_1000);
		achv[5] = AchievmentPopUp::createWithSpriteFrameNameee(ACH_2000);
	CCLOG("done filling array");
	for(int i=0;i<6;i++){
		achv[i]->verifyCollectedandChange();
		achv[i]->setPosition(posX,posY);
		posY-=offset;
		this->addChild(achv[i]);
		CCLOG("done%s",i);
	}
	return true;
}

