/*
 * Background.cpp
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Background.h"
#include "Utils.h"
#include "Constants.h"
#include "SpriteWithText.h"
using namespace cocos2d;
bool Background::init(){
	if (!CCLayer::init()) {
			return false;
		}
	maxmovementChmurki = Utils::getcorrectValue(0.025,true);
	currentTim=0;
	timeToWait=0;
	CCLOG("start background init");
	CCSprite *bg = CCSprite::create("Background.png");
	Utils::prepareBackgroundImg(bg);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("backgroundImages.plist");
	sun = CCSprite::createWithSpriteFrameName("Sun.png");
	chmurka[0] = CCSprite::createWithSpriteFrameName("chmurka1.png");
	chmurka[1] = CCSprite::createWithSpriteFrameName("chmurka2.png");
	chmurka[2] = CCSprite::createWithSpriteFrameName("chmurka3.png");
	buzka = CCSprite::createWithSpriteFrameName("sunFace_00001.png");
	Utils::scaleSprite(chmurka[0],3.76f,1,true);
	Utils::scaleSprite(chmurka[1],4.9f,1,true);
	Utils::scaleSprite(chmurka[2],2.35f,1,true);
	Utils::scaleSprite(sun,3.4,1,false);
	Utils::scaleSprite(buzka,3.4,1,false);
	orignalchmuraPos[1] = Utils::getCorrectPosition(0.53,0.75);
	orignalchmuraPos[2] = Utils::getCorrectPosition(0.74,0.89);
	orignalchmuraPos[0] = Utils::getCorrectPosition(0.80,0.71);
	this->addChild(sun);
	this->addChild(chmurka[0]);
	this->addChild(chmurka[1]);
	this->addChild(chmurka[2]);
	this->addChild(bg,-1);
	this->addChild(buzka);
	CCRepeatForever *repeat = CCRepeatForever::create(
				CCRotateBy::create(rotationDuration, 15));
	sun->runAction(repeat);
	beginAnimTime=1;
	beginAnimation();
	this->schedule(schedule_selector(Background::moveChmurkiRandom),1);
	return true;
}
void Background::moveChmurkiRandom(float dt){
	currentTim += dt;
	if(currentTim<beginAnimTime) return;
	const int i =((int)currentTim)%3;
	float posX, posY;
	CCLOG("%d triggered",i);
	if (chmurka[i]->getPositionX() >= orignalchmuraPos[i].x)
		posX = chmurka[i]->getPositionX() + Utils::getRandValue(-maxmovementChmurki, 0);
	else
		posX = chmurka[i]->getPositionX() + Utils::getRandValue(0, maxmovementChmurki);
	if (chmurka[i]->getPositionY() >= orignalchmuraPos[i].y)
		posY = chmurka[i]->getPositionY() + Utils::getRandValue(-maxmovementChmurki, 0);
	else
		posY = chmurka[i]->getPositionY() + Utils::getRandValue(0, maxmovementChmurki);
	chmurka[i]->runAction(CCMoveTo::create(3, ccp(posX,posY)));
}

void Background::updateMisses(int missesAmount){
	CCLOG("sunFace_%05d.png",missesAmount);
	CCString *name = CCString::createWithFormat("sunFace_%05d.png",missesAmount);
	buzka->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
}
void Background::beginAnimation(){
	const int sunSpeed = 1;
	const int chmSpeed[3] = {1.5,1.5,1.5};
	beginAnimTime=1.5;
	for(int i=0;i<3;i++) chmurka[i]->setPosition(orignalchmuraPos[i]);
	buzka->setPosition(Utils::getCorrectPosition(-0.4,0.8));
	sun->setPosition(Utils::getCorrectPosition(-0.4,0.76));
	chmurka[2]->setPosition(Utils::getCorrectPosition(1.4,0.9));
	chmurka[0]->setPosition(Utils::getCorrectPosition(1.6,0.70));
	chmurka[1]->setPosition(Utils::getCorrectPosition(1.5,0.73));
	for(int i=0;i<3;i++){
		chmurka[i]->runAction(CCMoveTo::create(chmSpeed[i],orignalchmuraPos[i]));
	}
	sun->runAction(CCMoveTo::create(sunSpeed,Utils::getCorrectPosition(0.26,0.793)));
	buzka->runAction(CCMoveTo::create(sunSpeed,Utils::getCorrectPosition(0.26,0.793)));
}

