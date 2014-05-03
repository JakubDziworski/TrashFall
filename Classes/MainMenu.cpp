/*
 * MainMenu.cpp
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */
#define COCOS2D_DEBUG 2
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "Trash.h"
#include "Game.h"
#include "Constants.h"
#include "SpriteWithText.h"
#include "AchievmentPopUp.h"
#include "AchvDisplayer.h"
#include "StatsDisplayer.h"
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
	 const float posx = CCDirector::sharedDirector()->getWinSize().width/2;
	 const float posy = CCDirector::sharedDirector()->getWinSize().height/2;
	 SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	 SimpleAudioEngine::sharedEngine()->preloadEffect("buttonClick.wav");
	 SimpleAudioEngine::sharedEngine()->preloadEffect("buttonClick2.mp3");
	 SimpleAudioEngine::sharedEngine()->preloadEffect("trashFelt.mp3");
	 SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mainMenu.mp3");
	 SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("inGame.mp3");
	 SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mainMenu.mp3",true);
	 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Buttons.plist");
	 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("trashes.plist");
	 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("backgroundImages.plist");
	 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Backgrounds.plist");
	 CCSprite *bg = CCSprite::create("Background.png");
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
			    	 this->addChild(menuAnim[j],2);
			     }
			     i=0;
			     this->schedule(schedule_selector(MainMenu::menuAnimSchedulerIN),odstepMiedzyPrzyciskami,2,0);
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
	if(i==3) i=0;
	menuAnim[i]->startAnimIn();
	i++;
}

void MainMenu::menuAnimSchedulerOUT(float) {
	if(i==3) i=0;
	menuAnim[i]->startAnimOut();
	i++;
}

void MainMenu::ShowStats() {
	this->schedule(schedule_selector(MainMenu::menuAnimSchedulerOUT),odstepMiedzyPrzyciskami,2,0);
	statsDisplayer->show();
	statsIsRunning=true;
	for(int j=0;j<3;j++) menu[j]->setTouchEnabled(false);
}
void MainMenu::playGame(){
	this->schedule(schedule_selector(MainMenu::menuAnimSchedulerOUT),odstepMiedzyPrzyciskami,2,0);
	wyrzucPuszki();
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	this->schedule(schedule_selector(MainMenu::waitToReplace),0.1,0,0.8f);
}
void MainMenu::wyrzucPuszki(){
	CCArray *arr = this->getChildren();
	for(int j=0;j<arr->count();j++){
		Trash *trash = dynamic_cast<Trash*>(arr->objectAtIndex(i));
		if(trash){
			trash->stopActionByTag(1);
			trash->runAction(CCMoveTo::create(0.3f,Utils::getCorrectPosition(1.5f,Utils::ratioValue(trash->getPositionY(),true)-0.1f)));
		}
	}
}
void MainMenu::keyBackClicked() {
	if(statsIsRunning){
		statsDisplayer->hide();
		this->schedule(schedule_selector(MainMenu::menuAnimSchedulerIN),odstepMiedzyPrzyciskami,2,0);
		statsIsRunning=false;
		for(int j=0;j<3;j++) menu[j]->setTouchEnabled(true);
		return;
	}
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick2.mp3");
	CCDirector::sharedDirector()->end();
}
void MainMenu::genFallingTrash(float dt){
	Trash *obj = Trash::create(Utils::getRandValueF(4,8),Utils::getRandValueF(2,4),3);
	this->addChild(obj,Utils::getRandValue(1,3));
}
void MainMenu::ShowAchievments(){
	for(int j=0;j<3;j++){
	menuAnim[j]->unscheduleAllSelectors();
	menuAnim[j]->stopAllActions();
	}
	achvDisplayer->start();
}
void MainMenu::disableTouch(){
	 this->schedule(schedule_selector(MainMenu::menuAnimSchedulerOUT),odstepMiedzyPrzyciskami,2,0);
	CCLOG("TOUCH DISABLED");
	this->setTouchEnabled(false);
	this->setKeypadEnabled(false);
	for(int j=0;j<3;j++){
	menu[j]->setTouchEnabled(false);
	menu[j]->setKeypadEnabled(false);
	}
}
void MainMenu::enableTouch(){
	this->schedule(schedule_selector(MainMenu::menuAnimSchedulerIN),odstepMiedzyPrzyciskami,2,0);
	CCLOG("TOUCH ENABLED");
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	for(int j=0;j<3;j++){
		menu[j]->setTouchEnabled(true);
		menu[j]->setKeypadEnabled(true);
		}
}

