/*
 * Animated.h
 *
 *  Created on: 30-04-2014
 *      Author: Jakub
 */

#ifndef ANIMATED_H_
#define ANIMATED_H_
#include "cocos2d.h"
class Animated:public cocos2d::CCNode{
protected:
	bool first,second,r1,r2;
	float beginnPosX;
	float endPosX;
	float beginPosY;
	float endPosY;
	float animTimee;
	float horAddition;
	float verAddition;
	float tToChill;
	float nowTime;
	//bool inited;
	void animIn(float);
	void animOut(float);
	void waitForAnim(float);

public:
	virtual ~Animated();
	Animated(float bposx,float endpox,float bposy,float eposy,float aTime=0.3f,float horAdd=0.2f,float verAdd=0,float timeToChill=3);
	void startAnimIn();
	void startAnimBoth();
	void startAnimOut();
	virtual void zamelduj();
};

#endif /* ANIMATED_H_ */
