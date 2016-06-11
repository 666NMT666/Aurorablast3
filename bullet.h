enum TBulletKind {
	BULLET_MAIN1,
	BULLET_SUB1,
	BULLET_MAIN2,
	BULLET_SUB2,
	BULLET_UNIQUE1,
	BULLET_SUB3,
	BULLET_WIDE1,

	BULLET_FILES,
};

enum TBulletForm {
	BULLET_RECT,
	BULLET_LINE,
};

typedef struct _TBulletFileData {
	char fname[64];
	int width;
	int height;
	TBulletForm form;
	int lifetime;
	TBltType type;
} TBulletFileData;

const TBulletFileData BULLET_FILE[BULLET_FILES]={
	{"dat/img/bullet-main1.bmp",10,46,BULLET_RECT,100, BLT_KEY},//0
	{"dat/img/bullet-sub1.bmp",18,99,BULLET_RECT,100 ,BLT_KEY },//1
	{"dat/img/bullet-main2.bmp",11,48,BULLET_RECT,100 ,BLT_KEY },//2
	{"dat/img/bullet-sub2.bmp",46,46,BULLET_LINE, 2,BLT_KEY },//3  –¢Žg—p
	{"dat/img/bullet-unique1.bmp",46,40,BULLET_RECT,3 ,BLT_NULL },//4
	{"dat/img/bullet-sub3.bmp",46,10,BULLET_RECT, 3,BLT_KEY },//5
	{"dat/img/bullet-wide.bmp",18,46,BULLET_RECT,100 ,BLT_KEY },//6
};

class CBullet:public CGameObject{
protected:
	CDebrisManager* mDebrisManager;
	CEffectManager* mEffectManager;
	CScore *mScore;
	CGameInfo* mGameInfo;
	CSoundEffect *mSE;
	int mLifeTime;
	bool mHitFlg;
	TBulletForm mForm;
public:
	CBullet():CGameObject(),mHitFlg(false){
		mSE=CSoundEffect::GetInstance();
		mEffectManager=CEffectManager::GetInstance();
		mDebrisManager=CDebrisManager::GetInstance();
		mScore=CScore::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		mAutoDelFlg=true;
		mLifeTime = 0;
	}
	void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info);
	void Hit();
	void Shielded();
	static int mHitTop;
	static int GetHitTop(){return mHitTop;}
	static void SsetHitTop(int y){mHitTop=y;}
};
int CBullet::mHitTop=0;

void CBullet::Update(){
	if(mHitFlg || mTimer > mLifeTime ){mDelFlg=true;}
	UpdateGameObject();
}

void CBullet::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	mImgId=kind;
	mDelFlg=false;
	mAutoDelFlg=true;
	m_vx=vx; m_vy=vy;
	m_width=BULLET_FILE[kind].width;
	m_height=BULLET_FILE[kind].height;
	mForm = BULLET_FILE[kind].form;
	mLifeTime = BULLET_FILE[kind].lifetime;
	mBltInfo.type = BULLET_FILE[kind].type;
	mBltY=subKind*m_height;
	mBltInfo.angle=info.bltInfo.angle;
}

void CBullet::Shielded(){
	mHitFlg=true;
	mScore->AddHaste(7421771 /(mTimer+1));
}
void CBullet::Hit(){
	mScore->AddHaste(7421771 / (mTimer + 1));
	if(mKind==4){
		int v=rand()%20+30;
		int pm=(rand()%2==0)?1:-1;
		int angle=rand()%30+60;
		double vx=v*cos(N_PI*(angle))*pm;
		double vy=-v*sin(N_PI*(angle))-20;
		if(rand()%2==0)mDebrisManager->CreateDebris((int)m_x,(int)m_y,3,0,vx,vy,0,1,0,10,0);
		mSE->PlayLoopSound(SE_KEZ1);
		mHitTop=m_y;
		if(mGameInfo->EnemyStopCheck())mGameInfo->AddQuake(10,10);
		return;
	} else {
		mHitFlg = true;
		if (rand() % 2 == 0)mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_EXPLOSION_LIGHT_40, 0, 0, -(rand() % 50)*0.1, 0, 2, 0, 0);
		for (int i = 0; i<3; i++) {
			int vx = rand() % 20 + 20;
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_PARTICLE1, 0, vx, -(rand() % 100)*0.1, 1, 2, 20, 0);
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_PARTICLE1, 0, -vx, -(rand() % 100)*0.1, 1, 2, 20, 0);
		}
	}
}
