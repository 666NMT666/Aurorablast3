class CBoss3:public CBoss{
private:
	static const int NUM_WHEELS=10;
	int mCicleCounter;
public:
	CBoss3():CBoss(){
		mLife=420;
		mExLife=1;
		mLife0=mLife;
		mCicleCounter=0;
	}
	void Update();
	void Update1();
	void Update2();

	void Swing();
	void SwingRight(double rate, int angle);
	void SwingLeft(double rate, int angle);
	void Create(int x,int y,int kind,int suKind,double vx,double vy,const CCreateInfo& info);
	void MainFire(int j);
};

void CBoss3::Swing() {
	mParts[0].InitParts(COMMON_PARTS_CANNON170x500, m_width / 2 + 110, 148);
	mParts[1].InitParts(COMMON_PARTS_CANNON170x500, m_width / 2 - 110, 148);
	for (int i = 0; i < 4; i++) {
		static const int rnd[4] = {1,7,5,17};
		mParts[4 + 2 * i].SetAngle(80 * cos(N_PI*mTimer + rnd[i] * 14) * sin(rnd[i]+N_PI * (13+rnd[i]) * mTimer));
		mParts[4 + 2 * i + 1].SetAngle(80 * sin(N_PI*mTimer+rnd[i]*14) * sin(-N_PI+ rnd[i] * (13 + rnd[i]) * mTimer));
	}
	for (int i = 0; i < 4; i++) {
		LinkFrontParts(12 + 2 * i, 4 + 2 * i, -40 * sin(N_PI * 13 * mTimer));
		LinkFrontParts(12 + 2 * i + 1, 4 + 2 * i + 1,  40 * sin(N_PI * 13 * mTimer));
	}
	for (int i = 0; i < 4; i++) {
		LinkFrontParts(20 + 2 * i, 12 + 2 * i, -140 * sin(N_PI * 13 * mTimer));
		LinkFrontParts(20 + 2 * i + 1, 12 + 2 * i + 1, 140 * sin(N_PI * 13 * mTimer));
	}
}

void CBoss3::SwingRight(double rate, int angle) {
	static const int rnd[4] = {25,1,9,55};
	for (int i = 0; i < 4; i++) {
		int a = mParts[4 + 2 * i + 1].GetAngle();
		a = ExMath::asymptote(a, angle, rate);
		mParts[4 + 2 * i + 1].SetAngle(a + rnd[i] / 2);
	}
	for (int i = 0; i < 4; i++) {
		int a = mParts[12 + 2 * i + 1].GetAngle();
		a = ExMath::asymptote(a, angle*1.2, rate);
		LinkFrontParts(12 + 2 * i + 1, 4 + 2 * i + 1, a);
	}
	for (int i = 0; i < 4; i++) {
		int a = mParts[20 + 2 * i + 1].GetAngle();
		a = ExMath::asymptote(a, angle*1.4, rate);
		LinkFrontParts(20 + 2 * i + 1, 12 + 2 * i + 1, a+rnd[i]);
	}
}

