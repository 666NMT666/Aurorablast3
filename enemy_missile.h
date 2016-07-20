enum TMissileMotion{
	EMISSILE_STOP_GO,
	EMISSILE_SHOT,
	EMISSILE_HIT_EXPLOSION,
	EMISSILE_HOMING,
	EMISSILE_BURNING,
	EMISSILE_HEDGEHOG,
	EMISSILE_MINE,
	EMISSILE_DEPTHCHARGE,
	EMISSILE_SPINNING_DEPTHCHARGE,
	EMISSILE_DEPTHCHARGE_Y,
	KILLERSHOT_GRAVITY,
	EMISSILE_GRAVITY_MINE,

	EMISSILE_MOTIONS,
};
enum TMissileFile {
	EB_MISSILE_48x14,
	EB_MISSILE_100x20,
	EB_KILLERSHOT_160x160,
	EB_MINE_30x30,
	EB_DEPTHCHARGE_32x20,
	EB_DEPTHCHARGE_48x30,
	EB_DEPTHCHARGE_60x30,
	KS_GRAVITY_100,

	EMISSILE_FILES,
};
typedef struct _TEMissileFileData {
	char fname[64];
	int width, height, numCycle, type;
} TEMissileFileData;

const TEMissileFileData EMISSILE_FILE[EMISSILE_FILES]={
	{"dat/img/eb/em-missiles.bmp",48,14,1,BLT_KEY},
	{"dat/img/eb/em-missiles100_20.bmp",100,20,1,BLT_KEY},
	{"dat/img/eb/eb-killershot160.bmp",160,160,1,BLT_KEY},
	{"dat/img/eb/em-mine30_30.bmp",30,30,4,BLT_KEY},
	{"dat/img/eb/em-depthcharge32x20.bmp",32,20,4,BLT_KEY},
	{"dat/img/eb/em-depthcharge48x30.bmp",48,30,4,BLT_KEY},
	{ "dat/img/eb/em-depthcharge60x30.bmp",60,30,1,BLT_KEY },
	{ "dat/img/eb/eb-killershot100.bmp",100,100,1,BLT_KEY },
};

class CEnemyMissile:public CEnemySideObject{
private:
	int mLife,mLethalFlg,mNumCycle,mIntervalAnim;
	CEffectManager* mEffectManager;
	CEffectManager* mEffectManagerUnder;
	CEnemyBulletManager* mEBManager;
	CGameInfo* mGameInfo;
	int mParams[5];
	int mMotionKind;
	int mImgRotation;

	void StopAndGo();
	void NormalShot();
	void Hedgehog();
	void HitAndExplode();
	void Homing1();
	void Burning();
	void Mine1();
	void Depthcharge();
	void SpiningDepthcharge();
	void DepthchargeY();
	void Gravity();
	void GravityMine();

public:
	CEnemyMissile():CEnemySideObject(),mLife(0),mLethalFlg(false){
		mMotionKind=0;
		mImgRotation=0;
		mIntervalAnim=1;
		mNumCycle=1;
		mEffectManager=CEffectManager::GetInstance();
		mEBManager=CEnemyBulletManager::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		CExRect::InitRect(&mRectScreenOut,-100-m_width/2,-100-m_height/2,BATTLE_RECT.right+100+m_width/2,BATTLE_RECT.bottom+100+m_height/2);
	}
	void Update();
	void Create(int x,int y,int kind,int img_sub_kind,double vx,double vy,const CCreateInfo& info);
	void CreateMissile(int x,int y,int kind,int img_sub_kind,double vx,double vy,int intervalAnim,int angle,int lethal,int intervalSwitch);
};

