const int GENERATOR_FILES=9;

enum TGeneratorType{
	GENERATOR_TRAIL_FORMED1,
	GENERATOR_LINER1,
	GENERATOR_FROM_LEFT,

	GENERATOR_ICE,
};

const TEnemyFile ENEMY_GENERATOR_DATA[GENERATOR_FILES]={
	{"dat/img/enemy/enemy-generator-dummy.bmp","",1,1,20,0,0}, //0
	{"dat/img/enemy/enemy-generator-dummy.bmp","",1,1,20,0,0}, //1 Liner
	{"dat/img/enemy/enemy-generator-dummy.bmp","",508,270,100,0,0},  //2 Ship
	{"dat/img/enemy/enemy-generator-dummy.bmp","",1,1,20,0,0}, //3 Ice
	{"dat/img/enemy/enemy-generator-dummy.bmp","",767,233,2000,0,0}, // 4 boss2
	{"dat/img/enemy/enemy-generator-dummy.bmp","",150,150,30,0,0}, // 5 Cluster
	{"dat/img/enemy/enemy-generator-dummy.bmp","",1,1,20,0,0}, //6 Propeller
	{"dat/img/enemy/enemy-generator-dummy.bmp","",1,1,20,0,0}, //7 SPINNER
	{"dat/img/enemy/enemy-generator-dummy.bmp","",1,1,20,0,0}, //8 Ball

};

class CEnemyGenerator:public CEnemySideObject{
protected:
	int mLife;
	CEnemyManager* mEnemyManager;
	CBulletManager* mBulletManager;
	CEnemyBulletManager* mEBManager;
	CItemManager* mItemManager;
	CGameInfo* mGameInfo;
	
public:
	CEnemyGenerator():CEnemySideObject(),mLife(10){
		mEnemyManager=CEnemyManager::GetInstance();
		mBulletManager=CBulletManager::GetInstance();
		mEBManager=CEnemyBulletManager::GetInstance();
		mItemManager=CItemManager::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
	}
	void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info);
	void Killed();

	void UpdateTrailFormed();
	void GeneratorLiner1Shot();
	void GeneratorShipShot();
	void GeneratorIceShot();
	void GeneratorBoss2();
	void GeneratorCluster();
	void GeneratorCluster2();
	void GeneratorCluster3();
	void GeneratorPropeller();
	void GeneratorSpinner();
	void GeneratorBall();
};

void CEnemyGenerator::Update(){
	m_x+=m_vx; m_y+=m_vy;
	RECT rc={(int)m_x-m_width/2+mHitPadding.left,(int)m_y-m_height/2+mHitPadding.top,
			(int)m_x+m_width/2-mHitPadding.right,(int)m_y+m_height/2-mHitPadding.bottom};
	bool hitFlg=false;
	if(!mInvincibleFlg && mBulletManager->HitTestRect(rc)){hitFlg=true;}
	if(hitFlg){
		mLife--;
		//mSE->PlayLoopSound(SE_KEZ1);
	}
	if(rc.left<mPlayer->GetX() && mPlayer->GetX()<rc.right && rc.top<mPlayer->GetY() && mPlayer->GetY()<rc.bottom){
		mPlayer->ForcePlayer(-14,0);
	}
	if(mLife<=0){Killed();}
	if(m_x<-20-m_width || m_x-m_width/2>750 || mLife<=0){
		mDelFlg=true;
	}
	if (mKind == GENERATOR_TRAIL_FORMED1) { UpdateTrailFormed(); }
	if (mKind == GENERATOR_LINER1) { GeneratorLiner1Shot(); }
	if (mKind == 2) { GeneratorShipShot(); }
	if(mKind==3){GeneratorIceShot();}
	if(mKind==4){GeneratorBoss2();}
	if(mKind==5){GeneratorCluster();}
	if(mKind==6){GeneratorPropeller();}
	if(mKind==7){GeneratorSpinner();}
	if(mKind==8){GeneratorBall();}
	UpdateGameObject();
}
void CEnemyGenerator::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,subKind,vx,vy);
	mImgId=kind;
	mDelFlg=false;
	m_vx=vx; m_vy=vy;
	mLife=ENEMY_GENERATOR_DATA[kind].life;
	m_width=ENEMY_GENERATOR_DATA[kind].width;
	m_height=ENEMY_GENERATOR_DATA[kind].height;
	mHitPadding.left=mHitPadding.top=mHitPadding.right=mHitPadding.bottom=0;
	mCreateInfo=info;
}

