/*
 * LoadingNode.cpp
 *
 *  Created on: 01-05-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "LoadingNode.h"
#include "SpriteWithText.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

using namespace CocosDenshion;
using namespace cocos2d;

bool LoadingNode::init() {
	if (!CCLayer::init())
		return false;
	/*	CCLabelBMFont *trashFall = CCLabelBMFont::create("TRASH\nFALL", "font.fnt", -1.0f, kCCTextAlignmentCenter);
		CCLabelBMFont *shadow = CCLabelBMFont::create("TRASH\nFALL", "font.fnt", -1.0f, kCCTextAlignmentCenter);
		shadow->setColor(ccColor3B{ 0, 0, 0 });
		Utils::scaleSprite(shadow, 1.1f, 1, true);
		Utils::scaleSprite(trashFall, 1.1f,1, true);
		shadow->setPosition(Utils::getCorrectPosition(0.48f, 0.48f));
		trashFall->setPosition(Utils::getCorrectPosition(0.5f, 0.5f));
		animthis = Animated::create();
		animthis->addChild(shadow,1);
		animthis->addChild(trashFall,2);
		animthis->setPosition(Utils::getCorrectPosition(1,0));
		animthis->initAnim(1,0,0,0,0.2f,0.1f,0,0,0);
		animthis->startAnimIn();
		this->addChild(animthis,1);*/
	return true;
}

void LoadingNode::replace(float dt) {
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->preloadEffect("bomb2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("buttonClick.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("buttonClick2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("trashFelt.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("missed.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("inGame.mp3");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("backgroundImages.plist");
	lateGoToMainMenu(2);
	//animthis->startAnimOut();
	this->scheduleOnce(schedule_selector(LoadingNode::lateGoToMainMenu), 2.5f);
}

void LoadingNode::onEnter() {
		CCLayer::onEnter();
		//replace(2);
		this->scheduleOnce(schedule_selector(LoadingNode::replace),0.1f);
}
CCScene* LoadingNode::scene() {
	CCScene *scene = CCScene::create();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Backgrounds.plist");
	CCSprite *bg = CCSprite::createWithSpriteFrameName("Background.png");
	Utils::prepareBackgroundImg(bg);
	LoadingNode *tad = LoadingNode::create();
	tad->addChild(bg,-1);
	scene->addChild(tad);
	return scene;
}
void LoadingNode::lateGoToMainMenu(float){
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("inGame.mp3", true);
}
