/*
 * Pause.h
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

#ifndef PAUSE_H_
#define PAUSE_H_

#include "cocos2d.h"
#include "SpriteWithText.h"

class Pause: public cocos2d::CCLayer {
private:
	bool paused;
public:
	virtual bool init();
	void toggle();
	void goToMainMenu();
	LAYER_CREATE_FUNC(Pause);
};

#endif /* PAUSE_H_ */
