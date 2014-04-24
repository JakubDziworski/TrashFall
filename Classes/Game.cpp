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
	currentTime=0;
	mSpeed=4;
	spread=1;
	this->schedule(schedule_selector(Game::genFallingTrashes),1);
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
	currentTime+=dt;
	Utils::setDifficulty(mSpeed,currentTime,atOnce);
	spread=mSpeed/4.0f;
	CCLOG("time = %.2f\n",currentTime);
	for(int i=0;i<atOnce;i++){
	Trash *obj = Trash::create(Utils::getRandValueF(mSpeed,mSpeed+spread),3);
	this->addChild(obj,Utils::getRandValue(1,3));
	}
}
void Game::cleaner(float dt){
	Utils::cleanView(this);
}

