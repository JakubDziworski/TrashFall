
#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "Utils.h"
#include "cocos2d.h"

class MainMenu : public cocos2d::CCLayer {
public:
	void tick();
	virtual bool init();
	virtual void keyBackClicked();
	static cocos2d::CCScene* scene();
	void playGame();
	void exitGame();
	void genFallingTrash(float dt);
	LAYER_CREATE_FUNC(MainMenu);
};

#endif /* MAINMENU_H_ */
