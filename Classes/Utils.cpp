/*
 * Utils.cpp
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Utils.h"
#include "Trash.h"

using namespace cocos2d;
CCSize Utils::sreensSize(){
	return CCDirector::sharedDirector()->getWinSize();
}
void Utils::scaleToFitScreen(CCSprite* input){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float dX = size.width/input->getContentSize().width;
	float dY = size.height/input->getContentSize().height;
	input->setScaleX(dX);
	input->setScaleY(dY);
}
void Utils::prepareBackgroundImg(CCSprite* input){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	input->setPosition(ccp(size.width/2,size.height/2));
	Utils::scaleToFitScreen(input);
}
cocos2d::CCSpriteFrame* Utils::getRandomTrash(){
	const int trashID = rand()%(Utils::trashAmount)+1;
	CCString *trashName = CCString::createWithFormat("trash%d.png",trashID);
	CCLOG(trashName->getCString());
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(trashName->getCString());
}
float Utils::getRandomXPos(){
	return rand()%((int)Utils::sreensSize().width+1);
}
int Utils::getRandValue(int min,int max){
	return rand()%(max-min+1)+min;
}
float Utils::getRandValueF(int min,int max){
	const float mnoznik= 1000;
	max*=mnoznik;
	min*=mnoznik;
	float x= (float)(rand()%(max-min+1)+min)/mnoznik;
	CCString *str = CCString::stringWithFormat("%.2f\n",x);
	CCLOG(str->getCString());
	return x;
}


