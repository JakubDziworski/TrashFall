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
using namespace cocos2d;

bool Trash::init() {

	if ( !CCSprite::init() )
		{
			return false;
		}
	this->setDisplayFrame(Utils::getRandomTrash());
	autoCheckMissesPoints=false;
	return true;
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
			trsh->schedule(schedule_selector(Trash::checkIfFallen));
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
