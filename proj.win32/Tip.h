#pragma once
#include "SpriteWithText.h"
#include "cocos2d.h"
#include <string>
class Tip :public SpriteWithText
{
public:
	virtual bool init();
	std::string losuj();
};

