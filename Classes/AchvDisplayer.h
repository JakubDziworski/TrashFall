/*
 * AchvDisplayer.h
 *
 *  Created on: 28-04-2014
 *      Author: Jakub
 */

#ifndef ACHVDISPLAYER_H_
#define ACHVDISPLAYER_H_
#define margin 60
#include "cocos2d.h"

class AchvDisplayer:public cocos2d::CCLayer {
	cocos2d::CCNode* plane;
	float startPos;
	float endPos;
	float posY;

public:
				void ccTouchesMoved(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent);
				void ccTouchesBegan(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent);
				void ccTouchesEnded(cocos2d::CCSet *pTouches,cocos2d::CCEvent * pEvent);
				float verifyendPoint(float);
				virtual bool init();
				LAYER_CREATE_FUNC(AchvDisplayer);
};

#endif /* ACHVDISPLAYER_H_ */
