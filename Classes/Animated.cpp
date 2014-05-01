/*
 * Animated.cpp
 *
 *  Created on: 30-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Animated.h"
#include "Utils.h"
#include "AchievmentPopUp.h"
#include <typeinfo>
using namespace cocos2d;


//INIT
void Animated::initAnim(float bposx, float endpox, float bposy, float eposy,
		float aTime, float horAdd, float verAdd, float timeToChill) {
	animTimee = aTime;
	nowTime = 0;
	horAddition = Utils::getcorrectValue(horAdd, true);
	verAddition = Utils::getcorrectValue(verAdd, false);
	beginnPosX = Utils::getcorrectValue(bposx, true);
	endPosX = Utils::getcorrectValue(endpox, true);
	beginPosY = Utils::getcorrectValue(bposy, false);
	endPosY = Utils::getcorrectValue(eposy, false);
	tToChill = timeToChill;
}

//START ANIMS
void Animated::startAnimIn(){
	this->stopAllActions();
	this->unscheduleAllSelectors();
	nowTime =0;
	first = false;
	second = false;
	r1 = true;
	r2 = true;
	this->schedule(schedule_selector(Animated::animIn),0.1f);
}

void Animated::startAnimOut() {
	this->stopAllActions();
	this->unscheduleAllSelectors();
	nowTime = 0;
	first = false;
	second = false;
	r1 = true;
	r2 = true;
	this->schedule(schedule_selector(Animated::animOut));
}
void Animated::startAnimBoth() {
	startAnimIn();
	this->schedule(schedule_selector(Animated::waitForAnim),0.1,0,tToChill);
}

//PRIVATE SHEDULDERS
void Animated::animIn(float dt) {
	if (nowTime > animTimee) return;
		nowTime += dt;
		if(first) {this->runAction(CCMoveTo::create(animTimee/2.0,ccp(endPosX+horAddition,endPosY+verAddition)));first = false;}
		if(second) {this->runAction(CCMoveTo::create(animTimee/2.0,ccp(endPosX,endPosY)));second = false;}
		if (nowTime < animTimee / 2.0 && r1){
				CCLOG("pierwsze czasie = %.2f\n",nowTime);
				first = true;
				r1=false;
			}
			else if (nowTime >= animTimee / 2.0 && r2)
			{
				CCLOG("drugie czasie = %.2f\n",nowTime);
				second = true;
				r2=false;
			}
}

void Animated::animOut(float dt) {
	if (nowTime > animTimee) return;
			nowTime += dt;
			if(first) {this->runAction(CCMoveTo::create(animTimee/2.0,ccp(endPosX+horAddition,endPosY+verAddition)));first = false;}
			if(second) {this->runAction(CCMoveTo::create(animTimee/2.0,ccp(beginnPosX,beginPosY)));second = false;}
			if (nowTime < animTimee / 2.0 && r1){
					first = true;
					r1=false;
				}
				else if (nowTime >= animTimee / 2.0 && r2)
				{
					second = true;
					r2=false;
				}
}

void Animated::waitForAnim(float dt) {
	startAnimOut();
}
Animated::~Animated() {
}

bool Animated::init() {
	return true;
}
