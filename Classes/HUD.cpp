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
#include "AchievmentPopUp.h"
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
	const float margin = Utils::getcorrectValue(0.015,true);
	const float shadowOffset = Utils::getcorrectValue(0.006,true);
	scoreLabel->setPosition(ccp(margin,Utils::sreensSize().height-margin));
	scoreShadow->setPositionY(scoreLabel->getPositionY()-shadowOffset);
	scoreShadow->setPositionX(scoreLabel->getPositionX()-shadowOffset);
	regularScale = scoreLabel->getScale();
	this->addChild(scoreShadow,-2);
	this->addChild(scoreLabel,-1);
	this->setTouchEnabled(true);
	this->schedule(schedule_selector(HUD::animateText));
	return true;
}

void HUD::addToScore(int value,int nomisses){
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
	AchievmentPopUp *achivscr=NULL;
	AchievmentPopUp *achivsingl = NULL;
	if (nomisses == 10)		achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_10_SINGLE,ccColor3B{0,0,0});
	else if (nomisses == 20)achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_20_SINGLE,ccColor3B{0,0,0});
	else if (nomisses == 50)achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_50_SINGLE,ccColor3B{0,0,0});
	else if (nomisses == 100)achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100_SINGLE,ccColor3B{0,0,0});
	else if (nomisses == 150)achivscr= AchievmentPopUp::createWithSpriteFrameNameee(ACH_150_SINGLE,ccColor3B{0,0,0});
	else if (nomisses == 250)achivscr= AchievmentPopUp::createWithSpriteFrameNameee(ACH_250_SINGLE,ccColor3B{0,0,0});
	if (score == 50)   		achivsingl= AchievmentPopUp::createWithSpriteFrameNameee(ACH_50,ccColor3B{0,0,0});
	else if (score == 100)  achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100,ccColor3B{0,0,0});
	else if (score == 250)  achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_250,ccColor3B{0,0,0});
	else if (score == 500)  achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_500,ccColor3B{0,0,0});
	else if (score == 1000) achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_1000,ccColor3B{0,0,0});
	else if (score == 2000) achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_2000,ccColor3B{0,0,0});
	CCLOG("B4");
	if(achivscr !=NULL) {CCLOG("NOMISSES = %d",nomisses);Utils::getBackground()->addChild(achivscr); achivscr->activate();}
	if(achivsingl != NULL) {CCLOG("SCORE = %d",score);Utils::getBackground()->addChild(achivsingl); achivsingl->activate();}
	CCLOG("AFTERA");

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
