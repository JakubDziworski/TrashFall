/*
 * Utils.cpp
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */
 
#include "Utils.h"
#include "Trash.h"
#include "AchvDisplayer.h"
#include <string.h>
#include "Constants.h"
#include <math.h>

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
	return rand()%((int)(0.9f*Utils::sreensSize().width))+Utils::sreensSize().width*0.05f;
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
			break;
		}
	}
}
int Utils::getdifficulty(float time){
	for (int i = 0; i < diffNumber; i++){
		if (time >= difficulties[i].timeElapse) return i;
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
	unsigned posbeg = input.find("_");
	unsigned posend = input.find(",")-posbeg-1;
	return input.substr(posbeg+1,posend);
}
std::string Utils::getAchvDescr(std::string input){
	unsigned pos = input.find(",");
	return input.substr(pos+1);
}
std::string Utils::getAchvTag(std::string input){
	unsigned pos = input.find("_");
	return input.substr(0,pos);
}

float Utils::ratioValue(float float1,bool h) {
	if(h)
	return float1/Utils::sreensSize().height;
	return float1/Utils::sreensSize().width;
}
std::string Utils::losujTIP(){
	int los = Utils::getRandValue(0, 3);
	std::string toReturn = "TIP:";
	switch (los)
	{
	case 0:
		return toReturn + "SWIPE INSTEAD OF TAPPING!\nTHIS WILL INCREASE YOUR\nCHANCE TO GRAB TRASHES!";
		break;
	case 1:
		return toReturn + "KEEP YOUR HAND LOW!\nYOU WILL HAVE MORE TIME\n TO CATCH TRASHES!";
		break;
	case 2:
		return toReturn + "CHECK OUT 'REWARDS' IN\nMAIN MENU! COLLECT THEM ALL!";
		break;
	case 3:
		return toReturn + "CHECK OUT STATISTICS\nIN MAIN MENU!";
		break;
	default:
		return "CHECK OUT STATISTICS\nIN MAIN MENU!";
		break;
	}
}
