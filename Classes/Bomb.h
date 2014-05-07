/*
 * Bomb.h
 *
 *  Created on: 06-05-2014
 *      Author: Jakub
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "Trash.h"

class Bomb: public Trash {
private:
	cocos2d::CCParticleSystemQuad *wybuch;
public:
	virtual void checkIfFallen(float dt);
	void WYBUCHSPRITE();
	static Bomb* createe(float speed,float size,float rotTime=rotationDuration);
	virtual void dotkniety();
	virtual bool init();
	LAYER_CREATE_FUNC (Bomb);
};
#endif /* BOMB_H_ */
