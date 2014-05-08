
#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "Utils.h"
#include "StatsDisplayer.h"
#include "ITouchDisablable.h"
#include "Animated.h"
#include "Game.h"
#include "cocos2d.h"

class MainMenu : public ITouchDisablable {
private:
	cocos2d::CCMenu *menu[3];
	AchvDisplayer *achvDisplayer;
	StatsDisplayer *statsDisplayer;
	Animated *menuAnim[3];
	void menuAnimSchedulerIN(float);
	void menuAnimSchedulerOUT(float);
	bool statsIsRunning;
	int i;
	bool resumed[2];
	bool doubleClicked;
public:
	void tick();
	void notdoubleClicked(float);
	virtual bool init();
	void loadingPopDown();
	virtual void keyBackClicked();
	static cocos2d::CCScene* scene();
	void playGame(cocos2d::CCObject* pObject);
	void waitToReplace(float dt){
		cocos2d::CCDirector::sharedDirector()->replaceScene(Game::scene());
	}
	void wyrzucPuszki();
	void exitGame();
	void genFallingTrash(float dt);
	void ShowAchievments(cocos2d::CCObject* pObject);
	virtual void disableTouch();
	virtual void enableTouch();
	void ShowStats(cocos2d::CCObject* pObject);
	LAYER_CREATE_FUNC(MainMenu);
};

#endif /* MAINMENU_H_ */
