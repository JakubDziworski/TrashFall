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
			const float offset=AchievmentPopUp::createWithSpriteFrameNameee(achievmentsNames[0].c_str(),baza)->getHeight()+Utils::getcorrectValue(0.01,false);
			CCLOG("%f",offset);
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
			CCString *collectedInfoText = CCString::createWithFormat("%d/%d",collected,achievmentsNames.size());
			info=SpriteWithText::createWithSpriteFrameNamee("offButton.png",collectedInfoText->getCString(),ccColor3B{1,1,1});
			Utils::scaleSprite(info,1.1f,1,true);
			float infposY = Utils::sreensSize().height + info->getContentSize().height*info->getScale()/2.0;
			info->setPosition(ccp(posX,infposY));
	this->addChild(info,2);
	this->addChild(plane);
	children = plane->getChildren();
	this->setVisible(false);
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
		info->runAction(CCMoveTo::create(0.2f,ccp(0.5f*Utils::sreensSize().width,Utils::sreensSize().height-info->getContentSize().height*info->getScale()/2.0f-Utils::getcorrectValue(0.01f))));
		ITouchDisablable* parent = (ITouchDisablable*) this->getParent();
		parent->disableTouch();
		this->setTouchEnabled(true);
		this->setKeypadEnabled(true);
		this->setVisible(true);
		j=0;
		this->schedule(schedule_selector(AchvDisplayer::jedenPoDrugimIN),0.03f,children->count()-1,0.2f);
}
void AchvDisplayer::end(){
	info->runAction(CCMoveTo::create(0.2f,ccp(0.5f*Utils::sreensSize().width,Utils::sreensSize().height+info->getContentSize().height*info->getScale()/2.0f)));
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
