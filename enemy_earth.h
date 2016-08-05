#pragma once

class CEnemyEarth : public CEnemy {

public:
	void UpdateEnemy() { m_vx = m_vy = 0; m_x = 480; m_y = 320; }
	void Killed();
};

void CEnemyEarth::Killed() {
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