void CEnemyGenerator::Killed(){
	mDelFlg=true;
	mPlayer->DestroyEnemy(16);
	mSE->PlaySingleSound(SE_EXP3);
	int p[5]={0,0,2,0,0};
	CBltInfo bi(BLT_ADD);
	CCreateInfo info(p,bi);
	TEffectFile e[2] = { EFFECT_EXPLOSION_LIGHT_40 ,EFFECT_EXPLOSION_LIGHT_80 };
	for(int i=0;i<20;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,e[rand()%2],0,rand()%20-10,rand()%20-10,0,2,0,0);
	for(int i=0;i<10;i++)mItemManager->CreateItem((int)m_x,(int)m_y,e[rand()%2],0,rand()%20-20,rand()%20-10);
	
}

void CEnemyGenerator::UpdateTrailFormed(){

	int k[7] = {
		ENEMY_TRAIL_FORMED2,
		ENEMY_TRAIL_FORMED2,
		ENEMY_TRAIL_FORMED2,
		ENEMY_TRAIL_FORMED2,
		ENEMY_TRAIL_FORMED2,
		ENEMY_TRAIL_FORMED2,
		ENEMY_TRAIL_FORMED2,
	};

	mInvincibleFlg=true;
	mAutoDelFlg=false;
	int kind=0;
	int interval=mCreateInfo.params[0]+1;
	int endNum=mCreateInfo.params[1];
	if(mCounter>=endNum)mDelFlg=true;

	CCreateInfo info;
	info.params[0]=m_x0;
	info.params[1]=m_y0;
	if (mTimer%interval == 0) {
		mEnemyManager->Create2(m_x, 0, k[mGameInfo->GetStage()], 0, 5, info);
		mCounter++;
	}
}

void CEnemyGenerator::GeneratorShipShot(){
	m_vx=-1;
	if(mTimer%3==0){
		CCreateInfo info;
		int x1=(int)m_x+rand()%4*50-40;
		int x2=(int)m_x+rand()%4*50-40;
		mEnemyManager->Create2(x1,(int)m_y-50,ENEMY_FO2,-10,-6-rand()%5,info);
		mEnemyManager->Create2(x2,(int)m_y+50,ENEMY_FO2,-10, 6+rand()%5,info);

		int p[5]={0,0,2,0,0};
		CBltInfo bi(BLT_ADD);
		CCreateInfo info_e(p,bi);
		for(int i=0;i<5;i++){
			mBackEffectManager->CreateEffect(x1,(int)m_y-50, EFFECT_EXPLOSION_LIGHT_40,0,rand()%4-2,-rand()%8,0,2,0,0);
			mBackEffectManager->CreateEffect(x2,(int)m_y+50, EFFECT_EXPLOSION_LIGHT_40,0,rand()%4-2, rand()%8,0,2,0,0);
		}
	}
}

void CEnemyGenerator::GeneratorIceShot(){
	m_vx=0; m_x=m_x0; // 位置は変更しない
	int kind=mCreateInfo.params[0];
	int num=mCreateInfo.params[1];
	mInvincibleFlg=true;
	if(mTimer%20==0){
		CCreateInfo info;
		if(rand()%2==0)info.params[0]=1;
		int y=rand()%440+20;
		if(m_x0>BATTLE_MIDDLE_X)mEnemyManager->Create2(640,y,kind,-5,0,info);
		else mEnemyManager->Create2(-10,y,kind,5,0,info);
	}
	if(mTimer==20*num){
		mDelFlg=true;
	}
}

