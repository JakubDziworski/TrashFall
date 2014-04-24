/*
 * Utils.cpp
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Utils.h"
#include "Trash.h"
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
		return -(sizeY / 1.5f);
	else
		return -(sizeX / 1.5f);
}

float Utils::getBeginHeight(cocos2d::CCSprite *input){
	const float sizeX = input->getContentSize().width*input->getScale();
	const float sizeY = input->getContentSize().height*input->getScale();
	if (sizeY > sizeX)
		return Utils::sreensSize().height+sizeY/2.0f;
	else
		return Utils::sreensSize().height+sizeX/2.0f;
}
void Utils::cleanView(CCLayer *inputLayer,bool checkForTrashes){
	int j=0;
	CCArray* array = inputLayer->getChildren();
	for(int i = 0; i < array->count(); i++) {
	    		Trash *trash = (Trash *)array->objectAtIndex(i);
	    		if(!Utils::isVisible(trash,checkForTrashes)){
	    			inputLayer->removeChild(trash,true);
	    			j++;
	    		}
	}
	CCLOG("clened up %d trashes.Remainig Trahes: %d",j,array->count());
}
bool Utils::isVisible(CCSprite *inputSprite,bool checkForTrashes){
	if(checkForTrashes)
	if(!dynamic_cast<Trash*>(inputSprite)) return true;
	if(inputSprite->getPositionY() < 0) return false;
	else return true;
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
void Utils::scaleSprite(CCSprite *sprite,float ratioo,float additional,bool wid){
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
void Utils::setSpritePositionRelativetoMyPhone(CCSprite *sprite,float Xpos,float Ypos){
	const CCSize tmpSize = Utils::sreensSize();
	CCLOG("screensize = %.2f\n",tmpSize.width);
	const float scrnw = tmpSize.width;
	const float scrnh = tmpSize.height;
	const float wRatio = Xpos/768.0;
	const float hRatio = Ypos/1184.0;
	sprite->setPositionX(wRatio*scrnw);
	sprite->setPositionY(hRatio*scrnh);
}
