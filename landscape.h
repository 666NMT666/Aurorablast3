const int LANDSCAPE_WIDTH=64;
typedef struct _TLandscapeStatus{
	char fname[64];
	int width;
	int height;
	int life;
	bool destroyable;
	bool lethal;
	bool base; // 右探索用フラグ
	bool push;
} TLandscapeStatus;

enum TLandscapeKind{
	LANDSCAPE_FLOOR1,
	LANDSCAPE_GAS_TANK1,
	LANDSCAPE_CONTAINER1,

	LANDSCAPE_FLOOR2,
	LANDSCAPE_CRYSTAL1,
	LANDSCAPE_CRYSTAL2,
	LANDSCAPE_CRYSTAL3,

	LANDSCAPE_FLOOR3,
	LANDSCAPE_NEEDLE1,
	LANDSCAPE_NEEDLE2,
	LANDSCAPE_NEEDLE3,

	LANDSCAPE_FLOOR4,
	LANDSCAPE_GAS_TANK2,

	LANDSCAPE_FLOOR5,
	LANDSCAPE_BLOCK1,
	LANDSCAPE_BLOCK2,

	LANDSCAPE_BAR1,
	LANDSCAPE_BAR2,

	LANDSCAPE_FLOOR6,

	LANDSCAPE_FILES,

	LANDSCAPE_VACUUMED_STAR,
	LANDSCAPE_PASSING_STAR1,
	LANDSCAPE_PASSING_STAR2,
	LANDSCAPE_CRYSTAL_ST6_1,
	LANDSCAPE_CRYSTAL_ST6_2,
	LANDSCAPE_CRYSTAL_ST6_3,
	LANDSCAPE_CRYSTAL_ST5,
};

const TLandscapeStatus LANDSCAPE_STATUS[LANDSCAPE_FILES]={
	{"dat/img/landscape/stage1/floor1.bmp",127,64,1,false,false,true,false},//LANDSCAPE_FLOOR1
	{"dat/img/landscape/stage1/gas-tank1.bmp",57,202,4,true,false,false,true},//LANDSCAPE_GAS_TANK1
	{"dat/img/landscape/stage1/container1.bmp",104,182,4,true,false,false,true},//LANDSCAPE_CONTAINER1
	
	{"dat/img/landscape/stage2/floor1.bmp",128,128,1,false,false,true,false},//LANDSCAPE_FLOOR2
	{"dat/img/landscape/stage2/crystal1.bmp",127,132,5,false,false,true,true},//LANDSCAPE_CRYSTAL1
	{"dat/img/landscape/stage2/crystal2.bmp",167,176,5,false,false,true,true},//LANDSCAPE_CRYSTAL2
	{"dat/img/landscape/stage2/crystal3.bmp",131,173,5,false,false,true,true},//LANDSCAPE_CRYSTAL3

	{"dat/img/landscape/stage3/floor1.bmp",128,128,1,false,false,true,false},//LANDSCAPE_FLOOR3
	{"dat/img/landscape/stage3/ice1.bmp",126,104,5,false,false,true,true},//LANDSCAPE_NEEDLE1
	{"dat/img/landscape/stage3/ice2.bmp",182,149,5,false,false,true,true},//LANDSCAPE_NEEDLE2
	{"dat/img/landscape/stage3/ice3.bmp",126,104,5,false,false,true,true},//LANDSCAPE_NEEDLE3

	{"dat/img/landscape/stage4/floor1.bmp",76,76,1,false,false,true,true},//LANDSCAPE_FLOOR4
	{"dat/img/landscape-gas-tank1.bmp",202,247,16,true,false,true,true},

	{"dat/img/landscape/stage5/floor1.bmp",128,128,1,false,false,true,false},//LANDSCAPE_FLOOR5
	{"dat/img/landscape/stage5/block1.bmp",128,128,1,false,false,true,true},//LANDSCAPE_BLOCK1
	{"dat/img/landscape/stage5/block2.bmp",128,128,1,false,false,true,true},//LANDSCAPE_BLOCK2
	{"dat/img/landscape/bar1.bmp",560,32,1,false,false,false,false},//LANDSCAPE_BAR1
	{"dat/img/landscape/bar2.bmp",560,112,1,false,false,false,false},//LANDSCAPE_BAR2

	{ "dat/img/landscape/stage6/floor.bmp",768,280,1,false,false,true,false },//LANDSCAPE_FLOOR6
	/*
	{"dat/img/landscape-star-300.bmp",300,300,4,false,false,false,false},
	{"dat/img/landscape-star-300.bmp",300,300,4,false,false,false,false},//LANDSCAPE_PASSING_STAR1
	{"dat/img/landscape-star-500.bmp",500,500,4,false,false,false,false},//LANDSCAPE_PASSING_STAR2
	{"dat/img/landscape-crystal-st6-1.bmp",131,161,5,false,false,true,true},
	{"dat/img/landscape-crystal-st6-2.bmp",146,128,5,false,false,true,true},
	{"dat/img/landscape-crystal-st6-3.bmp",131,173,5,false,false,true,true},
	{"dat/img/landscape-crystal-st5.bmp",146,128,5,false,false,true,true},*/
};

