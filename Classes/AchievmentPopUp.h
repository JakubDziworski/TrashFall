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
#define animTime 0.3f
#define endTime 4
class AchievmentPopUp: public cocos2d::CCNode {
	private:
	float currTime;
	float oczekiwanyfact;
	float scaleFactor;
	cocos2d::CCString *achvName;
	public:
		bool initWithParams(const char *pszSpriteFrameName,const char *additionalImgFrameName,const char *inputText,cocos2d::ccColor3B color);
		static AchievmentPopUp* createWithSpriteFrameNameee(const char *inputText,cocos2d::ccColor3B color,const char *pszSpriteFrameName="offButton.png",const char *additionalImgFrameName="trophy.png");
		void activate();
		void animate(float dt);
};

#endif /* ACHIEVMENTPOPUP_H_ */