void CEnemyMissile::Update(){
	mImgRotation=(++mImgRotation)%(mNumCycle*2);
	mBltX=0;
	mBltY=m_height*(mSubKind*mNumCycle+mImgRotation/2);
	UpdateGameObject();

	switch (mMotionKind){
		case EMISSILE_STOP_GO: StopAndGo(); break;
		case EMISSILE_SHOT: NormalShot(); break;
		case EMISSILE_HIT_EXPLOSION: HitAndExplode(); break;
		case EMISSILE_HOMING: Homing1(); break;
		case EMISSILE_BURNING: Burning(); break;
		case EMISSILE_HEDGEHOG: Hedgehog(); break;
		case EMISSILE_MINE: Mine1(); break;
		case EMISSILE_DEPTHCHARGE: Depthcharge(); break;
		case EMISSILE_SPINNING_DEPTHCHARGE: SpiningDepthcharge();  break;
		case EMISSILE_DEPTHCHARGE_Y: DepthchargeY(); break; 
		case KILLERSHOT_GRAVITY: Gravity(); break;
		case EMISSILE_GRAVITY_MINE: GravityMine(); break;
		default: break;
	}

	if(mLethalFlg){
		CVector r[4];
		CVector::getRect(r,m_x,m_y,m_width,m_height,0,-2,0,2);
		for(int i=0;i<4;i++)r[i].RotateAround(m_x,m_y,mBltInfo.angle*N_PI);
		if(CHitTest::MovingPolygonToPoint((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY(),(int)mPrevX,(int)mPrevY,mPlayer->GetPrevX(),mPlayer->GetPrevY(),r,4)){
			mDelFlg=true;
			if(!mPlayer->isInvincible())mPlayer->Killed();
		}
	}
}

void CEnemyMissile::Create(int x,int y,int kind,int img_sub_kind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,img_sub_kind,vx,vy);
	mImgId=kind;
	mAutoDelFlg=true;
	#ifndef _DEBUG
	memcpy(mParams,info.params,sizeof(info.params));
	#else
	for(int i=0;i<sizeof(info.params)/sizeof(info.params[0]);i++){mParams[i]=info.params[i];}
	#endif
	mDelFlg=false;
	mIntervalAnim=1;
	mBltX=0;
	mBltY=EMISSILE_FILE[kind].height*(img_sub_kind + EMISSILE_FILE[kind].numCycle-1);
	m_width=EMISSILE_FILE[kind].width;
	m_height=EMISSILE_FILE[kind].height;
	mNumCycle=EMISSILE_FILE[kind].numCycle;
	mMotionKind=mParams[0];
	int lv=(mGameInfo->GetLevel()+2)/3;
	const int MISSILE_LIFE[EMISSILE_MOTIONS]={5+lv,4+lv,5+lv,5+lv,5+lv,5+lv,5+lv,4+lv,4+lv,5,100,10};
	mLife=MISSILE_LIFE[mMotionKind];
}

void CEnemyMissile::StopAndGo(){ //SPIN_GO
	CExRect::InitRect(&mRectScreenOut,-50,-50,WND_RECT.right+50,WND_RECT.bottom+50);
	mAutoDelFlg=true;
	int abs_dx=abs((int)m_x-mPlayer->GetX());
	int abs_dy=abs((int)m_y-mPlayer->GetY());
	if(mTimer<mParams[1]){
		mLethalFlg=false;
		//if (mGameInfo->GetStage() == 3)mLife += 1;
		mBltInfo.angle=(mBltInfo.angle+47)%360;
		ForceFriction(0.82, 0.82);
	}else if((mTimer<mParams[1]+2 || mCounter!=1) && mTimer<mParams[1]+30){
		mLethalFlg=true;
		if(abs_dx<100 && abs_dy<100 && mTimer>=mParams[1])mCounter=1;
		int angle=(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY());
		SetVelPolar(mParams[2],angle);
		mBltInfo.angle=180-angle;
	}
	int gas_interval=1;
	if(mTimer%gas_interval==0)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,1,0,0,0,2,0,0);

	RECT rc={(int)m_x-m_width/2,(int)m_y-m_width/2,(int)m_x+m_width/2,(int)m_y+m_width/2};
	if(mParams[3]==1 && mBulletManager->HitTestRect(rc)){
		if(--mLife<=0){
			mDelFlg=true;
			mSE->PlaySingleSound(SE_EXP1);
			for(int i=0;i<5;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40, 0,6+i,2*sin(N_PI*(rand()%60)-30),0,2,0,0);
		}
	}
}

void CEnemyMissile::NormalShot(){ //SHOT
	mAutoDelFlg=true;
	int abs_dx=abs((int)m_x-mPlayer->GetX());
	int abs_dy=abs((int)m_y-mPlayer->GetY());
	mLethalFlg=true;
	mBltInfo.angle=mParams[1];
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_width/2,(int)m_x+m_width/2,(int)m_y+m_width/2};
	if(mParams[2]==1 && mBulletManager->HitTestRect(rc)){
		if(--mLife<=0){
			mDelFlg=true;
			mSE->PlaySingleSound(SE_EXP1);
			for(int i=0;i<5;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,0,6+i,2*sin(N_PI*(rand()%60)-30),0,2,0,0);
		}
	}
}

