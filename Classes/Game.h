/*
 * Game.h
 *
 *  Created on: 23-04-2014
 *      Author: Jakub
 */

#ifndef GAME_H_
#define GAME_H_

#include "cocos2d.h"
#include "SpriteWithText.h"

class Game: public cocos2d::CCLayer {
	float mSpeed;
	float atOnce;
	float spread;
	float currentTimee;
	float resettedTime;
	float touchTime;
	bool  fingerDown;
	bool monitorFallen;
public:
	cocos2d::CCLayer *animacjeLayer;
	int  bombsCollected;
	bool caught;
	float missedAmount;
	int notMissed;
	int missedInARow;
	int score;
	cocos2d::CCArray *trashAnimFramez;
	cocos2d::CCArray *bombAnimFramez;
	cocos2d::CCArray *getBombAnimFramez() { return bombAnimFramez; }
	cocos2d::CCArray *getTrashAnimFramez() { return trashAnimFramez; }
	void invaildTouch();
		void caughtExplosive();
		void missed();
		virtual bool init();
		static cocos2d::CCScene* scene();
		void ccTouchesMoved(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent);
		void ccTouchesBegan(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent);
		void ccTouchesEnded(cocos2d::CCSet *pTouches,cocos2d::CCEvent * pEvent);
 		void genFallingTrashes(float dt);
 		virtual void keyBackClicked();
		void removeAnim(CCNode* sender);
		void saveBeforLeaving();
		LAYER_CREATE_FUNC(Game);
		void wyrzucPuszki();
		void prepareTrashAnimFramez();
		void prepareBombAnim();
};

#endif /* GAME_H_ */
