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
	float beginnPosX;
	float endPosX;
	float beginPosY;
	float endPosY;
	float animTimee;
	float horAddition;
	float verAddition;
	float tToChill;
	float delayOut;
	float delayIn;
	//bool inited;
	void animIn(float);
	void animOffset(float);
	void animOut(float);
	void waitForAnim(float);

public:
	virtual ~Animated();
	void initAnim(float bposx,float endpox,float bposy,float eposy,float aTime=0.3f,float horAdd=0.3f,float verAdd=0,float timeToChill=3,float delayyin=0,float delayyout=0);
	void startAnimIn();
	void startAnimBoth();
	void startAnimOut();
	virtual bool init();
	LAYER_CREATE_FUNC (Animated);
};

#endif /* ANIMATED_H_ */
