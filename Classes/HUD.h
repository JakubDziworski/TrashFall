/*
 * HUD.h
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */

#ifndef HUD_H_
#define HUD_H_
#define animationStop 0.5f
#include "Background.h"
#include "cocos2d.h"

class HUD: public cocos2d::CCLayer {
private:
	cocos2d::CCLabelTTF* scoreLabel;
	cocos2d::CCLabelTTF* scoreShadow;
	float dx;
	float extrascale;
	float regularScale;
	float scaleStop;
	float animationTime;
	bool animate;
	bool extraAnim;
	int decr;
	int score;
	Background *bg;
	cocos2d::CCUserDefault *savedData;
public:
			virtual bool init();
			void addToScore(int value,int nomisses);
	 	//	virtual void keyBackClicked();
			LAYER_CREATE_FUNC(HUD);
			void animateText(float dt);
			void animateReset();
			int getScore(){return score;}

};

#endif /* HUD_H_ */
