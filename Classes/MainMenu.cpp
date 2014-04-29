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
	 SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mainMenu.mp3");
	 SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("inGame.mp3");
	 SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mainMenu.mp3",true);
	 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Buttons.plist");
	 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("trashes.plist");
	 CCSprite *bg = CCSprite::create("Background.png");
	 Utils::prepareBackgroundImg(bg);
	 SpriteWithText *playbtnon = SpriteWithText::createWithSpriteFrameNamee("onButton.png","PLAY",ccColor3B{0,0,0});
	 SpriteWithText *playbtnoff = SpriteWithText::createWithSpriteFrameNamee("offButton.png","PLAY",ccColor3B{0,0,0});
	 SpriteWithText *exitbtnoff = SpriteWithText::createWithSpriteFrameNamee("offButton.png","EXIT",ccColor3B{0,0,0});
	 SpriteWithText *exitbtnon = SpriteWithText::createWithSpriteFrameNamee("onButton.png","EXIT",ccColor3B{0,0,0});
	 SpriteWithText *achievmentsButtonOn = SpriteWithText::createWithSpriteFrameNamee("onButton.png","REWARDS",ccColor3B{0,0,0});
	 SpriteWithText *achievmentsButtonOff = SpriteWithText::createWithSpriteFrameNamee("offButton.png","REWARDS",ccColor3B{0,0,0});
	 CCMenuItemSprite *playBtn = CCMenuItemSprite::create(playbtnon,playbtnoff,this,menu_selector(MainMenu::playGame));
	 CCMenuItemSprite *exitBtn = CCMenuItemSprite::create(exitbtnon,exitbtnoff,this,menu_selector(MainMenu::keyBackClicked));
	 CCMenuItemSprite *achvBtn = CCMenuItemSprite::create(achievmentsButtonOn,achievmentsButtonOff,this,menu_selector(MainMenu::ShowAchievments));
//?
	 Utils::scaleButton(achvBtn,mainMenubuttonRatio);
	 Utils::scaleButton(playBtn,mainMenubuttonRatio);
	 Utils::scaleButton(exitBtn,mainMenubuttonRatio);
	 menu = CCMenu::create(playBtn,exitBtn,achvBtn,NULL);
			     menu->alignItemsVertically();
			    // AchievmentPopUp *pop = AchievmentPopUp::createWithSpriteFrameNameee("offButton.png","offPaused.png","MILESTONE 100",ccColor3B{0,0,0});
			     //pop->activate();
			     this->addChild(menu,3);
			    // this->addChild(pop,4);
			     this->addChild(bg,-1);
			     //latajace w tle gowna
			     genFallingTrash(0.1);
			     this->schedule(schedule_selector(MainMenu::genFallingTrash),4.5);
			     return true;
}
CCScene* MainMenu::scene(){
	 CCScene *scene = CCScene::create();
	 MainMenu *layer;
	 AchvDisplayer *achvDisplayer = AchvDisplayer::create();
	 layer = MainMenu::create();
	 scene->addChild(layer,1);
	 scene->addChild(achvDisplayer,1,TAG_ACHVDISPLAYER);
	 return scene;
}
void MainMenu::playGame(){
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	CCDirector::sharedDirector()->replaceScene(Game::scene());
}

void MainMenu::keyBackClicked() {
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick2.mp3");
	CCDirector::sharedDirector()->end();
}
void MainMenu::genFallingTrash(float dt){
	Trash *obj = Trash::create(Utils::getRandValueF(4,8),Utils::getRandValueF(2,4),3);
	this->addChild(obj,Utils::getRandValue(1,3));
}
void MainMenu::ShowAchievments(){
	Utils::getAchvDisplayer()->start();
}
void MainMenu::disableTouch(){
	this->setTouchEnabled(false);
	this->setKeypadEnabled(false);
	menu->setTouchEnabled(false);
	menu->setKeypadEnabled(false);
	CCLOG("TOUCH DISABLED");
}
void MainMenu::enableTouch(){
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	menu->setTouchEnabled(true);
	CCLOG("TOUCH ENABLED");
}