void CBoss3::SwingLeft(double rate, int angle) {
	static const int rnd[4] = { -25,-1,-9,-55 };
	for (int i = 0; i < 4; i++) {
		int a = mParts[4 + 2 * i].GetAngle();
		a = ExMath::asymptote(a, angle, rate);
		mParts[4 + 2 * i].SetAngle(a + rnd[i] / 2);
	}
	for (int i = 0; i < 4; i++) {
		int a = mParts[12 + 2 * i].GetAngle();
		a = ExMath::asymptote(a, angle*1.2, rate);
		LinkFrontParts(12 + 2 * i, 4 + 2 * i, a);
	}
	for (int i = 0; i < 4; i++) {
		int a = mParts[20 + 2 * i].GetAngle();
		a = ExMath::asymptote(a, angle*1.4, rate);
		LinkFrontParts(20 + 2 * i, 12 + 2 * i, a + rnd[i]);
	}
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
	}
	else if (mTimer<600) {
		if (mTimer % 8 == 0) {
			mSE->PlaySingleSound(SE_EXP2);
			mCounter++;
			for (int i = 0; i<3 + mGameLevel / 2; i++) {
				AngleShot(m_x, m_y - 100, EB_80, 0, (double)(1 - i - (4 - mGameLevel)), 30 * mCounter + 20);
				AngleShot(m_x, m_y - 100, EB_40, 0, (double)(13 - i - (4 - mGameLevel)), 30 * mCounter + 30);
				AngleShot(m_x, m_y - 100, EB_80, 0, (double)(13 - i - (4 - mGameLevel)), -30 * mCounter + 20);
				AngleShot(m_x, m_y - 100, EB_40, 0, (double)(13 - i - (4 - mGameLevel)), -30 * mCounter + 30);
			}
		}
	}
	else if(mTimer<800){
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
	Swing();
	if (mTimer == 1) {
		for (int i = 2; i < mMaxParts; i++) {
			mParts[i].SetBltType(BLT_KEY);
		}
		for (int i = 0; i < mMaxBackParts; i++) {
			mBackParts[i].SetBltType(BLT_KEY);
		}
		SetImg(BOSS3_2);
		CExRect::InitRect(&mRectPlayerHit, mRectPlayerHit.left, mRectPlayerHit.top, mRectPlayerHit.right, 130);
		CExRect::InitRect(&mRectBulletHit, mRectBulletHit.left, mRectBulletHit.top, mRectBulletHit.right, 90);
	}
	if (mTimer < 25) {
		if (mTimer == 2) mSE->PlaySingleSound(SE_TND1);
		if (mTimer % 4 == 0) mSE->PlaySingleSound(SE_EXP6);
		if (mTimer % 4 == 2) mSE->PlaySingleSound(SE_EXP5);
		if (mTimer % 4 == 0) {
			for (int i = 0; i<6; i++)mEffectManager->CreateEffect((int)m_x, BATTLE_TOP, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, -rand() % 5 + i * 10+5, 0, 3, 0, 0);
			mEffectManager->CreateEffect(m_x, m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
			for (int i = 0; i<4; i++) {
				mDebrisManager->CreateDebris((int)m_x, (int)m_y, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
				mDebrisManager->CreateDebris((int)m_x, (int)m_y, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			}
		}
	}

	if (mTimer < 100) {
		
	}
	else if (mTimer < 260) {
		if (mTimer % 70-mGameInfo->GetLevel()*5 == 0) {
			mSE->PlaySingleSound(SE_EXP2);
			int p[5] = { EMISSILE_ZIGZAG,0,0,0,0 };
			CCreateInfo info(p);
			int angle = ExMath::angleBetweenPoints(m_x, m_y, mPlayer->GetX(), mPlayer->GetY());
			AngleMissile((int)m_x, (int)m_y, EB_MINE_30x30, 0, 10.0, angle, CCreateInfo::CCreateInfo(EMISSILE_ZIGZAG, 0, 0, 0, 0));
		}

		int tt = mTimer % 35;
		if (tt < 20) {
			SwingRight(tt*0.5, 80);
			SwingLeft(tt*0.5, -80);
		}
		else {
			SwingRight(tt*0.5, 80 - (tt - 20) * 20);
			SwingLeft(tt*0.5, -80 + (tt - 20) * 20);
			if (mPlayer->GetX()>m_x + 100 || mPlayer->GetX() < m_x - 100) {
				mPlayer->ForcePlayer(0, 2);
			}
		}
	}
	else if (mTimer < 300) {
		int freq[5] = { 22,20,18,17,16 };
		if (mTimer%freq[mGameLevel] == 0) {
			for (int j = 0; j < 2; j++) {
				mSE->PlaySingleSound(SE_EXP3);
				int p[5] = { 0,20,30,1,0 };
				CCreateInfo info(p);
				for (int i = 0; i < 5; i++) {
					int x = mParts[j].GetTargetX() - m_width / 2;
					int y = mParts[j].GetTargetY() - m_height / 2;
					int dx = 40 * sin(N_PI*(20 + 30 * i));
					int dy = 40 * cos(N_PI*(20 + 30 * i));
					mEMManager->Create<CEnemyMissile>((int)m_x + x + dx, (int)m_y + y + dy, 0, 1, dx / 2, dy / 2, info);
					mEMManager->Create<CEnemyMissile>((int)m_x + x - dx, (int)m_y + y + dy, 0, 1, -dx / 2, dy / 2, info);
				}
			}
		}
	}
	else if (mTimer < 480) {
		int tt = mTimer - 300;
		if (tt < 100) {
			SwingRight(tt*0.5, 80);
			SwingLeft(tt*0.5, -80);

		}
		else if(tt<120) {
			SwingRight(tt*0.5, 80 - (tt - 100) * 20);
			SwingLeft(tt*0.5, -80 + (tt - 100) * 20);
			if (tt == 110) {
				mSE->PlaySingleSound(SE_BOM1);
				CCreateInfo info(KILLERSHOT_GRAVITY,0,0,0,0);
				AngleMissile((int)m_x, 10, EB_KILLERSHOT_160x160, 4, KILLERSHOT_GRAVITY, 20, 90, 80000, 0, 0);
			}
		}
	}
	else if (mTimer < 800) {
		int tt = mTimer % 70;
		int ttt = mTimer % 35;
		if (tt < 20) {
			SwingRight(ttt*0.5, 80);
		}
		else if (tt<35) {
			SwingRight(ttt*0.5, 80 - (ttt - 20) * 20);
			if (tt == 25) {
				mSE->PlaySingleSound(SE_BOM1);
				CCreateInfo info(KILLERSHOT_GRAVITY, 0, 0, 0, 0);
				AngleMissile((int)m_x +100, 10, EB_KILLERSHOT_160x160, 4, KILLERSHOT_GRAVITY, 20, 90, 80000, 0, 0);
			}
		}
		else if (tt < 35+20) {
			SwingLeft(ttt*0.5, -80);
		}
		else if (tt<70) {
			SwingLeft(ttt*0.5, -80 + (ttt - 20) * 20);
			if (tt == 30+25) {
				mSE->PlaySingleSound(SE_BOM1);
				CCreateInfo info(KILLERSHOT_GRAVITY, 0, 0, 0, 0);
				AngleMissile((int)m_x - 100, 10, EB_KILLERSHOT_160x160, 4, KILLERSHOT_GRAVITY, 20, 90, 80000, 0, 0);
			}
		}
	}
	else {
		mTimer = 40;
	}

	if (mTimer % 5 == 0 && mTimer%100 <40) {
		double spd = (double)(14 + mGameLevel * 4 + rand() % 10);
		mSE->PlaySingleSound(SE_EXP4);
		CVector head = GetFrontPartsHead(0);
		for (int i = 0; i<3; i++)
			AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
		head = GetFrontPartsHead(1);
		for (int i = 0; i<3; i++)
			AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
	}

	for (int i = 4; i < 27; i++) {
		if (mParts[i].hitTest(
			(int)m_x - m_width / 2 + mParts[i].GetTargetX() - mParts[i].GetStartX(),
			(int)m_y - m_height / 2 + mParts[i].GetTargetY() - mParts[i].GetStartY(),
			mPlayer->GetX(),
			mPlayer->GetY())
			) {
			if (m_x != mPlayer->GetX() || m_y != mPlayer->GetY()) {
				CVector v = CVector::EigenVector(m_x - mPlayer->GetX(), m_y - mPlayer->GetY());
				mPlayer->ForcePlayer(15.0*v.x, 15.0*v.y);
				//mPlayer->AddInertia(30.0*v.x, 30.0*v.y);
			}
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

	mParts[4].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT, m_width / 2 - 65, 35);
	mParts[5].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT, m_width / 2 + 65, 35);
	mParts[6].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT_SMALL, m_width / 2 -75, 73);
	mParts[7].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT_SMALL, m_width / 2 + 75, 73);
	mParts[8].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT_SMALL, m_width / 2 - 60, 93);
	mParts[9].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT_SMALL, m_width / 2 + 60, 93);
	mParts[10].InitParts(BOSS_PARTS_BOSS3_LEG1_LEFT, m_width / 2 - 50, 118);
	mParts[11].InitParts(BOSS_PARTS_BOSS3_LEG1_RIGHT, m_width / 2 + 50, 118);

	mParts[11 + 1].InitParts(BOSS_PARTS_BOSS3_LEG2_LEFT);
	mParts[11 + 2].InitParts(BOSS_PARTS_BOSS3_LEG2_RIGHT);
	mParts[11 + 3].InitParts(BOSS_PARTS_BOSS3_LEG2_LEFT_SMALL);
	mParts[11 + 4].InitParts(BOSS_PARTS_BOSS3_LEG2_RIGHT_SMALL);
	mParts[11 + 5].InitParts(BOSS_PARTS_BOSS3_LEG2_LEFT_SMALL);
	mParts[11 + 6].InitParts(BOSS_PARTS_BOSS3_LEG2_RIGHT_SMALL);
	mParts[11 + 7].InitParts(BOSS_PARTS_BOSS3_LEG2_LEFT);
	mParts[11 + 8].InitParts(BOSS_PARTS_BOSS3_LEG2_RIGHT);

	mParts[19 + 1].InitParts(BOSS_PARTS_BOSS3_LEG3_LEFT);
	mParts[19 + 2].InitParts(BOSS_PARTS_BOSS3_LEG3_RIGHT);
	mParts[19 + 3].InitParts(BOSS_PARTS_BOSS3_LEG3_LEFT_SMALL);
	mParts[19 + 4].InitParts(BOSS_PARTS_BOSS3_LEG3_RIGHT_SMALL);
	mParts[19 + 5].InitParts(BOSS_PARTS_BOSS3_LEG3_LEFT_SMALL);
	mParts[19 + 6].InitParts(BOSS_PARTS_BOSS3_LEG3_RIGHT_SMALL);
	mParts[19 + 7].InitParts(BOSS_PARTS_BOSS3_LEG3_LEFT);
	mParts[19 + 8].InitParts(BOSS_PARTS_BOSS3_LEG3_RIGHT);

	mBackParts[0].InitParts(BOSS_PARTS_BOSS3_TAIL1,m_width/2,117);
	CExRect::InitRect(&mRectBulletHit,-m_width/2-20,-m_height/2,m_width/2+20,-30);
	CExRect::InitRect(&mRectPlayerHit,-m_width/2-20,-m_height/2,m_width/2+20,20);

	for (int i = 2; i < mMaxParts; i++) {
		mParts[i].SetBltType(BLT_NULL);
	}
	mBackParts[0].SetBltType(BLT_NULL);
	
}
