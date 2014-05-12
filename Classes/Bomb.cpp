/*
 * Bomb.cpp
 *
 *  Created on: 06-05-2014
 *      Author: Jakub
 */
 
#include "Bomb.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;


void Bomb::dotkniety() {
	this->stopAllActions();
	this->unscheduleAllSelectors();
	WYBUCHSPRITE();
	Game *g = Utils::getGame();
	g->caughtExplosive();
	this->removeFromParentAndCleanup(true);
}

void Bomb::checkIfFallen(float dt) {
	if(this->getPositionY() <= endposY+1) {
				this->removeFromParentAndCleanup(true);
			}
}

void Bomb::WYBUCHSPRITE() {
		SimpleAudioEngine::sharedEngine()->playEffect("bomb2.mp3");
		CCSprite *animation = CCSprite::createWithSpriteFrameName("explosion_3.png");
		const float scalerate = 2*this->getContentSize().height*this->getScale() / animation->getContentSize().height;
		CCArray *frames = CCArray::create();
		for(int i = 3; i <= 59; i=i+2)
		{
			CCString *frame = CCString::createWithFormat("explosion_%d.png", i);
			CCSpriteFrame *spr = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame->getCString());
			frames->addObject(spr);
		}
		const CCPoint currpos = this->getPosition();
		animation->setPosition(currpos);
		animation->setScale(scalerate);
		((Game*)this->getParent())->animacjeLayer->addChild(animation);
		CCAnimate *animuj = CCAnimate::create(CCAnimation::create(frames, .04));
		CCCallFuncN * zniszcz = CCCallFuncN::create(animation, callfuncN_selector(Game::removeAnim));
		animation->runAction(CCSequence::create(animuj, zniszcz, NULL));
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
