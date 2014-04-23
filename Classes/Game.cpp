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
	currentTime=0;
	maxSpeed = 4;
	rozstaw = 1;
	CCSprite *bg = CCSprite::create("Background.png");
	Utils::prepareBackgroundImg(bg);
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
	maxSpeed = 4;
	if(currentTime>5)maxSpeed = 3;
	else if(currentTime>8)maxSpeed = 1.5f;
	else if(currentTime>12)maxSpeed = 1;
	else if(currentTime>15)maxSpeed = 0.5f;
	rozstaw=maxSpeed/4;

//	CCLOG("%.2f\n",Utils::getRandValueF(maxSpeed,maxSpeed+rozstaw));
	Trash *obj = Trash::create((3,(Utils::getRandValueF(maxSpeed,maxSpeed+rozstaw))),Utils::getRandValue(1,3));
	this->addChild(obj);
}
void Game::cleaner(float dt){
	Utils::cleanView(this);
}

