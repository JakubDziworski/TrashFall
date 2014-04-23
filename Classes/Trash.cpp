/*
 * Trash.cpp
 *
 *  Created on: 23-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Trash.h"
#include "Utils.h"
using namespace cocos2d;

bool Trash::init() {

	if ( !CCSprite::init() )
		{
			return false;
		}
	size=1;	//default values
	speed=4;
	const CCSize scrSize = Utils::sreensSize();
	this->setDisplayFrame(Utils::getRandomTrash());
	return true;
}

Trash* Trash::create(float speed,float size){
			Trash *trsh = Trash::create();
			CCSize scrSize = Utils::sreensSize();
			trsh->speed = speed;
			trsh->size = size;
			trsh->setScale(size);
			trsh->setPosition(ccp(Utils::getRandomXPos(),Utils::getBeginHeight(trsh)));
			CCRepeatForever *repeat = CCRepeatForever::create(
				CCRotateBy::create(1, 360));
			trsh->runAction(repeat);
			trsh->runAction(CCMoveTo::create(speed, ccp(trsh->getPositionX(),Utils::getEndHeight(trsh))));
			return trsh;
}
