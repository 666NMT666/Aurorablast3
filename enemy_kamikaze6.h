class CEnemyKamikaze6 :public CEnemy {
	double m_tx, m_ty;
public:
	void UpdateEnemy();
	void Killed();
	void CreateEnemy() { mAutoDelFlg = false; m_vy = 3; m_tx = m_ty = 0; }
};

void CEnemyKamikaze6::UpdateEnemy() {
	static const int startTimeInterval = 40;
	if (mTimer<startTimeInterval) {
		m_y += (300 - m_y) / 10.0;
		if (m_y0 >= BATTLE_MIDDLE_Y)mBltInfo.angle = 180;
		m_tx = mPlayer->GetX();
		m_ty = mPlayer->GetY();
	}
	else {
		if (mTimer % 2 == 0) {
			mEffectManager->ExplosionSample(m_x, m_y);
			mSE->PlaySingleSound(SE_EXP2);
		}
		double v = 0.6*(mTimer - startTimeInterval) + 1.0 + mGameLevel;
		if (v >= 17 + mGameLevel)v = 17 + mGameLevel;
		if (v<10) {
			SetVTo(mPlayer->GetX(), mPlayer->GetY(), v);
			DirectTo(mPlayer->GetX(), mPlayer->GetY());
		}
		else {
			SetVOnDirection(v);
		}

		if (mTimer % 4 == 0) {
			NormalShot(m_x, m_y, EB_26, 4, 8);
			NormalShot(m_x, m_y, EB_26, 4, 8, 0, 15);
			NormalShot(m_x, m_y, EB_26, 4, 8, 0, -15);
		}
	}
	BackLightSmall();
}

void CEnemyKamikaze6::Killed() {
	if (mKilledTimer == 0) { mSE->PlaySingleSound(mKilledSound); }
	mEffectManager->CreateEffect((int)m_x, (int)m_y + 15, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
	for (int i = 0; i<10; i++) {
		int v = rand() % 20 + 10;
		double vx = v*cos(N_PI * 18 * i);
		double vy = -v*sin(N_PI * 18 * i);
		mDebrisManager->CreateDebris((int)m_x, (int)m_y, 2, 0, vx, vy, 0, 0, 2, 10, 0);
	}
	mDelFlg = true;
	int pointMul = 200 - mTimer;
	if (pointMul<0)pointMul = 0;
	mPlayer->DestroyEnemy(16, pointMul*pointMul*pointMul);
	for (int i = 0; i<15; i++)mItemManager->CreateItem((int)m_x, (int)m_y, rand() % 2, 0, rand() % 20 - 10, rand() % 20 + (5 - mGameLevel));
}