void CEnemyMissile::Mine1(){ //MINE1
	mAutoDelFlg=true;
	mLethalFlg=true;
}

void CEnemyMissile::HitAndExplode(){
	if(CExRect::isInRect(&mRectScreenOut,m_x,m_y,m_width,m_height)){
		int abs_dx=abs((int)m_x-mPlayer->GetX());
		int abs_dy=abs((int)m_y-mPlayer->GetY());
		mLethalFlg=true;
		mBltInfo.angle=mParams[1];
		if(mTimer%2==0)mBltY+=m_height;
		if(mBltY>=m_height*3)mBltY=0;
	}else{
		CCreateInfo info=defaultCreateInfo;
		for(int i=0;i<10;i++){
			double spd=(double)(rand()%100)*0.1+10.0;
			int angle=rand()%20-10;
			int dy=rand()%60-30;
			double vx=spd*cos(N_PI*angle);
			double vy=spd*sin(N_PI*angle);
			mEBManager->Create<CEnemyBullet>(0,(int)m_y+dy,EB_40,0,vx,vy,info);
			mEBManager->Create<CEnemyBullet>(0,(int)m_y+dy,EB_40,0,-vx,vy,info);
		}
		mDelFlg=true;
	}
}

void CEnemyMissile::Homing1(){ //SPIN_GO
	/*
		used in Boss1 
	*/
	mAutoDelFlg=true;
	int abs_dx=abs((int)m_x-mPlayer->GetX());
	int abs_dy=abs((int)m_y-mPlayer->GetY());
	if(mTimer<mParams[1]){
		mBltInfo.angle=(mBltInfo.angle+47)%360;
		int angle=(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,(int)(m_x+m_vx),(int)(m_y+m_vy));
		mBltInfo.angle=180-angle;
		ForceFriction(0.82, 0.82);
	}else if((mTimer<mParams[1]+2 || mCounter!=1) && mTimer<mParams[1]+30){
		mLethalFlg=true;
		if(abs_dx<100 && abs_dy<100 && mTimer>=mParams[1])mCounter=1;
		int angle=(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY());
		SetVelPolar(mParams[2],angle);
		mBltInfo.angle=180-angle;
	}
	int gas_interval=1;
	if(mTimer%gas_interval==0)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,0,0,0,0,2,0,0);


	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
	if(mParams[3]==1 && mBulletManager->HitTestRect(rc)){
		if(--mLife<=0){
			mDelFlg=true;
			mSE->PlaySingleSound(SE_EXP1);
			for(int i=0;i<5;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,0,6+i,2*sin(N_PI*(rand()%60)-30),0,2,0,0);
		}
	}
}

void CEnemyMissile::Burning(){ //SHOT
	mAutoDelFlg=true;
	mLethalFlg=true;
	mBltInfo.angle=mParams[1];
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_width/2,(int)m_x+m_width/2,(int)m_y+m_width/2};
	if(mParams[2]==1 && mBulletManager->HitTestRect(rc)){
		if(--mLife<=0){
			mDelFlg=true;
			mSE->PlaySingleSound(SE_EXP1);
			for(int i=0;i<5;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,0,6+i,2*sin(N_PI*(rand()%60)-30),0,2,0,0);
		}
	}
	if(mTimer%4==0){
		mSE->PlaySingleSound(SE_EXP3);
		for(int i=0;i<10;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,0,rand()%20-5,rand()%20-10,0,2,0,0);
		for (int i = 0; i < 10; i++) {
			TEffectFile k = EFFECT_EXPLOSION_LIGHT_40;
			if (rand() % 2 == 0)k = EFFECT_EXPLOSION_LIGHT_80;
			mEffectManager->CreateEffect((int)m_x, (int)m_y, k, 0, rand() % 16 - 4, rand() % 16 - 8, 0, 2, 0, 0);
		}
	}
}

