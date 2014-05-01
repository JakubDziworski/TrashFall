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

class StatsDisplayer: public Animated{
private:
	Animated *animatorContainer;
	cocos2d::CCLabelTTF scrLabel;
public:
	static StatsDisplayer* createe();
	virtual bool initialize();
	void show();
	void hide();
};
#endif /* STATSDISPLAYER_H_ */
