/*
 * Loader.cpp
 *
 *  Created on: 27-04-2014
 *      Author: Jakub
 */

#include "Loader.h"

using namespace cocos2d;
virtual bool Loader::init(){
	 if ( !CCLayer::init() )
		    {
		        return false;
		    }
	 achivList = CCDictionary::create();
	 achivList->setObject(ACH_50_D,ACH_50);
	 achivList->setObject(ACH_100_D,ACH_100);
	 achivList->setObject(ACH_250_D,ACH_250);
	 achivList->setObject(ACH_500_D,ACH_500);
	 achivList->setObject(ACH_1000_D,ACH_1000);
	 achivList->setObject(ACH_2000_D,ACH_2000);

	achivList->setObject(ACH_10_SINGLE_D,ACH_10_SINGLE);
	achivList->setObject(ACH_20_SINGLE_D,ACH_20_SINGLE);
	achivList->setObject(ACH_50_SINGLE_D,ACH_50_SINGLE);
	achivList->setObject(ACH_100_SINGLE_D,ACH_100_SINGLE);
	achivList->setObject(ACH_150_SINGLE_D,ACH_150_SINGLE);
	achivList->setObject(ACH_250_SINGLE_D,ACH_250_SINGLE);
	return true;
}

