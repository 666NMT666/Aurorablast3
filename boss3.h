class CBoss3:public CBoss{
private:
	static const int NUM_WHEELS=10;
	int mCicleCounter;
public:
	CBoss3():CBoss(){
		mLife=40;
		mExLife=1;
		mLife0=mLife;
		mCicleCounter=0;
	}
	void Update();
	void Update1();
	void Update2();

	void Saw();
	void Create(int x,int y,int kind,int suKind,double vx,double vy,const CCreateInfo& info);
	void MainFire(int j);
};

void CBoss3::Saw() {
	for (int i = 0; i < NUM_WHEELS; i++) {
		int a = (mTimer * 23) % 360;
		mParts[i+4].SetAngle(a);
		mParts[i + NUM_WHEELS + 4].SetAngle(-a);
	}

	//‚±‚Ì•Ó‚ÅAŠewheel‚©‚çAngleShot();

}
void CBoss3::MainFire(int j){
	CVector head=GetFrontPartsHead(j);
	int angle=180-mParts[j].GetAngle();
	double spd=(mGameLevel+2)*4;
	mSE->PlaySingleSound(SE_EXP2);
	AngleShot(head.x,head.y,EDAB_66,0,20+spd,angle);
	AngleShot(head.x,head.y,EDAB_66,0,16+spd,angle);
	for(int i=0;i<16;i++)AngleShot(head.x,head.y,EB_26,2,4+i+spd,angle+rand()%20-10);
	mELManager->Create<CLazerBullet>((int)head.x,(int)head.y,0,0,-60.0,0.0,defaultCreateInfo);
}

void CBoss3::Update(){
	UpdateBoss();
	UpdateGameObject();
	if(mExLife<0)return;
	if(mExLife==1){
		Update1();
	}else if(mExLife==0){
		Update2();
	}
}

