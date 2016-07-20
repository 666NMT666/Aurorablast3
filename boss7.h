class CBoss7:public CBoss{
private:
	int mCicleCounter;
public:
	CBoss7():CBoss(){
		mLife=640;
		mExLife=2;
		mLife0=mLife;
		mCicleCounter=0;
	}
	void Update();
	void Update1();
	void Update2();
	void Update3();

	void Create(int x,int y,int kind,int suKind,double vx,double vy,const CCreateInfo& info);
	void Transform(int w, int h,int k) {
		mImgId = k;
		m_width = w;
		m_height = h;
	}
	void Walk();
	void MainFire();
	void GravityFire(double v);
	void IceFire(double v);	
};

void CBoss7::GravityFire(double v) {

}

void CBoss7::MainFire(){
	CVector head=GetBackPartsHead(1);
	int angle=180-mBackParts[3].GetAngle();
	double spd=(mGameLevel+2)*4;
	mSE->PlaySingleSound(SE_EXP2);
	AngleShot(head.x,head.y,EDAB_66,0,20+spd,angle);
	AngleShot(head.x,head.y,EDAB_66,0,16+spd,angle);
	for(int i=0;i<16;i++)AngleShot(head.x,head.y,EB_26,2,4+i+spd,angle+rand()%20-10);
	mELManager->Create<CLazerBullet>((int)head.x,(int)head.y,0,0,-60.0,0.0,defaultCreateInfo);
}

void CBoss7::Update(){
	UpdateBoss();
	UpdateGameObject();
	if(mExLife<0)return;

	if (mExLife == 2) {
		Update1();
	} else if(mExLife==1){
		Update2();
	}else if(mExLife==0){
		Update3();
	}
}

void CBoss7::Update1(){
	mBltInfo.angle = (mTimer * 13) % 360;
	mBackParts[0].SetAngle(mTimer * 29);
	mBackParts[1].SetAngle(-mTimer * 41);

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

	}
	else if(mTimer<100){
		if(mTimer==85)mSE->PlaySingleSound(SE_CRY1);
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

void CBoss7::Update2() {
	mBltInfo.angle = (mTimer * 13) % 360;
	if (mTimer < 10) {
		mCicleCounter = 0;
		mBackParts[0].SetBltType(BLT_NULL);
		mBackParts[1].SetBltType(BLT_NULL);
	}
	else if (mTimer<600) {
		double spd = 8 + mGameLevel * 6 + rand() % 5;
		int angle = 150 + rand() % (30 + mGameLevel * 6) - (30 + mGameLevel * 6) / 2;
		const int range = 140;
		if (mTimer % 3 == 0) {
			mSE->PlaySingleSound(SE_SHT1);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EB_26, 2, spd, angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EDAB_80, 0, 20 + spd + 2, angle);
		}
	}
	else {
		mTimer = 10;
		mCicleCounter++;
		if (mCicleCounter == 2) {
			mLife = -1;
		}
	}
}

void CBoss7::Update3() {
	mBltInfo.angle = (mTimer * 13) % 360;
	if (mTimer < 10) {
		mCicleCounter = 0;
		mBackParts[0].SetBltType(BLT_NULL);
		mBackParts[1].SetBltType(BLT_NULL);
	}
	else if (mTimer<600) {
		double spd = 8 + mGameLevel * 6 + rand() % 5;
		int angle = 150 + rand() % (30 + mGameLevel * 6) - (30 + mGameLevel * 6) / 2;
		const int range = 140;
		if (mTimer % 3 == 0) {
			mSE->PlaySingleSound(SE_SHT1);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EB_26, 2, spd, angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EDAB_80, 0, 20 + spd + 2, angle);
		}
	}
	else {
		mTimer = 10;
		mCicleCounter++;
		if (mCicleCounter == 2) {
			mLife = -1;
		}
	}
}

void CBoss7::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	CreateBoss();

	mBackParts[0].InitParts(BOSS_PARTS_BOSS7_SPINNER, m_width / 2, m_height / 2);
	mBackParts[1].InitParts(BOSS_PARTS_BOSS7_CROSS_GUN, m_width / 2, m_height / 2);

	//mParts[0].InitParts(BOSS_PARTS_BOSS1_HEAD,98,37);
}
