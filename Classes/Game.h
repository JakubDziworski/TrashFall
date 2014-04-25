/*
 * Game.h
 *
 *  Created on: 23-04-2014
 *      Author: Jakub
 */

#ifndef GAME_H_
#define GAME_H_

#include "cocos2d.h"

class Game: public cocos2d::CCLayer {
	float mSpeed;
	float atOnce;
	float spread;
	float currentTimee;
	float resettedTime;
	int missedAmount;
public:
//		void tick();
		void missed();
		virtual bool init();
		static cocos2d::CCScene* scene();
		void ccTouchesMoved(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent);
//		virtual void keyBackClicked();
//		void playGame();
//		void exitGame();
 		void genFallingTrashes(float dt);
 		virtual void keyBackClicked();
		void cleaner(float dt);
		LAYER_CREATE_FUNC(Game);
};

#endif /* GAME_H_ */
