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
	tr=true;
	ntr=true;
	extraAnim = false;
	trafiony = CCSprite::createWithSpriteFrameName("onPaused.png");
	nietrafiony = CCSprite::createWithSpriteFrameName("offPaused.png");
	Utils::scaleSprite(trafiony,15,1,true);
	Utils::scaleSprite(nietrafiony,15,1,true);
	this->addChild(trafiony);
	this->addChild(nietrafiony);
	effect = CCSprite::createWithSpriteFrameName("trashFallEffect.png");
	Utils::prepareBackgroundImg(effect);
	effect->setOpacity(0);
	savedData = CCUserDefault::sharedUserDefault();
	bg = Utils::getBackground();
	scoreLabel = CCLabelTTF::create("0",FONT_MAIN,Utils::getScaledFontSize(75));
	scoreShadow = CCLabelTTF::create("0",FONT_MAIN,Utils::getScaledFontSize(75));
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
	if (nomisses == 10)		achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_10_SINGLE.c_str(),savedData);
	else if (nomisses == 20)achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_20_SINGLE.c_str(),savedData);
	else if (nomisses == 50)achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_50_SINGLE.c_str(),savedData);
	else if (nomisses == 100)achivscr = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100_SINGLE.c_str(),savedData);
	else if (nomisses == 150)achivscr= AchievmentPopUp::createWithSpriteFrameNameee(ACH_150_SINGLE.c_str(),savedData);
	else if (nomisses == 250)achivscr= AchievmentPopUp::createWithSpriteFrameNameee(ACH_250_SINGLE.c_str(),savedData);
	if (score == 50)   		achivsingl= AchievmentPopUp::createWithSpriteFrameNameee(ACH_50.c_str(),savedData);
	else if (score == 100)  achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100.c_str(),savedData);
	else if (score == 250)  achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_250.c_str(),savedData);
	else if (score == 500)  achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_500.c_str(),savedData);
	else if (score == 1000) achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_1000.c_str(),savedData);
	else if (score == 2000) achivsingl = AchievmentPopUp::createWithSpriteFrameNameee(ACH_2000.c_str(),savedData);
	if(achivscr !=NULL) {Utils::getBackground()->addChild(achivscr); achivscr->activate();}
	if(achivsingl != NULL) {Utils::getBackground()->addChild(achivsingl);achivsingl->activate();}
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

void HUD::trashFallenEffects() {
	SimpleAudioEngine::sharedEngine()->playEffect("trashFelt.wav");
	effect->setOpacity(150);
	reached250=false;
	stopAnimRed=false;
	const unsigned int repeat = 500;
	const float repeatRate = 0.05f;
	CCLOG("PRZESKALOWANO");
	schedule(schedule_selector(HUD::animateTrashFallEffect));
}

void HUD::animateTrashFallEffect(float dt) {
	if(stopAnimRed) return;
	int x = effect->getOpacity();
	CCLOG("opacty = %d",x);
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
	if(traf){
		trafiony->runAction(CCFadeIn::create(0.2f));
		trafiony->setPosition(point);
		tr=true;
	}
	else{
		nietrafiony->setPosition(point);
		nietrafiony->runAction(CCFadeIn::create(0.2f));
		ntr=true;
	}
	schedule(schedule_selector(HUD::fadeoutTrafiony),0.21f,0,0.21f);
}

void HUD::fadeoutTrafiony(float) {
	if(tr) {trafiony->runAction(CCFadeOut::create(1));tr=false;}
	if(ntr) {nietrafiony->runAction(CCFadeOut::create(1));ntr=false;}
}

void HUD::animateReset() {
	extrascale=1;
	decr = 255;
	animationTime = 0;
	scoreLabel->setScale(regularScale);
	scoreShadow->setScale(regularScale);
	scoreLabel->setColor(ccColor3B{255,255,255});
}
