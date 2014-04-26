/*
 * Trash.h
 *
 *  Created on: 23-04-2014
 *      Author: Jakub
 */

#ifndef TRASH_H_
#define TRASH_H_


#include "cocos2d.h"
#include "Constants.h"

class Trash: public cocos2d::CCSprite {
private:
	float size;
	float speed;
	float posx;
	float endposY;
	bool  checkFallen;
	cocos2d::CCSize scrSize;
public:
	void setCheckFallen(bool input);
	virtual bool init();
	void checkIfFallen(float dt);
	static Trash* create(float speed,float size,float rotTime=rotationDuration);
	LAYER_CREATE_FUNC (Trash);
};

#endif /* TRASH_H_ */
