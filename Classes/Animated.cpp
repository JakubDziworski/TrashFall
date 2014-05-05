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
		float aTime, float horAdd, float verAdd, float timeToChill,float delayyin,float delayyout) {
	animTimee = aTime;
	tToChill = timeToChill;
	delayIn = delayyin;
	delayOut = delayyout;
	horAddition = Utils::getcorrectValue(horAdd, true);
	verAddition = Utils::getcorrectValue(verAdd, false);
	beginnPosX = Utils::getcorrectValue(bposx, true);
	endPosX = Utils::getcorrectValue(endpox, true);
	beginPosY = Utils::getcorrectValue(bposy, false);
	endPosY = Utils::getcorrectValue(eposy, false);
}

//START ANIMS
void Animated::startAnimIn(){
	this->stopAllActions();
	this->unscheduleAllSelectors();
	this->scheduleOnce(schedule_selector(Animated::animOffset),delayIn);
	this->scheduleOnce(schedule_selector(Animated::animIn),animTimee+delayIn);
}

void Animated::startAnimOut() {
	this->stopAllActions();
	this->unscheduleAllSelectors();
	this->scheduleOnce(schedule_selector(Animated::animOffset),delayOut);
	this->scheduleOnce(schedule_selector(Animated::animOut),animTimee+delayOut);
}
void Animated::startAnimBoth() {
	startAnimIn();
	this->scheduleOnce(schedule_selector(Animated::waitForAnim),animTimee+tToChill+delayIn);
}

//PRIVATE SHEDULDERS
void Animated::animIn(float dt) {
	this->runAction(CCMoveTo::create(animTimee,ccp(endPosX,endPosY)));
}

void Animated::animOut(float dt) {
	this->runAction(CCMoveTo::create(animTimee,ccp(beginnPosX,beginPosY)));
}

void Animated::waitForAnim(float dt) {
	startAnimOut();
}
Animated::~Animated() {
}

void Animated::animOffset(float dt) {
	this->runAction(CCMoveTo::create(animTimee,ccp(endPosX-horAddition,endPosY-verAddition)));
}

void Animated::AnimOffsetback(float st) {
	this->runAction(CCMoveTo::create(animTimee,ccp(beginnPosX+horAddition,beginPosY+verAddition)));
}

bool Animated::init() {
	return true;
}
