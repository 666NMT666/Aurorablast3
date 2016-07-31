#include <string>
typedef struct _TEnemyPartsFile{
	string fname;
	int startX;
	int startY;
	int endX;
	int endY;
	int width;
	int height;
} TEnemyPartsFile;

enum TEnemyParts{
	ENEMY_PARTS_SELF,
	COMMON_PARTS_CANNON29x160,
	COMMON_PARTS_CANNON42x190,
	COMMON_PARTS_CANNON46x92,
	COMMON_PARTS_CANNON30x79,
	COMMON_PARTS_CANNON170x500,

	COMMON__PARTS_SPIN_GUN_LEFT160x170,
	COMMON__PARTS_SPIN_GUN_RIGHT160x170,
	COMMON__PARTS_SPIN_GUN_LEFT270x310,
	COMMON__PARTS_SPIN_GUN_RIGHT270x310,

	COMMON_WING_LEFT,
	COMMON_WING_RIGHT,

	COMMON_SHIELD_LEFT,
	COMMON_SHIELD_RIGHT,


	ENEMY_PARTS_TANK1_MERUS_LEFT,
	ENEMY_PARTS_TANK1_MERUS_RIGHT,
	ENEMY_PARTS_TANK1_PROPODUS_LEFT,
	ENEMY_PARTS_TANK1_PROPODUS_RIGHT,

	ENEMY_PARTS_TANK3_MERUS_LEFT,
	ENEMY_PARTS_TANK3_MERUS_RIGHT,
	ENEMY_PARTS_TANK3_PROPODUS_LEFT,
	ENEMY_PARTS_TANK3_PROPODUS_RIGHT,

	ENEMY_PARTS_TANK4_MERUS_LEFT,
	ENEMY_PARTS_TANK4_MERUS_RIGHT,
	ENEMY_PARTS_TANK4_PROPODUS_LEFT,
	ENEMY_PARTS_TANK4_PROPODUS_RIGHT,

	ENEMY_PARTS_TANK5_MERUS_LEFT,
	ENEMY_PARTS_TANK5_MERUS_RIGHT,
	ENEMY_PARTS_TANK5_PROPODUS_LEFT,
	ENEMY_PARTS_TANK5_PROPODUS_RIGHT,

	ENEMY_PARTS_HC1_BODY,
	ENEMY_PARTS_HC1_MERUS_LEFT,
	ENEMY_PARTS_HC1_MERUS_RIGHT,
	ENEMY_PARTS_HC1_PROPODUS_LEFT_SHORT,
	ENEMY_PARTS_HC1_PROPODUS_RIGHT_SHORT,
	ENEMY_PARTS_HC1_PROPODUS_LEFT_LONG,
	ENEMY_PARTS_HC1_PROPODUS_RIGHT_LONG,

	ENEMY_PARTS_BB1_BODY,
	ENEMY_PARTS_BB1_MERUS_LEFT,
	ENEMY_PARTS_BB1_MERUS_RIGHT,
	ENEMY_PARTS_BB1_PROPODUS_LEFT_SHORT,
	ENEMY_PARTS_BB1_PROPODUS_RIGHT_SHORT,
	ENEMY_PARTS_BB1_PROPODUS_LEFT_LONG,
	ENEMY_PARTS_BB1_PROPODUS_RIGHT_LONG,

	BOSS_PARTS_BOSS1_TORSO,
	BOSS_PARTS_BOSS1_TAIL,
	BOSS_PARTS_BOSS1_WING_LEFT,
	BOSS_PARTS_BOSS1_WING_RIGHT,
	BOSS_PARTS_BOSS1_HEAD,
	BOSS_PARTS_BOSS1_SHOULDER_LEFT,
	BOSS_PARTS_BOSS1_SHOULDER_RIGHT,
	BOSS_PARTS_BOSS1_CANNON_LEFT,
	BOSS_PARTS_BOSS1_CANNON_RIGHT,

	BOSS_PARTS_BOSS2_HEAD,
	BOSS_PARTS_BOSS2_ARM_LEFT,
	BOSS_PARTS_BOSS2_ARM_RIGHT,
	BOSS_PARTS_BOSS2_SAW_LEFT,
	BOSS_PARTS_BOSS2_SAW_RIGHT,

	BOSS_PARTS_BOSS4_SPINNER,
	BOSS_PARTS_BOSS4_CROSS_GUN,

	BOSS_PARTS_BOSS5_HEAD,
	BOSS_PARTS_BOSS5_CANNON,

	BOSS_PARTS_BOSS6_BASE,
	BOSS_PARTS_BOSS6_CANNON_MAIN,
	BOSS_PARTS_BOSS6_CANNON_SUB,

	BOSS_PARTS_BOSS7_SPINNER,
	BOSS_PARTS_BOSS7_CROSS_GUN,

