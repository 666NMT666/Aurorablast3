#pragma once
class CEnemyRobo3 :public CEnemy {
public:
	void UpdateEnemy();
	void Killed();
};

void CEnemyRobo3::UpdateEnemy() {
	if (mTimer <= 1) {
		mAutoDelFlg = false;
		m_vx = 0; m_vy = 0;
		mInvincibleFlg = true;
	}
	else if (mTimer<40) {
		m_y = ExMath::asymptote((double)BATTLE_RECT.bottom + m_height / 2 - 1, (double)mCreateInfo.params[0], (double)mTimer);
	}
	else if (mTimer<70) { mInvincibleFlg = false; }
	else {
		m_vy = -12;
		mAutoDelFlg = true;
	}
	if (abs(mPrevY - m_y) < 10) {
		if(mBltY==0)DirectToPlayer();
		mBltY = m_height;

		mBltInfo.angle = (90-ExMath::angleBetweenPoints(m_x, m_y, mPlayer->GetX(), mPlayer->GetY()) + mBltInfo.angle*15)/16;


		if (mTimer == 40 + (5 - mGameLevel) * 4) {
			mSE->PlaySingleSound(SE_EXP6);
			AngleShot(m_x, m_y, EB_80, 0, 14.0, GetShotAngleFromBltAngle());
			for (int i = 0; i < 6 + mGameLevel; i++) {
				AngleShot(m_x+rand()%40-20, m_y + rand() % 40 - 20, EB_26, 0, 14.0-i, GetShotAngleFromBltAngle() + rand() % 10-5);
			}
		}
	}
	else {
		mBltInfo.angle = 0;
		mBltY = 0;
	}
}

void CEnemyRobo3::Killed() {
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


