
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

#define ACH_50 "BEGGINER COLLECTOR"
#define ACH_100 "INTERMEDIATE COLLECTOR"
#define ACH_250 "ADVANCED COLLECTOR"
#define ACH_500 "PRO COLLECTOR"
#define ACH_1000 "EXPERT COLLECTOR"
#define ACH_2000 "MASTER COLLECTOR"

#define ACH_10_SINGLE "CORRECTNESS"
#define ACH_20_SINGLE "FLAWLESSNESS"
#define ACH_50_SINGLE "CAREFULLNESS"
#define ACH_100_SINGLE "FAULTLESSNESS"
#define ACH_150_SINGLE "PERFECTION"
#define ACH_250_SINGLE "ACCURACY MASTER"



typedef enum{
	TAG_BACKGROUND,
	TAG_HUD,
	TAG_GAMELayer,
	TAG_GAMESCENE,
	TAG_PAUSE,
	TAG_GAMEOVER
} tags;
const int diffNumber = 6;
const difficulty LVL1  = {6,0,4};
const difficulty LVL2 =  {5,8,6};
const difficulty LVL3 =  {4,14,7};
const difficulty LVL4 =  {2,20,10};
const difficulty LVL5 =  {1.3f,26,12};
const difficulty LVL6 =  {0.8,35,25};
const difficulty difficulties[6]  ={LVL6,LVL5,LVL4,LVL3,LVL2,LVL1};

#endif
