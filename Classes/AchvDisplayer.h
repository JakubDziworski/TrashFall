/*
 * AchvDisplayer.h
 *
 *  Created on: 28-04-2014
 *      Author: Jakub
 */

#ifndef ACHVDISPLAYER_H_
#define ACHVDISPLAYER_H_
#define margin 10
#include <vector>
#include "SpriteWithText.h"
#include "cocos2d.h"

class AchvDisplayer:public cocos2d::CCLayer {
	cocos2d::CCNode* plane;
	float startPos;
	float endposss;
	float posYY;
	cocos2d::CCUserDefault *baza;
	std::vector<std::string> achievmentsNames;
	cocos2d::CCArray* children;
	SpriteWithText *info;
	int j;
public:
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent * pEvent);
	float verifyendPoint(float);
	void start();
	void end();
	virtual void keyBackClicked();
	void jedenPoDrugim(float dt);
	void jedenPoDrugimIN(float dt);
	virtual bool init();LAYER_CREATE_FUNC(AchvDisplayer);
};

#endif /* ACHVDISPLAYER_H_ */
