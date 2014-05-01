
#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "Utils.h"
#include "StatsDisplayer.h"
#include "ITouchDisablable.h"
#include "Animated.h"
#include "cocos2d.h"

class MainMenu : public ITouchDisablable {
private:
	cocos2d::CCMenu *menu;
	AchvDisplayer *achvDisplayer;
	StatsDisplayer *statsDisplayer;
	Animated *menuAnimatorParent;
	bool statsIsRunning;
	bool resumed[2];
public:
	void tick();
	virtual bool init();
	virtual void keyBackClicked();
	static cocos2d::CCScene* scene();
	void playGame();
	void exitGame();
	void genFallingTrash(float dt);
	void ShowAchievments();
	virtual void disableTouch();
	virtual void enableTouch();
	void ShowStats();
	LAYER_CREATE_FUNC(MainMenu);
};

#endif /* MAINMENU_H_ */
