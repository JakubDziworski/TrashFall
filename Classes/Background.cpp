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
	Utils::setSpritePositionRelativetoMyPhone(buzka,200,940);
	Utils::setSpritePositionRelativetoMyPhone(sun,200,940);
	Utils::setSpritePositionRelativetoMyPhone(chmurka[1],400,900);
	Utils::setSpritePositionRelativetoMyPhone(chmurka[2],550,1064);
	Utils::setSpritePositionRelativetoMyPhone(chmurka[0],625,880);
	orignalchmuraPos[0] = chmurka[0]->getPosition();
	orignalchmuraPos[1] = chmurka[1]->getPosition();
	orignalchmuraPos[2] = chmurka[2]->getPosition();
	this->addChild(sun);
	this->addChild(chmurka[0]);
	this->addChild(chmurka[1]);
	this->addChild(chmurka[2]);
	this->addChild(bg,-1);
	this->addChild(buzka);
	CCRepeatForever *repeat = CCRepeatForever::create(
				CCRotateBy::create(rotationDuration, 15));
	sun->runAction(repeat);
	this->schedule(schedule_selector(Background::moveChmurkiRandom),1);
	return true;
}
void Background::moveChmurkiRandom(float dt){
	currentTim += dt;
	const int i =((int)currentTim)%3;
	float posX, posY;
	CCLOG("%d triggered",i);
	if (chmurka[i]->getPositionX() >= orignalchmuraPos[i].x)
		posX = chmurka[i]->getPositionX() + Utils::getRandValue(-22, 0);
	else
		posX = chmurka[i]->getPositionX() + Utils::getRandValue(0, 22);
	if (chmurka[i]->getPositionY() >= orignalchmuraPos[i].y)
		posY = chmurka[i]->getPositionY() + Utils::getRandValue(-22, 0);
	else
		posY = chmurka[i]->getPositionY() + Utils::getRandValue(0, 22);
	chmurka[i]->runAction(CCMoveTo::create(3, ccp(posX,posY)));
}

void Background::updateMisses(int missesAmount){
	CCLOG("sunFace_%05d.png",missesAmount);
	CCString *name = CCString::createWithFormat("sunFace_%05d.png",missesAmount);
	buzka->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
}

