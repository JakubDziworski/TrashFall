/*
 * Game.cpp
 *
 *  Created on: 23-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Game.h"
#include "Trash.h"
#include "Utils.h"
#include "Constants.h"
#include "SimpleAudioEngine.h"
#include "Background.h"
#include "AchvDisplayer.h"
#include "AchievmentPopUp.h"
#include "GameOver.h"
#include "HUD.h"
#include "AchvList.h"
#include "StatsRecords.h"
#include "Bomb.h"
using namespace CocosDenshion;

using namespace cocos2d;
bool Game::init() {
	if (!CCLayer::init()) {
		return false;
	}
	//BACKGROUND
	isOver = false;
	notMissed=0;
	bombsCollected = 0;
	score = 0;
	missedAmount = 0;
	currentTimee=0;
	resettedTime=0;
	mSpeed=4;
	spread=1;
	fingerDown = false;
	monitorFallen = true;
	animacjeLayer = CCLayer::create();
	Utils::setDifficulty(mSpeed,currentTimee,atOnce);
	this->addChild(animacjeLayer);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->schedule(schedule_selector(Game::genFallingTrashes));
	return true;
}
CCScene* Game::scene() {
	CCScene *scene = CCScene::create();
	scene->setTag(TAG_GAMESCENE);
	Game *layer = Game::create();
	HUD *hud = HUD::create();
	Pause *pause = Pause::create();
	Background *bgLayer = Background::create();
	GameOver *gover = GameOver::create();
	
	//AchvDisplayer *achivdispl = AchvDisplayer::create();
	scene->addChild(bgLayer,-1,TAG_BACKGROUND);
	scene->addChild(layer,0,TAG_GAMELayer);
	scene->addChild(hud,1,TAG_HUD);
	scene->addChild(pause,3,TAG_PAUSE);
	scene->addChild(gover,4,TAG_GAMEOVER);
	return scene;
}
void Game::genFallingTrashes(float dt){
	currentTimee+=dt;
	resettedTime+=dt;
	if(fingerDown) touchTime += dt;
	if(resettedTime<(10/atOnce)) return;
	resettedTime = 0;
	Utils::setDifficulty(mSpeed,currentTimee,atOnce);
	spread=mSpeed/4.0f;
	const int czyBomba = Utils::getRandValue(0,8);
	Trash *obj;
	if(czyBomba == 5)
	 obj = Bomb::createe(Utils::getRandValueF(mSpeed,mSpeed+spread),Utils::getRandValueF(1,2.5f),monitorFallen);
	else obj = Trash::create(Utils::getRandValueF(mSpeed,mSpeed+spread),Utils::getRandValueF(1,2.5f),monitorFallen);
	obj->setAutoCheckMissesPoints(true);
	this->addChild(obj,1);
}
void Game::missed(){
	if(!monitorFallen) return;
	notMissed=0;
	Utils::getHUD()->trashFallenEffects();
	missedAmount++;
	if(missedAmount>21){
		monitorFallen = false;
		isOver = true;
		Utils::getBackground()->updateMisses(21);
		Utils::getGameOver()->trigger(Utils::getHUD()->getScore(),missedAmount);
		return;
	}
	Utils::getBackground()->updateMisses(missedAmount);
}

void Game::ccTouchesMoved(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent){
	if(pTouches->count()>1) return;
	if(touchTime > maxTouchTime) return;
	if(this->getChildren() == NULL) return;
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	CCArray *arr = this->getChildren();
	arr->retain();
	for(int i=1;i<arr->count();i++){
		CCLOG("before");
		Trash *trsh = dynamic_cast<Trash*>(arr->objectAtIndex(i));
		if (trsh){CCLOG("after");
		if(CCRect::CCRectContainsPoint(trsh->boundingBox(),location)){
			trsh->dotkniety();

		}
		}
	}
}
void Game::ccTouchesBegan(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent){
	if(pTouches->count()>1) return;
	caught=false;
	fingerDown=true;
	ccTouchesMoved(pTouches,pEvent);
}
void Game::ccTouchesEnded(cocos2d::CCSet *pTouches,cocos2d::CCEvent * pEvent){
	if(pTouches->count()>1) return;
	if(!caught){
		invaildTouch();
		CCTouch *touch = (CCTouch*)pTouches->anyObject();
		Utils::getHUD()->DisplayTrafion(CCDirector::sharedDirector()->convertToGL(touch->locationInView()),false);
	}
	fingerDown = false;
	touchTime=0;
}

void Game::invaildTouch() {
	SimpleAudioEngine::sharedEngine()->playEffect("missed.mp3");
		missedAmount+=1;
		missedInARow++;
		if(missedAmount>21){
			monitorFallen = false;
			Utils::getGameOver()->trigger(Utils::getHUD()->getScore(),missedAmount);
			return;
		}
		if(missedInARow == 10){
			AchievmentPopUp * ach=AchievmentPopUp::createWithSpriteFrameNameee(ACH_BLIND.c_str(),CCUserDefault::sharedUserDefault(),true);
			if(ach){
			ach->activate();
			
			Utils::getBackground()->addChild(ach);
			}
		}
		Utils::getBackground()->updateMisses(missedAmount);
}

void Game::caughtExplosive() {
	bombsCollected++;
	missedAmount += 4;
	notMissed=0;
	caught=true;
	if (missedAmount > 21) {
		monitorFallen = false;
		Utils::getBackground()->updateMisses(21);
		Utils::getGameOver()->trigger(Utils::getHUD()->getScore(),
				missedAmount);
		return;
	}
	Utils::getBackground()->updateMisses(missedAmount);
}


void Game::keyBackClicked() {
	Utils::getPause()->toggle(NULL);
}

void Game::removeAnim(CCNode* sender)
{
	Utils::getGame()->animacjeLayer->removeChild(sender, true);
}

void Game::saveBeforLeaving() {
	if(score > 3){
		CCUserDefault *dane = CCUserDefault::sharedUserDefault();
		dane->setIntegerForKey(STAT_COLLECTED,dane->getIntegerForKey(STAT_COLLECTED)+score);
		int sessionsOver=dane->getIntegerForKey(STAT_SESOVER)+1;
		dane->setIntegerForKey(STAT_SESOVER,sessionsOver);
		if(dane->getIntegerForKey(HIGH_SCORE) < score)
		dane->setIntegerForKey(HIGH_SCORE,score);
		const float accurancy = (float)score/(float)(score+missedAmount)*100;
		dane->setFloatForKey(STAT_ACCURANCY,(dane->getFloatForKey(STAT_ACCURANCY,0)*(float)(sessionsOver-1)+accurancy)/(float)sessionsOver);
		if (sessionsOver == 100) {
					AchievmentPopUp * ach = AchievmentPopUp::createWithSpriteFrameNameee(ACH_HARDCORE.c_str(), dane,true);
					if(ach)
					{
					ach->activate();
					Utils::getBackground()->addChild(ach);
					}
			}
		}
}
void Game::wyrzucPuszki(){
	CCArray *arr = this->getChildren();
	for (int j = 0; j < arr->count(); j++){
		Trash *trash = dynamic_cast<Trash*>(arr->objectAtIndex(j));
		if (trash){
			trash->resumeSchedulerAndActions();
			trash->stopActionByTag(1);
			trash->runAction(CCMoveTo::create(0.3f, Utils::getCorrectPosition(1.5f, Utils::ratioValue(trash->getPositionY(), true) - 0.1f)));
		}
	}
}
