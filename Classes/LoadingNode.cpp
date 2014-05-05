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
	CCLOG("wywolano init");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Buttons.plist");
	SpriteWithText *baseLoadingText = SpriteWithText::createWithSpriteFrameNamee("offButton.png","LOADING", ccColor3B { 0, 0, 0 });
		baseLoadingText->setPosition(Utils::getCorrectPosition(0.5, 0.5));
		Animated *animthis = Animated::create();
		animthis->addChild(baseLoadingText);
		animthis->setPosition(Utils::getCorrectPosition(1,0));
		animthis->initAnim(1,0,0,0,0.2f,0.1f,0,0,0);
		animthis->startAnimIn();
		this->addChild(animthis,1);
	return true;
}

void LoadingNode::replace(float dt) {
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->preloadEffect("buttonClick.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("buttonClick2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("trashFelt.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("missed.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("inGame.mp3");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"backgroundImages.plist");
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("inGame.mp3",true);
}

void LoadingNode::onEnter() {
		CCLayer::onEnter();
		this->scheduleOnce(schedule_selector(LoadingNode::replace),0.45f);
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



