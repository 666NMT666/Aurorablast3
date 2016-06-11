#pragma once
class CEnemyTank05 :public CEnemy {
public:
	void UpdateEnemy();
	void CreateEnemy() {
		mLandscapeFlg = true;
		mKilledSound = SE_EXP3;
		for (int i = 0; i<4; i++) {
			mBackParts[i].InitParts(ENEMY_PARTS_TANK5_MERUS_LEFT, 2, 7 + i * 4);
			mBackParts[i + 4].InitParts(ENEMY_PARTS_TANK5_MERUS_RIGHT, 23, 7 + i * 4);
			mBackParts[i + 8].InitParts(ENEMY_PARTS_TANK5_PROPODUS_LEFT);
			mBackParts[i + 12].InitParts(ENEMY_PARTS_TANK5_PROPODUS_RIGHT);
		}
		mAutoDelFlg = false;
		if (m_y0<380) {
			m_y = BATTLE_RECT.bottom + m_height / 2 - 1;
			m_vy = -5;
		}
		else {
			m_y = 0 - m_height / 2 + 1;
			m_vy = 5;
		}
		CExRect::InitRect(&mRectBulletHit, -m_width / 2 - 20, -m_height / 2, m_width / 2 + 20, m_height / 2 + 30);
		CExRect::InitRect(&mRectPlayerHit, -m_width / 2 - 20, -m_height / 2, m_width / 2 + 20, m_height / 2 + 30);
	}
	void Killed();
};

void CEnemyTank05::UpdateEnemy() {
	int angle = 0;
	//DirectFrontPartsTo(0,mPlayer->GetX(),mPlayer->GetY());
	if (mGameInfo->GetStage() == 1) {
		mBltInfo.type = BLT_STRUCTURE;
		for (int i = 0; i < mMaxParts; i++)mParts[i].SetBltType(BLT_STRUCTURE);
		for (int i = 0; i < mMaxBackParts; i++)mBackParts[i].SetBltType(BLT_STRUCTURE);
	}
	int omega = 13;
	if (m_y0<380) {
		if (m_y<mCreateInfo.params[0]) {
			m_vy = 0;
			omega = 13;
		}
	}
	else {
		omega = 13;
		if (m_y>mCreateInfo.params[0]) { m_vy = 0; }
	}
	if (mTimer<200) {}
	else { m_vy = 5; }
	for (int i = 0; i<4; i++) {
		int i01 = 0;
		if (i % 2 == 0)i01 = 1;
		mBackParts[i].SetAngle(-50 + i * 20 + (int)(30 * sin(N_PI*(omega*mTimer + i01 * 90))));
		mBackParts[i + 4].SetAngle(50 - i * 20 + (int)(30 * sin(N_PI*(omega*mTimer + i01 * 90))));
		LinkBackParts(i + 8, i, -10 + i * 20 + (int)(50 * sin(N_PI*(omega*mTimer + i01 * 90))));
		LinkBackParts(i + 12, i + 4, 10 - i * 20 + (int)(50 * sin(N_PI*(omega*mTimer + i01 * 90))));
	}
}

void CEnemyTank05::Killed() {
	if (mKilledTimer == 0) mSE->PlaySingleSound(mKilledSound);
	m_vy = 4;
	PurgeBackParts(5,30, mMaxBackParts*2,6,0,0);

	for (int i = 0; i < mGameLevel*2 + 1; i++)
		if (mKilledTimer == 4 + i * 4) {
			NormalShot(m_x, m_y, EB_40, EB_DESTROYABLE[EB_40], 8 + i * 2, 0, 0);
			NormalShot(m_x, m_y, EB_26, EB_DESTROYABLE[EB_26], 6 + i * 2, 9 + 2 * mGameLevel, -5);
			NormalShot(m_x, m_y, EB_26, EB_DESTROYABLE[EB_26], 6 + i * 2, 9 + 2 * mGameLevel,  5);
		}
	if (mKilledTimer % 4 == 0) {
		for (int i = 0; i < 5; i++) {
			TEffectFile k = EFFECT_EXPLOSION_160;
			if (i % 2 == 0)k = EFFECT_EXPLOSION_90;
			mBackEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, k, 0, rand() % 30 - 15, -rand() % 8 + 60 - i * 10, 0, 3, 0, 0);
		}
		mBackEffectManager->CreateEffect((int)m_x, (int)m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
	}
	if (mKilledTimer >= 16) { mDelFlg = true; }
	int pointMul = 500 - mTimer;
	if (pointMul < 0)pointMul = 0;
	mPlayer->DestroyEnemy(16, pointMul*pointMul*pointMul);
	if (mKilledTimer == 8) {
		for (int i = 0; i<16; i++)mItemManager->CreateItem((int)m_x, (int)m_y, rand() % 2, 0, rand() % 20 - 10, rand() % 20);
	}
	if (mKilledTimer == 12) {
		for (int i = 0; i<4; i++)mItemManager->CreateItem((int)m_x, (int)m_y, 2, rand() % 20 - 10, 0, rand() % 20);
	}
}