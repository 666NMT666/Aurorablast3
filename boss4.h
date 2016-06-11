class CBoss4:public CBoss{
private:
	int mCicleCounter;
public:
	CBoss4():CBoss(){
		mLife=340;
		mExLife=0;
		mLife0=mLife;
		mCicleCounter=0;
		
	}
	void Update();
	void Update1();
	void Update2();

	void Create(int x,int y,int kind,int suKind,double vx,double vy,const CCreateInfo& info);
	void Spin1();
	void Spin2();
	void MainFire(int j);
};

void CBoss4::MainFire(int j){
	// 0 <= j <= 3
	if (j < 0)j = 0;
	if (j > 3)j = 3;
/*	CVector head= GetFrontPartsHead(0);
	int angle = 180 - mParts[0].GetAngle();
	double spd=(mGameLevel+2)*4;
	mSE->PlaySingleSound(SE_EXP2);
	
	AngleShot(head.x,head.y,EDAB_66,0,20+spd,angle+90);
	AngleShot(head.x,head.y,EDAB_66,0,16+spd,angle-90);
	for(int i=0;i<16;i++)NormalShot(head.x,head.y,EB_26,2,4+i+spd,angle+rand()%20-10);
	mELManager->Create<CLazerBullet>((int)head.x,(int)head.y,0,0,-60.0,0.0,defaultCreateInfo);*/
}

void CBoss4::Update(){
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

void CBoss4::Spin1() {

}
void CBoss4::Spin2() {

}

void CBoss4::Update1(){
	mBackParts[0].SetAngle(((int)(mTimer*sin(N_PI*mTimer * 23))) % 360);
	mBackParts[1].SetAngle(((int)(-mTimer*sin(N_PI*mTimer * 13))) % 360);
	if(mTimer==1){
		m_y=BATTLE_BOTTOM+m_height/2;
		m_x=(BATTLE_RECT.right+BATTLE_RECT.left)/2;
	}
	if(mTimer<=200){
		m_x=ExMath::asymptote(m_x,(BATTLE_RECT.right+BATTLE_RECT.left)/2,mTimer*0.125);
		m_y=ExMath::asymptote(m_y,150,mTimer*0.125);
		if(m_y<150)m_y=150;
	}
	if(mTimer<50){ }
	else if(mTimer<100){

	}else if(mTimer<200){
		int freq[5]={8,7,6,5,4};
		if(mTimer%freq[mGameLevel]==0){
			mSE->PlaySingleSound(SE_SHT3);
			int p[5]={0,20,30,1,0};
			CCreateInfo info(p);
			mEMManager->Create<CEnemyMissile>((int)m_x - 40, (int)m_y, EB_DEPTHCHARGE_60x30, 0, 0, -16 - rand() % (20 + mGameLevel * 5), info);
			mEMManager->Create<CEnemyMissile>((int)m_x + 40, (int)m_y, EB_DEPTHCHARGE_60x30, 0, 0, -16 - rand() % (20 + mGameLevel * 5), info);
			mEMManager->Create<CEnemyMissile>((int)m_x - 40, (int)m_y, EB_DEPTHCHARGE_60x30, 0, 0, +16 + rand() % (20 + mGameLevel * 5), info);
			mEMManager->Create<CEnemyMissile>((int)m_x + 40, (int)m_y, EB_DEPTHCHARGE_60x30, 0, 0, +16 + rand() % (20 + mGameLevel * 5), info);
		}
	}else if(mTimer<250){

	}else if(mTimer<300){
		if(mTimer%5==0){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head=GetBackPartsHead(0);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
	}else if(mTimer<350){
		m_y=ExMath::asymptote(m_y,300,(mTimer-300)*0.125);
	}else if(mTimer<400){
		m_y=ExMath::asymptote(m_y,150,(mTimer-350)*0.125);
	}else if(mTimer<600){
		if(mTimer%6==0){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head=GetBackPartsHead(0);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
		if(mTimer%6==3){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_SHT1);
			CVector head=GetBackPartsHead(0);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
		int freq[5]={8,7,6,5,4};
		if(mTimer%freq[mGameLevel]==0){
			mSE->PlaySingleSound(SE_SHT3);
			int p[5]={0,20,30,1,0};
			CCreateInfo info(p);
			mEMManager->Create<CEnemyMissile>((int)m_x-40,(int)m_y,0,0,0,-20-rand()%(30+mGameLevel*5),info);
			mEMManager->Create<CEnemyMissile>((int)m_x+40,(int)m_y,0,0,0,-20-rand()%(30+mGameLevel*5),info);
		}
		m_x = 480 + 100 * sin(N_PI * 17 * (mTimer - 400));
		m_y = 150 + 100 * sin(N_PI * 7 * (mTimer - 400));
		if(mTimer%40==0 && mGameLevel>1){
			for(int i=0;i<10;i++){
				AngleShot(m_x-m_width/2,m_y-m_height/2,EB_40,1,5,36*i+rand()%36);
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
	Spin1();
	return;
}

void CBoss4::Update2(){
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

void CBoss4::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	CreateBoss();

	mBackParts[0].InitParts(BOSS_PARTS_BOSS4_CROSS_GUN,m_width/2,m_height/2);
	mBackParts[1].InitParts(BOSS_PARTS_BOSS4_SPINNER,m_width/2,m_height/2);
}
