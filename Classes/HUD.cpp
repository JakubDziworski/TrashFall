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
#include "AchvList.h"
#include "AchievmentPopUp.h"
#include "SimpleAudioEngine.h"
#include "StatsRecords.h"

#define animationStop 0.5f
#define tintoRed CCTintTo::create(animationStop / 2.0f, 254, 15, 15)
#define tintoNormal CCTintTo::create(animationStop / 3.0f, 254, 254, 254)
#define scaleToMax CCScaleTo::create(animationStop / 3.0f, regularScale+0.3f)
#define scaleToNormal CCScaleTo::create(animationStop / 2.0f, regularScale)
#define pokazISchowajCzerwone CCSequence::create(CCFadeIn::create(0.2f), CCFadeOut::create(0.8f), CCCallFuncN::create(this, callfuncN_selector(HUD::hideRedEffect)), NULL)

using namespace CocosDenshion;
using namespace cocos2d;

bool HUD::init() {
	if (!CCLayer::init()) {
		return false;
	}
	score =0;
	effect = CCSprite::createWithSpriteFrameName("trashFallEffect.png");
	effect->setAnchorPoint(ccp(0, 0));
	effect->setOpacity(0);
	Utils::scaleSprite(effect, 1, 1, true);
	effect->setVisible(false);
	savedData = CCUserDefault::sharedUserDefault();
	beginGlobalScore = savedData->getIntegerForKey(STAT_COLLECTED);
	bg = Utils::getBackground();
	scoreLabel = CCLabelBMFont::create("0", "font.fnt");
	scoreShadow = CCLabelBMFont::create("0", "font.fnt");
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
	anim = Animated::create();
	anim->addChild(scoreLabel,1);
	anim->addChild(scoreShadow,0);
	anim->initAnim(-0.3f,0,0,0,0.15f,-0.1f,0,0,1.0f,0.8f);
	this->addChild(anim,-2);
	this->setTouchEnabled(true);
	this->addChild(effect);
	anim->setPositionX(Utils::getcorrectValue(-0.1f));
	anim->startAnimIn();
	return true;
}

void HUD::hideScore(){
	anim->startAnimOut();
}
void HUD::addToScore(int value, int nomisses){
	score += value;
	beginGlobalScore += value;
	if (beginGlobalScore >= 5000 && beginGlobalScore < 5005  && score>3){
		AchievmentPopUp * ach = AchievmentPopUp::createWithSpriteFrameNameee(ACH_MASSIVE.c_str(), savedData, true);
		if (ach){
			Utils::getBackground()->addChild(ach);
			ach->activate();
		}
	}
	if (Utils::getGame()->bombsCollected == 0 && score == 100){
		AchievmentPopUp * ach = AchievmentPopUp::createWithSpriteFrameNameee(ACH_AVOIDER.c_str(), savedData, true);
		if (ach){
			ach->activate();
			Utils::getBackground()->addChild(ach);
		}
	}

	checkAchivmets(nomisses);
	scoreLabel->setString(CCString::createWithFormat("%d", score)->getCString());
	scoreShadow->setString(scoreLabel->getString());
	if (score % 10 == 0){
		scoreLabel->runAction(CCSequence::create(tintoRed, tintoNormal, NULL));
			scoreLabel->runAction(CCSequence::create(scaleToMax, scaleToNormal, NULL));
			scoreShadow->runAction(CCSequence::create(scaleToMax, scaleToNormal, NULL));
	}
}

void HUD::trashFallenEffects() {
	SimpleAudioEngine::sharedEngine()->playEffect("trashFelt.wav");
	effect->setVisible(true);
	effect->stopAllActions();
	effect->runAction(pokazISchowajCzerwone);
}

void HUD::DisplayTrafion(cocos2d::CCPoint point,bool traf) {
		CCSprite *ntraf = CCSprite::createWithSpriteFrameName("missed.png");
		Utils::scaleSprite(ntraf, 5, 1, true);
		this->addChild(ntraf);
		ntraf->setOpacity(255);
		ntraf->setPosition(point);
		ntraf->runAction(CCSequence::create(CCFadeOut::create(0.9f), CCCallFuncN::create(ntraf, callfuncN_selector(HUD::deleteMissed)), NULL));
}



void HUD::checkAchivmets(int nomisses) {
		AchievmentPopUp *generalScore=NULL;
		AchievmentPopUp *inArowScore = NULL;
		switch(nomisses){
		case 10:	inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_10_SINGLE.c_str(),savedData,true);break;
		case 20:    inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_20_SINGLE.c_str(),savedData,true);break;
		case 50:	inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_35_SINGLE.c_str(),savedData,true);break;
		case 100:	inArowScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_50_SINGLE.c_str(),savedData,true);break;
		case 150:	inArowScore= AchievmentPopUp::createWithSpriteFrameNameee(ACH_75_SINGLE.c_str(),savedData,true);break;
		case 250:	inArowScore= AchievmentPopUp::createWithSpriteFrameNameee(ACH_150_SINGLE.c_str(),savedData,true);break;
		}
		switch(score){
		case 50:	generalScore= AchievmentPopUp::createWithSpriteFrameNameee(ACH_25.c_str(),savedData,true);break;
		case 100:    generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_50.c_str(),savedData,true);break;
		case 250:   generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_100.c_str(),savedData,true);break;
		case 500:   generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_175.c_str(),savedData,true);break;
		case 1000:  generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_300.c_str(),savedData,true);break;
		case 2000:  generalScore = AchievmentPopUp::createWithSpriteFrameNameee(ACH_500.c_str(),savedData,true);break;
		}
		if(inArowScore !=NULL) {Utils::getBackground()->addChild(inArowScore); inArowScore->activate();}
		if(generalScore != NULL) {Utils::getBackground()->addChild(generalScore);generalScore->activate();}
}

void HUD::deleteMissed(cocos2d::CCNode* inp)
{
	inp->removeFromParentAndCleanup(true);
}

void HUD::hideRedEffect(cocos2d::CCNode* inp)
{
	effect->setVisible(false);
}
