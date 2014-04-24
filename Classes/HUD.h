/*
 * HUD.h
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */

#ifndef HUD_H_
#define HUD_H_

#include "cocos2d.h"

class HUD: public cocos2d::CCLayer {
private:
	cocos2d::CCLabelTTF* scoreLabel;
	cocos2d::CCLabelTTF* scoreShadow;
	int score;
public:
			virtual bool init();
			static cocos2d::CCScene* scene();
			void addToScore(int value);
	 	//	virtual void keyBackClicked();
			LAYER_CREATE_FUNC(HUD);
};

#endif /* HUD_H_ */