	ENEMY_PARTS_WS1_WHIP1,
	ENEMY_PARTS_WS1_WHIP2,
	ENEMY_PARTS_WS1_WHIP3,
	ENEMY_PARTS_WS1_MERUS_LEFT,
	ENEMY_PARTS_WS1_MERUS_RIGHT,
	ENEMY_PARTS_WS1_PROPODUS_LEFT,
	ENEMY_PARTS_WS1_PROPODUS_RIGHT,
	ENEMY_PARTS_WS1_DACTYLUS_LEFT,
	ENEMY_PARTS_WS1_DACTYLUS_RIGHT,
	ENEMY_PARTS_WS1_PEDIPALP1_LEFT,
	ENEMY_PARTS_WS1_PEDIPALP1_RIGHT,
	ENEMY_PARTS_WS1_PEDIPALP2_LEFT,
	ENEMY_PARTS_WS1_PEDIPALP2_RIGHT,
	ENEMY_PARTS_WS1_CANNON,
	ENEMY_PARTS_WS2_WHIP1,
	ENEMY_PARTS_WS2_WHIP2,
	ENEMY_PARTS_WS2_WHIP3,
	ENEMY_PARTS_WS2_MERUS_LEFT,
	ENEMY_PARTS_WS2_MERUS_RIGHT,
	ENEMY_PARTS_WS2_PROPODUS_LEFT,
	ENEMY_PARTS_WS2_PROPODUS_RIGHT,
	ENEMY_PARTS_WS2_DACTYLUS_LEFT,
	ENEMY_PARTS_WS2_DACTYLUS_RIGHT,
	ENEMY_PARTS_WS2_PEDIPALP1_LEFT,
	ENEMY_PARTS_WS2_PEDIPALP1_RIGHT,
	ENEMY_PARTS_WS2_PEDIPALP2_LEFT,
	ENEMY_PARTS_WS2_PEDIPALP2_RIGHT,
	BOSS_PARTS_BOSS3_CHELICERAE_LEFT,
	BOSS_PARTS_BOSS3_CHELICERAE_RIGHT,
	BOSS_PARTS_BOSS3_TAIL1,
	BOSS_PARTS_BOSS3_TAIL2,
	BOSS_PARTS_BOSS3_LEG1_LEFT,
	BOSS_PARTS_BOSS3_LEG1_RIGHT,
	BOSS_PARTS_BOSS3_LEG2_LEFT,
	BOSS_PARTS_BOSS3_LEG2_RIGHT,
	BOSS_PARTS_BOSS3_LEG3_LEFT,
	BOSS_PARTS_BOSS3_LEG3_RIGHT,
	BOSS_PARTS_BOSS3_LEG1_LEFT_SMALL,
	BOSS_PARTS_BOSS3_LEG1_RIGHT_SMALL,
	BOSS_PARTS_BOSS3_LEG2_LEFT_SMALL,
	BOSS_PARTS_BOSS3_LEG2_RIGHT_SMALL,
	BOSS_PARTS_BOSS3_LEG3_LEFT_SMALL,
	BOSS_PARTS_BOSS3_LEG3_RIGHT_SMALL,
	ENEMY_PARTS_FILES,
};
TEnemyPartsFile *ENEMY_PARTS_DATA;
class CEnemyParts{
protected:
	int mStartX,mStartY,mEndX,mEndY,mTargetX,mTargetY,mBltX,mBltY,mWidth,mHeight,mImgId;
	bool mDelFlg,mDamagedFlg;
	double mPurgeVX, mPurgeVY;
	CImageDIB* mBG;
	CBltInfo mBltInfo;
public:
	CEnemyParts():mDelFlg(false),mDamagedFlg(false){
		mStartX=mStartY=0;
		mEndX=mEndY=0;
		mTargetX=mTargetY=0;
		mBltX=mBltY=0;
		mWidth=mHeight=0;
		mBG=CImageDIB::GetInstance();
		mBltInfo.type=BLT_KEY;
		mImgId=0;
		mPurgeVX=mPurgeVY=0.0;
	}
	CBltInfo* GetBltInfo(){return &mBltInfo;}
	~CEnemyParts(){}
	void InitParts(const int i,int tx=0,int ty=0){
		TEnemyPartsFile f=ENEMY_PARTS_DATA[i];
		InitParts(f.startX,f.startY,f.endX,f.endY,tx,ty,0,0,f.width,f.height);
		mImgId=i;
	}
	void InitParts(int sx,int sy,int bltX,int bltY,int w,int h){
		InitParts(sx,sy,0,0,0,0,bltX,bltY,w,h);
	}
	void InitParts(int sx,int sy,int tx,int ty,int bltX,int bltY,int w,int h){
		InitParts(sx,sy,tx,ty,tx,ty,bltX,bltY,w,h);
	}
	void InitParts(int sx,int sy,int ex,int ey,int tx,int ty,int bltX,int bltY,int w,int h){
		mStartX=sx; mStartY=sy;
		mEndX=ex; mEndY=ey;
		mTargetX=tx;mTargetY=ty;
		mBltX=bltX; mBltY=bltY;
		mWidth=w;   mHeight=h;
		mBltInfo.link_x=mStartX;
		mBltInfo.link_y=mStartY;
		mImgId=0;
		mPurgeVX = mPurgeVY = 0.0;
	}
	void SetImgId(int i) { mImgId = i; }
	int GetImgId() { return mImgId; }
	void Killed(){}
	void Blt(int x,int y,CImage32 *img);
	void SetAngle(int a) { mBltInfo.angle = a; }
	void SetBltType(TBltType t) { mBltInfo.type = t; }
	void SetBltRect(int bx, int by, int w, int h) { mWidth = w; mHeight = h; mBltX = bx; mBltY = by; }
	void Damaged() { mDamagedFlg = true; }
	/*void Update(){
		mDamagedFlg=false;
	}*/
	void SetVel(double x, double y) {
		mPurgeVX = x;
		mPurgeVY = y;
	}
	void Move() {
		mTargetX += mPurgeVX;
		mTargetY += mPurgeVY;
	}
	void SetZoom(double z) { mBltInfo.zoom = z; }
	void SetTargetPos(int x,int y){mTargetX=x; mTargetY=y;}
	const int GetStartX(){return mStartX;}
	const int GetStartY(){return mStartY;}
	const int GetEndX(){return mEndX;}
	const int GetEndY(){return mEndY;}
	const int GetTargetX(){return mTargetX;}
	const int GetTargetY(){return mTargetY;}
	const int GetBltX(){return mBltX;}
	const int GetBltY(){return mBltY;}
	const int GetWidth(){return mWidth;}
	const int GetHeight(){return mHeight;}
	const int GetAngle(){return mBltInfo.angle;}

