class CBoss1:public CBoss{
private:
	int mCicleCounter;
protected:
	void _UpdateAfterDeath();
public:
	CBoss1():CBoss(){
		mLife=340;
		mExLife=0;
		mLife0=mLife;
		mCicleCounter=0;
		
	}
	void Update();
	void Update1();
	void Update2();

	void Create(int x,int y,int kind,int suKind,double vx,double vy,const CCreateInfo& info);
	void Walk();
	void MainFire();
};

void CBoss1::MainFire(){
	CVector head=GetFrontPartsHead(3);
	int angle=180-mBackParts[3].GetAngle();
	double spd=(mGameLevel+2)*4;
	mSE->PlaySingleSound(SE_EXP2);
	AngleShot(head.x,head.y,EDAB_66,0,20+spd,angle);
	AngleShot(head.x,head.y,EDAB_66,0,16+spd,angle);
	for(int i=0;i<16;i++)AngleShot(head.x,head.y,EB_26,2,4+i+spd,angle+rand()%20-10);
	mELManager->Create<CLazerBullet>((int)head.x,(int)head.y,0,0,-60.0,0.0,defaultCreateInfo);
}

void CBoss1::Update(){
	UpdateBoss();
	UpdateGameObject();
	if(mExLife<0)return;
	Update1();
	return;



	if(mExLife==1){
		Update1();
	}else if(mExLife==0){
		Update2();
	}
}

void CBoss1::Walk(){
	for(int i=5;i>0;i--){
		LinkBackParts(i,i-1,0);
		mBackParts[i].SetAngle((int)((30.0-i*2+10.0*sin(N_PI*mTimer*4))*sin(3.1415*(i*0.134+mTimer/20.0))));
	}
	if(mTimer%3==0){
		mBackParts[6].SetAngle( 60);
		mBackParts[7].SetAngle(-60);
		mBackParts[6].SetImgId(BOSS_PARTS_BOSS1_WING_LEFT);
		mBackParts[7].SetImgId(BOSS_PARTS_BOSS1_WING_RIGHT);
	}else if(mTimer%3==1){
		mBackParts[6].SetAngle( 120);
		mBackParts[7].SetAngle(-120);
		mBackParts[6].SetImgId(BOSS_PARTS_BOSS1_WING_RIGHT);
		mBackParts[7].SetImgId(BOSS_PARTS_BOSS1_WING_LEFT);
	}else{
		mBackParts[6].SetAngle( 160);
		mBackParts[7].SetAngle(-160);
		mBackParts[6].SetImgId(BOSS_PARTS_BOSS1_WING_RIGHT);
		mBackParts[7].SetImgId(BOSS_PARTS_BOSS1_WING_LEFT);
	}
}

