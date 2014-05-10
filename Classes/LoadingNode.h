/*
 * LoadingNode.h
 *
 *  Created on: 01-05-2014
 *      Author: Jakub
 */

#ifndef LOADINGNODE_H_
#define LOADINGNODE_H_

#include "Animated.h"
#include "cocos2d.h"

class LoadingNode: public cocos2d::CCLayer {
public:
	bool init();
	void replace(float);
	void onEnter();
	static cocos2d::CCScene* scene();
	//static LoadingNode* create();
	LAYER_CREATE_FUNC(LoadingNode);
	void lateGoToMainMenu(float);
	Animated *animthis;
};

#endif /* LOADINGNODE_H_ */
