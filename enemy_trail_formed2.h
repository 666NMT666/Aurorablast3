class CEnemyTrailFormed2:public CEnemy{
protected:
	int mShotPhase;
	int mType;
public:
	void CreateEnemy(){
		mType = rand()%2;
		mShotPhase=rand()%100;
		mDisabledFlg=(rand()%(CGameInfo::NUM_LEVEL*2-mGameLevel)>0)?true:false; // 0‚æ‚è‘å‚«‚¯‚ê‚ÎŒ‚‚½‚È‚¢
		mBltY = mType * m_height;
	}
	void UpdateEnemy();
	void Killed();
};

void CEnemyTrailFormed2::UpdateEnemy(){
	m_vy=6;
	if (mType)m_vx = sin(N_PI * 4 * mTimer);
	else m_vx = sin(-N_PI * 4 * mTimer);
	DirectWithVel();
	if(m_y>320+mGameLevel*100){}
	else if((mTimer+mShotPhase)%(60+(CGameInfo::NUM_LEVEL-mGameLevel)*10)==0 && mDisabledFlg==false){
		//for(int i=0;i<3;i++)NormalShot((int)m_x+m_width/2,(int)m_y+m_height/2,EB_16,0,20-i*2);
		for(int i=0;i<2;i++)NormalShot((int)m_x+m_width/2,(int)m_y+m_height/2,EB_40,3,10-i-(5-mGameLevel)*0.5);
		if(mGameLevel>=3)NormalShot((int)m_x+m_width/2, (int)m_y+m_height/2,EB_40,3,14);
	}
}

void CEnemyTrailFormed2::Killed(){
	if(mKilledTimer==0){ mSE->PlaySingleSound(mKilledSound); }
	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80,0,rand()%20-10,-rand()%5+50-i*7,0,2,0,0);
	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80_2,0,rand()%30-15,-rand()%5+60+i*10,0,5,0,0);
	mEffectManager->CreateEffect((int)m_x,(int)m_y+15,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
	for(int i=0;i<6;i++){
		int v=rand()%30+15;
		double vx=v*cos(N_PI*(30*i+15));
		double vy=-v*sin(N_PI*(30*i+15));
		mDebrisManager->CreateDebris((int)m_x,(int)m_y,2,0,vx,vy,0,0,2,10,0);
	}
	mDelFlg=true;
	int pointMul=200-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	for(int i=0;i<15;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20+(5-mGameLevel));
}