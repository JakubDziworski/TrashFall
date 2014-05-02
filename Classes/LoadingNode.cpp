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
#include "MainMenu.h"
using namespace cocos2d;

bool LoadingNode::init() {
	return true;
}
void LoadingNode::onEnter(){
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Buttons.plist");
		SpriteWithText *baseLoadingText = SpriteWithText::createWithSpriteFrameNamee("offButton.png","LOADING",ccColor3B{0,0,0});
		baseLoadingText->setPosition(Utils::getCorrectPosition(0.5,0.5));
		this->addChild(baseLoadingText);
		this->schedule(schedule_selector(LoadingNode::show),0.1,0,0.2);
}
void LoadingNode::show(float dt) {
	CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
}

void LoadingNode::hide() {
}


