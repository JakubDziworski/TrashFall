/*
 * HUD.cpp
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#define wzrostmnoznik 500
#define spadekmnoznik 200
#include "HUD.h"
#include "Constants.h"
#include "Utils.h"
#include "AchvList.h"
#include "AchievmentPopUp.h"
#include "SimpleAudioEngine.h"
#include "StatsRecords.h"
using namespace CocosDenshion;
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
	stopAnimRed=true;
	extraAnim = false;
	effect = CCSprite::createWithSpriteFrameName("trashFallEffect.png");
	effect->setAnchorPoint(ccp(0, 0));
	Utils::scaleSprite(effect, 1, 1, true);
	effect->setOpacity(0);
	savedData = CCUserDefault::sharedUserDefault();
	beginGlobalScore = savedData->getIntegerForKey(STAT_COLLECTED);
	bg = Utils::getBackground();
	scoreLabel = CCLabelBMFont::create("0", "font.fnt", -1.0F, kCCTextAlignmentLeft);
	scoreShadow = CCLabelBMFont::create("0", "font.fnt", -1.0F, kCCTextAlignmentLeft);
	scoreShadow->setColor(ccColor3B{0,0,0});
	scoreLabel->setAnchorPoint(ccp(0,1));
	scoreShadow->setAnchorPoint(ccp(0,1));
	Utils::scaleSprite(scoreLabel,scoreLabelRatio,1,true);
	Utils::scaleSprite(scoreShadow,scoreLabelRatio,1,true);
	const float marginn = Utils::getcorrectValue(0.015,true);
	const float shadowOffset = Utils::getcorrectValue(0.006,true);
	scoreLabel->setPosition(ccp(marginn,Utils::sreensSize().height-marginn));
	scoreShadow->setPositionY(scoreLabel->getPositionY()-shadowOffset);
	scoreShadow->setPositionX(scoreLabel->getPositionX()-shadowOffset);
	regularScale = scoreLabel->getScale();
	Animated *anim = Animated::create();
	anim->addChild(scoreLabel,1);
	anim->addChild(scoreShadow,0);
	anim->initAnim(-0.1f,0,0,0,0.15f,-0.1f,0,0,1.3f);
	this->addChild(anim,-2);
	this->setTouchEnabled(true);
	this->addChild(effect);
	this->schedule(schedule_selector(HUD::animateText));
	anim->setPositionX(Utils::getcorrectValue(-0.1f));
	anim->startAnimIn();
	return true;
}


void HUD::addToScore(int value,int nomisses){
	score+=value;
	beginGlobalScore+=value;
	if(beginGlobalScore >=10000 &&beginGlobalScore < 10005 && score>3){
					AchievmentPopUp * ach=AchievmentPopUp::createWithSpriteFrameNameee(ACH_MASSIVE.c_str(),savedData,true);
					if(ach){
					Utils::getBackground()->addChild(ach);
					ach->activate();
					}
	}
	checkAchivmets(nomisses);
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
		scoreLabel->setColor(ccColor3B{255,decr,decr});
		if(extraAnim && extrascale < scaleStop){
			extrascale+=scaleStop*(2.0*dt/animationStop);
			scoreLabel->setScale(extrascale);
			scoreShadow->setScale(extrascale);
		}
	}
	else if(decr < 254-dx){
		decr+=dx;
		scoreLabel->setColor(ccColor3B{255,decr,decr});
		if(extraAnim && extrascale > regularScale){
					extrascale-=scaleStop*(2.0*dt/animationStop);
					scoreLabel->setScale(extrascale);
					scoreShadow->setScale(extrascale);
				}
	}
}

void HUD::trashFallenEffects() {
	SimpleAudioEngine::sharedEngine()->playEffect("trashFelt.wav");
	effect->setOpacity(150);
	reached250=false;
	stopAnimRed=false;
	const unsigned int repeat = 500;
	const float repeatRate = 0.05f;
	schedule(schedule_selector(HUD::animateTrashFallEffect));
}

void HUD::animateTrashFallEffect(float dt) {
	if(stopAnimRed) return;
	int x = effect->getOpacity();
	if(x<255 && !reached250){
		if(dt*wzrostmnoznik+x>=255){reached250=true; x=255;}
		else x+=dt*wzrostmnoznik;
	}
	else{
		if(x-dt*spadekmnoznik<0) {stopAnimRed=true; x=0;}
		else x-=dt*spadekmnoznik;
	}
	effect->setOpacity(x);
}

void HUD::DisplayTrafion(cocos2d::CCPoint point,bool traf) {
		CCSprite *ntraf = CCSprite::createWithSpriteFrameName("missed.png");
		Utils::scaleSprite(ntraf, 5, 1, true);
		this->addChild(ntraf);
		ntraf->setOpacity(255);
		ntraf->setPosition(point);
		ntraf->runAction(CCFadeOut::create(0.9f));
}

void HUD::checkAchivmets(int nomisses) {
		AchievmentPopUp *generalScore=NULL;
		AchievmentPopUp *inArowScore = NULL;
		switch(nomisses){
		case 10:	inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_10_SINGLE.c_str(),savedData,true);break;
		case 20:    inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_20_SINGLE.c_str(),savedData,true);break;
		case 50:	inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_50_SINGLE.c_str(),savedData,true);break;
		case 100:	inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100_SINGLE.c_str(),savedData,true);break;
		case 150:	inArowScore= AchievmentPopUp::createWithSpriteFrameNameee(ACH_150_SINGLE.c_str(),savedData,true);break;
		case 250:	inArowScore= AchievmentPopUp::createWithSpriteFrameNameee(ACH_250_SINGLE.c_str(),savedData,true);break;
		}
		switch(score){
		case 50:	generalScore= AchievmentPopUp::createWithSpriteFrameNameee(ACH_50.c_str(),savedData,true);break;
		case 100:    generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100.c_str(),savedData,true);break;
		case 250:   generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_250.c_str(),savedData,true);break;
		case 500:   generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_500.c_str(),savedData,true);break;
		case 1000:  generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_1000.c_str(),savedData,true);break;
		case 2000:  generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_2000.c_str(),savedData,true);break;
		}
		if(inArowScore !=NULL) {Utils::getBackground()->addChild(inArowScore); inArowScore->activate();}
		if(generalScore != NULL) {Utils::getBackground()->addChild(generalScore);generalScore->activate();}
}

void HUD::animateReset() {
	extrascale=1;
	decr = 255;
	animationTime = 0;
	scoreLabel->setScale(regularScale);
	scoreShadow->setScale(regularScale);
	scoreLabel->setColor(ccColor3B{255,255,255});
}