void CEnemyMissile::Hedgehog(){ //SHOT
	mAutoDelFlg=true;
	mLethalFlg=true;
	mBltInfo.angle=mParams[1];// angle
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
	if(mBulletManager->HitTestRect(rc)){// life
		if(--mLife<=0){
			mDelFlg=true;
			mSE->PlaySingleSound(SE_EXP1);
			for(int i=0;i<5;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,0,2*sin(N_PI*(rand()%60)-30),6+i,0,2,0,0);
		}
	}
	if(m_vy*m_vy+m_vx*m_vx>10.0){ ForceFriction(0.8, 0.8); }
	else if(mTimer<50){ }
	else if(mTimer%6==0){
		mCounter++;
		for(int i=0;i<4;i++){
			mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_LIGHT_80,0,rand()%16-8,-rand()%5+25+i*3,0,2,0,0);
			mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_PARTICLE_16,0,40-rand()%15,-rand()%15+40,1,2,10,0);
			mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_PARTICLE_16,0,-40+rand()%15,-rand()%15+40,1,2,10,0);
		}
		mSE->PlaySingleSound(SE_EXP5);
		CCreateInfo info;
		for(int i=0;i<3;i++)mEBManager->Create<CEnemyBullet>((int)m_x,(int)m_y,EB_40,0,(double)(rand()%30-15),30.0-i*3,info);
		if(mCounter>=3)mDelFlg=true;
	}
	{
		int gas_interval=1;
		if(mTimer%gas_interval==0)
			mEffectManager->CreateEffect((int)m_x,(int)m_y-m_height/2+5, EFFECT_EXPLOSION_40,0,0,-5.0-0.1*(rand()%90),0,2,0,0);
	}
}

void CEnemyMissile::Depthcharge(){
	mAutoDelFlg=true;
	mLethalFlg=true;
	mBltInfo.angle=mParams[1];// angle
	RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
	if(mBulletManager->HitTestRect(rc)){// life
		if(--mLife<=0){
			mDelFlg=true;
			mSE->PlaySingleSound(SE_EXP1);
			for(int i=0;i<5;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40,0,2*sin(N_PI*(rand()%60)-30),6+i,0,2,0,0);
		}
	}
	if(m_vy*m_vy+m_vx*m_vx>10.0){ ForceFriction(0.8, 0.8); }
	else if(mTimer<50){ }
	else if(mTimer%6==0){
		mCounter++;
		for(int i=0;i<4;i++){
			mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_80,0,rand()%16-8,-rand()%5+25+i*3,0,2,0,0);
			mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_PARTICLE_16,0,40-rand()%15,-rand()%15+40,1,2,10,0);
			mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_PARTICLE_16,0,-40+rand()%15,-rand()%15+40,1,2,10,0);
			mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_LIGHT_80,0,-rand()%10+5,rand()%15+5,0,2,0,0);
		}
		mSE->PlaySingleSound(SE_EXP5);
		CCreateInfo info;
		for(int i=0;i<3;i++){
			mEBManager->Create<CEnemyBullet>((int)m_x,(int)m_y,EB_40,0,(double)(rand()%30-15),30.0-i*3,info);
		}
		if(mCounter>=3)mDelFlg=true;
	}
}

void CEnemyMissile::SpiningDepthcharge() {
	mAutoDelFlg = true;
	mLethalFlg = true;
	mBltInfo.angle += mParams[1];//omega
	RECT rc = { (int)m_x - m_width / 2,(int)m_y - m_height / 2,(int)m_x + m_width / 2,(int)m_y + m_height / 2 };
	if (mBulletManager->HitTestRect(rc)) {// life
		if (--mLife <= 0) {
			mDelFlg = true;
			mSE->PlaySingleSound(SE_EXP1);
			for (int i = 0; i<5; i++)mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_EXPLOSION_40, 0, 2 * sin(N_PI*(rand() % 60) - 30), 6 + i, 0, 2, 0, 0);
		}
	}
	if (m_vy*m_vy + m_vx*m_vx>10.0) { ForceFriction(0.8, 0.8); }
	else if (mTimer<50) {}
	else if (mTimer % 6 == 0) {
		mCounter++;
		for (int i = 0; i<4; i++) {
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_EXPLOSION_80, 0, rand() % 16 - 8, -rand() % 5 + 25 + i * 3, 0, 2, 0, 0);
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_PARTICLE_16, 0, 40 - rand() % 15, -rand() % 15 + 40, 1, 2, 10, 0);
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_PARTICLE_16, 0, -40 + rand() % 15, -rand() % 15 + 40, 1, 2, 10, 0);
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_EXPLOSION_LIGHT_80, 0, -rand() % 10 + 5, rand() % 15 + 5, 0, 2, 0, 0);
		}
		mSE->PlaySingleSound(SE_EXP5);
		CCreateInfo info;
		for (int i = 0; i<3; i++) {
			mEBManager->Create<CEnemyBullet>((int)m_x, (int)m_y, EB_40, 0, (double)(rand() % 30 - 15), 30.0 - i * 3, info);
		}
		if (mCounter >= 3)mDelFlg = true;
	}
}

