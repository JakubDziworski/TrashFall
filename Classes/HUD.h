/*
 * HUD.h
 *
 *  Created on: 24-04-2014
 *      Author: Jakub
 */

#ifndef HUD_H_
#define HUD_H_
#define animationStop 0.5f
#include "Background.h"
#include "cocos2d.h"

class HUD: public cocos2d::CCLayer {
private:
	cocos2d::CCLabelBMFont*  scoreLabel;
	cocos2d::CCLabelBMFont* scoreShadow;
	float dx;
	float extrascale;
	float regularScale;
	float scaleStop;
	bool  reached250;
	bool  stopAnimRed;
	float animationTime;
	bool animate;
	bool extraAnim;
	int decr;
	int score;
	int beginGlobalScore;
	Background *bg;
	cocos2d::CCSprite *effect;
	cocos2d::CCUserDefault *savedData;
public:
			void checkAchivmets(int nomisses);
			void DisplayTrafion(cocos2d::CCPoint,bool);
			void trashFallenEffects();
			void animateTrashFallEffect(float);
			virtual bool init();
			void addToScore(int value,int nomisses);
	 	//	virtual void keyBackClicked();
			LAYER_CREATE_FUNC(HUD);
			void animateText(float dt);
			void animateReset();
			int getScore(){return score;}

};

#endif /* HUD_H_ */
