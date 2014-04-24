/*
 * Background.h
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_


#include "cocos2d.h"
class Background: public cocos2d::CCLayer {
private:
	cocos2d::CCSprite *sun;
	cocos2d::CCSprite *chmurka[3];
	cocos2d::CCSprite *buzka;
	cocos2d::CCPoint orignalchmuraPos[3];
	float currentTim;
	float timeToWait;
public:
			virtual bool init();
			LAYER_CREATE_FUNC(Background);
			void moveChmurkiRandom(float dt);
};
#endif /* BACKGROUND_H_ */
