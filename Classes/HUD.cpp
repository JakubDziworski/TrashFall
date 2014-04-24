/*
 * HUD.cpp
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */

#include "HUD.h"
#include "Constants.h"
#include "Utils.h"
using namespace cocos2d;

bool HUD::init() {
	if (!CCLayer::init()) {
		return false;
	}
	score =0;
	CCSprite *bg = CCSprite::create("Background.png");
	Utils::prepareBackgroundImg(bg);
	this->addChild(bg,-1);
	scoreLabel = CCLabelTTF::create("SCORE:0",FONT_MAIN,75);
	scoreLabel->setColor(ccColor3B{0,0,0});
	scoreLabel->setAnchorPoint(ccp(0,1));
	this->setTouchEnabled(true);
	scoreLabel->setPosition(ccp(5,Utils::sreensSize().height-5));
	this->addChild(scoreLabel);
	return true;
}
CCScene* HUD::scene() {
	CCScene *scene = CCScene::create();
	HUD *layer = HUD::create();
	scene->addChild(layer);
	return scene;
}
void HUD::addToScore(int value){
	score+=value;
	scoreLabel->setString(CCString::createWithFormat("SCORE:%d",score)->getCString());
}
