/*
 * AchvDisplayer.h
 *
 *  Created on: 28-04-2014
 *      Author: Jakub
 */

#ifndef ACHVDISPLAYER_H_
#define ACHVDISPLAYER_H_
#include "cocos2d.h"

class AchvDisplayer:public cocos2d::CCLayer {
public:
				virtual bool init();
				LAYER_CREATE_FUNC(AchvDisplayer);
};

#endif /* ACHVDISPLAYER_H_ */
