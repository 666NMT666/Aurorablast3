class CEnemyFO06:public CEnemy{
protected:
public:
	void UpdateEnemy();
	void CreateEnemy();
	void Killed();
};
void CEnemyFO06::CreateEnemy(){
	mKilledSound=SE_EXP5;
}
void CEnemyFO06::UpdateEnemy(){
	if(mTimer<=1){
		m_vx=0;
		m_y=BATTLE_BOTTOM+m_height/2;
	}else if(mTimer<40){
		int maxY=mCreateInfo.params[0];
		if(maxY==0)maxY=600;
		m_y=ExMath::asymptote(BATTLE_BOTTOM+m_height/2,maxY,mTimer*0.5);
	}else if(mTimer<120){
		if(mTimer%8==0){
			mCounter++;
			for(int i=0;i<3+mGameLevel/2;i++){
				AngleShot(m_x, m_y,EB_26,1,(double)(13-i-(4-mGameLevel)),30*mCounter+20);
				AngleShot(m_x, m_y,EB_26,1,(double)(13-i-(4-mGameLevel)),30*mCounter+30);
			}
		}
		m_vy=1.0;
	}else if(mTimer<180){
		if(mTimer==160){
			mSE->PlaySingleSound(SE_EXP5);
			NormalShot((int)m_x,(int)m_y,EDAB_66,0,20+mGameLevel*3);
			NormalShot((int)m_x,(int)m_y,EDAB_66,0,16+mGameLevel*3);
			for(int i=0;i<15;i++)AngleShot((int)m_x,(int)m_y,EB_26,1,5+i+mGameLevel*3,(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY())+rand()%10-5);
		}
	}else{
		if(mGameLevel>1 && mTimer%3==0){
			NormalShot((int)m_x, (int)m_y+m_height/2-rand()%40,EB_16,0,8,0,rand()%10-5);
			NormalShot((int)m_x, (int)m_y-rand()%40,EB_16,0,8,0,rand()%10-5);
		}
		m_vy-=0.25;
	}
	BackLightMedium();
}
void CEnemyFO06::Killed(){
	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);

	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_160,0,rand()%30-15,-rand()%10+60-i*10,0,2,0,0);
	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80,0,rand()%20-10,-rand()%5+50-i*7,0,2,0,0);
	for(int i=0;i<3;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80_2,0,rand()%3-1,-rand()%5+5+i*10,0,4,0,0);
	mEffectManager->CreateEffect((int)m_x,(int)m_y+15,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
	for(int i=0;i<8;i++){
		int v=rand()%40+100;
		double vx=v*cos(N_PI*(10*i+50));
		double vy=-v*sin(N_PI*(10*i+50))-20;
		mDebrisManager->CreateDebris((int)m_x,(int)m_y,1,0,vx,vy,0,0,2,10,0);
	}
	mDelFlg=true;
	int pointMul=300-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	for(int i=0;i<20;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20);
}