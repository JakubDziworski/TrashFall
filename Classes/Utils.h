/*
 * Utils.h
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <sstream>
#include "cocos2d.h"
#include "Pause.h"
#include "HUD.h"
#include "Game.h"
#include "Background.h"
#include "GameOver.h"
class Utils {
public:
	static const int trashAmount = 5;
	cocos2d::CCLayer* layer;
	static HUD* getHUD();
	static Game* getGame();
	static Pause* getPause();
	static GameOver* getGameOver();
	static Background* getBackground();
	static int getRandValue(int min,int max);
	static float getRandValueF(float a,float b);
	static cocos2d::CCSpriteFrame* getRandomTrash();
	static float getRandomXPos();
	static cocos2d::CCSize sreensSize();
	static void scaleToFitScreen(cocos2d::CCSprite* input);
	static void prepareBackgroundImg(cocos2d::CCSprite* input);
	static float getEndHeight(cocos2d::CCSprite *input);
	static float getBeginHeight(cocos2d::CCSprite *input);
	static void cleanView(cocos2d::CCLayer*);
	static void cleanView(cocos2d::CCLayer*,bool checkForTrashes);
	static bool isVisible(cocos2d::CCSprite*,bool checkForTrashes);
	static void setDifficulty(float& spd,float tim,float& atonc);
	static void scaleSprite(cocos2d::CCSprite *sprite,float ratioo,float additional=1,bool wid=false);
	static void scaleButton(cocos2d::CCMenuItemSprite *sprite,float ratioo);
	static void setSpritePositionRelativetoMyPhone(cocos2d::CCSprite *sprite,float Xpos,float Ypos);
	static int getScaledFontSize(int fontsize);
	static cocos2d::CCPoint getCorrectPosition(float xRatio,float yRatio);
	static float getcorrectValue(float input,bool width=false);
};
#endif /* UTILS_H_ */
