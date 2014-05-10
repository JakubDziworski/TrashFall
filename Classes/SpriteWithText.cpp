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
	label = CCLabelBMFont::create(inputText,"font.fnt",-1,kCCTextAlignmentCenter,ccp(0,0));
	fontsize = ((CCSprite*) label->getChildByTag(0))->getContentSize().height;
	label->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - fontsize*0.08f);
	label->setScale(0.65f*this->getContentSize().height*this->getScale() / fontsize);
	label->setColor(color);
	this->addChild(label);
}
void SpriteWithText::setTextSize(float wielkosc){
	label->setScale(0.65f*wielkosc*this->getContentSize().height*this->getScale() / fontsize);
	label->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - wielkosc*fontsize*0.08f);
}
void SpriteWithText::setTextString(const char *txt){
	label->setString(txt);
}

void SpriteWithText::setTextMaxInLine(float amount)
{
	label->setWidth(amount);
}
