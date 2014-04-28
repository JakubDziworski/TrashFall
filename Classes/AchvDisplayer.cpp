/*
 * AchvDisplayer.cpp
 *
 *  Created on: 28-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "AchvDisplayer.h"
#include "SpriteWithText.h"
#include "Utils.h"
#include "AchvList.h"
#include <vector>
#include <string.h>
#include "Constants.h"
using namespace cocos2d;

bool AchvDisplayer::init(){
	if (!CCLayer::init()) {
			return false;
		}
	CCUserDefault *baza = CCUserDefault::sharedUserDefault();
	const float offset =CCSprite::createWithSpriteFrameName("offButton.png")->getContentSize().height+Utils::getcorrectValue(0.005, false);
	float posY = Utils::getcorrectValue(0.9);
	const float posX = Utils::getcorrectValue(0.5, true);

	CCArray *achievmenty = CCArray::create();
	std::vector<std::string> achievmentsNames;
	//calkowite
	const std::string ACH_250_SINGLE = "PERFECTION,COLLECT 250 TRASHES IN SINGLE RUN";

	achievmentsNames.push_back(ACH_50);
	achievmentsNames.push_back(ACH_100);
	achievmentsNames.push_back(ACH_250);
	achievmentsNames.push_back(ACH_500);
	achievmentsNames.push_back(ACH_1000);
	achievmentsNames.push_back(ACH_2000);
	//pod rzad
	achievmentsNames.push_back(ACH_10_SINGLE);
	achievmentsNames.push_back(ACH_20_SINGLE);
	achievmentsNames.push_back(ACH_50_SINGLE);
	achievmentsNames.push_back(ACH_100_SINGLE);
	achievmentsNames.push_back(NOWY);

	//
	for(int i=0;i<achievmentsNames.size();i++){
		SpriteWithText *record;
		if(baza->getIntegerForKey(achievmentsNames[i].c_str(),0) != 0){
			CCString *str = CCString::create(Utils::getAchvName(achievmentsNames[i]));
			CCString *toput = CCString::createWithFormat("ACHIEVMENT %s UNLOCKED",str->getCString());
			record = SpriteWithText::createWithSpriteFrameNamee("offButton.png",toput->getCString(),ccColor3B{0,0,0});
		}
		else{
			CCString *str = CCString::create(Utils::getAchvName(achievmentsNames[i]));
			CCString *toput = CCString::createWithFormat("ACHIEVMENT '%s' LOCKED",str->getCString());
			record = SpriteWithText::createWithSpriteFrameNamee("onButton.png",toput->getCString(),ccColor3B{0,0,0});
		}
		record->setPosition(ccp(posX,posY));
		this->addChild(record);
		posY-=offset;
		achievmenty->addObject(record);
		CCLOG("ADDED %s",achievmentsNames[i].c_str());
	}
	return true;
}


