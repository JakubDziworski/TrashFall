/*
 * MainMenu.cpp
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */
 
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "Trash.h"
#include "Game.h"
#include "Constants.h"
#include "SpriteWithText.h"
#include "AchievmentPopUp.h"
#include "AchvDisplayer.h"
#include "StatsDisplayer.h"
#include "Utils.h"
#define odstepMiedzyPrzyciskami 0.15f

using namespace cocos2d;
using namespace CocosDenshion;


bool MainMenu::init(){
	 if ( !CCLayer::init() )
	    {
	        return false;
	    }
	 this->setKeypadEnabled(true);
	 //sounds
	 doubleClicked=false;
	 usrDef = CCUserDefault::sharedUserDefault();
	 const float posx = CCDirector::sharedDirector()->getWinSize().width/2;
	 const float posy = CCDirector::sharedDirector()->getWinSize().height/2;
	 CCSprite *bg = CCSprite::createWithSpriteFrameName("Background.png");
	 Utils::prepareBackgroundImg(bg);
	 SpriteWithText *playbtnon = SpriteWithText::createWithSpriteFrameNamee("onButton.png","PLAY",ccColor3B{0,0,0});
	 SpriteWithText *playbtnoff = SpriteWithText::createWithSpriteFrameNamee("offButton.png","PLAY",ccColor3B{0,0,0});
	 SpriteWithText *exitbtnoff = SpriteWithText::createWithSpriteFrameNamee("offButton.png","STATS",ccColor3B{0,0,0});
	 SpriteWithText *exitbtnon = SpriteWithText::createWithSpriteFrameNamee("onButton.png","STATS",ccColor3B{0,0,0});
	 SpriteWithText *achievmentsButtonOn = SpriteWithText::createWithSpriteFrameNamee("onButton.png","REWARDS",ccColor3B{0,0,0});
	 SpriteWithText *achievmentsButtonOff = SpriteWithText::createWithSpriteFrameNamee("offButton.png","REWARDS",ccColor3B{0,0,0});
	 CCMenuItemSprite *playBtn = CCMenuItemSprite::create(playbtnon,playbtnoff,this,menu_selector(MainMenu::playGame));
	 CCMenuItemSprite *exitBtn = CCMenuItemSprite::create(exitbtnon,exitbtnoff,this,menu_selector(MainMenu::ShowStats));
	 CCMenuItemSprite *achvBtn = CCMenuItemSprite::create(achievmentsButtonOn,achievmentsButtonOff,this,menu_selector(MainMenu::ShowAchievments));
	 Utils::scaleButton(achvBtn,mainMenubuttonRatio);
	 Utils::scaleButton(playBtn,mainMenubuttonRatio);
	 Utils::scaleButton(exitBtn,mainMenubuttonRatio);
	 menu[0] = CCMenu::create(playBtn, NULL);
	 menu[1] = CCMenu::create(exitBtn, NULL);
	 menu[2] = CCMenu::create(achvBtn, NULL);
			     this->addChild(bg,-1);
			     statsIsRunning=false;
			     statsDisplayer = StatsDisplayer::createe();
			     achvDisplayer = AchvDisplayer::create();
			     this->addChild(statsDisplayer,7);
			     this->addChild(achvDisplayer,6);
			     //latajace w tle gowna
			     genFallingTrash(0.1);
			     this->schedule(schedule_selector(MainMenu::genFallingTrash),4.5);
			     for(int j=0;j<3;j++){
			    	 menuAnim[j] = Animated::create();
			    	 menuAnim[j]->addChild(menu[j],NULL);
			    	 menuAnim[j]->setPosition(Utils::getCorrectPosition(-1,0.2-0.2*j));
			    	 menuAnim[j]->initAnim(-1,0,0.2-0.2*j,0.2-0.2*j,0.2f,-0.1,0,0,0.6,0);
			    	 this->addChild(menuAnim[j],3);
				 } 
				 prepareSoundButt();
			     i=0;
			     this->schedule(schedule_selector(MainMenu::menuAnimSchedulerIN),odstepMiedzyPrzyciskami,3,0);
			     return true;
}
CCScene* MainMenu::scene(){
	 CCScene *scene = CCScene::create();
	 MainMenu *layer;
	 layer = MainMenu::create();
	 scene->addChild(layer,1);
	 return scene;
}


void MainMenu::menuAnimSchedulerIN(float) {
	if(i==4) i=0;
	menuAnim[i]->startAnimIn();
	i++;
}

void MainMenu::menuAnimSchedulerOUT(float) {
	if(i==4) i=0;
	menuAnim[i]->startAnimOut();
	i++;
}

void MainMenu::notdoubleClicked(float) {
	doubleClicked=false;
}

