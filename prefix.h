#ifndef _PREFIX_H_
#define _PREFIX_H_

#define N_PI 0.01745329251994329576
const double N_PI100=3.1415*2/100;
#define BATTLE_LEFT   200
#define BATTLE_RIGHT  760
#define BATTLE_TOP    0
#define BATTLE_BOTTOM 720
#define BATTLE_WIDTH  560
#define BATTLE_HEIGHT  720
const int BATTLE_MIDDLE_X=(BATTLE_LEFT+BATTLE_RIGHT)/2;
const int BATTLE_MIDDLE_Y=(BATTLE_TOP+BATTLE_BOTTOM)/2;
static const RECT BATTLE_RECT={200,0,960-200,720};

static const RECT ED_RECT={50,50,620,430};
static const RECT WND_RECT={0,0,960,720};

static const RECT ENDURANCE_RECT={11,11,271,480-11};

template <class T>
inline void SWAP(T* a,T* b){
	T tmp=*a;
	*a=*b;
	*b=tmp;
};

template <class T> void RANGE(T* a,T max,T min){
	if(*a>max)*a=max;
	if(*a<min)*a=min;
};

template <class T>
inline bool IN_RECT(RECT rc,T x,T y){
	return (rc.top<y && y<rc.bottom && rc.left<x && x<rc.right);
};

inline bool OVERRAP_RECT(RECT rc1,RECT rc2){
	return (rc1.left<rc2.right && rc2.left<rc1.right && rc1.top<rc2.bottom && rc2.top<rc1.bottom);
};

#define TITLE_VIEW_CONTROLLER 1
#define ENDURANCE_VIEW_CONTROLLER 2
#define CONFIG_VIEW_CONTROLLER 3
#define REPLAY_VIEW_CONTROLLER 4
#define ENDING_VIEW_CONTROLLER 5
#define SELECT_VIEW_CONTROLLER 6
#define NAME_ENTRY_VIEW_CONTROLLER 7
typedef struct _TSize {
	int width;
	int height;
} TSize;

typedef struct _TFileData {
	char fname[64];
	int width;
	int height;
	int loop;
} TFileData;

typedef struct _TEnemyFileData {
	char fname[64];
	int width;
	int height;
	int front_parts;
	int back_parts;
} TEnemyFileData;

typedef struct _TItemStatus{
	int ext;
	int point;
} TItemStatus;

#endif