/*
 * Background.cpp
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "Background.h"
#include "Utils.h"
#include "Constants.h"
#include "SpriteWithText.h"
using namespace cocos2d;
bool Background::init(){
	if (!CCLayer::init()) {
			return false;
		}
	maxmovementChmurki = Utils::getcorrectValue(0.03,true);
	timeToWait=0;
	currentTim=0;
	beginAnimTime = timeToShowBGItemz;
	//initsprites
	sun = CCSprite::createWithSpriteFrameName("Sun.png");
	sunHurt = CCSprite::createWithSpriteFrameName("SunHurt.png");
	sunHurt->setOpacity(0);
	chmurka[0] = CCSprite::createWithSpriteFrameName("chmurka1.png");
	chmurka[1] = CCSprite::createWithSpriteFrameName("chmurka2.png");
	chmurka[2] = CCSprite::createWithSpriteFrameName("chmurka3.png");
	buzka = CCSprite::createWithSpriteFrameName("sunFace_00001.png");
	//beginpos
	buzka->setPosition(Utils::getCorrectPosition(-0.4, 0.8));
	sunHurt->setPosition(Utils::getCorrectPosition(-0.4, 0.8));
	sun->setPosition(Utils::getCorrectPosition(-0.4, 0.8));
	chmurka[0]->setPosition(Utils::getCorrectPosition(1.6, 0.70));
	chmurka[1]->setPosition(Utils::getCorrectPosition(1.5, 0.73));
	chmurka[2]->setPosition(Utils::getCorrectPosition(1.4, 0.9));
	//animatecreate
	sunMover = Animated::create();
	for (int i = 0; i < 3; i++)
	chmurkaMover[i] = Animated::create();
	//aniamteinitAnim
	chmurkaMover[0]->initAnim(0, -0.8f, 0, 0, 0.4f, 0.05f, 0, 0, 0.12,0.12f);
	chmurkaMover[1]->initAnim(0, -0.97, 0, 0, 0.4f, 0.05f, 0, 0, 0, 0.3f);
	chmurkaMover[2]->initAnim(0, -0.66, 0, 0, 0.4f, 0.05f, 0, 0, 0.4f,0);
	sunMover->initAnim(0, 0.66f,0,0,0.4f,-0.06f,0,0,0.6f);
	//addchild
	sunMover->addChild(sun,0);
	sunMover->addChild(buzka,2);
	sunMover->addChild(sunHurt,1);
	for (int i = 0; i < 3; i++) chmurkaMover[i]->addChild(chmurka[i]);

	CCSprite *bg = CCSprite::createWithSpriteFrameName("Background.png");
	Utils::prepareBackgroundImg(bg);
	CCLOG("ENDBG INIT");
	Utils::scaleSprite(chmurka[0],3.76f,1,true);
	Utils::scaleSprite(chmurka[1],4.9f,1,true);
	Utils::scaleSprite(chmurka[2],2.35f,1,true);
	Utils::scaleSprite(sun,3.4,1,false);
	Utils::scaleSprite(sunHurt, 3.4, 1, false);
	Utils::scaleSprite(buzka,3.4,1,false);
	this->addChild(bg,-1);
	for (int i = 0; i < 3; i++)
	this->addChild(chmurkaMover[i], 0);
	this->addChild(sunMover, 0);
	CCRepeatForever *repeat = CCRepeatForever::create(
				CCRotateBy::create(rotationDuration, 15));
	CCRepeatForever *repeat2 = CCRepeatForever::create(
		CCRotateBy::create(rotationDuration, 15));
	sun->runAction(repeat);
	sunHurt->runAction(repeat2);
	this->schedule(schedule_selector(Background::moveChmurkiRandom),1);
	sunMover->startAnimIn();
	for (int i = 0; i < 3; i++) chmurkaMover[i]->startAnimIn();

	return true;
}
void Background::moveChmurkiRandom(float dt){
	currentTim += dt;
	if(currentTim<beginAnimTime) return;
	const int i =((int)currentTim)%3;
	float posX, posY;
	CCLOG("%d triggered",i);
	if (chmurka[i]->getPositionX() >= orignalchmuraPos[i].x)
		posX = chmurka[i]->getPositionX() + Utils::getRandValue(-maxmovementChmurki, 0);
	else
		posX = chmurka[i]->getPositionX() + Utils::getRandValue(0, maxmovementChmurki);
	if (chmurka[i]->getPositionY() >= orignalchmuraPos[i].y)
		posY = chmurka[i]->getPositionY() + Utils::getRandValue(-maxmovementChmurki, 0);
	else
		posY = chmurka[i]->getPositionY() + Utils::getRandValue(0, maxmovementChmurki);
	chmurka[i]->runAction(CCMoveTo::create(3, ccp(posX,posY)));
}

void Background::updateMisses(int missesAmount){
	CCLOG("sunFace_%05d.png",missesAmount);
	CCFadeIn *fadeIn = CCFadeIn::create(0.2f);
	CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
	sunHurt->runAction(CCSequence::create(fadeIn, fadeOut, NULL));
	CCString *name = CCString::createWithFormat("sunFace_%05d.png",missesAmount);
	buzka->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
}

void Background::wywalChmuriIslonce(){
	Utils::getGame()->wyrzucPuszki();
	for (int i = 0; i < 3;i++)
	chmurkaMover[i]->startAnimOut();
	sunMover->startAnimOut();
	Utils::getHUD()->hideScore();
}