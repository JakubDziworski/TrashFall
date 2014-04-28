/*
 * AchievmentDisplayer.h
 *
 *  Created on: 27-04-2014
 *      Author: Jakub
 */

#ifndef ACHIEVMENTDISPLAYER_H_
#define ACHIEVMENTDISPLAYER_H_

#include "cocos2d.h"
using namespace cocos2d;

class AchievmentDisplayer: public cocos2d::CCLayer {
public:
		virtual bool init();
		LAYER_CREATE_FUNC(AchievmentDisplayer);
};

#endif /* ACHIEVMENTDISPLAYER_H_ */
