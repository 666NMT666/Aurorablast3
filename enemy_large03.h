#pragma once
class CEnemyLarge03 :public CEnemy {
public:
	void UpdateEnemy();
	void Killed();
};

void CEnemyLarge03::UpdateEnemy() {
	if (mTimer <= 1) {
		mAutoDelFlg = false;
		m_vx = 0; m_vy = 0;
		mInvincibleFlg = true;
	} else if (mTimer<40) {
		m_y = ExMath::asymptote((double)BATTLE_RECT.bottom + m_height / 2 - 1, (double)mCreateInfo.params[0], (double)mTimer);
	}
	else if (mTimer<60) { mInvincibleFlg = false; }
	else if(mTimer<200){
		m_vy = -0.5;
		mAutoDelFlg = true;
	}else if(mTimer<400){
		m_vy = 0;
	}
	else {
		m_vy = -5;
	}
	if (rand() % (3 + 5 - mGameLevel) == 0 && mTimer>40) {
		int rnd = rand() % 4;
		if (rnd == 0)AngleMissile((int)m_x + 50, (int)m_y + 35, 3, 0, 6, (double)(3 + rand() % 4), 90 + rand() % 19 - 9 - 20, 0, 0, 0);
		if (rnd == 1)AngleMissile((int)m_x - 50, (int)m_y + 35, 3, 0, 6, (double)(3 + rand() % 4), 90 + rand() % 19 - 9 + 20, 0, 0, 0);
		if (rnd == 2)AngleMissile((int)m_x + 35, (int)m_y + 40, 3, 0, 6, (double)(3 + rand() % 4), 90 + rand() % 19 - 9 - 13, 0, 0, 0);
		if (rnd == 3)AngleMissile((int)m_x - 35, (int)m_y + 40, 3, 0, 6, (double)(3 + rand() % 4), 90 + rand() % 19 - 9 + 13, 0, 0, 0);
	}
}

void CEnemyLarge03::Killed() {
	m_y += 2;
	m_x += rand() % 3 - 1;
	if (mKilledTimer == 0) { mSE->PlaySingleSound(mKilledSound); }
	if (mKilledTimer % 4 == 0) {
		for (int i = 0; i<6; i++)mEffectManager->CreateEffect(m_x, m_y + m_height / 2, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, -rand() % 5 + 60 - i * 10, 0, 3, 0, 0);
		mEffectManager->CreateEffect(m_x, m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
		for (int i = 0; i<4; i++) {
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
		}
	}
	if (mKilledTimer == 8) {
		mDelFlg = true;
		for (int i = 0; i<20; i++) {
			int v = rand() % 10 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = v*sin(N_PI * 18 * i) + 40;
			mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
	}
	if (mKilledTimer >= 16) {
		for (int i = 0; i<20; i++) {
			int v = rand() % 20 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = v*sin(N_PI * 18 * i) + 40;
			mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
	}
	if (mKilledTimer >= 16) {
		mDelFlg = true;
		int pointMul = 300 - mTimer;
		if (pointMul<0)pointMul = 0;
		mPlayer->DestroyEnemy(16, pointMul*pointMul*pointMul);
		for (int i = 0; i<20; i++)mItemManager->CreateItem((int)m_x, (int)m_y, rand() % 2, 0, rand() % 20 - 10, rand() % 20);
	}
}


