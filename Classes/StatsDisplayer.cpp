/*
 * StatsDisplayer.cpp
 *
 *  Created on: 30-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "StatsDisplayer.h"
#include "StatsRecords.h"
#include "Constants.h"
#include "Background.h"
#include "Utils.h"

using namespace cocos2d;
bool StatsDisplayer::init(){
	if (!CCLayer::init()) {
				return false;
			}
	CCLOG("weszlo");
	CCSprite *bg = CCSprite::createWithSpriteFrameName("scoreBoardBG.png");
	CCUserDefault *usrDefault = CCUserDefault::sharedUserDefault();
	CCLOG("POBIERANIE WARTOSCI");
	int sessions = usrDefault->getIntegerForKey(STAT_SESOVER,0);
	int trCollec = usrDefault->getIntegerForKey(STAT_COLLECTED,0);
	float accurancy = usrDefault->getFloatForKey(STAT_ACCURANCY,0);
	int bestScore = usrDefault->getIntegerForKey(HIGH_SCORE,0);
	CCLOG("zakonczenie pobierania");
	CCString *wyniki = CCString::createWithFormat("SESSIONS NUMBER:%d\nBEST SCORE:%d\nTRASHES COLLECTED:%d\nTOTAL ACCURANCY%.1f\n",sessions,bestScore,trCollec,accurancy);
	//CCLabelAtlas *wynikiLab = CCLabelAtlas::create(wyniki->getCString(),FONT_MAIN);
	CCLOG("stworzenie tekstu");
	CCLabelTTF *wynikiLab = CCLabelTTF::create(wyniki->getCString(),FONT_MAIN,80);
	CCLOG("stworzenie labela");
	wynikiLab->setPosition(Utils::getCorrectPosition(0.5,0.5));
	bg->setPosition(Utils::getCorrectPosition(0.5f,0.5f));
	this->addChild(wynikiLab,2);
	Utils::scaleSprite(bg,0.9,1,true);
	this->addChild(bg);
	return true;
}
