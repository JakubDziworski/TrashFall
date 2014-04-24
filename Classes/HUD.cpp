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
	scoreLabel = CCLabelTTF::create("SCORE:0",FONT_MAIN,75);
	scoreShadow = CCLabelTTF::create("SCORE:0",FONT_MAIN,75);
	scoreShadow->setColor(ccColor3B{0,0,0});
	scoreLabel->setAnchorPoint(ccp(0,1));
	scoreShadow->setAnchorPoint(ccp(0,1));
	Utils::scaleSprite(scoreLabel,scoreLabelRatio,1,true);
	Utils::scaleSprite(scoreLabel,scoreLabelRatio,1,true);
	scoreLabel->setPosition(ccp(5,Utils::sreensSize().height-5));
	scoreShadow->setPositionY(scoreLabel->getPositionY()-3);
	scoreShadow->setPositionX(scoreLabel->getPositionX()-3);
	this->addChild(scoreShadow,-2);
	this->addChild(scoreLabel,-1);
	this->setTouchEnabled(true);
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
	scoreShadow->setString(scoreLabel->getString());
}
