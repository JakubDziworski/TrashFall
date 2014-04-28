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
	CCLOG("CREATING main sprite %S",inputText);
	mainSprite = SpriteWithText::createWithSpriteFrameNamee(pszSpriteFrameName, inputText, color);
	CCLOG("FINISHED CREATING MAIN SPRITE %S",inputText);
	currTime=0;
	CCLOG("FINISHED CREATING MAIN SPRITE %S",inputText);
	scaleFactor=0;
	CCLOG("FINISHED CREATING MAIN SPRITE %S",inputText);
	achvName = CCString::create(inputText);
	CCLOG("ACHVNAME = CCSTRING;CREATE");
	const float popWidth = mainSprite->getContentSize().width;
	const float popHeight = mainSprite->getContentSize().height;
	CCSprite *addItionalIMG = CCSprite::createWithSpriteFrameName(
			additionalImgFrameName);
	CCString *toDisplay = CCString::createWithFormat("ACHIEVMENT UNLOCKED\n%s",inputText);
	addItionalIMG->setScale(0.7*popHeight/addItionalIMG->getContentSize().height);
	addItionalIMG->setPositionX(mainSprite->getPositionX()- 0.35*mainSprite->getContentSize().width);
	mainSprite->setachivmentStyle(toDisplay->getCString());
	this->addChild(mainSprite);
	this->addChild(addItionalIMG,1);
	oczekiwanyfact = 0.9*Utils::sreensSize().width/mainSprite->getContentSize().width;
	return true;
}
AchievmentPopUp* AchievmentPopUp::createWithSpriteFrameNameee(const char *inputText,cocos2d::ccColor3B color,const char *pszSpriteFrameName,const char *additionalImgFrameName){
	CCLOG("CREATING %s",inputText);
	AchievmentPopUp *achv = new AchievmentPopUp();
	CCLOG("memory %s",inputText);
	achv->initWithParams(pszSpriteFrameName,additionalImgFrameName,inputText,color);
	achv->autorelease();
	return achv;
}
void AchievmentPopUp::activate(){
//	if(CCUserDefault::sharedUserDefault()->getIntegerForKey(achvName->getCString(),0) != 0){
//		this->removeFromParentAndCleanup(true);
//		return;
//	}
	CCUserDefault::sharedUserDefault()->setIntegerForKey(achvName->getCString(),1);
	this->setScale(scaleFactor);
	this->setPosition(Utils::getCorrectPosition(0.5,0.8));
	//Utils::getBackground()->addChild(this,4);
	this->schedule(schedule_selector(AchievmentPopUp::animate));
}
void AchievmentPopUp::animate(float dt){
	if(currTime>endTime + animTime){
			this->removeFromParentAndCleanup(true);
			return;
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

void AchievmentPopUp::verifyCollectedandChange(){
	if(CCUserDefault::sharedUserDefault()->getIntegerForKey(achvName->getCString()) == 0){
		//CCString *toDisplay = CCString::createWithFormat("ACHIEVMENT '%s' UNLOCKED",Utils::getAchvName(achvName->getCString()));
		//mainSprite->label->setString(toDisplay->getCString());
	}
	else{
		//CCString *toDisplay = CCString::createWithFormat("%s TO UNLOCK",Utils::getAchvDescr(achvName->getCString()));
		mainSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("greyButton.png"));
		//mainSprite->label->setString(toDisplay->getCString());
	}
}
