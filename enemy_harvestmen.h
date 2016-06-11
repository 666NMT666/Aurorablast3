class CEnemyHarvestmen01 :public CEnemy {
public:
	void UpdateEnemy();
	void CreateEnemy() {
		mLandscapeFlg = true;
		mKilledSound = SE_EXP3;
		mParts[0].InitParts(COMMON_SHIELD_LEFT, m_width / 2, m_height / 2);//shield
		mParts[1].InitParts(COMMON_SHIELD_RIGHT, m_width / 2, m_height / 2);//–C‘ä
		for (int i = 0; i<4; i++) {
			mBackParts[i].InitParts(ENEMY_PARTS_TANK3_MERUS_LEFT, 4, 24 + i * 10);
			mBackParts[i + 4].InitParts(ENEMY_PARTS_TANK3_MERUS_RIGHT, m_width-4, 24 + i * 10);

			mBackParts[i + 8].InitParts(ENEMY_PARTS_TANK3_PROPODUS_LEFT);
			mBackParts[i + 12].InitParts(ENEMY_PARTS_TANK3_PROPODUS_RIGHT);
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
void CEnemyHarvestmen01::UpdateEnemy() {
	int angle = 0;

	int omega = 13;
	if (m_y0<380) {
		if (m_y<mCreateInfo.params[0]) {
			m_vy = 0;
			omega = 13;
			mCounter += 2;
		}
	}
	else {
		omega = 13;
		if (m_y>mCreateInfo.params[0]) {
			mCounter += 2;
			m_vy = 0;

		}
	}

	int sldX = min(mCounter,50); 
	mParts[0].SetTargetPos(m_width / 2 - sldX, m_height / 2);
	mParts[1].SetTargetPos(m_width / 2 + sldX, m_height / 2);


	if (mTimer<300) {
		int freq = 60 - mGameLevel * 5;
		if (mTimer>50) {
			double spd = 10 + mGameLevel * 4;
			if ((mTimer - 50) % freq == freq - 1) {
				mSE->PlaySingleSound(SE_SHT1);
				AngleShot((int)m_x, (int)(m_y + m_height / 2), EDAB_66, 0, 18.0, 90);
				for (int i = 0; i<5; i++)
					AngleShot((int)m_x, (int)(m_y + m_height / 2), EB_80, 0, 12.0 + i, 90);
				for (int i = 0; i<7; i++)
					AngleShot((int)m_x, (int)(m_y + m_height / 2), EB_40, 0, (double)(17 - i), 90);
			}
		}
	}
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

void CEnemyHarvestmen01::Killed() {
	if (mKilledTimer == 0) mSE->PlaySingleSound(mKilledSound);
	if (mKilledTimer % 4 == 0) {
		for (int i = 0; i<6; i++)mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_160, 0, rand() % 30 - 15, -rand() % 5 + 60 - i * 10, 0, 3, 0, 0);
		mEffectManager->CreateEffect((int)m_x, (int)m_y + 15 + m_height / 2, EFFECT_EXPLOSION_HEAD1, 0, 0, -15, 0, 1, 0, 0);
		for (int i = 0; i<4; i++) {
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, 40 - rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
			mDebrisManager->CreateDebris((int)m_x, (int)m_y + m_height / 2, 2, 0, -40 + rand() % 15, rand() % 15 - 40, 1, 0, 2, 10, 0);
		}
	}
	/*if(mKilledTimer==8){
	for(int i=0;i<20;i++){
	int v=rand()%10+10;
	double vx=v*cos(N_PI*18*i);
	double vy=-v*sin(N_PI*18*i)-20;
	mEffectManager->CreateEffect(m_x,m_y+m_height/2,EFFECT_EXPLOSION_90,vx,vy,0,0,3,0,0);
	}
	}*/
	if (mKilledTimer >= 16) {
		mDelFlg = true;
		for (int i = 0; i<20; i++) {
			int v = rand() % 20 + 10;
			double vx = v*cos(N_PI * 18 * i);
			double vy = v*sin(N_PI * 18 * i) - 20;
			mEffectManager->CreateEffect((int)m_x, (int)m_y + m_height / 2, EFFECT_EXPLOSION_90, 0, vx, vy, 0, 3, 0, 0);
		}
		mItemManager->CreateItem(m_x,m_y,4,0,4,4);
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