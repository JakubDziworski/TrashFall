/*
 * ITouchDisablable.h
 *
 *  Created on: 29-04-2014
 *      Author: Jakub
 */

#ifndef ITOUCHDISABLABLE_H_
#define ITOUCHDISABLABLE_H_
#include "cocos2d.h"
class ITouchDisablable: public cocos2d::CCLayer{
public:
	virtual void disableTouch()=0;
	virtual void enableTouch()=0;
	virtual void enablewithoutblockingTouch(){}
	virtual void disablewithoutblockingTouch(){}
};
#endif /* ITOUCHDISABLABLE_H_ */
