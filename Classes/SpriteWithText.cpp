/*
 * SpriteWithText.cpp
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

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
		SpriteWithText* nowy = SpriteWithText::create();
		nowy->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName));
		nowy->setText(inputText,color);
		return nowy;
}
void SpriteWithText::setText(const char *inputText,ccColor3B color){
	label = CCLabelTTF::create(inputText,FONT_MAIN,this->getContentSize().height);
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
