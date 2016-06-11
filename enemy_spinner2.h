class CEnemySpinner2:public CEnemy{
public:
	void UpdateEnemy();
	void Killed();
};

void CEnemySpinner2::UpdateEnemy(){
	CVector mTargetPos(mCreateInfo.params[0],mCreateInfo.params[1]);
	mBltInfo.angle=37*mTimer;
	if(mTimer<2){m_vx=0;m_vy=0;}
	else if(mTimer<40){
		mCounter=0;
		if(mTimer<20)mInvincibleFlg=true;
		else mInvincibleFlg=false;
		m_x=ExMath::asymptote(m_x0,mTargetPos.x,mTimer*0.25);
		m_y=ExMath::asymptote(m_y0,mTargetPos.y,mTimer*0.25);
		if(mTimer>=5)mBackEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_BACKLIGHT1,0,0,0,0,2,0,0);
		return;
	}
	if(mTimer>200){
		mCounter=0;
		m_vx=10;
		if(mTimer>=5)mBackEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_BACKLIGHT1,0,0,0,0,2,0,0);
		return;
	}

	mInvincibleFlg=false;
	mBackEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_BACKLIGHT1,0,0,0,0,2,0,0);

	if(mTimer>100-mGameLevel*4){
		if(mTimer%2==0 && mTimer%20<10){
			mSE->PlaySingleSound(SE_EXP2);
			NormalShot(m_x,m_y,EB_40,0,6+rand()%5);
		}
	}
}

void CEnemySpinner2::Killed(){
	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);

	for(int i=0;i<3;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_160,0,rand()%30-15,rand()%5+40-i*10,0,2,0,0);
	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80,0,rand()%20-10,rand()%5+30-i*7,0,2,0,0);
	mEffectManager->CreateEffect((int)m_x,(int)m_y+15,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
	for(int i=0;i<8;i++){
		int v=rand()%40+50;
		double vx=v*cos(N_PI*(10*i+50));
		double vy=-v*sin(N_PI*(10*i+50))-20;
		mDebrisManager->CreateDebris((int)m_x,(int)m_y,1,0,vx,vy,0,1,0,10,0);
	}
	mDelFlg=true;
	int pointMul=200-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	for(int i=0;i<15;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20+(5-mGameLevel));
}
