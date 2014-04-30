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

float AchievmentPopUp::getHeight(){
	return baseBg->getContentSize().height*this->getScale();
}
bool AchievmentPopUp::initWithParams(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color){
	CCLOG("w AchievmentPopUp::initWithParams %s",inputText);
	baseBg = SpriteWithText::createWithSpriteFrameNamee(
			pszSpriteFrameName, inputText, color);
	achvName = CCString::create(inputText);
	const float popWidth = baseBg->getContentSize().width;
	const float popHeight = baseBg->getContentSize().height;
	this->addChild(baseBg);
	this->setScale(0.77*Utils::sreensSize().width/baseBg->getContentSize().width);
	return true;
}
AchievmentPopUp* AchievmentPopUp::createWithSpriteFrameNameee(const char *inputText,CCUserDefault *savedDat,cocos2d::ccColor3B color,const char *pszSpriteFrameName,const char *additionalImgFrameName){
	CCLOG("w AchievmentPopUp::createWithSpriteFrameNameee %s",inputText);
	AchievmentPopUp *achv = new AchievmentPopUp();
	achv->savedData = savedDat;
	achv->initWithParams(pszSpriteFrameName,additionalImgFrameName,inputText,color);
	achv->autorelease();
	return achv;
}
void AchievmentPopUp::activate(){
	if(isCollected()){
		this->removeFromParentAndCleanup(true);
		return;
	}
	savedData->setBoolForKey(Utils::getAchvTag(achvName->getCString()).c_str(),true);
	CCLOG("ZAPISYWANIE");
	currTime=0;
	first=false;second=false;third=false;forth=false;
	r1=true;r2=true;r3=true;r4=true;
	CCString *toDisplay = CCString::createWithFormat("ACHIEVMENT UNLOCKED!\n%s",Utils::getAchvName(achvName->getCString()).c_str());
	CCLOG("error1");
	baseBg->setTextSize(baseBg->getContentSize().height/4);
	baseBg->setTextString(toDisplay->getCString());
	CCLOG("error1");
	this->setPosition(Utils::getCorrectPosition(beginPosX,posY));
	CCLOG("error1");
	this->schedule(schedule_selector(AchievmentPopUp::animate));
	CCLOG("error1");
}
void AchievmentPopUp::activateForListing(){
	CCString *toDisplay;
	this->setPositionX(Utils::getcorrectValue(beginPosX));
	if(isCollected()){
		baseBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("onCollected.png"));
		toDisplay= CCString::createWithFormat("'%s' UNLOCKED\n(%s)",Utils::getAchvName(achvName->getCString()).c_str(),Utils::getAchvDescr(achvName->getCString()).c_str());
	}
	else {
		baseBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("offCollected.png"));
		toDisplay= CCString::createWithFormat("%s \n TO UNLOCK THIS ACHIEVMENT",Utils::getAchvDescr(achvName->getCString()).c_str());
	}
	baseBg->setTextString(toDisplay->getCString());
	baseBg->setTextSize(baseBg->getContentSize().height/4);
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
void AchievmentPopUp::startAnimIn(){
	currTime=0;
	mystaticYpos=this->getPositionY()/Utils::sreensSize().height;
	mystaticEndpos=0.5;
	first=false;second=false;third=false;forth=false;
	r1=true;r2=true;r3=false;r4=false;
	this->setPosition(Utils::getCorrectPosition(beginPosX,mystaticYpos));
	this->schedule(schedule_selector(AchievmentPopUp::animateIn));
}
void AchievmentPopUp::startAnimOut(){
	currTime=0;
	first=false;second=false;third=false;forth=false;
	r1=false;r2=false;r3=true;r4=true;
	this->schedule(schedule_selector(AchievmentPopUp::animateOut));
}
void AchievmentPopUp::animateIn(float dt){
	if (currTime > animTime) return;
	CCLOG("time = %f x=%f,y=%f",currTime,this->getPositionX(),this->getPositionY());
	currTime += dt;
	if(first) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(mystaticEndpos-0.4f,mystaticYpos)));first = false;}
	if(second) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(mystaticEndpos,mystaticYpos)));second = false;}
	if (currTime < animTime / 2.0 && r1){
			first = true;
			r1=false;
		}
		else if (currTime >= animTime / 2.0 && r2)
		{
			second = true;
			r2=false;
		}
}
void AchievmentPopUp::animateOut(float dt){
	if (currTime > animTime){
		this->unscheduleAllSelectors();
		return;
	}
	CCLOG("time = %f x=%f,y=%f",currTime,this->getPositionX(),this->getPositionY());
	currTime += dt;
	if(third) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(mystaticEndpos-0.2f,mystaticYpos)));third = false;}
	if(forth) {this->runAction(CCMoveTo::create(animTime/2.0,Utils::getCorrectPosition(beginPosX,mystaticYpos)));forth = false;}
	if (currTime < animTime / 2.0 && r3){
			third = true;
			r3=false;
		}

	else if (currTime > animTime /2.0 && r4){
			forth = true;
			r4=false;
		}
}

bool AchievmentPopUp::isCollected(){
	if(savedData->getBoolForKey(Utils::getAchvTag(achvName->getCString()).c_str(),false) == true) return true;
	return false;
}
