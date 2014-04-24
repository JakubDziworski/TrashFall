/*
 * MainMenu.cpp
 *
 *  Created on: 22-04-2014
 *      Author: Jakub
 */
//#define COCOS2D_DEBUG 2
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "Trash.h"
#include "Game.h"

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
	 CCSprite *playbtnoff = CCSprite::createWithSpriteFrameName("play_of.png");
	 CCSprite *playbtnon = CCSprite::createWithSpriteFrameName("play_on.png");
	 CCSprite *exitbtnon = CCSprite::createWithSpriteFrameName("exit_on.png");
	 CCSprite *exitbtnoff = CCSprite::createWithSpriteFrameName("exit_off.png");
	 CCMenuItemSprite *playBtn = CCMenuItemSprite::create(playbtnon,playbtnoff,this,menu_selector(MainMenu::playGame));
	 CCMenuItemSprite *exitBtn = CCMenuItemSprite::create(exitbtnon,exitbtnoff,this,menu_selector(MainMenu::keyBackClicked));
	 CCMenu *menu = CCMenu::create(playBtn,exitBtn,NULL);
	 	 	 	 menu->alignItemsVertically();
			     menu->setPosition(ccp(posx,posy));
			     this->addChild(bg,0);
			     this->addChild(menu,3);
			     //latajace w tle gowna
			     this->schedule(schedule_selector(MainMenu::genFallingTrash),1);
			     this->schedule(schedule_selector(MainMenu::cleaner),10);
			     return true;
}
CCScene* MainMenu::scene(){
	 CCScene *scene = CCScene::create();
	 MainMenu *layer;
	 layer = MainMenu::create();
	 scene->addChild(layer);
	 return scene;
}
void MainMenu::playGame(){
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick.wav");
	Utils::cleanView(this);
	CCDirector::sharedDirector()->replaceScene(Game::scene());
}

void MainMenu::keyBackClicked() {
	SimpleAudioEngine::sharedEngine()->playEffect("buttonClick2.mp3");
//CCDirector::sharedDirector()->end();
}
void MainMenu::genFallingTrash(float dt){
	CCLOG("time = %.2f\n",dt);
	Trash *obj = Trash::create(Utils::getRandValueF(3,6),Utils::getRandValueF(0,4));
	this->addChild(obj,Utils::getRandValue(1,3));
}
void MainMenu::cleaner(float dt){
	Utils::cleanView(this);
}
