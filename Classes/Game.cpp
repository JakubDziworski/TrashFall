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
using namespace cocos2d;
bool Game::init() {
	if (!CCLayer::init()) {
		return false;
	}
	CCSprite *bg = CCSprite::create("Background.png");
	Utils::prepareBackgroundImg(bg);
	currentTimee=0;
	resettedTime=0;
	mSpeed=4;
	spread=1;
	Utils::setDifficulty(mSpeed,currentTimee,atOnce);
	this->schedule(schedule_selector(Game::genFallingTrashes));
	this->schedule(schedule_selector(Game::cleaner),5);
	return true;
}
CCScene* Game::scene() {

	CCScene *scene = CCScene::create();
	Game *layer;
	layer = Game::create();
	scene->addChild(layer);
	return scene;
}
void Game::genFallingTrashes(float dt){
	currentTimee+=dt;
	resettedTime+=dt;
	if(resettedTime<(10/atOnce)) return;
	resettedTime = 0;
	Utils::setDifficulty(mSpeed,currentTimee,atOnce);
	spread=mSpeed/4.0f;
	CCLOG("time = %.2f\n",currentTimee);
	Trash *obj = Trash::create(Utils::getRandValueF(mSpeed,mSpeed+spread),3);
	this->addChild(obj,Utils::getRandValue(1,3));
}
void Game::cleaner(float dt){
	Utils::cleanView(this);
}

