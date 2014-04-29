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
			const float offset =CCSprite::createWithSpriteFrameName("offButton.png")->getContentSize().height;
			posYY = Utils::getcorrectValue(0.9);
			const float posX = Utils::getcorrectValue(0.5, true);
			for(int i=0;i<achievmentsNames.size();i++){
				AchievmentPopUp *record;
				CCLOG("w funkcji achvdisplayer ini %s",achievmentsNames[i].c_str());
				record = AchievmentPopUp::createWithSpriteFrameNameee(achievmentsNames[i].c_str(),baza);
				record->setPosition(ccp(posX,posYY));
				record->activateForListing();
				plane->addChild(record);
				posYY-=offset;
				CCLOG("ADDED %s",achievmentsNames[i].c_str());
			}
	this->addChild(plane);
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
		ITouchDisablable* parent = (ITouchDisablable*) this->getParent();
		parent->disableTouch();
		this->setTouchEnabled(true);
		this->setKeypadEnabled(true);
		this->setVisible(true);
}
void AchvDisplayer::end(){
	ITouchDisablable* parent = (ITouchDisablable*) this->getParent();
	parent->enableTouch();
	this->setTouchEnabled(false);
	this->setKeypadEnabled(false);
	this->setVisible(false);
}
void AchvDisplayer::keyBackClicked(){
	end();
}
