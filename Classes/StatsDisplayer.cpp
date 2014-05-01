/*
 * StatsDisplayer.cpp
 *
 *  Created on: 30-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#define mystaticYpos 0.5f
#define beginPosX 1.5f
#include "StatsDisplayer.h"
#include "StatsRecords.h"
#include "Constants.h"
#include "Background.h"
#include "ITouchDisablable.h"
#include "Utils.h"

using namespace cocos2d;

bool StatsDisplayer::initialize() {
	//DATA
	CCUserDefault *usrDefault = CCUserDefault::sharedUserDefault();
		int sessions = usrDefault->getIntegerForKey(STAT_SESOVER,0);
		int trCollec = usrDefault->getIntegerForKey(STAT_COLLECTED,0);
		float accurancy = usrDefault->getFloatForKey(STAT_ACCURANCY,0);
		int bestScore = usrDefault->getIntegerForKey(HIGH_SCORE,0);
	//GUI
	CCLabelTTF *labelTitle = CCLabelTTF::create("STATS",FONT_MAIN,Utils::getScaledFontSize(115));
	labelTitle->setColor(ccColor3B{0,0,0});
	CCSprite *bg = CCSprite::createWithSpriteFrameName("scoreBoardBG.png");
	CCString *wyniki = CCString::createWithFormat("SESSIONS NUMBER:%d\nBEST SCORE:%d\nTRASHES COLLECTED:%d\nAVERAGE ACCURANCY:%.1f\%%",sessions,bestScore,trCollec,accurancy);
	CCLabelTTF *wynikiLab = CCLabelTTF::create(wyniki->getCString(),FONT_MAIN,Utils::getScaledFontSize(45));
	wynikiLab->setColor(ccColor3B{0,0,0});
	labelTitle->setPositionY(Utils::getcorrectValue(0.2f));
	this->addChild(labelTitle);
	this->addChild(wynikiLab);
	this->setPosition(Utils::getCorrectPosition(0.5f,0.5f));
	Utils::scaleSprite(bg,1.1,1,true);
	this->addChild(bg,-1);
	this->setPosition(Utils::getCorrectPosition(1.5f,0.5f));
	this->initAnim(1.5f,0.5,0.5,0.5,0.3f,0.1f,0,0,0.3f,0);
	return true;
}

StatsDisplayer* StatsDisplayer::createe() {
		CCLOG("Po zainacializowaniu");
		StatsDisplayer *sts = new StatsDisplayer();
		sts->initialize();
		sts->autorelease();
		return sts;
}

void StatsDisplayer::hide() {
		this->unscheduleAllSelectors();
		this->stopAllActions();
		this->startAnimOut();
}

void StatsDisplayer::show() {
		this->startAnimIn();
}
