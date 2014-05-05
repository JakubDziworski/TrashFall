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
		SpriteWithText* nowy = SpriteWithText::create();
		nowy->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName));
		nowy->setText(inputText,color);
		return nowy;
}
void SpriteWithText::setText(const char *inputText,ccColor3B color){
	label = CCLabelTTF::create(inputText,FONT_MAIN,this->getContentSize().height);
	label->setColor(color);
	label->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
	this->addChild(label);

}
void SpriteWithText::setTextSize(float wielkosc){
	label->setFontSize(wielkosc);
}
void SpriteWithText::setTextString(const char *txt){
	label->setString(txt);
}
