/*
 * Utils.h
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <sstream>
#include "cocos2d.h"
class Utils {
public:
	static const int trashAmount = 5;
	cocos2d::CCLayer* layer;

	static int getRandValue(int min,int max);
	static float getRandValueF(float a,float b);
	static cocos2d::CCSpriteFrame* getRandomTrash();
	static float getRandomXPos();
	static cocos2d::CCSize sreensSize();
	static void scaleToFitScreen(cocos2d::CCSprite* input);
	static void prepareBackgroundImg(cocos2d::CCSprite* input);
	static float getEndHeight(cocos2d::CCSprite *input);
	static float getBeginHeight(cocos2d::CCSprite *input);
	static float cleanView(cocos2d::CCLayer*);
	static bool isVisible(cocos2d::CCSprite*);
};

#endif /* UTILS_H_ */
