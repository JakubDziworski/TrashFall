/*
 * AchvDisplayer.cpp
 *
 *  Created on: 28-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "AchvDisplayer.h"
#include "AchievmentPopUp.h"
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
	plane = CCNode::create();
	CCUserDefault *baza = CCUserDefault::sharedUserDefault();
	const float offset =CCSprite::createWithSpriteFrameName("offButton.png")->getContentSize().height+Utils::getcorrectValue(0.005, false);
	posY = Utils::getcorrectValue(0.9);
	const float posX = Utils::getcorrectValue(0.5, true);

	CCArray *achievmenty = CCArray::create();
	std::vector<std::string> achievmentsNames;
	//calkowite

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
	//
	for(int i=0;i<achievmentsNames.size();i++){
		AchievmentPopUp *record;
		if(baza->getIntegerForKey(achievmentsNames[i].c_str(),0) != 0){
			CCString *str = CCString::create(Utils::getAchvName(achievmentsNames[i]));
			CCString *toput = CCString::createWithFormat("ACHIEVMENT %s UNLOCKED",str->getCString());
			record = AchievmentPopUp::createWithSpriteFrameNameee(toput->getCString(),baza);
		}
		else{
			CCString *str = CCString::create(Utils::getAchvName(achievmentsNames[i]));
			CCString *toput = CCString::createWithFormat("ACHIEVMENT '%s' LOCKED",str->getCString());
			record = AchievmentPopUp::createWithSpriteFrameNameee(toput->getCString(),baza);
		}
		record->setPosition(ccp(posX,posY));
		record->activateForListing();
		plane->addChild(record);
		posY-=offset;
		achievmenty->addObject(record);
		CCLOG("ADDED %s",achievmentsNames[i].c_str());
	}
	this->setTouchEnabled(true);
	this->addChild(plane);
	return true;
}
void AchvDisplayer::ccTouchesMoved(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent){
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	endPos = location.y;
	const float absodleglosc = abs(startPos - endPos);
	const float odleglosc = endPos - startPos;
	if(absodleglosc > 5){
		startPos = endPos;
		plane->setPositionY(verifyendPoint(plane->getPositionY()+odleglosc));
	}
}
void AchvDisplayer::ccTouchesBegan(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent){
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	startPos = location.y;
}
void AchvDisplayer::ccTouchesEnded(cocos2d::CCSet *pTouches,cocos2d::CCEvent * pEvent){
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
		CCPoint location = touch->locationInView();
		location = CCDirector::sharedDirector()->convertToGL(location);

		endPos = location.y;
		const float absodleglosc = abs(startPos - endPos);
			const float odleglosc = endPos - startPos;
			if(absodleglosc > 5){
				plane->setPositionY(verifyendPoint(plane->getPositionY()+odleglosc));
			}

}
float AchvDisplayer::verifyendPoint(float input){
	if(input < -margin) return -margin;
	if(input > -posY) return -posY;
	return input;
}

