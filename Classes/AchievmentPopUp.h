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
#include "Animated.h"
class AchievmentPopUp:public Animated {
	private:
	cocos2d::CCString *achvName;
	SpriteWithText *baseBg;
	public:
		cocos2d::CCUserDefault *savedData;
		bool initWithParams(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color);
		static AchievmentPopUp* createWithSpriteFrameNameee(const char *inputText,cocos2d::CCUserDefault *savedDat,bool whileRunning = false,cocos2d::ccColor3B color=cocos2d::ccColor3B{0,0,0},const char *pszSpriteFrameName="onCollected.png",const char *additionalImgFrameName="trophy.png");
		void activate();
		float getHeight();
		void activateForListing();
		bool isCollected();
		void show();
		void hide();
		void showAndHide();
};

#endif /* ACHIEVMENTPOPUP_H_ */
