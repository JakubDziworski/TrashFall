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
#include "GameOver.h"
using namespace CocosDenshion;

using namespace cocos2d;
bool Game::init() {
	if (!CCLayer::init()) {
		return false;
	}
	//BACKGROUND
	missedAmount = 0;
	currentTimee=0;
	resettedTime=0;
	mSpeed=4;
	spread=1;
	fingerDown = false;
	monitorFallen = true;
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("inGame.mp3",true);
	Utils::setDifficulty(mSpeed,currentTimee,atOnce);
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
	CCLOG("created pause");
	Pause *pause = Pause::create();
	Background *bgLayer = Background::create();
	GameOver *gover = GameOver::create();
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
	//CCLOG("time = %.2f\n",currentTimee);
	Trash *obj = Trash::create(Utils::getRandValueF(mSpeed,mSpeed+spread),Utils::getRandValueF(1,4),monitorFallen);
	obj->setAutoCheckMissesPoints(true);
	CCLOG("%.2f\n",obj->getContentSize().height*obj->getScale());
	CCLOG("%.2f\n",Utils::sreensSize().height);
	this->addChild(obj,Utils::getRandValue(1,3));
}
void Game::missed(){
	if(!monitorFallen) return;
	missedAmount++;
	if(missedAmount>21){
		monitorFallen = false;
		Utils::getGameOver()->trigger(Utils::getHUD()->getScore(),200);
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
	for(int i=0;i<arr->count();i++){
		Trash *trsh = (Trash*) arr->objectAtIndex(i);
		if(CCRect::CCRectContainsPoint(trsh->boundingBox(),location)){
			SimpleAudioEngine::sharedEngine()->playEffect("buttonClick2.mp3");
			this->removeChild(trsh,true);
			Utils::getHUD()->addToScore(1);
		}
	}
}
void Game::ccTouchesBegan(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent){
	if(pTouches->count()>1) return;
	CCLOG("ROZPOCZETO DOTKNIECIE");
	fingerDown=true;
	ccTouchesMoved(pTouches,pEvent);
}
void Game::ccTouchesEnded(cocos2d::CCSet *pTouches,cocos2d::CCEvent * pEvent){
	if(pTouches->count()>1) return;
	fingerDown = false;
	touchTime=0;
}
void Game::keyBackClicked() {
	Utils::getPause()->toggle();
}
