class CEnemyFO05:public CEnemy{
	CVector mTarget;
protected:
public:
	CEnemyFO05():CEnemy(){mTarget=CVector::Vector(0.0,0.0);}
	void UpdateEnemy();
	void Killed();
};

void CEnemyFO05::UpdateEnemy(){
	int freq=90-mGameLevel*10;
	int startTime=26-mGameLevel*2;
	int shotLength=10+3*mGameLevel;
	if(mTimer<13){
		int y=200+rand()%200;
		mTarget.y=y-rand()%150+75;
		mTarget.x=rand()%BATTLE_WIDTH+BATTLE_LEFT;
	}
	if(mTimer<50){
		if((int)(mTarget.x-m_x)!=0 && (int)(mTarget.y-m_y)!=0){
			CVector v=CVector::EigenVector(m_x,m_y,mTarget.x,mTarget.y);
			m_vx=v.x*5;//in the later stages,use 10
			m_vy=v.y*5;
		}
	}
	if(/* mTimer%freq<shotLength && mTimer%3==0 && */ startTime<mTimer && mCounter==0){
		mCounter++;
		mSE->PlaySingleSound(SE_EXP5);
		CCreateInfo info=defaultCreateInfo;
		/*
		AngleMissile(m_x+22, m_y,1,0,100,90);
		AngleMissile(m_x-22, m_y,1,0,100,90);
		mEBManager->Create<CEnemyBullet>(m_x+22,m_y,EB_40_1,0,24,info);
		mEBManager->Create<CEnemyBullet>(m_x-22,m_y,EB_40_1,0,24,info);
		*/
		AngleMissile((int)m_x,(int)m_y,EB_MISSILE_100x20,2,40.0,90,CCreateInfo::CCreateInfo(EMISSILE_HEDGEHOG,90,0,0,0));
		//AngleMissile((int)m_x,(int)m_y,EB_DEPTHCHARGE_32x20,0,10.0,90,CCreateInfo::CCreateInfo(EMISSILE_DEPTHCHARGE,0,0,0,0));
	}
	BackLightSmall();
	if(mTimer>startTime+60)m_vy-=0.25;
}

void CEnemyFO05::Killed(){
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

/*
class CEnemyFO05:public CEnemy{
protected:
public:
	void UpdateEnemy();
	void UpdateEnemy2();
};

void CEnemyFO05::UpdateEnemy2(){
	if(mLife>4)mLife=4;
	mBltInfo.type=BLT_NULL;
	CCreateInfo info_e=CCreateInfoFactory::GetEffectBltInfo(0,0,2,0,0);
	mEffectManager->Create<CEffect>(m_x,m_y,EFFECT_ICEBLOCK1,0,0,info_e);
	//mSE->PlaySingleSound(SE_EXP4);
	m_y0+=m_vy;


	int lethal=mCreateInfo.params[0];
	if(HitRadius(m_width/2) && !mPlayer->isInvincible()){mPlayer->Killed();}
	if(mTimer>400)mDelFlg=true;
}

void CEnemyFO05::UpdateEnemy(){
	if(mGameInfo->GetStage()==5 || mGameInfo->GetStage()==6){
		UpdateEnemy2();return;
	}
	int disabled=mCreateInfo.params[0];
	if(disabled==1){
		mBltInfo.type=BLT_NULL;
		if(mLife<=5)mLife=0;
		if(mGameInfo->GetStage()==6)m_vx-=0.02;
	}
	if(mTimer<=1){
		mCounter=1;
		if(mGameInfo->GetStage()==1)m_vx=-(rand()%30)*0.1-0.5;
		if(m_y0>BATTLE_MIDDLE_Y) m_vy=-(rand()%10)*0.1;
		else m_vy=(rand()%10)*0.1;
		mBltInfo.angle=rand()%360;
	}
	if(mGameInfo->GetStage()==2)m_vx+=0.25;
	if(mLife>5){
		CCreateInfo info_e=CCreateInfoFactory::GetEffectBltInfo(0,0,2,0,0);
		mEffectManager->Create<CEffect>(m_x,m_y,EFFECT_ICEBLOCK1,0,0,info_e);
		mTimer=2;
		return;
	}
	if(mLife<=5 && mCounter==1){
		mInvincibleFlg=true;
		mCounter=0;
		mLife--;
		m_vy=rand()%10-5;
		mSE->PlaySingleSound(SE_EXP4);
		for(int i=0;i<10;i++)mBackEffectManager->CreateEffect(m_x,m_y,5,rand()%20-5,rand()%20-10,0,1,2,0,0);
	}
	double tmp=m_vx;
	m_vx=9.0-(mTimer-mCreateInfo.params[0])*(mTimer-mCreateInfo.params[0])*0.006+mCreateInfo.params[1]-6.0;
	if(tmp>=0.0 && m_vx<0.0){
		mInvincibleFlg=false;
		NormalShot(m_x+m_width/2, m_y+m_height/2,EB_20_1,14);
		NormalShot(m_x+m_width/2, m_y+m_height/2,EB_16_1,12);
		NormalShot(m_x+m_width/2, m_y+m_height/2,EB_16_1,10);
	}
	if(m_vx<-10.0)m_vx=-10.0;
	mBltInfo.angle=-180-ExMath::angleBetweenPoints(m_x,m_y,mPlayer->GetX(),mPlayer->GetY());
	CCreateInfo info_e=CCreateInfoFactory::GetEffectBltInfo(0,0,2,0,0);
	mBackEffectManager->Create<CEffect>(m_x,m_y,EFFECT_BACKLIGHT2,0,0,info_e);

	m_y+=(mPlayer->GetY()-m_y)/20;
	if(mGameLevel>1 && mTimer%10==9 && rand()%(8-mGameLevel)==0 && (m_x>mPlayer->GetX()+40+mGameLevel*20 || m_y>mPlayer->GetY()+40+mGameLevel*20)){
		for(int i=0;i<3;i++)NormalShot(m_x+m_width/2, m_y+m_height/2,EB_16_1,10.0+(i+mGameLevel)*2.0);
	}
	if(mGameLevel==3 && m_x<mPlayer->GetX()-100 & mTimer%10==0){
		NormalShot(m_x+m_width/2, m_y+m_height/2,EB_20_1,14);
		NormalShot(m_x+m_width/2, m_y+m_height/2,EB_16_1,12);
		NormalShot(m_x+m_width/2, m_y+m_height/2,EB_16_1,10);
	}
}
*/