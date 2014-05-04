
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
const difficulty LVL1  = {3,0,9};
const difficulty LVL2 =  {2.6f,6,13};
const difficulty LVL3 =  {2.2f,12,15};
const difficulty LVL4 =  {1.8f,19,19};
const difficulty LVL5 =  {1.6f,25,21};
const difficulty LVL6 =  {1.4f,38,23};
const difficulty LVL7 =  {1.2f,52,25};
const difficulty LVL8 =  {1,69,28};
const difficulty LVL9 =  {1,90,30};
const difficulty LVL10 = {0.92f,120,31};
const difficulty LVL11 = {0.8f,180,32};
const difficulty difficulties[diffNumber]  ={LVL11,LVL10,LVL9,LVL8,LVL7,LVL6,LVL5,LVL4,LVL3,LVL2,LVL1};

#endif
