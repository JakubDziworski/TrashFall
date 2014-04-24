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
	CCLOG("totime = %2f.\n",currentTime);
	if(currentTime>15) mSpeed = 0.5f;
	else if(currentTime>12) mSpeed = 1;
	else if(currentTime>8) mSpeed = 1.5f;
	else if(currentTime>5)mSpeed = 3;
	else mSpeed = 4;
	spread=mSpeed/4.0f;

//	CCLOG("%.2f\n",Utils::getRandValueF(maxSpeed,maxSpeed+rozstaw));
	Trash *obj = Trash::create(Utils::getRandValueF(mSpeed,mSpeed+spread),3);
	this->addChild(obj,Utils::getRandValue(1,3));
}
void Game::cleaner(float dt){
	Utils::cleanView(this);
}

