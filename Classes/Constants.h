
#include "cocos2d.h"
#include <vector>

const float rotationDuration = 0.5f;
struct difficulty{
	//difficulty(float is,float it,int at) : speed(is),timeElapse(it),atOnce(at){}
	const float speed;
	const float timeElapse;
	const int atOnce;
};
const int diffNumber = 6;
const difficulty LVL1  = {6,0,1};
const difficulty LVL2 =  {5,8,1};
const difficulty LVL3 =  {4,14,2};
const difficulty LVL4 =  {2,20,2};
const difficulty LVL5 =  {1,26,3};
const difficulty LVL6 =  {0.4f,35,3};
const difficulty difficulties[6]  ={LVL6,LVL5,LVL4,LVL3,LVL2,LVL1};
