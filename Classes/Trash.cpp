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
using namespace cocos2d;

bool Trash::init() {

	if ( !CCSprite::init() )
		{
			return false;
		}
	//default values, later overriden if create used

	this->setDisplayFrame(Utils::getRandomTrash());
	return true;
}

Trash* Trash::create(float speedd,float sizee){
			Trash *trsh = Trash::create();
			CCSize scrSize = Utils::sreensSize();
			const int angle = Utils::getRandValue(-360,360);
			Utils::scaleSprite(trsh,spriteRatio,sizee);
			trsh->speed = speedd;
			trsh->size = sizee;
			trsh->setPosition(ccp(Utils::getRandomXPos(),Utils::getBeginHeight(trsh)));
			CCRepeatForever *repeat = CCRepeatForever::create(
			CCRotateBy::create(rotationDuration, angle));
			trsh->runAction(repeat);
			CCLOG("spped =%.2f\n,endhpos = %.2f\n,sstarthpos = %.2f\n",speedd,Utils::getEndHeight(trsh),Utils::getBeginHeight(trsh));
			trsh->runAction(CCMoveTo::create(speedd, ccp(trsh->getPositionX(),Utils::getEndHeight(trsh))));
			return trsh;
}
