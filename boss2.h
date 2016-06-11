class CBoss2:public CBoss{
private:
	int mCicleCounter;
	double mOmega;
public:
	CBoss2():CBoss(){
		mLife=490;
		mExLife=0;
		mLife0=mLife;
		mCicleCounter=0;
		mOmega = 21;
	}
	void Update();
	void Update1();
	void Update2();

	void Create(int x,int y,int kind,int suKind,double vx,double vy,const CCreateInfo& info);
	void MainFire();
	void Saw();
	void SwingSaw(int i);
};

void CBoss2::Saw() {
	
	if (isInPartsCircle(5,100) || isInPartsCircle(6, 100)) {
		mPlayer->Killed();
	}
}

void CBoss2::MainFire(){
	CVector head=GetFrontPartsHead(0);
	int angle=180-mParts[0].GetAngle();
	double spd=(mGameLevel+2)*4;
	mSE->PlaySingleSound(SE_EXP2);
	AngleShot(head.x,head.y,EDAB_66,0,20+spd,angle);
	AngleShot(head.x,head.y,EDAB_66,0,16+spd,angle);
	for(int i=0;i<16;i++)AngleShot(head.x,head.y,EB_26,2,4+i+spd,angle+rand()%20-10);
	mELManager->Create<CLazerBullet>((int)head.x,(int)head.y,0,0,-60.0,0.0,defaultCreateInfo);
}

