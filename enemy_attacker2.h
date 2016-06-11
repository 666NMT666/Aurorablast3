class CEnemyAttacker2:public CEnemy{
protected:
public:
	void CreateEnemy(){
//		mDisabledFlg=(rand()%(CGameInfo::NUM_LEVEL-mGameLevel)>1)?true:false; // 0‚æ‚è‘å‚«‚¯‚ê‚ÎŒ‚‚½‚È‚¢
		m_vy = 10;
		m_vx=0;
	}
	void UpdateEnemy();
	void Killed();
};
void CEnemyAttacker2::UpdateEnemy() {
	int t = mTimer - mCreateInfo.params[0];
	//mBltInfo.angle = -180 - (int)ExMath::angleBetweenPoints((int)m_x, (int)m_y, mPlayer->GetX(), mPlayer->GetY());
	if(mTimer<10){
		m_vy=10;
	}
	else if (mTimer%20 == 0 && mTimer<80) {
		CVector v = GetVectorToPlayer(10.0);
		m_vx=v.x;
		m_vy=v.y;
		DirectToPlayer();
	}
	if (m_y>420 + mGameLevel * 60) {}
	else if ((mGameLevel >= 3 || mRandom % 3 == 0) && mTimer % 30 == 0) {
		for (int i = 0; i<2; i++)NormalShot((int)m_x + m_width / 2, (int)m_y + m_height / 2, EB_40, 0, 14 - i * 2 - (5 - mGameLevel));
	}
	BackLightSmall();
}
/*
void CEnemyAttacker2::UpdateEnemy(){
	int t=mTimer-mCreateInfo.params[0];
	m_vy=10.0;
	mBltInfo.angle=-180-(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY());
	if(m_y<400)m_x+=(mPlayer->GetX()-m_x0)/100;
	if(m_y>420+mGameLevel*60){}
	else if((mGameLevel>=3 || mRandom%3==0)&& mTimer%30==0){
		for(int i=0;i<2;i++)NormalShot((int)m_x+m_width/2, (int)m_y+m_height/2,EB_40,0,14-i*2-(5-mGameLevel));
	}
	BackLightSmall();
}
*/
void CEnemyAttacker2::Killed(){
	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);

	for(int i=0;i<2;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_160,0,rand()%30-15,rand()%5+40-i*10,0,2,0,0);
	for(int i=0;i<3;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80,0,rand()%20-10,rand()%5+30-i*7,0,2,0,0);
	mEffectManager->CreateEffect((int)m_x,(int)m_y+15,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
	for(int i=0;i<4;i++){
		int v=rand()%40+50;
		double vx=v*cos(N_PI*(20*i+50));
		double vy=-v*sin(N_PI*(20*i+50))-20;
		mDebrisManager->CreateDebris((int)m_x,(int)m_y,1,0,vx,vy,0,1,0,10,0);
	}
	mDelFlg=true;
	int pointMul=200-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	for(int i=0;i<10;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20+(5-mGameLevel));
}