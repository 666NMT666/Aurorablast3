class CBoss6:public CBoss{
private:
	int mCicleCounter;
public:
	CBoss6():CBoss(){
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
	void MainFire();
	void MainFire2();
	void SubFire(int i);
	void Kyp(int index, int st, int et);
};

void CBoss6::Kyp(int i, int st, int et) {
	if (mTimer >= et)return;
	if (mTimer == st)mSE->PlaySingleSound(SE_KYP1);
	int t = (mTimer - st);
	int x = (int)(m_x - m_width / 2 + mParts[i].GetTargetX());
	int y = (int)(m_y - m_height / 2 + mParts[i].GetTargetY());
	mFrontEffectManager->CreateEclipsedCircle(x, y, 10 + t * 12, x - 4, y - 6, 8 + (int)(t*11.5), 0xFFFFFFFF);
}

void CBoss6::SubFire(int i) {
	CVector v(mParts[i].GetEndX() - mParts[i].GetStartX(), mParts[i].GetEndY() - mParts[i].GetStartY());
	v.Rotate(N_PI*mParts[i].GetAngle());
	double spd = 1 + mGameLevel * 6 + rand() % 25;
	int angle = GetShotAngleFromPartsAngle(i);
	const int range = 140;

	mSE->PlaySingleSound(SE_SHT1);
	int x = m_x - m_width / 2 + mParts[i].GetTargetX() + v.x;
	int y = m_y - m_height / 2 + mParts[i].GetTargetY() + v.y;
	AngleShot(x, y, EB_26, 2, spd, angle + rand() % 20 - 10);
	AngleShot(x, y, EDAB_80, 0, 20 + spd + 2, angle + rand() % 20 - 10);
}

void CBoss6::MainFire2() {
	CVector v(mParts[0].GetEndX() - mParts[0].GetStartX(), mParts[0].GetEndY() - mParts[0].GetStartY());
	v.Rotate(N_PI*mParts[0].GetAngle());
	double spd = 1 + mGameLevel * 6 + rand() % 5 + mCounter / 10;
	int angle = GetShotAngleFromPartsAngle(0);
	const int range = 140;

	mCounter++;
	mSE->PlaySingleSound(SE_SHT1);
	int x = m_x - m_width / 2 + mParts[0].GetTargetX() + v.x;
	int y = m_y - m_height / 2 + mParts[0].GetTargetY() + v.y;
	AngleShot(x, y, EB_26, 2, spd, angle + rand() % 20 - 10);
	AngleShot(x, y, EB_80, 0,40+ spd, angle + rand() % 20 - 10);
	AngleShot(x, y, EDAB_80, 0, 20 + spd + 2, angle + rand() % 20 - 10);
}

void CBoss6::MainFire(){
	CVector head=GetFrontPartsHead(0);
	int angle=180-mBackParts[0].GetAngle();
	double spd=(mGameLevel+2)*4;
	mSE->PlaySingleSound(SE_EXP2);
	AngleShot(head.x,head.y,EDAB_66,0,20+spd,angle);
	AngleShot(head.x,head.y,EDAB_66,0,16+spd,angle);
	for(int i=0;i<16;i++)AngleShot(head.x,head.y,EB_26,2,4+i+spd,angle+rand()%20-10);
	mELManager->Create<CLazerBullet>((int)head.x,(int)head.y,0,0,0.0,60.0,defaultCreateInfo);
}

void CBoss6::Update(){
	UpdateBoss();
	UpdateGameObject();
	if(mExLife<0)return;
	
	if(mExLife==2){
		Update1();
	}
	else if (mExLife == 1) {
		Update2();
	}
	else if (mExLife == 0) {
		Update3();
	}
}



void CBoss6::Update1(){
	if(mTimer==1){
		m_x=(BATTLE_RECT.right+BATTLE_RECT.left)/2;
	}
	if (mTimer < 5) {
		if (mTimer == 2) mSE->PlaySingleSound(SE_TND1);
		if (mTimer % 4 == 0) mSE->PlaySingleSound(SE_EXP6);
		if (mTimer % 4 == 2) mSE->PlaySingleSound(SE_EXP5);
		if (mTimer % 4 == 0) {
			for (int i = 0; i<6; i++)mEffectManager->CreateEffect((int)m_x, BATTLE_BOTTOM, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, rand() % 5 - i * 10, 0, 3, 0, 0);
			mEffectManager->CreateEffect(m_x, m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
			for (int i = 0; i<4; i++) {
				mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
				mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			}
		}
	}else if (mTimer < 20) {
		for (int i = 0; i<20; i++) {
			int v = rand() % 20 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = -v*sin(N_PI * 18 * i) - 20;
			mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
		DirectFrontPartsTo(0,BATTLE_RIGHT,BATTLE_BOTTOM);
	}
	else if (mTimer<200) {
		Kyp(0,21,100);
		if(mTimer%3==0)ChacePartsAngle(mParts[0], mPlayer->GetX(), mPlayer->GetY(), 1);
		if (mTimer > 100) {
			if (mTimer % 3 == 0)MainFire2();
		}

		/*
		int d = ExMath::distanceBetweenPoints(mParts[0].GetTargetX() + m_x, mParts[0].GetTargetY() + m_y, mPlayer->GetX(), mPlayer->GetY());
		int angle = mTimer * 13;
		int sx = m_x - m_width / 2 + mParts[0].GetTargetX();
		int sy = m_y - m_height / 2 + mParts[0].GetTargetY();
		int tx = d * sin(N_PI * angle) + sx;
		int ty = d * cos(N_PI * angle) + sy;

		CLine::drawLine2(m_bg, sx    , sy, tx, ty, 0xFF0000, BATTLE_RECT);
		CLine::drawLine2(m_bg, sx + 1, sy, tx, ty, 0xFFFF0000, BATTLE_RECT);

		mEffectManager->CreateEffect(tx, ty, EFFECT_EXPLOSION_LIGHT_80, 0, 0.02 * (rand() % 100), 0.02 * (rand() % 100), EFFECT_MOTION_SINGLE, 1,0,0);
		CHitTest::CircleToPoint(tx, ty, mPlayer->GetX(), mPlayer->GetY(), 50);
		*/
	}
	else if (mTimer<400) {
		if (rand() % (4 + 5 - mGameLevel) == 0 && mTimer>40) {
			int rnd = rand() % 2;
			CCreateInfo info(m_x+rand()%300-150,rand()%200,0,0,0);
			if (rnd == 0)mEnemyManager->Create2(m_x+rand()%200-100, 100+rand()%350, ENEMY_SPINNER3,0,-5,info);
		}
	} 
	else if (mTimer < 550) {
		if (mTimer % 3 == 0) {
			SubFire(1);
			SubFire(2);
		}
		if (mTimer == 420) {
			for (int i = 0; i < 36; i++) {
				AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 1, mGameInfo->GetLevel() * 3 + 10, i * 10);
				AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 1, mGameInfo->GetLevel() * 3 + 8, i * 10);
			}
		}
	}
	else if (700) {
		int freq[5] = { 28,27,26,22,20 };
		if (mTimer%freq[mGameLevel] == 0) {
			mSE->PlaySingleSound(SE_SHT3);
			int p[5] = { 0,20,30,1,0 };
			CCreateInfo info(p);
			mEMManager->Create<CEnemyMissile>((int)m_x - 140, (int)m_y , EB_DEPTHCHARGE_60x30, 0, rand() % 20 - 10, 10 - rand() % (30 + mGameLevel * 5), info);
			mEMManager->Create<CEnemyMissile>((int)m_x + 140, (int)m_y , EB_DEPTHCHARGE_60x30, 0, rand() % 20 - 10, 10 - rand() % (30 + mGameLevel * 5), info);
		}
	}
	else {
		mTimer=20;
		mCicleCounter++;
		if(mCicleCounter==2){
			mLife=-1;
		}
	}

	m_vx=0;
	return;
}

void CBoss6::Update2() {
	mBackParts[0].SetBltType(BLT_NULL);
	CExRect::InitRect(&mRectPlayerHit, mRectPlayerHit.left, mRectPlayerHit.top, mRectPlayerHit.right, 130);

	int wobble_amp = 300 - mTimer;
	if (wobble_amp < 0)wobble_amp = 0;

	int x_range = wobble_amp * sin(N_PI*mTimer);
	m_x = 480 + x_range * sin(N_PI*mTimer*1.4142);

	int y_range = wobble_amp * sin(N_PI*mTimer*1.723);
	m_y = 180 + y_range * sin(N_PI*mTimer*2.25);

	if (mTimer % 3 == 0 && mTimer % 70 < 25 && mTimer > 120) {
		SubFire(1);
		SubFire(2);
	}

	if (mTimer < 5) {
		if (mTimer == 2) mSE->PlaySingleSound(SE_TND1);
		if (mTimer % 4 == 0) mSE->PlaySingleSound(SE_EXP6);
		if (mTimer % 4 == 2) mSE->PlaySingleSound(SE_EXP5);
		if (mTimer % 4 == 0) {
			for (int i = 0; i<6; i++)mEffectManager->CreateEffect((int)m_x, BATTLE_BOTTOM, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, rand() % 5 - i * 10, 0, 3, 0, 0);
			mEffectManager->CreateEffect(m_x, m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
			for (int i = 0; i<4; i++) {
				mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
				mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			}
		}
	}
	else if (mTimer < 20) {
		for (int i = 0; i<20; i++) {
			int v = rand() % 20 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = -v*sin(N_PI * 18 * i) - 20;
			mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
		DirectFrontPartsTo(0, BATTLE_RIGHT, BATTLE_BOTTOM);
	}
	else if (mTimer<120) {

	}
	else if (mTimer<250) {
		double spd = 8 + mGameLevel * 6 + rand() % 5;
		int angle = 30 + rand() % (30 + mGameLevel * 6) - (30 + mGameLevel * 6) / 2;
		const int range = 140;
		if (mTimer % 3 == 0) {
			mSE->PlaySingleSound(SE_SHT1);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EB_26, 2, spd, angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EDAB_80, 0, 20 + spd + 2, angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EB_26, 2, spd, 180 - angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EDAB_80, 0, 20 + spd + 2, 180 - angle);
		}
	}
	else if (mTimer < 340) {
		if (rand() % 9 == 0) {
			CCreateInfo info(300 + rand() % 360, rand() % 700, 0, 0, 0);
			mEnemyManager->Create2(m_x, m_y, ENEMY_SPINNER3, 0, -5, info);
		}
	}
	else if (mTimer < 400) {
		if (mTimer == 320)mSE->PlaySingleSound(SE_KYP1);
		Kyp(0, 320, 400);

		int angle1 = 5 * (mTimer - 200);
		int angle2 = -13 * (mTimer - 200);
		if (mTimer % 4 == 0 && mTimer > 330) {
			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 1, mGameInfo->GetLevel() * 3 + 10, angle1);
			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 1, mGameInfo->GetLevel() * 3 + 8, angle1);

			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 0, mGameInfo->GetLevel() * 3 + 7, angle2);
			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 0, mGameInfo->GetLevel() * 3 + 4, angle2);
		}
	}
	else if (mTimer < 600) {
		if (mTimer % 60 == 0)mSE->PlaySingleSound(SE_TND1);
		if (mTimer % 30 == 0) {
			AngleMissile((int)m_x, (int)m_y + 100, EB_KILLERSHOT_160x160, 4, KILLERSHOT_GRAVITY, (double)(5 + rand() % 4), 90 - 40, 80000, 0, rand() % 20 - 10);
			AngleMissile((int)m_x, (int)m_y + 100, EB_KILLERSHOT_160x160, 4, KILLERSHOT_GRAVITY, (double)(5 + rand() % 4), 90 + 40, 80000, 0, rand() % 20 - 10);
		}
	}
	else if (mTimer < 800) {
		if (rand() % 9 == 0) {
			CCreateInfo info(300 + rand() % 360, rand() % 700, 0, 0, 0);
			mEnemyManager->Create2(m_x, m_y, ENEMY_SPINNER3, 0, -5, info);
		}
	}
	else {
		mTimer = 120;
		mCicleCounter++;
		if (mCicleCounter == 2) {
			mLife = -1;
		}
	}
}

