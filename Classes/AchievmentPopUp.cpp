/*
 * AchievmentPopUp.cpp
 *
 *  Created on: 26-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#define animTime 0.3f
#define endTime 4
#define endPos 0.58f
#define beginPosX 1.4f
#define posY 0.92f
#include "AchievmentPopUp.h"
#include "SpriteWithText.h"
#include "Utils.h"

using namespace cocos2d;

bool AchievmentPopUp::initWithParams(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color){
	SpriteWithText *popup = SpriteWithText::createWithSpriteFrameNamee(
			pszSpriteFrameName, inputText, color);
	currTime=0;
	first=false;second=false;third=false;forth=false;
	r1=true;r2=true;r3=true;r4=true;
	achvName = CCString::create(inputText);
	const float popWidth = popup->getContentSize().width;
	const float popHeight = popup->getContentSize().height;
	CCString *toDisplay = CCString::createWithFormat("ACHIEVMENT UNLOCKED!\n%s",Utils::getAchvName(inputText).c_str());
	popup->setachivmentStyle(toDisplay->getCString());
	this->addChild(popup);
	this->setScale(0.77*Utils::sreensSize().width/popup->getContentSize().width);
	return true;
}
AchievmentPopUp* AchievmentPopUp::createWithSpriteFrameNameee(const char *inputText,cocos2d::ccColor3B color,const char *pszSpriteFrameName,const char *additionalImgFrameName){
	AchievmentPopUp *achv = new AchievmentPopUp();
	achv->initWithParams(pszSpriteFrameName,additionalImgFrameName,inputText,color);
	achv->autorelease();
	return achv;
}
void AchievmentPopUp::activate(){
	if(CCUserDefault::sharedUserDefault()->getIntegerForKey(achvName->getCString(),0) != 0){
		this->removeFromParentAndCleanup(true);
		return;
	}
	CCUserDefault::sharedUserDefault()->setIntegerForKey(achvName->getCString(),1);
	this->setPosition(Utils::getCorrectPosition(beginPosX,posY));
	//Utils::getBackground()->addChild(this,4);
	this->schedule(schedule_selector(AchievmentPopUp::animate));
}
void AchievmentPopUp::animate(float dt){
	currTime += dt;
	if (currTime > endTime + animTime) {
		this->removeFromParentAndCleanup(true);
		return;
	}
	if(first) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(endPos-0.4f,posY)));first = false;}
	if(second) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(endPos,posY)));second = false;}
	if(third) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(endPos-0.1f,posY)));third = false;}
	if(forth) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(beginPosX,posY)));forth = false;}
	if (currTime < animTime / 2.0 && r1){
		first = true;
		r1=false;
	}
	else if (currTime >= animTime / 2.0 && currTime <= animTime && r2)
	{
		second = true;
		r2=false;
	}
	else if (currTime > endTime && currTime <= animTime / 2.0 + endTime && r3){
		third = true;
		r3=false;
	}

	else if (currTime > endTime + animTime / 2.0 && r4){
		forth = true;
		r4=false;
	}
}
