#pragma once

class CEnemyAmblypygi1 : public CEnemy {
public:
	void UpdateEnemy();
	void CreateEnemy() {
		mLandscapeFlg = true;
		mKilledSound = SE_EXP3;
		mParts[0].InitParts(COMMON_PARTS_CANNON30x79, m_width / 2, m_height / 2);//–C‘ä
		
		mParts[1].InitParts(ENEMY_PARTS_WS1_WHIP1, m_width / 2-32, m_height / 2 + 56);
		mParts[2].InitParts(ENEMY_PARTS_WS1_WHIP1, m_width / 2+32, m_height / 2 + 56);
		mParts[3].InitParts(ENEMY_PARTS_WS1_WHIP2);
		mParts[4].InitParts(ENEMY_PARTS_WS1_WHIP2);
		mParts[5].InitParts(ENEMY_PARTS_WS1_WHIP3);
		mParts[6].InitParts(ENEMY_PARTS_WS1_WHIP3);
		mParts[7].InitParts(ENEMY_PARTS_WS1_PEDIPALP1_LEFT, m_width / 2 - 20, m_height / 2+55);
		mParts[8].InitParts(ENEMY_PARTS_WS1_PEDIPALP1_RIGHT, m_width / 2 + 20, m_height / 2+55);
		mParts[9].InitParts(ENEMY_PARTS_WS1_PEDIPALP2_LEFT);
		mParts[10].InitParts(ENEMY_PARTS_WS1_PEDIPALP2_RIGHT);

		for (int i = 0; i<3; i++) {
			mBackParts[i].InitParts(ENEMY_PARTS_WS1_MERUS_LEFT, 4, 94 + i * 14);
			mBackParts[i + 3].InitParts(ENEMY_PARTS_WS1_MERUS_RIGHT, m_width-6, 94 + i * 14);

			mBackParts[i + 6].InitParts(ENEMY_PARTS_WS1_PROPODUS_LEFT);
			mBackParts[i +9].InitParts(ENEMY_PARTS_WS1_PROPODUS_RIGHT);

			mBackParts[i + 12].InitParts(ENEMY_PARTS_WS1_DACTYLUS_LEFT);
			mBackParts[i + 15].InitParts(ENEMY_PARTS_WS1_DACTYLUS_RIGHT);

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
	void Walk();
};
 
//////// 19 20 21 22   23 24   25 26 27 28 29   30

void CEnemyAmblypygi1::Walk() {
	int omega = 23;
	const int NUM_LEG_PARES = 3;
	for (int i = 0; i<NUM_LEG_PARES; i++) {
		double i01 = 0.5;
		if (i % 3 == 0)i01 = 1.0;
		else if (i % 3 == 1)i01 = 0.0;
		mBackParts[i].SetAngle(-40 + i * 10 + (int)(50 * sin(N_PI*(omega*mTimer + i01 * 90))));
		mBackParts[i + NUM_LEG_PARES].SetAngle(40 - i * 10 + (int)(50 * sin(N_PI*(omega*mTimer + i01 * 90))));

		LinkBackParts(i + NUM_LEG_PARES * 2, i + NUM_LEG_PARES * 0, 70 + i * 17 - (int)(10 * sin(N_PI*(omega*mTimer + i01 * 90))));
		LinkBackParts(i + NUM_LEG_PARES * 3, i + NUM_LEG_PARES * 1, -70 - i * 17 - (int)(10 * sin(N_PI*(omega*mTimer + i01 * 90))));
		LinkBackParts(i + NUM_LEG_PARES * 4, i + NUM_LEG_PARES * 2, 30 + i * 27 - (int)(30 * sin(N_PI*(omega*mTimer + i01 * 90))));
		LinkBackParts(i + NUM_LEG_PARES * 5, i + NUM_LEG_PARES * 3, -30 - i * 27 - (int)(30 * sin(N_PI*(omega*mTimer + i01 * 90))));
	}

	mParts[1].SetAngle(-150 + (int)(3 * sin(N_PI*(omega*mTimer))));
	mParts[2].SetAngle(180 + 150 + (int)(3 * sin(N_PI*(omega*mTimer))));

	LinkFrontParts(3, 1, -130 + (int)(5 * sin(N_PI*(omega*mTimer))));
	LinkFrontParts(4, 2, 180 + 130 + (int)(5 * sin(N_PI*(omega*mTimer))));
	LinkFrontParts(5, 3, -110 + (int)(5 * sin(N_PI*(omega*mTimer))));
	LinkFrontParts(6, 4, 180 + 110 + (int)(5 * sin(N_PI*(omega*mTimer))));

	mParts[7].SetAngle(10 + (int)(10 * sin(N_PI*(0.1*omega*mTimer))));
	mParts[8].SetAngle(-10 - (int)(10 * sin(N_PI*(0.1*omega*mTimer))));
	LinkFrontParts(9, 7, -7 + (int)(5 * sin(N_PI*(0.1*omega*mTimer))));
	LinkFrontParts(10, 8, 7 - (int)(5 * sin(N_PI*(0.1*omega*mTimer))));

}

void CEnemyAmblypygi1::UpdateEnemy() {
	Walk();
	int angle = 0;
	if (m_y0<380) {
		if (m_y<mCreateInfo.params[0]) { m_vy = sin(N_PI*mTimer); }
	}
	else {
		if (m_y>mCreateInfo.params[0]) { m_vy = - sin(N_PI*mTimer);}
	}
	{
		CVector v(mParts[0].GetEndX() - mParts[0].GetStartX(), mParts[0].GetEndY() - mParts[0].GetStartY());
		v.Rotate(N_PI*mParts[0].GetAngle());
		TARGB clr;
		clr.ARGB = 0x00FF0000;
		clr.G = 124 + 100 * sin(N_PI*mTimer * 33);
		CLine::drawLine2(m_bg, (int)(m_x - m_width / 2 + mParts[0].GetTargetX() + v.x), (int)(m_y - m_height / 2 + mParts[0].GetTargetY() + v.y), 700, GetShotAngleFromPartsAngle(0), clr.ARGB, BATTLE_RECT);
		CLine::drawLine2(m_bg, (int)(m_x - m_width / 2 + mParts[0].GetTargetX() + v.x) + 1, (int)(m_y - m_height / 2 + mParts[0].GetTargetY() + v.y), 700, GetShotAngleFromPartsAngle(0), clr.ARGB, BATTLE_RECT);
	}
	{
		CVector v(mParts[0].GetEndX() - mParts[0].GetStartX(), mParts[0].GetEndY() - mParts[0].GetStartY());
		v.Rotate(N_PI*mParts[0].GetAngle());
		int freq = 60 - mGameLevel * 5;
		if (mTimer>50) {
			double spd = 10 + mGameLevel * 4;
			if ((mTimer - 50) % freq>5 && (mTimer - 50) % freq<30) {
				ChacePartsAngle(mParts[0], mPlayer->GetX(), mPlayer->GetY(), 1);
			}
			else if ((mTimer - 50) % freq<40) {
				int t = (mTimer - 50) % freq;
				if ((mTimer - 50) % freq == 30)mSE->PlaySingleSound(SE_KYP1);
				int x = (int)(m_x - m_width / 2 + mParts[0].GetTargetX() + v.x);
				int y = (int)(m_y - m_height / 2 + mParts[0].GetTargetY() + v.y);
				mFrontEffectManager->CreateEclipsedCircle(x, y, 10 + ((mTimer - 50) % freq - 30) * 12, x - 4, y - 5, 9 + ((mTimer - 50) % freq - 30) * 11, 0xFFFFFFFF);
				mFrontEffectManager->CreateThrash(x, y, 8, t * 7, mTimer * 40, 0xFFFFFFFF);
				mFrontEffectManager->CreateThrash(x, y, 8, t * 10, mTimer * 40, 0xFFFFFFFF);
			}
			if ((mTimer - 50) % freq == freq - 1) {
				mSE->PlaySingleSound(SE_SHT1);
				AngleShot((int)(m_x - m_width / 2 + mParts[0].GetTargetX() + v.x), (int)(m_y - m_height / 2 + mParts[0].GetTargetY() + v.y), EDAB_66, 0, 18.0, GetShotAngleFromPartsAngle(0));
				for (int i = 0; i<5; i++)
					AngleShot((int)(m_x - m_width / 2 + mParts[0].GetTargetX() + v.x), (int)(m_y - m_height / 2 + mParts[0].GetTargetY() + v.y), EB_20, 3, 12.0 + i, GetShotAngleFromPartsAngle(0));
				for (int i = 0; i<7; i++)
					AngleShot((int)(m_x - m_width / 2 + mParts[0].GetTargetX() + v.x), (int)(m_y - m_height / 2 + mParts[0].GetTargetY() + v.y), EB_26,
						2, (double)(17 - i), GetShotAngleFromPartsAngle(0) + rand() % 16 - 8);
			}
		}

	}

	if (mTimer<150) {
		if (mTimer % 30 == 0)m_vx = 0.1*(rand() % 100 - 50);
		m_vx += 0.025*(rand() % 60 - 30);
		if (m_x < BATTLE_LEFT && m_vx < 0)m_vx *= -1;
		if (m_x > BATTLE_RIGHT && m_vx > 0)m_vx *= -1;
	}
	else { m_vy = 3; }

}



void CEnemyAmblypygi1::Killed() {
	if (mKilledTimer == 0) mSE->PlaySingleSound(mKilledSound);
	m_vy = 4;
	PurgeBackParts(5, 30, mMaxBackParts * 2, 4, 0, 0);

	for (int i = 0; i < mGameLevel + 1; i++) {
		if (mKilledTimer == 4 + i * 4) {
			NormalShot(m_x, m_y, EB_40, EB_DESTROYABLE[EB_40], 8 + i * 2, 0, 0);
			NormalShot(m_x, m_y, EB_26, EB_DESTROYABLE[EB_26], 6 + i * 2, 9 + 2 * mGameLevel, -5);
			NormalShot(m_x, m_y, EB_26, EB_DESTROYABLE[EB_26], 6 + i * 2, 9 + 2 * mGameLevel, 5);
		}
	}
	if (mGameInfo->GetStage() == 1) {
		mBltInfo.type = BLT_STRUCTURE;
		for (int i = 0; i < mMaxParts; i++)mParts[i].SetBltType(BLT_STRUCTURE);
		for (int i = 0; i < mMaxBackParts; i++)mBackParts[i].SetBltType(BLT_STRUCTURE);
	}
	if (mKilledTimer % 4 == 0) {
		for (int i = 0; i<6; i++)mBackEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, -rand() % 5 + 60 - i * 10, 0, 3, 0, 0);
		mBackEffectManager->CreateEffect((int)m_x, (int)m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
		for (int i = 0; i<4; i++) {
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
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