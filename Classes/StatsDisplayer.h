/*
 * StatsDisplayer.h
 *
 *  Created on: 30-04-2014
 *      Author: Jakub
 */

#ifndef STATSDISPLAYER_H_
#define STATSDISPLAYER_H_

#include "cocos2d.h"
#include "Animated.h"

class StatsDisplayer: public cocos2d::CCNode{
public:
	virtual bool init();
	LAYER_CREATE_FUNC(StatsDisplayer);
};
#endif /* STATSDISPLAYER_H_ */