class CLandscape:public CEnemySideObject {
protected:
	int mLife;
	bool mLethalFlg,mDestroyableFlg,mBaseFlg,mPushFlg;// 素材ごとのフラグ
	int mImgSubId,mRoofFlg; // paramsで受け取る変数
	CBulletManager* mBulletManager;
	CEffectManager* mEffectManager;
	CItemManager* mItemManager;
	CEnemyManager* mEnemyManager;
	CSoundEffect* mSE;
public:
	CLandscape():CEnemySideObject(),mLife(1),mLethalFlg(false),mDestroyableFlg(false),mBaseFlg(false),mPushFlg(false){
		mBulletManager=CBulletManager::GetInstance();
		mEffectManager=CEffectManager::GetInstance();
		mItemManager=CItemManager::GetInstance();
		mEnemyManager=CEnemyManager::GetInstance();
		mSE=CSoundEffect::GetInstance();
	}
	void Update();
	//void Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info);
	void Create(int x, int y, int img_kind, int img_kind_sub, double vx, double vy);
	void Killed();
	const bool isBase(){return mBaseFlg;}
	virtual void UpdateLandscape(){}
};

void CLandscape::Update(){
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
	if(m_x+m_width<0 || m_x-m_width>BATTLE_RIGHT){mDelFlg=true;}
	if(m_y+m_height<0 || m_y-m_height>BATTLE_BOTTOM){mDelFlg=true;}
	UpdateLandscape();
	if(mLife<=0){Killed();}
	UpdateGameObject();
}

/*
void CLandscape::Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	mImgId=kind;
	mMotion=info.params[0];
	mImgSubId=info.params[1];
	mRoofFlg=info.params[2];
	mDelFlg=false;
	m_width=LANDSCAPE_STATUS[kind].width;
	m_height=LANDSCAPE_STATUS[kind].height;
	mDestroyableFlg=LANDSCAPE_STATUS[kind].destroyable;
	mLethalFlg=LANDSCAPE_STATUS[kind].lethal;
	mBaseFlg=LANDSCAPE_STATUS[kind].base;
	mLife=LANDSCAPE_STATUS[kind].life;
	mPushFlg=LANDSCAPE_STATUS[kind].push;
	mBltY=mImgSubId*m_height; //m_height指定完了後にmBltY決定
}
*/

void CLandscape::Create(int x, int y, int img_kind, int img_kind_sub, double vx, double vy) {
	CreateGameObject(x, y, img_kind, vx, vy);
	mImgId = img_kind;
	mImgSubId = img_kind_sub;
	mDelFlg = false;
	m_width = LANDSCAPE_STATUS[img_kind].width;
	m_height = LANDSCAPE_STATUS[img_kind].height;
	mDestroyableFlg = LANDSCAPE_STATUS[img_kind].destroyable;
	mLethalFlg = LANDSCAPE_STATUS[img_kind].lethal;
	mBaseFlg = LANDSCAPE_STATUS[img_kind].base;
	mLife = LANDSCAPE_STATUS[img_kind].life;
	mPushFlg = LANDSCAPE_STATUS[img_kind].push;
	mBltY = mImgSubId*m_height; //m_height指定完了後にmBltY決定
}

void CLandscape::Killed(){
	mDelFlg=true;
	mPlayer->DestroyEnemy(2);
	mSE->PlaySingleSound(SE_EXP2);
	int rh=m_height/2;
	//for(int i=0;i<18;i++)mEffectManager->Create<CEffect>(m_x,m_y+rand()%rh-rh/2,EFFECT_EXPLOSION_40,rand()%20+5,rand()%20-10,
	//	CCreateInfoFactory::GetEffectBltInfo(0,2,2,0,0));

	mEffectManager->CreateEffect(m_x,m_y+m_height/2, EFFECT_EXPLOSION_160,0,(-rand()%5-10)*0.25,40.0,0,3,0,0);
	for(int i=0;i<6;i++)mEffectManager->CreateEffect(m_x,m_y+m_height/2, EFFECT_EXPLOSION_80_2,0,rand()%10-5,rand()%5+30+i*5,0,4,0,0);
	for(int i=0;i<4;i++){
		mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,25-rand()%15,-rand()%15+30,1,0,2,10,0);
		mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,-25+rand()%15,-rand()%15+30,1,0,2,10,0);
	}
	//if(mKind!=4){
		//for(int i=0;i<20;i++)mItemManager->CreateItem((int)m_x,(int)m_y,2,0,rand()%20-20,rand()%20-10);
	//}else{
		for(int i=0;i<5;i++)mItemManager->CreateItem((int)m_x,(int)m_y,1,0,rand()%20-20,rand()%20-10);
	//}
		if (mKind == LANDSCAPE_CONTAINER1) {
			for (int i = 0; i<5; i++)mItemManager->CreateItem((int)m_x, (int)m_y, 0, 0, rand() % 20 - 20, rand() % 20 - 10);
		}
	if(mKind==9){
		mSE->PlaySingleSound(SE_EXP5);
		const TEffectFile e[2] = { EFFECT_EXPLOSION_LIGHT_40 ,EFFECT_EXPLOSION_LIGHT_80 };
		for(int i=0;i<10;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,e[rand()%2],0,rand()%16-8,rand()%16-12,0,2,0,0);
		for(int j=0;j<3;j++)for(int i=0;i<10;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y-40*j, EFFECT_EXPLOSION_LIGHT_80,0,rand()%16-8,rand()%16-12,0,2,0,0);
	}
}