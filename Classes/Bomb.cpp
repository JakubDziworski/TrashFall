/*
 * Bomb.cpp
 *
 *  Created on: 06-05-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Bomb.h"
#include "Utils.h"

using namespace cocos2d;


void Bomb::dotkniety() {
	this->stopAllActions();
	this->unscheduleAllSelectors();
	WYBUCHSPRITE();
	//SimpleAudioEngine::sharedEngine()->playEffect("buttonClick2.mp3");
	Game *g = Utils::getGame();
	g->caughtExplosive();
	//this->removeFromParentAndCleanup(true);
}

void Bomb::checkIfFallen(float dt) {
	if(this->getPositionY() <= endposY+1) {
				this->removeFromParentAndCleanup(true);
			}
}

void Bomb::WYBUCHSPRITE() {
		CCSprite *animation = CCSprite::create();
		CCArray *frames = CCArray::create();
		for(int i = 1; i <= 63; i++)
		{
			CCString *frame = CCString::createWithFormat("explosion_%d.png", i);
			CCSpriteFrame *spr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame->getCString());
			frames->addObject(spr);
		}
		CCLOG("tutaj1");
		const CCPoint currpos = this->getPosition();
		CCLOG("posy = %.2f",this->getPosition().y);
		CCLOG("posx = %.2f",this->getPositionX());
		CCLOG("tutaj2");
		animation->setPosition(currpos);
		CCLOG("tutaj3");
		this->getParent()->addChild(animation);
		CCLOG("tutaj4");
		this->setVisible(false);
		CCLOG("tutaj5");
		//animation->setScale(5);
		animation->runAction(CCAnimate::create(CCAnimation::create(frames,.15)));
		CCLOG("tutaj6");
}

Bomb* Bomb::createe(float speedd, float sizee, float rotTime) {
	Bomb *bmb = Bomb::create();
	CCSize scrSize = Utils::sreensSize();
	const int angle = Utils::getRandValue(-360, 360);
	Utils::scaleSprite(bmb, spriteRatio, sizee);
	bmb->speed = speedd;
	bmb->size = sizee;
	bmb->endposY = Utils::getEndHeight(bmb);
	bmb->setPosition(ccp(Utils::getRandomXPos(),Utils::getBeginHeight(bmb)));
	CCMoveTo *act = CCMoveTo::create(bmb->speed,
			ccp(bmb->getPositionX(),Utils::getEndHeight(bmb)));
	act->setTag(1);
	CCRepeatForever *repeat = CCRepeatForever::create(
			CCRotateBy::create(rotTime, angle));
	bmb->runAction(repeat);
	bmb->runAction(act);
	bmb->schedule(schedule_selector(Bomb::checkIfFallen));
	return bmb;
}

bool Bomb::init() {
	if ( !CCSprite::init() )
			{
				return false;
			}
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomba.png"));
		autoCheckMissesPoints=false;
		return true;
}
