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
	const float sizeX = input->getContentSize().width;
	const float sizeY = input->getContentSize().height;
	if (sizeY > sizeX)
		return -(sizeY / 1.5f);
	else
		return -(sizeX / 1.5f);
}

float Utils::getBeginHeight(cocos2d::CCSprite *input){
	const float sizeX = input->getContentSize().width;
	const float sizeY = input->getContentSize().height;
	if (sizeY > sizeX)
		return Utils::sreensSize().height+sizeY/2.0f;
	else
		return Utils::sreensSize().height+sizeX/2.0f;
}
float Utils::cleanView(CCLayer *inputLayer){
	int j=0;
	CCArray* array = inputLayer->getChildren();
	for(int i = 0; i < array->count(); i++) {
	    		Trash *trash = (Trash *)array->objectAtIndex(i);
	    		if(!Utils::isVisible(trash)){
	    			inputLayer->removeChild(trash,true);
	    			j++;
	    		}
	}
	CCLOG("clened up %d trashes.Remainig Trahes: %d",j,array->count());
}
bool Utils::isVisible(CCSprite *inputSprite){
	if(!dynamic_cast<Trash*>(inputSprite)) return true;
	if(inputSprite->getPositionY() < 0) return false;
	else return true;
}
void Utils::setDifficulty(float& speed,float timeEl,float& atO){
	for(int i=0;i<diffNumber;i++){
		CCLOG("timenormal = %.2f\n, timeexpect = %.2f\n",timeEl,difficulties[i].timeElapse);
		if(timeEl >= difficulties[i].timeElapse){
			CCLOG("Chosen level %d",i);
			speed = difficulties[i].speed;
			atO = difficulties[i].atOnce;
			break;
		}

	}
}

