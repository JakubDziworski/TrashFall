/*
 * SpriteWithText.h
 *
 *  Created on: 25-04-2014
 *      Author: Jakub
 */

#ifndef SPRITEWITHTEXT_H_
#define SPRITEWITHTEXT_H_

#include "cocos2d.h"

class SpriteWithText: public cocos2d::CCSprite {
	cocos2d::CCLabelBMFont *label;
	float fontsize;
public:
	virtual bool init();
	static SpriteWithText* createWithSpriteFrameNamee(const char *pszSpriteFrameName,const char *inputText,cocos2d::ccColor3B color);
	void setTextSize(float);
	void setText(const char *inputText,cocos2d::ccColor3B color);
	void setTextString(const char *txt);
	LAYER_CREATE_FUNC (SpriteWithText);
};

#endif /* SPRITEWITHTEXT_H_ */