void CBoss6::Update3() {
	CExRect::InitRect(&mRectPlayerHit, mRectPlayerHit.left, mRectPlayerHit.top, mRectPlayerHit.right, 130);
	mBltInfo.angle=(mTimer*13)%360;
	mBackParts[0].SetBltType(BLT_NULL);
	for (int i = 0; i < 3; i++)mParts[i].SetBltType(BLT_NULL);
	if (mTimer < 5) {
		if (mTimer == 1) {
			SetImg(BOSS6_2);
			CExRect::InitRect(&mRectPlayerHit, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
		}
		if (mTimer == 2) mSE->PlaySingleSound(SE_TND1);
		if (mTimer % 4 == 0) mSE->PlaySingleSound(SE_EXP6);
		if (mTimer % 4 == 2) mSE->PlaySingleSound(SE_EXP5);
		if (mTimer % 4 == 0) {
			for (int i = 0; i<6; i++)mEffectManager->CreateEffect((int)m_x, BATTLE_BOTTOM, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, rand() % 5 - i * 10, 0, 3, 0, 0);
			mEffectManager->CreateEffect(m_x, m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
			for (int i = 0; i<4; i++) {
				mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
				mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			}
		}
	}
	else if (mTimer < 20) {
		for (int i = 0; i<20; i++) {
			int v = rand() % 20 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = -v*sin(N_PI * 18 * i) - 20;
			mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
		DirectFrontPartsTo(0, BATTLE_RIGHT, BATTLE_BOTTOM);
	}
	else if (mTimer<120) {

	}
	else if (mTimer<250) {
		double spd = 8 + mGameLevel * 6 + rand() % 5;
		int angle = 30 + rand() % (30 + mGameLevel * 6) - (30 + mGameLevel * 6) / 2;
		const int range = 140;
		if (mTimer % 3 == 0) {
			mSE->PlaySingleSound(SE_SHT1);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EB_26, 2, spd, angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EDAB_80, 0, 20 + spd + 2, angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EB_26, 2, spd, 180 - angle);
			AngleShot(m_x + rand() % range - range / 2, m_y + rand() % range - range / 2 - 50, EDAB_80, 0, 20 + spd + 2, 180 - angle);
		}
	}
	else if (mTimer < 340) {
		if (rand() % 9 == 0) {
			CCreateInfo info(300 + rand() % 360, rand() % 700, 0, 0, 0);
			mEnemyManager->Create2(m_x, m_y, ENEMY_SPINNER3, 0, -5, info);
		}
	}
	else if (mTimer < 400) {
		if (mTimer == 320)mSE->PlaySingleSound(SE_KYP1);
		Kyp(0, 320, 400);

		int angle1 = 5 * (mTimer - 200);
		int angle2 = -13 * (mTimer - 200);
		if (mTimer % 4 == 0 && mTimer > 330) {
			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 1, mGameInfo->GetLevel() * 3 + 10, angle1);
			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 1, mGameInfo->GetLevel() * 3 + 8, angle1);

			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 0, mGameInfo->GetLevel() * 3 + 7, angle2);
			AngleMissile(m_x, m_y - m_height / 2 + mParts[0].GetTargetY(), EB_MINE_30x30, 0, mGameInfo->GetLevel() * 3 + 4, angle2);
		}
	}
	else if (mTimer < 600) {
		if (mTimer % 60 == 0)mSE->PlaySingleSound(SE_TND1);
		if (mTimer % 30 == 0) {
			AngleMissile((int)m_x, (int)m_y + 100, EB_KILLERSHOT_160x160, 4, KILLERSHOT_GRAVITY, (double)(5 + rand() % 4), 90 - 40, 80000, 0, rand() % 20 - 10);
			AngleMissile((int)m_x, (int)m_y + 100, EB_KILLERSHOT_160x160, 4, KILLERSHOT_GRAVITY, (double)(5 + rand() % 4), 90 + 40, 80000, 0, rand() % 20 - 10);
		}
	}
	else if (mTimer < 800) {
		if (rand() % 9 == 0) {
			CCreateInfo info(300 + rand() % 360, rand() % 700, 0, 0, 0);
			mEnemyManager->Create2(m_x, m_y, ENEMY_SPINNER3, 0, -5, info);
		}
	}
	else {
		mTimer = 120;
		mCicleCounter++;
		if (mCicleCounter == 2) {
			mLife = -1;
		}
	}
}

void CBoss6::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	CreateBoss();
	

	mBackParts[0].InitParts(BOSS_PARTS_BOSS6_BASE,m_width/2,m_height/2-80);
	mParts[0].InitParts(BOSS_PARTS_BOSS6_CANNON_MAIN, m_width / 2, 287);
	mParts[1].InitParts(BOSS_PARTS_BOSS6_CANNON_SUB, m_width / 2 - 100, 245);
	mParts[2].InitParts(BOSS_PARTS_BOSS6_CANNON_SUB, m_width / 2 + 100, 245);
	CExRect::InitRect(&mRectPlayerHit, mRectPlayerHit.left, mRectPlayerHit.top, mRectPlayerHit.right, mRectPlayerHit.bottom - 250);
}
