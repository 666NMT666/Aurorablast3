class CEnemyFlankAttacker1:public CEnemy{
protected:
public:
	void UpdateEnemy();
	void Killed();
	void CreateEnemy(){mAutoDelFlg=false;m_vy=3;}
};

void CEnemyFlankAttacker1::UpdateEnemy(){
	int freq=90-mGameLevel*10;
	if(mTimer<40){
		m_x=ExMath::asymptote(m_x0,mCreateInfo.params[0],1+mTimer*0.1);
	}else{
		mAutoDelFlg=true;
	}
	m_vy-=0.2;
	if(rand()%freq==0){
		//static const int distanceLimit[5]={200,150,100,60,50};
		//if(abs(m_x-mPlayer->GetX())>distanceLimit[mGameLevel] || abs(m_y-mPlayer->GetY())>distanceLimit[mGameLevel]){
		for(int i=-2;i<2;i++)NormalShot((int)m_x, (int)m_y,EB_26,2,14-2*i-(5-mGameLevel));
		//}
	}
	BackLightSmall();
}

void CEnemyFlankAttacker1::Killed(){
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