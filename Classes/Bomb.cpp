/*
 * Bomb.cpp
 *
 *  Created on: 06-05-2014
 *      Author: Jakub
 */

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
	g->caught=true;
	this->removeFromParentAndCleanup(true);
}

void Bomb::checkIfFallen(float dt) {
	if(this->getPositionY() <= endposY+1) {
				this->removeFromParentAndCleanup(true);
			}
}

void Bomb::WYBUCHSPRITE() {
//		wybuch = new CCParticleSystemQuad();
//		wybuch = CCParticleFire::create();
//		wybuch->setEmitterMode(kCCParticleModeRadius);
//		wybuch->setPosition(ccp(this->getContentSize().width * this->getAnchorPoint().x,
//				this->getContentSize().height * this->getAnchorPoint().y));
//		wybuch->setTexture(CCTextureCache::sharedTextureCache()->addImage("particl.png"));
//		this->addChild(wybuch);
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
