/*
 * SpriteWithText.cpp

 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "SpriteWithText.h"
#include "Utils.h"
#include "Constants.h"

using namespace cocos2d;

bool SpriteWithText::init(){
	if (!CCSprite::init()) {
				return false;
			}
	return true;
}
SpriteWithText* SpriteWithText::createWithSpriteFrameNamee(const char *pszSpriteFrameName,const char *inputText,ccColor3B color) {
		CCLOG("working");
		SpriteWithText* nowy = SpriteWithText::create();
		CCLOG("PRZED SET DISPLAY");
		nowy->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName));
		CCLOG("PO SET DISPLAY");
		nowy->setText(inputText,color);
		CCLOG("PO SETtext");
		return nowy;
}
void SpriteWithText::setText(const char *inputText,ccColor3B color){

	CCLOG("stworzenie labela");
	label = CCLabelTTF::create(inputText,FONT_MAIN,15);
	CCLOG("po stworzeniu labela");
	//Utils::getScaledFontSize(this->getContentSize().height/2)
	label->setColor(color);
	label->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
	this->addChild(label);
}
void SpriteWithText::setachivmentStyle(const char *text){
	label->setFontSize(this->getContentSize().height/4);
	label->setPositionX(label->getPositionX()+this->getContentSize().width/8*this->getScaleX());
	label->setString(text);
}
