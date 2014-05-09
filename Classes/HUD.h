/*
 * HUD.h
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */

#ifndef HUD_H_
#define HUD_H_
#include "Background.h"
#include "cocos2d.h"

class HUD: public cocos2d::CCLayer {
private:
	cocos2d::CCLabelBMFont*  scoreLabel;
	cocos2d::CCLabelBMFont* scoreShadow;
	int score;
	int beginGlobalScore;
	Background *bg;
	cocos2d::CCSprite *effect;
	cocos2d::CCUserDefault *savedData;
	float regularScale;
public:
			void checkAchivmets(int nomisses);
			void DisplayTrafion(cocos2d::CCPoint,bool);
			void trashFallenEffects();
			virtual bool init();
			void addToScore(int value,int nomisses);
			LAYER_CREATE_FUNC(HUD);
			int getScore(){return score;}
			void hideRedEffect(cocos2d::CCNode*);
			void deleteMissed(cocos2d::CCNode*);

};

#endif /* HUD_H_ */
