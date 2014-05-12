#include "AppDelegate.h"
#include "MainMenu.h"
#include "LoadingNode.h"
#include "SimpleAudioEngine.h"
#include "Pause.h"
#include "Game.h"
#include "GameOver.h"
#include "Constants.h"
using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
	srand(time(NULL));

#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	CCEGLView::sharedOpenGLView().setDesignResolutionSize(320, 480);
#endif
	
    CCDirector *pDirector = CCDirector::sharedDirector();

    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *scena = LoadingNode::scene();
    // run
    pDirector->runWithScene(scena);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
	Pause *paus = Utils::getPause();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	GameOver *g = Utils::getGameOver();
	if (g && paus){
		if (paus->isPaused() == false){
			if(g->isVisiblee() == false)
			paus->toggle(NULL);
		}
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    Pause *paus = Utils::getPause();
	GameOver *g = Utils::getGameOver();
	if (paus && g){
		if (paus->isPaused()){
			return;
		}
		else if(g->isVisiblee() == false) paus->toggle(NULL);
		else SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
