/*
 * AchievmentPopUp.cpp
 *
 *  Created on: 26-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "AchievmentPopUp.h"
#include "SpriteWithText.h"
#include "Utils.h"
using namespace cocos2d;

bool AchievmentPopUp::initWithParams(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color){
	SpriteWithText *popup = SpriteWithText::createWithSpriteFrameNamee(
			pszSpriteFrameName, inputText, color);
	currTime=0;
	scaleFactor=0;
	const float popWidth = popup->getContentSize().width;
	const float popHeight = popup->getContentSize().height;
	CCSprite *addItionalIMG = CCSprite::createWithSpriteFrameName(
			additionalImgFrameName);
	CCString *toDisplay = CCString::createWithFormat("ACHIEVMENT UNLOCKED\n%s",inputText);
	addItionalIMG->setScale(0.7*popHeight/addItionalIMG->getContentSize().height);
	addItionalIMG->setPositionX(popup->getPositionX()- 0.35*popup->getContentSize().width);
	popup->setachivmentStyle(toDisplay->getCString());
	this->addChild(popup);
	this->addChild(addItionalIMG,1);
	oczekiwanyfact = 0.9*Utils::sreensSize().width/popup->getContentSize().width;
	return true;
}
AchievmentPopUp* AchievmentPopUp::createWithSpriteFrameNameee(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color){
	AchievmentPopUp *achv = new AchievmentPopUp();
	achv->initWithParams(pszSpriteFrameName,additionalImgFrameName,inputText,color);
	achv->autorelease();
	return achv;
}
void AchievmentPopUp::activate(){
	this->setScale(scaleFactor);
	this->setPosition(Utils::getCorrectPosition(0.5,0.5));
	//Utils::getBackground()->addChild(this);
	this->schedule(schedule_selector(AchievmentPopUp::animate));
}
void AchievmentPopUp::animate(float dt){
	if(currTime>endTime + animTime){
			this->removeFromParentAndCleanup(true);
		}
	currTime+=dt;
		if(currTime<animTime){
			if(currTime < animTime/2.0){
				scaleFactor+=dt*2.0*(oczekiwanyfact+0.2)/animTime;
			}
			else scaleFactor-=dt*2.0*0.2/animTime;
		}
		else if(currTime >endTime){
			if(currTime < endTime + animTime/2.0){
				scaleFactor+=dt*2.0*0.2/animTime;
			}
			else scaleFactor-=dt*2.0*(oczekiwanyfact+0.1)/animTime;
		}
		else scaleFactor = oczekiwanyfact;
		this->setScale(scaleFactor);
}
