/*
 * Background.h
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_


#include "cocos2d.h"
#include "Animated.h"
class Background: public cocos2d::CCLayer {
private:
	cocos2d::CCSprite *sun;
	cocos2d::CCSprite *chmurka[3];
	cocos2d::CCSprite *buzka;
	cocos2d::CCSprite* sunHurt;
	cocos2d::CCPoint orignalchmuraPos[3];
	float maxmovementChmurki;
	float beginAnimTime;
	float currentTim;
	float timeToWait;
	Animated * sunMover;
	Animated *chmurkaMover[3];
public:
			virtual bool init();
			void updateMisses(int);
			LAYER_CREATE_FUNC(Background);
			void beginAnimation();
			void moveChmurkiRandom(float dt);
			void wywalChmuriIslonce();
};
#endif /* BACKGROUND_H_ */
