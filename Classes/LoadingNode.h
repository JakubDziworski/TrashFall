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

class LoadingNode: public cocos2d::CCScene {
public:
	bool init();
	void onEnter();
	void show(float);
	void hide();
	SCENE_CREATE_FUNC(LoadingNode);
};

#endif /* LOADINGNODE_H_ */
