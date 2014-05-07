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
protected	:
	float size;
	float speed;
	float posx;
	float endposY;
	bool  autoCheckMissesPoints;
	cocos2d::CCSize scrSize;
public:
	void setAutoCheckMissesPoints(bool input);
	virtual bool init();
	virtual void checkIfFallen(float dt);
	virtual void dotkniety();
	static Trash* create(float speed,float size,float rotTime=rotationDuration);
	LAYER_CREATE_FUNC (Trash);
};

#endif /* TRASH_H_ */
