class CEnemyKamikaze3:public CEnemy{
	double m_tx,m_ty;
	public:
	void UpdateEnemy();
	void Killed();
	void CreateEnemy(){
		mAutoDelFlg=false;
		m_vy=3;m_vy=3;
		m_tx=m_ty=0;
		mBackParts[0].InitParts(ENEMY_PARTS_BIG_WING_LEFT, m_width / 2 - 100, m_height / 2);
		mBackParts[1].InitParts(ENEMY_PARTS_BIG_WING_RIGHT, m_width / 2 + 100, m_height / 2);
	}
};

void CEnemyKamikaze3::UpdateEnemy(){
	static const int startTimeInterval=1;
	if(mTimer<5){
		if(mTimer%2==0){
			mEffectManager->ExplosionSample(m_x,m_y);
			mSE->PlaySingleSound(SE_EXP2);
		}
		double v=0.6*(mTimer-startTimeInterval)+16.0+mGameLevel;
		if(v>=20+mGameLevel)v=20+mGameLevel;
		SetVTo(mPlayer->GetX(),mPlayer->GetY(),v);
		DirectTo(mPlayer->GetX(),mPlayer->GetY());
	}
	BackLightSmall();
	mBackParts[0].SetBltType(BLT_NULL);
	mBackParts[1].SetBltType(BLT_NULL);
}

void CEnemyKamikaze3::Killed(){
	m_y += 8.0;
	PurgeBackParts(5, 30, 4, 8, 0, 0);
	/////////////        PURGE  PARTS      ///////////////////
	for (int i = 0; i < 2;i++)mBackParts[i].SetBltType(BLT_KEY);

	if (mKilledTimer == 0) mSE->PlaySingleSound(mKilledSound);
	if (mKilledTimer % 4 == 0) {
		for (int i = 0; i<6; i++)mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, -rand() % 5 + 60 - i * 10, 0, 3, 0, 0);
		mEffectManager->CreateEffect((int)m_x, (int)m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
		for (int i = 0; i<4; i++) {
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
		}
	}
	if (mKilledTimer == 8) {
		for (int i = 0; i < 20; i++) {
			int v = rand() % 10 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = -v*sin(N_PI * 18 * i) - 20;
			mBackEffectManager->CreateEffect(m_x, m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
	}
	if (mKilledTimer >= 16) {
		mDelFlg = true;
		for (int i = 0; i<20; i++) {
			int v = rand() % 20 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = v*sin(N_PI * 18 * i) - 20;
			mBackEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
	}
	int pointMul = 500 - mTimer;
	if (pointMul<0)pointMul = 0;
	mPlayer->DestroyEnemy(16, pointMul*pointMul*pointMul);
	if (mKilledTimer == 8) {
		for (int i = 0; i<16; i++)mItemManager->CreateItem((int)m_x, (int)m_y, rand() % 2, 0, rand() % 20 - 10, rand() % 20);
	}
	if (mKilledTimer == 12) {
		for (int i = 0; i<4; i++)mItemManager->CreateItem((int)m_x, (int)m_y, 2, rand() % 20 - 10, 0, rand() % 20);
	}
}