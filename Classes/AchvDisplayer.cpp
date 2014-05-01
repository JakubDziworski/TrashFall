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
#include "ITouchDisablable.h"
#include <vector>
#include <string.h>
#include "MainMenu.h"
#include "Constants.h"

using namespace cocos2d;

bool AchvDisplayer::init(){
	if (!CCLayer::init()) {
			return false;
		}
	baza = CCUserDefault::sharedUserDefault();
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
	achievmentsNames.push_back(ACH_250_SINGLE);
	achievmentsNames.push_back(ACH_150_SINGLE);
	achievmentsNames.push_back(ACH_250_SINGLE);

	plane = CCNode::create();
	info = Animated::create();
			const float offset=AchievmentPopUp::createWithSpriteFrameNameee(achievmentsNames[0].c_str(),baza)->getHeight()+Utils::getcorrectValue(0.01,false);
			posYY = Utils::getcorrectValue(0.9);
			const float posX = Utils::getcorrectValue(0.5, true);
			int collected=0;
			posYY-=offset;
			for(int i=0;i<achievmentsNames.size();i++){
				AchievmentPopUp *record;
				CCLOG("w funkcji achvdisplayer ini %s",achievmentsNames[i].c_str());
				record = AchievmentPopUp::createWithSpriteFrameNameee(achievmentsNames[i].c_str(),baza);
				record->setPosition(ccp(posX,posYY));
				record->activateForListing();
				if(record->isCollected()) collected++;
				plane->addChild(record);
				posYY-=offset;
				CCLOG("ADDED %s",achievmentsNames[i].c_str());
			}
			CCString *collectedinfoSpriteText = CCString::createWithFormat("%d/%d",collected,achievmentsNames.size());
			SpriteWithText *infoSprite=SpriteWithText::createWithSpriteFrameNamee("offButton.png",collectedinfoSpriteText->getCString(),ccColor3B{1,1,1});
			CCLOG("inf pos = %.2f\n",info->getPositionY());
			info->addChild(infoSprite);
			info->setScale(0.77*Utils::sreensSize().width/infoSprite->getContentSize().width);
			float infposY = Utils::sreensSize().height + infoSprite->getContentSize().height*info->getScale()/2.0;
			info->setPosition(ccp(posX,infposY));
	this->addChild(info,2);
	this->addChild(plane);
	children = plane->getChildren();
    info->initAnim(0.5,0.5,infposY/Utils::sreensSize().height,0.92f,0.2,0,0.05f,0,0.7f,0.6f);
	return true;
}
void AchvDisplayer::ccTouchesMoved(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent){
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	endposss = location.y;
	const float absodleglosc = abs(startPos - endposss);
	const float odleglosc = endposss - startPos;
	if(absodleglosc > 5){
		startPos = endposss;
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
		endposss = location.y;
		const float absodleglosc = abs(startPos - endposss);
			const float odleglosc = endposss - startPos;
			if(absodleglosc > 5){
				plane->setPositionY(verifyendPoint(plane->getPositionY()+odleglosc));
			}
}
float AchvDisplayer::verifyendPoint(float input){
	if(input < -margin) return -margin;
	if(input > -posYY) return -posYY;
	return input;
}
void AchvDisplayer::start(){
		info->startAnimIn();
		ITouchDisablable* parent = (ITouchDisablable*) this->getParent();
		parent->disableTouch();
		this->setTouchEnabled(true);
		this->setKeypadEnabled(true);
		this->setVisible(true);
		j=0;
		this->schedule(schedule_selector(AchvDisplayer::jedenPoDrugimIN),0.03f,children->count()-1,0.2f);
}
void AchvDisplayer::end(){
	info->startAnimOut();
	ITouchDisablable* parent = (ITouchDisablable*) this->getParent();
	parent->enableTouch();
	this->setTouchEnabled(false);
	this->setKeypadEnabled(false);
	j=0;
	this->schedule(schedule_selector(AchvDisplayer::jedenPoDrugim),0.03f,children->count()-1,0.2f);
}
void AchvDisplayer::keyBackClicked(){
	end();
}
void AchvDisplayer::jedenPoDrugim(float dt){
	CCLOG("info pos = %.2f\n",info->getPositionY());
	CCLOG("info pos = %.2f\n",((CCNode*)info->getChildren()->objectAtIndex(0))->getPositionY());
	AchievmentPopUp* popup;
	popup = (AchievmentPopUp*)children->objectAtIndex(j);
	popup->hide();
	j++;
}
void AchvDisplayer::jedenPoDrugimIN(float dt){
	AchievmentPopUp* popup;
	popup = (AchievmentPopUp*)children->objectAtIndex(j);
	popup->show();
	j++;
}
