/*
 * Trash.cpp
 *
 *  Created on: 23-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Trash.h"
#include "Constants.h"
#include "Utils.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "HUD.h"
using namespace CocosDenshion;
using namespace cocos2d;

bool Trash::init() {
	if ( !CCSprite::init() )
		{
			return false;
		}
	this->setDisplayFrame(Utils::getRandomTrash());
	autoCheckMissesPoints=false;
	schedule(schedule_selector(Trash::checkIfFallen),0.1f);
	return true;
}

void Trash::dotkniety() {
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick2.mp3");
	WYBUCHSPRITE();
	Game *g = Utils::getGame();
	HUD *h = Utils::getHUD();
	g->notMissed++;
	g->score++;
	g->missedInARow=0;
	g->caught=true;
	h->addToScore(1,g->notMissed);
	this->removeFromParentAndCleanup(true);
}
void Trash::WYBUCHSPRITE() {
	CCSprite *animation = CCSprite::createWithSpriteFrameName("collected_00000.png");
	const float scalerate = 1.4f*this->getContentSize().height*this->getScale() / animation->getContentSize().height;
	CCArray *frames = CCArray::create();
	for (int i = 0; i <= 15; i++)
	{
		CCString *frame;
		if (i<10) frame = CCString::createWithFormat("collected_0000%d.png", i);
		else frame = CCString::createWithFormat("collected_000%d.png", i);
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

Trash* Trash::create(float speedd,float sizee,float rotTime){
			Trash *trsh = Trash::create();
			CCSize scrSize = Utils::sreensSize();
			const int angle = Utils::getRandValue(-360,360);
			Utils::scaleSprite(trsh,spriteRatio,sizee);
			trsh->speed = speedd;
			trsh->size = sizee;
			trsh->endposY = Utils::getEndHeight(trsh);
			trsh->setPosition(ccp(Utils::getRandomXPos(),Utils::getBeginHeight(trsh)));
			CCMoveTo *act = CCMoveTo::create(trsh->speed, ccp(trsh->getPositionX(),Utils::getEndHeight(trsh)));
			act->setTag(1);
			CCRepeatForever *repeat = CCRepeatForever::create(
			CCRotateBy::create(rotTime, angle));
			trsh->runAction(repeat);
			trsh->runAction(act);
			return trsh;
}
void Trash::checkIfFallen(float dt){
	if(this->getPositionY() <= endposY+1){
	if(autoCheckMissesPoints) Utils::getGame()->missed();
	this->removeFromParentAndCleanup(true);
	}
}

void Trash::setAutoCheckMissesPoints(bool input){
	autoCheckMissesPoints = input;
}