void CBoss1::Update1(){
	if(mTimer==1){
		m_y=BATTLE_BOTTOM+m_height/2;
		m_x=(BATTLE_RECT.right+BATTLE_RECT.left)/2;
	}
	if(mTimer<=200){
		m_x=ExMath::asymptote(m_x,(BATTLE_RECT.right+BATTLE_RECT.left)/2,mTimer*0.125);
		m_y=ExMath::asymptote(m_y,150,mTimer*0.125);
		if(m_y<150)m_y=150;
	}
	if(mTimer<50){
		LinkFrontParts(3,1,0);
		LinkFrontParts(4,2,0);
	}
	else if(mTimer<100){
		//mParts[1].AddAngle(-10);
		//mParts[2].AddAngle(+10);
		int angle=2*(mTimer-50);
		if(angle>50)angle=50;
		LinkFrontParts(3,1,-angle);
		LinkFrontParts(4,2,angle);
		if(mTimer==85)mSE->PlaySingleSound(SE_CRY1);
	}else if(mTimer<200){
		int freq[5]={8,7,6,5,4};
		if(mTimer%freq[mGameLevel]==0){
			mSE->PlaySingleSound(SE_SHT4);
			int p[5]={0,20,30,1,0};
			CCreateInfo info(p);
			mEMManager->Create<CEnemyMissile>((int)m_x-40,(int)m_y,0,0,0,-16-rand()%(20+mGameLevel*5),info);
			mEMManager->Create<CEnemyMissile>((int)m_x+40,(int)m_y,0,0,0,-16-rand()%(20+mGameLevel*5),info);
		}
	}else if(mTimer<250){
		int angle=50-(mTimer-200)*2;
		if(angle<0)angle=0;
		int angleArm=-(mTimer-200)*3;
		if(angleArm<-180)angleArm=-180;
		mParts[2].SetAngle(angleArm);
		LinkFrontParts(4,2,angle);
	}else if(mTimer<300){
		if(mTimer%5==0){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head=GetFrontPartsHead(4);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
	}else if(mTimer<350){
		m_y=ExMath::asymptote(m_y,300,(mTimer-300)*0.125);
		int angle=50-(mTimer-300)*2;
		if(angle<0)angle=0;
		int angleArm=(mTimer-300)*3;
		if(angleArm>180)angleArm=180;
		mParts[1].SetAngle(angleArm);
		LinkFrontParts(3,1,-angle);
		if(mTimer%3==0){
			CVector head=GetFrontPartsHead(3);
			mSE->PlaySingleSound(SE_EXP5);
			SampleExplosion((int)head.x,(int)head.y);
		}
	}else if(mTimer<400){
		m_y=ExMath::asymptote(m_y,150,(mTimer-350)*0.125);
	}else if(mTimer<600){
		if(mTimer%6==0){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head=GetFrontPartsHead(4);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
		if(mTimer%6==3){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_SHT1);
			CVector head=GetFrontPartsHead(3);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
		int freq[5]={8,7,6,5,4};
		if(mTimer%freq[mGameLevel]==0){
			mSE->PlaySingleSound(SE_SHT4);
			int p[5]={0,20,30,1,0};
			CCreateInfo info(p);
			mEMManager->Create<CEnemyMissile>((int)m_x-40,(int)m_y,0,0,0,-20-rand()%(30+mGameLevel*5),info);
			mEMManager->Create<CEnemyMissile>((int)m_x+40,(int)m_y,0,0,0,-20-rand()%(30+mGameLevel*5),info);
		}
		m_x=480+100*sin(N_PI*2*(mTimer-400));
		if(mTimer%40==0 && mGameLevel>1){
			for(int i=0;i<10;i++){
				AngleShot(m_x-m_width/2+mParts[0].GetTargetX(),m_y-m_height/2+mParts[0].GetTargetY(),EB_40,1,5,36*i+rand()%36);
			}
		}
	}else{
		mTimer=10;
		mCicleCounter++;
		if(mCicleCounter==2){
			mLife=-1;
		}
	}

	m_vx=0;
	Walk();
	return;
}

void CBoss1::Update2(){
	if(mTimer<600){
		double spd=8+mGameLevel*6+rand()%5;
		int angle=150+rand()%(30+mGameLevel*6)-(30+mGameLevel*6)/2;
		const int range=140;
		if(mTimer%3==0){
			mSE->PlaySingleSound(SE_SHT1);
			AngleShot(m_x+rand()%range-range/2,m_y+rand()%range-range/2-50,EB_26,2,spd,angle);
			AngleShot(m_x+rand()%range-range/2,m_y+rand()%range-range/2-50,EDAB_80,0,20+spd+2,angle);
		}
	}
}

void CBoss1::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	CreateBoss();

	for(int i=0;i<5;i++){
		mBackParts[i].InitParts(BOSS_PARTS_BOSS1_TORSO,98,85);
	}
	mBackParts[5].InitParts(BOSS_PARTS_BOSS1_TAIL);
	mBackParts[6].InitParts(BOSS_PARTS_BOSS1_WING_LEFT,58,33);
	mBackParts[7].InitParts(BOSS_PARTS_BOSS1_WING_RIGHT,m_width-58,33);
	
	mParts[0].InitParts(BOSS_PARTS_BOSS1_HEAD,98,37);
	mParts[1].InitParts(BOSS_PARTS_BOSS1_SHOULDER_LEFT ,      0,75);
	mParts[2].InitParts(BOSS_PARTS_BOSS1_SHOULDER_RIGHT,m_width,75);
	mParts[3].InitParts(BOSS_PARTS_BOSS1_CANNON_LEFT);
	mParts[4].InitParts(BOSS_PARTS_BOSS1_CANNON_RIGHT);
}


void CBoss1::_UpdateAfterDeath() {
	mDeadTimer++;
	if (mDeadTimer>60)mBltInfo.type = BLT_NULL;
	if (mDeadTimer>200)mDelFlg = true;
	mBltInfo.type = BLT_NULL;


	/////////////        PURGE  PARTS      ///////////////////
	if (mDeadTimer == 1) {
		for (int i = 0; i < mMaxParts    ; i++) 
			{     mParts[i].SetVel((double) 5 * (rand() % mMaxParts     - mMaxParts/2    ), (double) 15 * (mMaxParts-i + 2)); }
		for (int i = 0; i < mMaxBackParts; i++) 
			{ mBackParts[i].SetVel((double) 4 * (rand() % mMaxBackParts - mMaxBackParts/2), (double) 12 * (i + 3)); }
	}
	for (int i = 0; i < mMaxParts; i++) {
		mParts[i].SetAngle(rand() % 360);
		mParts[i].Move();
	}
	for (int i = 0; i < mMaxBackParts; i++) {
		mBackParts[i].SetAngle(rand() % 360);
		mBackParts[i].Move();
	}
	
	//////////////         EXPLOSION            /////////////
	if (mDeadTimer == 2) {
		mGameInfo->SetQuake(70);
		mSE->PlaySingleSound(SE_EXP3);
		TEffectFile k = EFFECT_EXPLOSION_LIGHT_40;
		if (rand() == 0)k = EFFECT_EXPLOSION_LIGHT_80;
		for (int i = 0; i<20; i++)mEffectManager->CreateEffect((int)m_x, (int)m_y, k, 0, rand() % 20 - 10, rand() % 20 - 10, 0, 2, 0, 0);
	}

	if (mDeadTimer == 4) {
		mSE->PlaySingleSound(SE_EXP5);
		for (int i = 0; i<16; i++)mEffectManager->CreateEffect(m_x, m_y + m_height / 2, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, rand() % 5 - 60 + i * 10, 0, 3, 0, 0);
		mEffectManager->CreateEffect(m_x, m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
		for (int i = 0; i<4; i++) {
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
		}
	}
	if (mDeadTimer == 9) {
		mSE->PlaySingleSound(SE_EXP6);
		for (int i = 0; i<20; i++) {
			int v = rand() % 10 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = -v*sin(N_PI * 18 * i) - 20;
			mEffectManager->CreateEffect(m_x, m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
	}
	if (mDeadTimer == 19) {
		mSE->PlaySingleSound(SE_SHT1);
		for (int i = 0; i<20; i++) {
			int v = rand() % 20 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = -v*sin(N_PI * 18 * i) - 20;
			mEffectManager->CreateEffect(m_x, m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
	}
}