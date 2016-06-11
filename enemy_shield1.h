class CEnemyShield1:public CEnemy{
private:
	CVector mTarget;
	RECT mRectShield;
public:
	CEnemyShield1():CEnemy(){mTarget=CVector::Vector(0.0,0.0);}

	void UpdateEnemy();
	void Killed();
	void CreateEnemy(){
		CExRect::InitRect(&mRectShield,-20,-m_height/2,m_width/2,m_height/2);
	}
	void UpdateEnemyPre();
};

void CEnemyShield1::UpdateEnemy(){
	int freq=90-mGameLevel*10;
	int startTime=46-mGameLevel*2;
	int shotLength=10+3*mGameLevel;
	if(mTimer<13){
		int y=200+rand()%200;
		mTarget.y=y-rand()%150+75;
		mTarget.x=rand()%BATTLE_WIDTH+BATTLE_LEFT;
	}
	if(mTimer<50){
		if(fabs(mTarget.x-m_x)>5 && fabs(mTarget.y-m_y)>5){
			CVector v=CVector::EigenVector(m_x,m_y,mTarget.x,mTarget.y);
			m_vx=v.x*5;//in the later stages,use 10
			m_vy=v.y*5;
		}
	}else if(mTimer<60){
		m_vx=m_vy=0.0;
	}

	if(startTime<mTimer && mCounter==0){
		mCounter++;
		mSE->PlaySingleSound(SE_EXP5);
		CCreateInfo info=defaultCreateInfo;
		AngleMissile((int)m_x,(int)m_y,EB_MISSILE_100x20,0,18.0,90,CCreateInfo::CCreateInfo(EMISSILE_SHOT,90,0,0,0));
	}
	BackLightSmall(m_x,m_y-10);
	if(mTimer>startTime+40)m_vy-=0.25;
}
void CEnemyShield1::UpdateEnemyPre(){
	if(mBulletManager->HitTestRectWithKind(mRectShield,0,m_x,m_y)){
		mSE->PlayLoopSound(SE_SLD1);
	}
}
void CEnemyShield1::Killed(){
	if(mKilledTimer==0){ mSE->PlaySingleSound(mKilledSound); }
	mEffectManager->CreateEffect((int)m_x,(int)m_y+15,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_160,0,rand()%30-15,-rand()%5+60-i*10,0,2,0,0);
	for(int i=0;i<6;i++){
		int v=rand()%40+15;
		double vx=v*cos(N_PI*(30*i+15));
		double vy=-v*sin(N_PI*(30*i+15));
		mDebrisManager->CreateDebris((int)m_x,(int)m_y,2,0,vx,vy,0,0,2,10,0);
	}
	mDelFlg=true;
	int pointMul=200-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	for(int i=0;i<20;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20);
}