void CBoss2::Update(){
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

void CBoss2::Update1(){
	if(mTimer>80)Saw();
	mParts[5].SetAngle(mTimer*mOmega);
	mParts[6].SetAngle(-mTimer*mOmega);
	if(mTimer==1){
		m_y=BATTLE_BOTTOM+m_height/2;
		m_x= BATTLE_MIDDLE_X;
	}
	if(mTimer<=200){
		m_x=ExMath::asymptote(m_x, BATTLE_MIDDLE_X,mTimer*0.125);
		m_y=ExMath::asymptote(m_y,250,mTimer*0.125);
		if(m_y<150)m_y=150;
	}
	if(mTimer<90){
		double a[4] = {
			mTimer*sin(N_PI*mTimer),
			mTimer*cos(N_PI*mTimer),
			mTimer*cos(N_PI*(mTimer + 60)),
			mTimer*sin(N_PI*(mTimer + 60)),
		};
		mParts[1].SetAngle(a[0]);
		mParts[2].SetAngle(-a[0]);
		LinkFrontParts(3, 1,  a[1]);
		LinkFrontParts(4, 2, -a[1]);
		LinkFrontParts(5, 3, a[2]);
		LinkFrontParts(6, 4, a[3]);
		DirectFrontPartsTo(0,mPlayer->GetX(),mPlayer->GetY());
		if(mTimer==85)mSE->PlaySingleSound(SE_CRY1);
	}else if(mTimer<150){
		if(mTimer==90)mSE->PlaySingleSound(SE_KYP1);
		for(int i=5;i<=6;i++){
			int t=(mTimer-90);
			int x=(int)(m_x-m_width /2+mParts[i].GetTargetX());
			int y=(int)(m_y-m_height/2+mParts[i].GetTargetY());
			mFrontEffectManager->CreateEclipsedCircle(x,y,10+t*12,x-4,y-5,8+(int)(t*11.5),0xFFFFFFFF);
		}
	}else if(mTimer<250){
		if(mTimer%8==0){
			mSE->PlaySingleSound(SE_EXP2);
			mCounter++;
			for(int j=5;j<=6;j++){
				for(int i=0;i<2+mGameLevel/2;i++){
					AngleShot(m_x-m_width/2+mParts[j].GetTargetX(), m_y-m_height/2+mParts[j].GetTargetY(),EB_20,0,(double)(1-i-(4-mGameLevel)),30*mCounter+20);
					AngleShot(m_x-m_width/2+mParts[j].GetTargetX(), m_y-m_height/2+mParts[j].GetTargetY(),EB_40,0,(double)(13-i-(4-mGameLevel)),30*mCounter+30);
					AngleShot(m_x-m_width/2+mParts[j].GetTargetX(), m_y-m_height/2+mParts[j].GetTargetY(),EB_20,0,(double)(13-i-(4-mGameLevel)),-30*mCounter+20);
					AngleShot(m_x-m_width/2+mParts[j].GetTargetX(), m_y-m_height/2+mParts[j].GetTargetY(),EB_40,0,(double)(13-i-(4-mGameLevel)),-30*mCounter+30);
				}
			}
		}
		/*
		int freq=70;
		if((mTimer-50)%freq==freq-1 || (mTimer-50)%freq==freq-1-20){
				mSE->PlaySingleSound(SE_SHT2);
				AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_80,0,18.0,GetShotAngleFromPartsAngle(0));
				for(int i=0;i<5;i++)
					AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_20,3,12.0+i,GetShotAngleFromPartsAngle(0));
				for(int i=0;i<7;i++)
					AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_26,
					2,(double)(17-i),GetShotAngleFromPartsAngle(0)+rand()%16-8);
		}*/

	}else if(mTimer<350){
		if(mTimer==290)mSE->PlaySingleSound(SE_KYP1);
		int t=(mTimer-290);
		int x=(int)(m_x-m_width /2+mParts[0].GetTargetX());
		int y=(int)(m_y-m_height/2+mParts[0].GetTargetY());
		mFrontEffectManager->CreateEclipsedCircle(x,y,10+t*12,x-4,y-5,8+(int)(t*11.5),0xFFFFFFFF);
	}else if(mTimer<420){
		CVector v(mParts[0].GetEndX()-mParts[0].GetStartX(), mParts[0].GetEndY()-mParts[0].GetStartY());
		v.Rotate(N_PI*mParts[0].GetAngle());
		double spd=1+mGameLevel*6+rand()%5+mCounter/10;
		int angle= GetShotAngleFromPartsAngle(0);
		const int range=140;
		if(mTimer%3==0){
			mCounter++;
			mSE->PlaySingleSound(SE_SHT1);
			int x=m_x-m_width/2 +mParts[0].GetTargetX()+v.x;
			int y=m_y-m_height/2+mParts[0].GetTargetY()+v.y;
			AngleShot(x,y,EB_26,2,spd,angle+rand()%20-10);
			AngleShot(x,y,EDAB_80,0,20+spd+2,angle+rand()%20-10);
		}
	}else if(mTimer<500){
		if(mTimer==420)mSE->PlaySingleSound(SE_KYP1);
		for(int i=5;i<=6;i++){
			int t=(mTimer-420);
			int x=(int)(m_x-m_width /2+mParts[i].GetTargetX());
			int y=(int)(m_y-m_height/2+mParts[i].GetTargetY());
			mFrontEffectManager->CreateEclipsedCircle(x,y,10+t*12,x-4,y-5,8+(int)(t*11.5),0xFFFFFFFF);
		}
	}else if(mTimer<700){
		m_y=ExMath::asymptote(m_y,400,(mTimer-420)*0.125);
		if(mTimer%3==0){
			mSE->PlaySingleSound(SE_SHT1);
		}
		mParts[1].SetAngle(-abs(200*sin(N_PI*(mTimer*23))));
		mParts[2].SetAngle( abs(200*sin(N_PI*(mTimer*23+90))));
		LinkFrontParts(3, 1, -abs(270*sin(N_PI*(mTimer*23))));
		LinkFrontParts(4, 2,  abs(270*sin(N_PI*(mTimer*23+90))));
		LinkFrontParts(5, 3, mParts[5].GetAngle());
		LinkFrontParts(6, 4, mParts[6].GetAngle());
		
		if(mTimer%3==0){
			CVector head=GetFrontPartsHead(5);
			mSE->PlaySingleSound(SE_EXP5);
			SampleExplosion2((int)head.x,(int)head.y);
			AngleShot((int)head.x, (int)head.y,EB_40,0,2+rand()%5,rand()%360);

			head=GetFrontPartsHead(6);
			mSE->PlaySingleSound(SE_EXP5);
			SampleExplosion2((int)head.x,(int)head.y);
			AngleShot((int)head.x, (int)head.y,EB_40,0,2+rand()%5,rand()%360);
		}
	}else{
		mTimer=10;
		mCicleCounter++;
		if(mCicleCounter==2){mLife=-1;}
	}

	m_vx=0;
	BackLightLarge();
	return;
}

void CBoss2::Update2(){
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

void CBoss2::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	CreateBoss();
	CExRect::InitRect(&mRectBulletHit,-m_width/2,-m_height/2,m_width/2,0);
	CExRect::InitRect(&mRectPlayerHit,-m_width/2,-m_height/2,m_width/2,0);
	mParts[0].InitParts(BOSS_PARTS_BOSS2_HEAD,m_width/2,98);
	mParts[1].InitParts(BOSS_PARTS_BOSS2_ARM_LEFT ,m_width/2-50,105);
	mParts[2].InitParts(BOSS_PARTS_BOSS2_ARM_RIGHT,m_width/2+50,105);
	mParts[3].InitParts(BOSS_PARTS_BOSS2_ARM_LEFT);
	mParts[4].InitParts(BOSS_PARTS_BOSS2_ARM_RIGHT);
	mParts[5].InitParts(BOSS_PARTS_BOSS2_SAW_LEFT);
	mParts[6].InitParts(BOSS_PARTS_BOSS2_SAW_RIGHT);
}