void CEnemyMissile::DepthchargeY() { //
	mAutoDelFlg = true;
	mLethalFlg = false;
	mBltInfo.angle = mParams[4]*mTimer; // angle
	RECT rc = { (int)m_x - m_width / 2,(int)m_y - m_height / 2,(int)m_x + m_width / 2,(int)m_y + m_height / 2 };

	if ( m_y > mPlayer->GetY() && mTimer % 6 == 0) {
		mCounter++;
		for (int i = 0; i<4; i++) {
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_EXPLOSION_LIGHT_80, 0, rand() % 16 - 8, -rand() % 5 + 25 + i * 3, 0, 2, 0, 0);
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_PARTICLE_16, 0, 40 - rand() % 15, -rand() % 15 + 40, 1, 2, 10, 0);
			mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_PARTICLE_16, 0, -40 + rand() % 15, -rand() % 15 + 40, 1, 2, 10, 0);
		}
		mSE->PlaySingleSound(SE_EXP5);
		CCreateInfo info;
		for (int i = 0; i<3; i++)mEBManager->Create<CEnemyBullet>((int)m_x, (int)m_y, EB_40, 0, (double)(rand() % 30 - 15), 30.0 - i * 3, info);
		if (mCounter >= 3)mDelFlg = true;
	}
	{
		int gas_interval = 1;
		if (mTimer%gas_interval == 0)
			mEffectManager->CreateEffect((int)m_x, (int)m_y - m_height / 2 + 5, EFFECT_EXPLOSION_40, 0, 0, -5.0 - 0.1*(rand() % 90), 0, 2, 0, 0);
	}
}

void CEnemyMissile::Gravity() {
	mAutoDelFlg = true;
	mLethalFlg = true;
	double fc = mParams[2];
	double dy=m_y - mPlayer->GetY() ;
	double dx=m_x - mPlayer->GetX() ;
	double d2=dx*dx + dy*dy;
	if (d2<m_width*m_width /4) {
        d2=m_width*m_width /4;
    }
	CVector v = CVector::TargetVector(m_x, m_y, mPlayer->GetX(), mPlayer->GetY(), fc / d2);
	mPlayer->ForcePlayer(-v.x, -v.y);
	mBltInfo.zoom = mTimer*0.05 < 1.0 ? mTimer*0.05 : 1.0;
	if ( mTimer > 100) {
		mDelFlg = true;
	}
}

void CEnemyMissile::GravityMine() {
	mAutoDelFlg = true;
	mLethalFlg = true;

	
	mBltInfo.angle += mParams[1];//omega
	RECT rc = { (int)m_x - m_width / 2,(int)m_y - m_height / 2,(int)m_x + m_width / 2,(int)m_y + m_height / 2 };
	if (mBulletManager->HitTestRect(rc)) {// life
		--mLife;
	}
	if (--mLife <= 0) {
		mLife = 50;
		mImgId = KS_GRAVITY_100;
		mMotionKind = KILLERSHOT_GRAVITY;

		mBltY = EMISSILE_FILE[mImgId].height*(mMotionKind + EMISSILE_FILE[mImgId].numCycle - 1);
		m_width = EMISSILE_FILE[mImgId].width;
		m_height = EMISSILE_FILE[mImgId].height;
		mNumCycle = EMISSILE_FILE[mImgId].numCycle;
		mParams[2] = 70000;
		mSE->PlaySingleSound(SE_EXP1);
		for (int i = 0; i<5; i++)mEffectManager->CreateEffect((int)m_x, (int)m_y, EFFECT_EXPLOSION_40, 0, 2 * sin(N_PI*(rand() % 60) - 30), 6 + i, 0, 2, 0, 0);
	}
	if (m_vy*m_vy + m_vx*m_vx>10.0) { ForceFriction(0.8, 0.8); }
	else if (mTimer<50) {}
	else if (mTimer % 6 == 0) {
		mLife--;
	}
}