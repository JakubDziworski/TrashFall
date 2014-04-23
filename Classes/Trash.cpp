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
	float size=2;
	float speed=4;
	const CCSize scrSize = Utils::sreensSize();
	posx = Utils::getRandomXPos();
	this->setDisplayFrame(Utils::getRandomTrash());
	this->setPosition(ccp(posx,1.1*scrSize.height));
	return true;
}

Trash* Trash::create(float speed,float size){
			Trash *trsh = Trash::create();
			CCSize scrSize = Utils::sreensSize();
			trsh->speed = speed;
			trsh->size = size;
			trsh->setScale(size);
			CCRepeatForever *repeat = CCRepeatForever::create(
				CCRotateBy::create(1, 360));
			trsh->runAction(repeat);
			trsh->runAction(CCMoveTo::create(speed, ccp(trsh->posx,-0.1*scrSize.height)));
			return trsh;
}
