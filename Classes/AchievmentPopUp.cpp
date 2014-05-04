/*
 * AchievmentPopUp.cpp
 *
 *  Created on: 26-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#define beginPosX 1.4f
#define posY 0.92f
#include "AchievmentPopUp.h"
#include "Animated.h"
#include "SpriteWithText.h"
#include "Utils.h"

using namespace cocos2d;

float AchievmentPopUp::getHeight(){
	return baseBg->getContentSize().height*this->getScale();
}
bool AchievmentPopUp::initWithParams(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color){
	baseBg = SpriteWithText::createWithSpriteFrameNamee(
			pszSpriteFrameName, inputText, color);
	achvName = CCString::create(inputText);
	const float popWidth = baseBg->getContentSize().width;
	const float popHeight = baseBg->getContentSize().height;
	this->addChild(baseBg);
	this->setScale(0.77*Utils::sreensSize().width/popWidth);
	return true;
}
AchievmentPopUp* AchievmentPopUp::createWithSpriteFrameNameee(const char *inputText,CCUserDefault *savedDat,bool whileRunning,cocos2d::ccColor3B color,const char *pszSpriteFrameName,const char *additionalImgFrameName){
	if(whileRunning){
		if(savedDat->getBoolForKey(inputText)) return NULL;
	}
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
	CCString *toDisplay = CCString::createWithFormat("ACHIEVMENT UNLOCKED!\n%s",Utils::getAchvName(achvName->getCString()).c_str());
	baseBg->setTextSize(baseBg->getContentSize().height/4);
	baseBg->setTextString(toDisplay->getCString());
	this->setPosition(Utils::getCorrectPosition(beginPosX,posY));
	this->initAnim(beginPosX,0.6f,Utils::ratioValue(this->getPositionY(),true),Utils::ratioValue(this->getPositionY(),true),0.24,0.3f,0,3);
	this->startAnimBoth();
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
	this->initAnim(beginPosX,0.5f,Utils::ratioValue(this->getPositionY(),true),Utils::ratioValue(this->getPositionY(),true),0.24,0.2f);
}

bool AchievmentPopUp::isCollected(){
	if(savedData->getBoolForKey(Utils::getAchvTag(achvName->getCString()).c_str(),false) == true) return true;
	return false;
}

void AchievmentPopUp::show() {
	this->startAnimIn();
}

void AchievmentPopUp::hide() {
	this->startAnimOut();
}

void AchievmentPopUp::showAndHide() {
	this->startAnimBoth();
}
