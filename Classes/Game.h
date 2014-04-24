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
	int atOnce;
	float spread;
	float currentTime;
public:
//		void tick();
		virtual bool init();
		static cocos2d::CCScene* scene();
//		virtual void keyBackClicked();
//		void playGame();
//		void exitGame();
 		void genFallingTrashes(float dt);
		void cleaner(float dt);
		LAYER_CREATE_FUNC(Game);
};

#endif /* GAME_H_ */