void CEnemyGenerator::GeneratorLiner1Shot(){
	m_vx=0; m_x=m_x0; // 位置は変更しない
	int kind=mCreateInfo.params[0];
	int num=mCreateInfo.params[1];
	mInvincibleFlg=true;
	if(mTimer%6==0){
		CCreateInfo info;
		if(kind==21){
			if(m_y0<240)info.params[0]=90;
			else info.params[0]=270;
		}
		if(m_y0>BATTLE_MIDDLE_Y)mEnemyManager->Create2((int)m_x,BATTLE_RECT.bottom,kind,0,-5,info);
		else mEnemyManager->Create2((int)m_x,BATTLE_RECT.top,kind,0,5,info);
	}
	if(mTimer==6*num){
		mDelFlg=true;
	}
}

void CEnemyGenerator::GeneratorBoss2(){
	if(m_x0<0){
		if(mTimer<=1)m_x=0-m_width/2;
		if(mTimer<320)m_vx=1;
		else if(mTimer<400)m_vx=0;
		else m_vx=1;
	}else{
		if(mTimer<=1)m_x=640+m_width/2;
		if(mTimer<320)m_vx=-1;
		else if(mTimer<400)m_vx=0;
		else m_vx=1;
	}

	m_y=480-m_height/2+5*(1-sin(N_PI*mTimer));
	if(mTimer%3==0){
		CCreateInfo info;
		int x1=(int)m_x+rand()%4*50+60;
		int x2=(int)m_x+rand()%4*50+60;
		if(mTimer%2==0)mEnemyManager->Create2(x1,(int)m_y-70,ENEMY_FO2,-10,-6-rand()%5,info);
		else mEnemyManager->Create2(x2,(int)m_y-70,ENEMY_FO2,-10,-3-rand()%5,info);

		int p[5]={0,0,2,0,0};
		CBltInfo bi(BLT_ADD);
		CCreateInfo info_e(p,bi);
		for(int i=0;i<5;i++){
			mBackEffectManager->CreateEffect(x1,(int)m_y-70, EFFECT_EXPLOSION_LIGHT_40,0,rand()%4-2,-rand()%8,0,2,0,0);
			mBackEffectManager->CreateEffect(x2,(int)m_y-70, EFFECT_EXPLOSION_LIGHT_40,0,rand()%4-2,-rand()%8,0,2,0,0);
		}
	}
}
void CEnemyGenerator::GeneratorCluster3(){	
	if(mTimer<2){
		int pm=(m_x0>320)?1:-1;
		int pmy=(m_y0>240)?1:-1;
		mCounter=0;
		SetVel(pm*(-20-rand()%10),pmy*(-20));
	}else if(mCounter==0){
		if(m_x<=10 || m_x>=640-10)m_vx*=-1;
		if(m_y<=10 || m_y>=480-10)m_vy*=-1;
		if(m_x>350 && m_y>100 && m_y<380 && mTimer>40){
			mCounter=1;
			if(m_y>300)m_vy=-0.5;
			else if(m_y<150)m_vy=0.5;
			else m_vy=0.0;
		}

	}else{
		m_vx=-1;
	}
	if(mTimer%60<30 && mTimer%3==0){
		mSE->PlaySingleSound(SE_EXP4);
	}
	if(mTimer%5==0){
		CCreateInfo info;
		int x=(int)m_x+rand()%50-25;
		int angle=rand()%360;
		double speed=10+rand()%10;
		double vy=speed*sin(N_PI*angle);
		double vx=speed*cos(N_PI*angle);
		if(mTimer%2==0){
			mEnemyManager->Create2(x,(int)m_y,ENEMY_FO2,vx,vy,info);
		}
		int p[5]={0,0,2,0,0};
		CBltInfo bi(BLT_ADD);
		CCreateInfo info_e(p,bi);
		for(int i=0;i<5;i++){
			double x=(4+i)*sin(N_PI*angle+rand()%10-5);
			double y=(4+i)*cos(N_PI*angle+rand()%10-5);
			mBackEffectManager->CreateEffect((int)m_x,(int)m_y-m_width/2, EFFECT_EXPLOSION_LIGHT_40,0,x,y,0,2,0,0);
		}
	}
}
void CEnemyGenerator::GeneratorCluster2(){
	mBltX=m_width;
	m_vx=-1;
	if(mTimer%60<30 && mTimer%3==0){
		mSE->PlaySingleSound(SE_EXP4);
		CCreateInfo info=defaultCreateInfo;
		mEBManager->Create<CEnemyBullet>((int)m_x,(int)m_y-5,0,0,-20,0,info);
		mEBManager->Create<CEnemyBullet>((int)m_x,(int)m_y+5,0,0,-20,0,info);
	}
	if(mTimer%4==0){
		CCreateInfo info;
		int x=(int)m_x+rand()%50-25;
		int angle=rand()%360;
		double speed=10+rand()%10;
		double vy=speed*sin(N_PI*angle);
		double vx=speed*cos(N_PI*angle);
		mEnemyManager->Create2(x,(int)m_y-m_width/2,ENEMY_FO2,vx,vy,info);
		for(int i=0;i<5;i++){
			double x=(4+i)*sin(N_PI*angle+rand()%10-5);
			double y=(4+i)*cos(N_PI*angle+rand()%10-5);
			mBackEffectManager->CreateEffect((int)m_x,(int)m_y-m_width/2, EFFECT_EXPLOSION_LIGHT_40,0,x,y,0,2,0,0);
		}
	}
}
void CEnemyGenerator::GeneratorCluster(){
	if(mGameInfo->GetStage()==4){GeneratorCluster2();return;}
	if(mGameInfo->GetStage()==5){GeneratorCluster3();return;}
	m_vy=-1;
	if(mTimer%4==0){
		CCreateInfo info;
		
		int x=(int)m_x+rand()%50-25;
		int angle=rand()%360;
		double speed=10+rand()%10;
		double vy=speed*sin(N_PI*angle);
		double vx=speed*cos(N_PI*angle);
		mEnemyManager->Create2(x,(int)m_y-m_width/2,ENEMY_FO2,vx,vy,info);
		for(int i=0;i<5;i++){
			double x=(4+i)*sin(N_PI*angle+rand()%10-5);
			double y=(4+i)*cos(N_PI*angle+rand()%10-5);
			mBackEffectManager->CreateEffect((int)m_x,(int)m_y-m_width/2, EFFECT_EXPLOSION_LIGHT_40,0,x,y,0,2,0,0);
		}
	}
}