	void DirectTo(int tx,int ty);
	void LimitAngle(int min,int max);
	void AddAngle(int a);
	void AddAngle(int a,int max,int min);

	bool hitTest(int dx,int dy, int x,int y);
	CVector GetHead();
};

bool CEnemyParts::hitTest(int dx,int dy,int x, int y) {
	//mWidth, mHeight;
	dx += (int)(mBltInfo.link_x*mBltInfo.zoom);
	dy += (int)(mBltInfo.link_y*mBltInfo.zoom);

	CVector v[4];
	v[0].Set(-mBltInfo.link_x, -mBltInfo.link_y); // ç∂è„
	v[1].Set(-mBltInfo.link_x + mWidth, -mBltInfo.link_y); // âEè„
	v[2].Set(-mBltInfo.link_x + mWidth, -mBltInfo.link_y + mHeight); // âEâ∫
	v[3].Set(-mBltInfo.link_x, -mBltInfo.link_y + mHeight); // ç∂â∫

	// âÒì]ÅEägëÂÇÇ∑ÇÈ
	for (int i = 0; i<4; i++) {
		v[i].Mul(mBltInfo.zoom);
		v[i].Rotate(N_PI*mBltInfo.angle);
		v[i].Add(dx, dy);
	}

	test_fo = ExMath::isInPoligon(x, y, v, 4);
	return ExMath::isInPoligon(x, y, v, 4);
}

void CEnemyParts::Blt(int x,int y,CImage32* src){

	if(mBltInfo.zoom==1.0 && mBltInfo.angle==0){
		CImageBlender::Blt(mBG,src,&mBltInfo,BATTLE_RECT,x,y,mBltX,mBltY,mWidth,mHeight);
	}else if(mBltInfo.zoom!=1.0 && mBltInfo.angle==0)
		CImageBlenderStretch::Blt(mBG,src,&mBltInfo,BATTLE_RECT,x,y,mBltX,mBltY,mWidth,mHeight);
	else
		CImageBlenderTexmap::Blt(mBG,src,&mBltInfo,BATTLE_RECT,x,y,mBltX,mBltY,mWidth,mHeight);
}

void CEnemyParts::LimitAngle(int min,int max){
	int angle=GetAngle();
	while(angle<=-180)angle+=360;
	while(angle>=180)angle-=360;
	if(angle<min)angle=min;
	if(angle>max)angle=max;
	SetAngle(angle);
}

void CEnemyParts::AddAngle(int a){
	int angle=GetAngle();
	angle+=a;
	while(angle>360)angle-=360;
	while(angle<0)angle+=360;
	SetAngle(angle);
}

void CEnemyParts::AddAngle(int a,int max,int min){
	int angle=GetAngle();
	angle+=a;
	if(angle>max)angle=max;
	if(angle<min)angle=min;

	while(angle>360)angle-=360;
	while(angle<0)angle+=360;
	SetAngle(angle);
}