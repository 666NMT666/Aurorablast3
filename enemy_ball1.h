class CEnemyBall1:public CEnemy{
	bool mClosedFlg; 
	int mEscapeCounter;
	RECT mRectShield;
public:
	void UpdateEnemyPre();
	void UpdateEnemy();
	void Killed();
	void CreateEnemy() {
		mClosedFlg = true;
		mEscapeCounter = 0;
		CExRect::InitRect(&mRectShield, -m_width / 2, -m_height / 2, m_width / 2, m_height / 2);
	}
};
void CEnemyBall1::UpdateEnemyPre() {
	if (mBulletManager->HitTestRectWithKind(mRectShield, 0, m_x, m_y)) {
		mSE->PlayLoopSound(SE_SLD1);
	}
}

void CEnemyBall1::UpdateEnemy(){
	int deltaBltY = 0;
	if (mGameInfo->GetStage() == 5)deltaBltY = m_height * 2;
	if (mClosedFlg) {
		mBltY = deltaBltY;
	}
	else {
		mBltY = m_height + deltaBltY;
	}

	if(mTimer<2){
		mClosedFlg = true;
		mInvincibleFlg=true;
		int pm=(m_x0>BATTLE_MIDDLE_X)?1:-1;
		int pmy=(m_y0>BATTLE_MIDDLE_Y)?1:-1;
		mCounter=0;
		SetVel(pm*(-10-rand()%5),-10*pmy);
	}else if(mCounter==0){
		if(m_x<=BATTLE_LEFT || m_x>=BATTLE_RIGHT){
			if(mEscapeCounter<3)m_vx*=-1;
			mSE->PlaySingleSound(SE_EXP1);
		}
		if(m_y<=BATTLE_TOP || m_y>=BATTLE_BOTTOM){
			m_vy*=-1;
			mSE->PlaySingleSound(SE_EXP1);
		}
		if(m_y<mCreateInfo.params[0] && mTimer>40){
			mCounter=1;
			m_vy=0.5;
			m_vx=0;
		}
		mBltInfo.angle=rand()%360;
	}
	if(mTimer>50){
		mClosedFlg = false;
		DirectToPlayer();
		mInvincibleFlg=false;
		if(m_x<mPlayer->GetX())m_vx=1;
		else m_vx=-1;
		if (mTimer % 2 == 0) {
			mSE->PlaySingleSound(SE_EXP2);
			NormalShot(m_x, m_y, EB_20, 2, 10 + rand() % 3, 3, 0);
			if (mGameInfo->GetStage() == 5) {
				NormalShot(m_x, m_y, EB_40, 0, 10 + rand() % 3, 0, 0);
			}
		}
	}
	if (mTimer > 70) {
		mTimer = 0;
		mCounter=0;
		mEscapeCounter++;
	}
}

void CEnemyBall1::Killed(){
	if(mKilledTimer==0){ mSE->PlaySingleSound(mKilledSound); }
	mEffectManager->CreateEffect((int)m_x,(int)m_y+15,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
	for(int i=0;i<10;i++){
		int v=rand()%20+10;
		double vx=v*cos(N_PI*18*i);
		double vy=-v*sin(N_PI*18*i);
		mDebrisManager->CreateDebris((int)m_x,(int)m_y,2,0,vx,vy,0,0,2,10,0);
	}
	mDelFlg=true;
	int pointMul=200-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	for(int i=0;i<15;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20+(5-mGameLevel));
}