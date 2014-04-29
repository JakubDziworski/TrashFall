/*
 * AchievmentPopUp.h
 *
 *  Created on: 26-04-2014
 *      Author: Jakub
 */

#ifndef ACHIEVMENTPOPUP_H_
#define ACHIEVMENTPOPUP_H_

#include "SpriteWithText.h"
#include "cocos2d.h"

class AchievmentPopUp: public cocos2d::CCNode {
	private:
	float currTime;
	bool first,second,third,forth,r1,r2,r3,r4;
	cocos2d::CCString *achvName;
	SpriteWithText *baseBg;
	float mystaticYpos;
	float mystaticEndpos;
	public:
		cocos2d::CCUserDefault *savedData;
		bool initWithParams(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color);
		static AchievmentPopUp* createWithSpriteFrameNameee(const char *inputText,cocos2d::CCUserDefault *savedDat,cocos2d::ccColor3B color=cocos2d::ccColor3B{0,0,0},const char *pszSpriteFrameName="offButton.png",const char *additionalImgFrameName="trophy.png");
		void activate();
		float getHeight();
		void animate(float dt);
		void activateForListing();
		bool isCollected();
		void animateIn(float);
		void animateOut(float);
		void startAnimOut();
		void startAnimIn();

	};

#endif /* ACHIEVMENTPOPUP_H_ */
