/*
 * GameOver.h
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "cocos2d.h"

class GameOver: public cocos2d::CCLayer {
	virtual bool init();
	void toggle();
	LAYER_CREATE_FUNC(GameOver);
};

#endif /* GAMEOVER_H_ */
