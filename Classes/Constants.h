

struct difficulty{
	//difficulty(float is,float it,int at) : speed(is),timeElapse(it),atOnce(at){}
	const float speed;
	const float timeElapse;
	const float atOnce;	//per 10 seconds
};
const float spriteRatio = 15;	//normalnie jeden sprite jest wysokosci 1/15 ekranu
const float rotationDuration = 0.5f;
#define FONT_MAIN "TrashCinemaBB.ttf"
typedef enum{
	TAG_BACKGROUND,
	TAG_HUD,
	TAG_GAMELayer,
	TAG_GAMESCENE
} tags;
const int diffNumber = 6;
const difficulty LVL1  = {6,0,4};
const difficulty LVL2 =  {5,8,6};
const difficulty LVL3 =  {4,14,7};
const difficulty LVL4 =  {2,20,10};
const difficulty LVL5 =  {1.3f,26,12};
const difficulty LVL6 =  {1,35,18};
const difficulty difficulties[6]  ={LVL6,LVL5,LVL4,LVL3,LVL2,LVL1};
