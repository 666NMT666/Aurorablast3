class CBoss5:public CBoss{
private:
	int mCicleCounter;
	static const int NUM_ARMS = 8;
	static const int NUM_SECTIONS_PER_ARMS = 4;
public:
	CBoss5():CBoss(){
		mLife=540;
		mExLife=0;
		mLife0=mLife;
		mCicleCounter=0;
		
	}
	void Update();
	void Update1();
	void Update2();

	void Create(int x,int y,int kind,int suKind,double vx,double vy,const CCreateInfo& info);
	void MainFire();
};

void CBoss5::MainFire(){
	CVector head=GetFrontPartsHead(0);
	int angle=180-mBackParts[0].GetAngle();
	double spd=(mGameLevel+2)*4;
	mSE->PlaySingleSound(SE_EXP2);
	AngleShot(head.x,head.y,EDAB_66,0,20+spd,angle);
	AngleShot(head.x,head.y,EDAB_66,0,16+spd,angle);
	for(int i=0;i<16;i++)AngleShot(head.x,head.y,EB_26,2,4+i+spd,angle+rand()%20-10);
	mELManager->Create<CLazerBullet>((int)head.x,(int)head.y,0,0,-60.0,0.0,defaultCreateInfo);
}

void CBoss5::Update(){
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

void CBoss5::Update1(){
	if(mTimer==1){
		m_y=BATTLE_BOTTOM+m_height/2;
		m_x=(BATTLE_RECT.right+BATTLE_RECT.left)/2;
	}
	if(mTimer<=100){
		m_x=ExMath::asymptote(m_x,(BATTLE_RECT.right+BATTLE_RECT.left)/2,mTimer*0.125);
		m_y=ExMath::asymptote(m_y,150,mTimer*0.125);

		if (rand() % (4 + 5 - mGameLevel) == 0 && mTimer>40) {
			int rnd = rand() % 2;
			if (rnd == 0)AngleMissile((int)m_x + 50, (int)m_y + 125, EB_DEPTHCHARGE_60x30, 3, EMISSILE_DEPTHCHARGE_Y, (double)(5 + rand() % 4),90 + rand() % 19 - 9, 0, 0, rand() % 20 - 10);
			if (rnd == 1)AngleMissile((int)m_x - 50, (int)m_y + 125, EB_DEPTHCHARGE_60x30, 3, EMISSILE_DEPTHCHARGE_Y, (double)(5 + rand() % 4), 90 + rand() % 19 - 9, 0, 0, rand() % 20 - 10);
			//if (rnd == 2)AngleMissile((int)m_x + 135, (int)m_y + 40, EB_DEPTHCHARGE_60x30, 3, EMISSILE_DEPTHCHARGE_Y, (double)(3 + rand() % 4), 90 + rand() % 19 - 9, 0, 0, rand() % 20 - 10);
			//if (rnd == 3)AngleMissile((int)m_x - 135, (int)m_y + 40, EB_DEPTHCHARGE_60x30, 3, EMISSILE_DEPTHCHARGE_Y, (double)(3 + rand() % 4), 90 + rand() % 19 - 9, 0, 0, rand() % 20 - 10);
		}

		if(m_y<150)m_y=150;
	}
	if(mTimer<50){}
	else if(mTimer<100){
		int angle=2*(mTimer-50);
		if(angle>50)angle=50;
	}else if(mTimer<200){
		int freq[5]={18,14,12,10,8};
		if(mTimer%freq[mGameLevel]==0){
			mSE->PlaySingleSound(SE_SHT3);
			int p[5]={0,20,25,1,0};
			CCreateInfo info(p);
			mEMManager->Create<CEnemyMissile>((int)m_x-140,(int)m_y, EB_DEPTHCHARGE_60x30,0,0,-16-rand()%(20+mGameLevel*5),info);
			mEMManager->Create<CEnemyMissile>((int)m_x+140,(int)m_y, EB_DEPTHCHARGE_60x30,0,0,-16-rand()%(20+mGameLevel*5),info);
		}
	}else if(mTimer<250){
	}else if(mTimer<300){
		if(mTimer%5==0){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head=GetFrontPartsHead(0);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
	}else if(mTimer<350){
	
	}else if(mTimer<450){
		int freq[5]={28,27,26,22,20};
		if(mTimer%freq[mGameLevel]==0){
			mSE->PlaySingleSound(SE_SHT3);
			int p[5]={0,20,30,1,0};
			CCreateInfo info(p);
			mEMManager->Create<CEnemyMissile>((int)m_x-140,(int)m_y+220, EB_DEPTHCHARGE_60x30,0,0,30-rand()%(30+mGameLevel*5),info);
			mEMManager->Create<CEnemyMissile>((int)m_x+140,(int)m_y + 220, EB_DEPTHCHARGE_60x30,0,0,30-rand()%(30+mGameLevel*5),info);
		}
		if (m_x < mPlayer->GetX() - 10)m_x += 1;
		if (m_x > mPlayer->GetX() + 10)m_x -= 1;
	}else if(mTimer<700){
		if (mTimer % 9 == 0) {
			double spd = (double)(14 + mGameLevel * 4 + rand() % 10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head = GetFrontPartsHead(0);
			for (int i = 0; i<3; i++) AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
		}
		if (mTimer % 9 == 3) {
			double spd = (double)(14 + mGameLevel * 4 + rand() % 10);
			mSE->PlaySingleSound(SE_SHT3);
			CVector head = GetFrontPartsHead(1);
			for (int i = 0; i<3; i++)
				AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
		}
		if (mTimer % 9 == 6) {
			double spd = (double)(14 + mGameLevel * 4 + rand() % 10);
			mSE->PlaySingleSound(SE_SHT3);
			CVector head = GetFrontPartsHead(2);
			for (int i = 0; i<3; i++)
				AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
		}
	}else{
		mTimer=10;
		mCicleCounter++;
		if(mCicleCounter==2){
			mLife=-1;
		}
	}

	m_vx=0;
	return;
}

void CBoss5::Update2(){
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

void CBoss5::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	CreateBoss();
	mParts[0].InitParts(BOSS_PARTS_BOSS5_HEAD,m_width/2,133);
	mParts[1].InitParts(BOSS_PARTS_BOSS5_CANNON, m_width / 2 - 112, 211);
	mParts[2].InitParts(BOSS_PARTS_BOSS5_CANNON, m_width / 2 + 112, 211);
}