void CEnemyGenerator::GeneratorPropeller(){
	if(mTimer!=2)return;
	int currentY=60;
	for(int i=0;i<5;i++){
		currentY+=30+rand()%30;
		CCreateInfo info;
		info.params[0]=300+rand()%300;
		mEnemyManager->Create2(0,currentY,ENEMY_PROPELLER1,0,0,info);
		if(mGameInfo->GetStage()!=4)mEnemyManager->Create2(0,480-currentY,ENEMY_PROPELLER1,0,0,info);
	}
	mDelFlg=true;
}

void CEnemyGenerator::GeneratorSpinner(){
	if(mTimer!=2)return;
	for(int i=0;i<5;i++){
		CCreateInfo info;
		info.params[0]=150+rand()%350;
		info.params[1]=40+rand()%400;
		mEnemyManager->Create2(rand()%640,0-10,ENEMY_SPINNER1,0,0,info);
	}
	for(int i=0;i<5;i++){
		CCreateInfo info;
		info.params[0]=150+rand()%350;
		info.params[1]=40+rand()%400;
		mEnemyManager->Create2(rand()%640,480+10,ENEMY_SPINNER1,0,0,info);
	}
	mDelFlg=true;
}

void CEnemyGenerator::GeneratorBall(){
	if(mTimer!=2)return;
	int currentY=60;
	for(int i=0;i<5;i++){
		currentY+=30+rand()%30;
		CCreateInfo info;
		info.params[0]=300+rand()%300;
		mEnemyManager->Create2(0,currentY,ENEMY_PROPELLER1,0,0,info);
		if(mGameInfo->GetStage()!=4)mEnemyManager->Create2(0,480-currentY,ENEMY_PROPELLER1,0,0,info);
	}
	mDelFlg=true;
}