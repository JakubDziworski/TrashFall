/*
 * GameOver.h
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "cocos2d.h"
#include "SpriteWithText.h"
#include "Animated.h"
class GameOver: public cocos2d::CCLayer {
private:
	SpriteWithText *currentScore;
	SpriteWithText *highScore;
	SpriteWithText *newScoreSet;
	cocos2d::CCSprite *ok;
	cocos2d::CCSprite *scoreBoardBg;
	cocos2d::CCMenu *menu;
	Animated *anim;
	int curScore;
	int bestScore;

public:
	virtual bool init();
	void lateMainMenu(float);
	void trigger(int scorr,int);
	void playGame();
	void keyBackClicked();
	void enableTouchAfterWait(float);
	LAYER_CREATE_FUNC(GameOver);
};

#endif /* GAMEOVER_H_ */
