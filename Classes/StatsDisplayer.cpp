/*
 * StatsDisplayer.cpp
 *
 *  Created on: 30-04-2014
 *      Author: Jakub
 */

#include "StatsDisplayer.h"

using namespace cocos2d;
bool StatsDisplayer::init(){
	if (!CCLayer::init()) {
				return false;
			}
	CCSprite *bg = CCSprite::createWithSpriteFrameName("scoreBoardBG.png");
	Utils::scaleSprite(bg,0.9,1,true);

}
