
#ifndef CONSTANTS_H_
#define CONSTANTS_H_



struct difficulty{
	//difficulty(float is,float it,int at) : speed(is),timeElapse(it),atOnce(at){}
	const float speed;
	const float timeElapse;
	const float atOnce;	//per 10 seconds
};
const float spriteRatio = 8;	//normalnie jeden sprite jest wysokosci 1/10 ekranu
const float mainMenubuttonRatio = 1.1f;
const float rotationDuration = 0.5f;
const float scoreLabelRatio = 9;
const float maxTouchTime = 0.35f;
#define FONT_MAIN "TrashCinemaBB.ttf"
#define HIGH_SCORE "highscore"
//achievments





typedef enum{
	TAG_BACKGROUND,
	TAG_HUD,
	TAG_GAMELayer,
	TAG_GAMESCENE,
	TAG_PAUSE,
	TAG_GAMEOVER,
	TAG_ACHVDISPLAYER
} tags;
const int diffNumber = 11;
const difficulty LVL1  = {2.5f,0,6};
const difficulty LVL2 =  {2.0f,6,8};
const difficulty LVL3 =  {1.2f,12,10};
const difficulty LVL4 =  {0.8f,21,13};
const difficulty LVL5 =  {0.7f,30,16};
const difficulty LVL6 =  {0.65f,35,18};
const difficulty LVL7 =  {0.61f,42,20};
const difficulty LVL8 =  {0.58f,50,22};
const difficulty LVL9 =  {0.54f,65,25};
const difficulty LVL10 = {0.52f,80,29};
const difficulty LVL11 = {0.5f,100,32};
const difficulty difficulties[diffNumber]  ={LVL11,LVL10,LVL9,LVL8,LVL7,LVL6,LVL5,LVL4,LVL3,LVL2,LVL1};

#endif
