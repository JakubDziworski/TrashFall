/*
 * Utils.cpp
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Utils.h"
#include "Trash.h"
#include "AchvDisplayer.h"
#include <string.h>
#include "Constants.h"

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
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(trashName->getCString());
}
float Utils::getRandomXPos(){
	return rand()%((int)Utils::sreensSize().width+1);
}
int Utils::getRandValue(int min,int max){
	return rand()%(max-min+1)+min;
}
float Utils::getRandValueF(float a,float b){
	float random = ((float) rand()) / (float) RAND_MAX;
	    float diff = b - a;
	    float r = random * diff;
	    return a + r;
}
float Utils::getEndHeight(cocos2d::CCSprite *input){
	const float sizeX = input->getContentSize().width*input->getScale();
	const float sizeY = input->getContentSize().height*input->getScale();
	if (sizeY > sizeX)
		return -(sizeY/2 );
	else
		return -(sizeX /2);
}

float Utils::getBeginHeight(cocos2d::CCSprite *input){
	const float sizeX = input->getContentSize().width*input->getScale();
	const float sizeY = input->getContentSize().height*input->getScale();
	if (sizeY > sizeX)
		return Utils::sreensSize().height+sizeY/2.0f;
	else
		return Utils::sreensSize().height+sizeX/2.0f;
}
void Utils::setDifficulty(float& speed,float timeEl,float& atO){
	for(int i=0;i<diffNumber;i++){
		if(timeEl >= difficulties[i].timeElapse){
			speed = difficulties[i].speed;
			atO = difficulties[i].atOnce;
			CCLOG("difficulty : %d",i);
			break;
		}
	}
}
HUD* Utils::getHUD(){
	if(CCDirector::sharedDirector()->getRunningScene()->getTag() == TAG_GAMESCENE)
	return (HUD*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_HUD);
	else return NULL;
}
Background* Utils::getBackground(){
	if(CCDirector::sharedDirector()->getRunningScene()->getTag() == TAG_GAMESCENE)
		return (Background*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_BACKGROUND);
		else return NULL;
}
Game* Utils::getGame(){
	if(CCDirector::sharedDirector()->getRunningScene()->getTag() == TAG_GAMESCENE)
			return (Game*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_GAMELayer);
			else return NULL;
}
Pause* Utils::getPause(){
	if(CCDirector::sharedDirector()->getRunningScene()->getTag() == TAG_GAMESCENE)
			return (Pause*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_PAUSE);
			else return NULL;
}
GameOver* Utils::getGameOver(){
	if(CCDirector::sharedDirector()->getRunningScene()->getTag() == TAG_GAMESCENE)
				return (GameOver*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_GAMEOVER);
				else return NULL;
}
AchvDisplayer* Utils::getAchvDisplayer(){
				return (AchvDisplayer*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_ACHVDISPLAYER);
}
void Utils::scaleSprite(CCNode *sprite,float ratioo,float additional,bool wid){
	float expectedRatio = Utils::sreensSize().height/ratioo;
	float mnoznik  = expectedRatio/sprite->getContentSize().height;
	if(wid){
		expectedRatio = Utils::sreensSize().width/ratioo;
		mnoznik = expectedRatio/sprite->getContentSize().width;
	}
	sprite->setScale(mnoznik*additional);
}
void Utils::scaleButton(CCMenuItemSprite *sprite,float ratioo){
	const float expectedRatio = Utils::sreensSize().width/ratioo;
	const float mnoznik = expectedRatio/sprite->getContentSize().width;
	sprite->setScale(mnoznik);
}
int Utils::getScaledFontSize(int fontsize){
	return fontsize*Utils::sreensSize().width/768;
}
CCPoint Utils::getCorrectPosition(float xRatio,float yRatio){
	return ccp(CCDirector::sharedDirector()->getWinSize().width * xRatio,
			CCDirector::sharedDirector()->getWinSize().height * yRatio);
}
float Utils::getcorrectValue(float input,bool width){
	if(width) return input*CCDirector::sharedDirector()->getWinSize().width;
	return input*CCDirector::sharedDirector()->getWinSize().height;
}
std::string Utils::getAchvName(std::string input){
	unsigned pos = input.find(",");
	return input.substr(0,pos);
}
std::string Utils::getAchvDescr(std::string input){
	unsigned pos = input.find(",");
	return input.substr(pos+1);
}
std::string Utils::getAchvTag(std::string input){
	return input.substr(0,3);
}