void CBoss3::Update1(){
	mBackParts[0].SetBltType(BLT_NULL);
	if(mTimer==1){
		m_y=BATTLE_BOTTOM+m_height/2;
		m_x=(BATTLE_RECT.right+BATTLE_RECT.left)/2;
	}
	if(mTimer<=200){
		m_x=ExMath::asymptote(m_x,(BATTLE_RECT.right+BATTLE_RECT.left)/2,mTimer*0.125);
		m_y=ExMath::asymptote(m_y,150,mTimer*0.125);
		if(m_y<150)m_y=150;
	}
	if(mTimer<50){}
	else if(mTimer<100){ }
	else if(mTimer<200){
		int freq[5]={22,20,18,17,16};
		if(mTimer%freq[mGameLevel]==0){
			int j=rand()%2;
			mSE->PlaySingleSound(SE_EXP3);
			int p[5]={0,20,30,1,0};
			CCreateInfo info(p);
			for(int i=0;i<5;i++){
				int x=mParts[j].GetTargetX()-m_width/2;
				int y=mParts[j].GetTargetY()-m_height/2;
				int dx=40*sin(N_PI*(20+30*i));
				int dy=40*cos(N_PI*(20+30*i));
				mEMManager->Create<CEnemyMissile>((int)m_x+x+dx,(int)m_y+y+dy,0,1, dx/2,dy/2,info);
				mEMManager->Create<CEnemyMissile>((int)m_x+x-dx,(int)m_y+y+dy,0,1,-dx/2,dy/2,info);
			}
		}
	}else if(mTimer<250){	
	}else if(mTimer<400){
		if(mTimer%5==0){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head=GetFrontPartsHead(0);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
			head=GetFrontPartsHead(1);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
	}else if(mTimer<600){
		int freq[5]={32,30,26,20,16};
		if(mTimer%freq[mGameLevel]==0){
			int j=rand()%2;
			mSE->PlaySingleSound(SE_EXP3);
			int p[5]={0,20,30,1,0};
			CCreateInfo info(p);
			for(int i=0;i<5;i++){
				int x=mParts[j].GetTargetX()-m_width/2;
				int y=mParts[j].GetTargetY()-m_height/2;
				int dx=40*sin(N_PI*(20+30*i));
				int dy=40*cos(N_PI*(20+30*i));
				mEMManager->Create<CEnemyMissile>((int)m_x+x+dx,(int)m_y+y+dy,0,1, dx/2,dy/2,info);
				mEMManager->Create<CEnemyMissile>((int)m_x+x-dx,(int)m_y+y+dy,0,1,-dx/2,dy/2,info);
			}
		}
		if(mTimer%5==0){
			double spd=(double)(14+mGameLevel*4+rand()%10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head=GetFrontPartsHead(0);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
			head=GetFrontPartsHead(1);
			for(int i=0;i<3;i++)
				AngleShot(head.x,head.y,EB_80,0,spd+i*2,90);
		}
	}else if(mTimer<800){
		if(mTimer%8==0){
			mSE->PlaySingleSound(SE_EXP2);
			mCounter++;
			for(int i=0;i<3+mGameLevel/2;i++){
				AngleShot(m_x, m_y-100,EB_80,0,(double)(1-i-(4-mGameLevel)),30*mCounter+20);
				AngleShot(m_x, m_y-100,EB_40,0,(double)(13-i-(4-mGameLevel)),30*mCounter+30);
				AngleShot(m_x, m_y-100,EB_80,0,(double)(13-i-(4-mGameLevel)),-30*mCounter+20);
				AngleShot(m_x, m_y-100,EB_40,0,(double)(13-i-(4-mGameLevel)),-30*mCounter+30);
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
	return;
}

void CBoss3::Update2(){
	Saw();
	if (mTimer == 1) {
		for (int i = 2; i < mMaxParts; i++) {
			mParts[i].SetBltType(BLT_KEY);
		}
		for (int i = 0; i < mMaxBackParts; i++) {
			mBackParts[i].SetBltType(BLT_KEY);
		}
	}
	if (mTimer < 20) {
		SetImg(BOSS3_2);
		CExRect::InitRect(&mRectPlayerHit, mRectPlayerHit.left, mRectPlayerHit.top, mRectPlayerHit.right, 130);
		CExRect::InitRect(&mRectBulletHit, mRectBulletHit.left, mRectBulletHit.top, mRectBulletHit.right, 90);

	}
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

void CBoss3::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	CreateBoss();
	mParts[0].InitParts(COMMON_PARTS_CANNON170x500,m_width/2+100,298);
	mParts[1].InitParts(COMMON_PARTS_CANNON170x500,m_width/2-100,298);

	mParts[2].InitParts(BOSS_PARTS_BOSS3_CHELICERAE_LEFT, m_width / 2 - 30, 53);
	mParts[3].InitParts(BOSS_PARTS_BOSS3_CHELICERAE_RIGHT, m_width / 2 + 30, 53);

	mParts[4].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT, m_width / 2 - 80, 53);
	mParts[5].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT, m_width / 2 + 80, 53);
	mParts[6].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT, m_width / 2 -100, 73);
	mParts[7].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT, m_width / 2 + 100, 73);

	mParts[8].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT, m_width / 2 - 120, 93);
	mParts[9].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT, m_width / 2 + 120, 93);
	mParts[10].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT, m_width / 2 - 140, 113);
	mParts[11].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT, m_width / 2 + 140, 113);

	mBackParts[0].InitParts(BOSS_PARTS_BOSS3_TAIL1,m_width/2,117);
	CExRect::InitRect(&mRectBulletHit,-m_width/2-20,-m_height/2,m_width/2+20,-30);
	CExRect::InitRect(&mRectPlayerHit,-m_width/2-20,-m_height/2,m_width/2+20,20);

	for (int i = 2; i < mMaxParts; i++) {
		mParts[i].SetBltType(BLT_NULL);
	}
	mBackParts[0].SetBltType(BLT_NULL);
	
}
