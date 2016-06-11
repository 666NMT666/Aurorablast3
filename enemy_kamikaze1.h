class CEnemyKamikaze1:public CEnemy{

	public:
	void UpdateEnemy();
	void Killed();
	void CreateEnemy(){mAutoDelFlg=false;m_vy=3;}
};

void CEnemyKamikaze1::UpdateEnemy(){
	static const int startTimeInterval=30;

	if(mTimer<startTimeInterval){ m_y+=(300-m_y)/30.0; }
	else {
		if(mTimer%2==0){		
			mEffectManager->ExplosionSample(m_x,m_y);
			mSE->PlaySingleSound(SE_EXP2);
		}
		double v=0.6*(mTimer-startTimeInterval)+1.0+mGameLevel;
		if(v>=17+mGameLevel)v=17+mGameLevel;
	
		if(mTimer<startTimeInterval+10+5*mGameLevel && mPlayer->GetY()>m_y){
			SetVToPlayer(v);
			DirectToPlayer();
		}

		NormalShot(m_x,m_y,EB_26,2,6,2);

	}

	BackLightSmall();
}

void CEnemyKamikaze1::Killed(){
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