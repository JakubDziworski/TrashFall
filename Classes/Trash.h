/*
 * Trash.h
 *
 *  Created on: 23-04-2014
 *      Author: Jakub
 */

#ifndef TRASH_H_
#define TRASH_H_

#include "cocos2d.h"

class Trash: public cocos2d::CCSprite {
private:
	float size;
	float speed;
	float posx;
	cocos2d::CCSize scrSize;
public:
	virtual bool init();
	static Trash* create(float speed,float size);
//	void stop();
//	void reset();
//	void start();
//	void wasTapped();
//	bool getIsUp();
//	void stopEarly();
	LAYER_CREATE_FUNC (Trash);
};

#endif /* TRASH_H_ */