void MainMenu::ShowStats(cocos2d::CCObject* pObject) {
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	this->schedule(schedule_selector(MainMenu::menuAnimSchedulerOUT),odstepMiedzyPrzyciskami,3,0);
	statsDisplayer->show();
	statsIsRunning=true;
	for(int j=0;j<3;j++) menu[j]->setTouchEnabled(false);
}
void MainMenu::playGame(cocos2d::CCObject* pObject){
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	this->unscheduleAllSelectors();
	this->stopAllActions();
	this->schedule(schedule_selector(MainMenu::menuAnimSchedulerOUT),odstepMiedzyPrzyciskami,3,0);
	wyrzucPuszki();
	this->schedule(schedule_selector(MainMenu::waitToReplace),0.1,0,1);
}
void MainMenu::wyrzucPuszki(){
	CCArray *arr = this->getChildren();
	for(int j=0;j<arr->count();j++){
		Trash *trash = dynamic_cast<Trash*>(arr->objectAtIndex(j));
		if(trash){
			trash->stopActionByTag(1);
			trash->runAction(CCMoveTo::create(0.3f,Utils::getCorrectPosition(1.5f,Utils::ratioValue(trash->getPositionY(),true)-0.1f)));
		}
	}
}
void MainMenu::keyBackClicked() {
	if(statsIsRunning){
		SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
		statsDisplayer->hide();
		this->schedule(schedule_selector(MainMenu::menuAnimSchedulerIN),odstepMiedzyPrzyciskami,3,0);
		statsIsRunning=false;
		for(int j=0;j<3;j++) menu[j]->setTouchEnabled(true);
		return;
	}
	if(!doubleClicked){ doubleClicked=true;
		scheduleOnce(schedule_selector(MainMenu::notdoubleClicked),0.5f);
		return;
	}
	CCDirector::sharedDirector()->end();
}
void MainMenu::genFallingTrash(float dt){
	Trash *obj = Trash::create(Utils::getRandValueF(4,8),Utils::getRandValueF(2,4),3);
	this->addChild(obj,Utils::getRandValue(1,3));
}
void MainMenu::ShowAchievments(cocos2d::CCObject* pObject){
	for(int j=0;j<3;j++){
	menuAnim[j]->unscheduleAllSelectors();
	menuAnim[j]->stopAllActions();
	}
	achvDisplayer->start();
}
void MainMenu::disableTouch(){
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	 this->schedule(schedule_selector(MainMenu::menuAnimSchedulerOUT),odstepMiedzyPrzyciskami,3,0);
	this->setTouchEnabled(false);
	this->setKeypadEnabled(false);
	for(int j=0;j<3;j++){
	menu[j]->setTouchEnabled(false);
	menu[j]->setKeypadEnabled(false);
	}
}
void MainMenu::enableTouch(){
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	this->schedule(schedule_selector(MainMenu::menuAnimSchedulerIN),odstepMiedzyPrzyciskami,3,0);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	for(int j=0;j<3;j++){
		menu[j]->setTouchEnabled(true);
		menu[j]->setKeypadEnabled(true);
		}
}
void MainMenu::prepareSoundButt(){
	CCSprite *onsoundSpr = CCSprite::createWithSpriteFrameName("soundOn.png");
	CCSprite *offsoundSpr = CCSprite::createWithSpriteFrameName("soundOff.png");
	CCSprite *onsoundSpr2 = CCSprite::createWithSpriteFrameName("soundOn.png");
	CCSprite *offsoundSpr2 = CCSprite::createWithSpriteFrameName("soundOff.png");

	CCMenuItemSprite *musicOn = CCMenuItemSprite::create(onsoundSpr, offsoundSpr);
	CCMenuItemSprite *musicOff = CCMenuItemSprite::create(offsoundSpr2, onsoundSpr2);
	CCMenuItemToggle *toggle = CCMenuItemToggle::create(this, menu_selector(MainMenu::toggleSound), musicOn, musicOff, NULL);
	CCMenu *turnSound = CCMenu::create(toggle, NULL);
	turnSound->setAnchorPoint(ccp(0,0));
	turnSound->setScale(0.1f*Utils::sreensSize().height/offsoundSpr->getContentSize().height);
	const float marginn = Utils::getcorrectValue(0.1f,true);
	turnSound->setPositionY(Utils::getcorrectValue(1,false)-marginn);
	turnSound->setPositionX(Utils::getcorrectValue(1,true)-marginn);
	menuAnim[3] = Animated::create();
	menuAnim[3]->addChild(turnSound, NULL);
	menuAnim[3]->setPosition(Utils::getCorrectPosition(0, 0.4f));
	menuAnim[3]->initAnim(0, 0, 0.15f, 0, 0.2f, 0, 0.05f, 0, 0.4f,0.06f);
	if (usrDef->getBoolForKey(SOUND_ENABLED, true))
		toggle->setSelectedIndex(0);
	else{
		toggle->setSelectedIndex(1);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
	}
	this->addChild(menuAnim[3],3);
}
void MainMenu::toggleSound(cocos2d::CCObject* pObject){
	bool curr = usrDef->getBoolForKey(SOUND_ENABLED,true);
	curr = !curr;
	usrDef->setBoolForKey(SOUND_ENABLED, curr);
	if (curr){
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
	}
	else{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
	}
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
}

