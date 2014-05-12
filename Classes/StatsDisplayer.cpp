/*
 * StatsDisplayer.cpp
 *
 *  Created on: 30-04-2014
 *      Author: Jakub
 */
 
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
	CCLabelBMFont *labelTitle = CCLabelBMFont::create("STATS","font.fnt",1000,kCCTextAlignmentCenter);
	Utils::scaleSprite(labelTitle,12,1,false);
	labelTitle->setColor(ccColor3B{0,0,0});
	CCSprite *bg = CCSprite::createWithSpriteFrameName("scoreBoardBG.png");
	CCString *wyniki = CCString::createWithFormat("SESSIONS NUMBER:%d\nBEST SCORE:%d\nTRASHES COLLECTED:%d\nAVERAGE ACCURACY:%.1f\%%",sessions,bestScore,trCollec,accurancy);
	CCLabelBMFont *wynikiLab = CCLabelBMFont::create(wyniki->getCString(),"font.fnt",10000,kCCTextAlignmentCenter);
	wynikiLab->setColor(ccColor3B{0,0,0});
	labelTitle->setPositionY(Utils::getcorrectValue(0.2f));
	Utils::scaleSprite(wynikiLab,6,1,false);
	this->addChild(labelTitle);
	this->addChild(wynikiLab);
	this->setPosition(Utils::getCorrectPosition(0.5f,0.5f));
	Utils::scaleSprite(bg,1.1,1,true);
	this->addChild(bg,-1);
	this->setPosition(Utils::getCorrectPosition(1.5f,0.5f));
	this->initAnim(1.5f,0.5,0.5,0.5,0.3f,0.1f,0,0,0.7f,0);
	return true;
}

StatsDisplayer* StatsDisplayer::createe() {
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
