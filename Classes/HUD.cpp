/*
 * HUD.cpp
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "HUD.h"
#include "Constants.h"
#include "Utils.h"
using namespace cocos2d;

bool HUD::init() {
	if (!CCLayer::init()) {
		return false;
	}
	score =0;
	animationTime=0;
	extrascale=1;
	decr = 255;
	animate = false;
	extraAnim = false;
	scoreLabel = CCLabelTTF::create("0",FONT_MAIN,Utils::getScaledFontSize(75));
	scoreShadow = CCLabelTTF::create("0",FONT_MAIN,Utils::getScaledFontSize(75));
	scoreShadow->setColor(ccColor3B{0,0,0});
	scoreLabel->setAnchorPoint(ccp(0,1));
	scoreShadow->setAnchorPoint(ccp(0,1));
	Utils::scaleSprite(scoreLabel,scoreLabelRatio,1,true);
	Utils::scaleSprite(scoreShadow,scoreLabelRatio,1,true);
	scoreLabel->setPosition(ccp(5,Utils::sreensSize().height-5));
	scoreShadow->setPositionY(scoreLabel->getPositionY()-3);
	scoreShadow->setPositionX(scoreLabel->getPositionX()-3);
	regularScale = scoreLabel->getScale();
	this->addChild(scoreShadow,-2);
	this->addChild(scoreLabel,-1);
	this->setTouchEnabled(true);
	this->schedule(schedule_selector(HUD::animateText));
	return true;
}

void HUD::addToScore(int value){
	score+=value;
	scoreLabel->setString(CCString::createWithFormat("%d",score)->getCString());
	scoreShadow->setString(scoreLabel->getString());
	if(score%10 == 0){
	animateReset();
	scaleStop = 3;
	animate = true;
	extraAnim = true;
	}
	if(score%20 == 0){
		scaleStop = 10;
	}

}
void HUD::animateText(float dt){
	if(!animate) return;
	animationTime+=dt;

	if(animationTime>animationStop){
		animate = false;
		extraAnim = false;
		animateReset();
		return;
	}
	dx = 254.0*(2.0*dt/animationStop);
	if(animationTime < animationStop/2 && decr > dx+1){
		decr-=dx;
		CCLOG("zmniejszanie %d",decr);
		scoreLabel->setColor(ccColor3B{255,decr,decr});
		if(extraAnim && extrascale < scaleStop){
			extrascale+=scaleStop*(2.0*dt/animationStop);
			scoreLabel->setScale(extrascale);
			scoreShadow->setScale(extrascale);
		}
	}
	else if(decr < 254-dx){
		decr+=dx;
		CCLOG("zwiekszaniee %d",decr);
		scoreLabel->setColor(ccColor3B{255,decr,decr});
		if(extraAnim && extrascale > regularScale){
					extrascale-=scaleStop*(2.0*dt/animationStop);
					scoreLabel->setScale(extrascale);
					scoreShadow->setScale(extrascale);
				}
	}
}
void HUD::animateReset(){
	extrascale=1;
	decr = 255;
	animationTime = 0;
	scoreLabel->setScale(regularScale);
	scoreShadow->setScale(regularScale);
	scoreLabel->setColor(ccColor3B{255,255,255});
}
