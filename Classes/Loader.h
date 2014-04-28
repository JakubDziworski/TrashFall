/*
 * Loader.h
 *
 *  Created on: 27-04-2014
 *      Author: Jakub
 */

#ifndef LOADER_H_
#define LOADER_H_

#include "cocos2d.h"

class Loader: public cocos2d::CCLayer {
private:
 	 cocos2d::CCDictionary *achivList;
public:
	virtual bool init();
	LAYER_CREATE_FUNC(Loader);
};

