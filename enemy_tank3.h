class CEnemyTank03:public CEnemy{
public:
	void UpdateEnemy();
	void CreateEnemy(){
		mLandscapeFlg=true;
		mKilledSound=SE_EXP3;
		mParts[0].InitParts(COMMON_PARTS_CANNON29x160,m_width/2,m_height/2);//–C‘ä
		for(int i=0;i<4;i++){
			mBackParts[i  ].InitParts(ENEMY_PARTS_TANK3_MERUS_LEFT , 4,24+i*10);
			mBackParts[i+4].InitParts(ENEMY_PARTS_TANK3_MERUS_RIGHT,46,24+i*10);

			mBackParts[i+ 8].InitParts(ENEMY_PARTS_TANK3_PROPODUS_LEFT);
			mBackParts[i+12].InitParts(ENEMY_PARTS_TANK3_PROPODUS_RIGHT);
		}
		mAutoDelFlg=false;
		if(m_y0<380){
			m_y=BATTLE_RECT.bottom+m_height/2-1;
			m_vy=-5;
		}else{
			m_y=0-m_height/2+1;
			m_vy=5;
		}
		CExRect::InitRect(&mRectBulletHit,-m_width/2-20,-m_height/2,m_width/2+20,m_height/2+30);
		CExRect::InitRect(&mRectPlayerHit,-m_width/2-20,-m_height/2,m_width/2+20,m_height/2+30);
	}
	void Killed();
};
void CEnemyTank03::UpdateEnemy() {
	int angle = 0;
	//DirectFrontPartsTo(0,mPlayer->GetX(),mPlayer->GetY());
	if (mGameInfo->GetStage() == 1) {
		mBltInfo.type = BLT_STRUCTURE;
		for (int i = 0; i < mMaxParts; i++)mParts[i].SetBltType(BLT_STRUCTURE);
		for (int i = 0; i < mMaxBackParts; i++)mBackParts[i].SetBltType(BLT_STRUCTURE);
	}

	int omega=13;
	if(m_y0<380){
		if(m_y<mCreateInfo.params[0]){
			m_vy=0;
			omega=13;
		}
	}else{
		omega=13;
		if(m_y>mCreateInfo.params[0]){
			m_vy=0;
		}
	}
	if(mTimer<200){
		CVector v(mParts[0].GetEndX()-mParts[0].GetStartX(), mParts[0].GetEndY()-mParts[0].GetStartY());
		v.Rotate(N_PI*mParts[0].GetAngle());
		int freq=60-mGameLevel*5;
		if(mTimer>50){
			double spd=10+mGameLevel*4;
			CVector v(mParts[0].GetEndX()-mParts[0].GetStartX(), mParts[0].GetEndY()-mParts[0].GetStartY());
			v.Rotate(N_PI*mParts[0].GetAngle());
			TARGB clr;
			clr.ARGB=0x00FF0000;
			clr.G=124+100*sin(N_PI*mTimer*33);
			CLine::drawLine2(m_bg,(int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x),(int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),700, GetShotAngleFromPartsAngle(0),clr.ARGB,BATTLE_RECT);
			CLine::drawLine2(m_bg,(int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x)+1,(int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),700, GetShotAngleFromPartsAngle(0),clr.ARGB,BATTLE_RECT);
			if((mTimer-50)%freq>5 && (mTimer-50)%freq<30){
				ChacePartsAngle(mParts[0],mPlayer->GetX(),mPlayer->GetY(),1);
			}else if((mTimer-50)%freq<40){
				int t=(mTimer-50)%freq;
				if((mTimer-50)%freq==30)mSE->PlaySingleSound(SE_KYP1);
				int x=(int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x);
				int y=(int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y);
				mFrontEffectManager->CreateEclipsedCircle(x,y,10+((mTimer-50)%freq-30)*12,x-4,y-5,9+((mTimer-50)%freq-30)*11,0xFFFFFFFF);
				mFrontEffectManager->CreateThrash(x,y,8,t*7,mTimer*40,0xFFFFFFFF);
				mFrontEffectManager->CreateThrash(x,y,8,t*10,mTimer*40,0xFFFFFFFF);
			}
			if((mTimer-50)%freq==freq-1){
				mSE->PlaySingleSound(SE_SHT1);
				AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EDAB_66,0,18.0, GetShotAngleFromPartsAngle(0));
				for(int i=0;i<5;i++)
					AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_20,3,12.0+i, GetShotAngleFromPartsAngle(0));
				for(int i=0;i<7;i++)
					AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_26,
					2,(double)(17-i), GetShotAngleFromPartsAngle(0) +rand()%16-8);
			}
		}
	}else{ m_vy=5; }
	for(int i=0;i<4;i++){
		int i01=0;
		if(i%2==0)i01=1;
		mBackParts[i  ].SetAngle(-50+i*20+(int)(30*sin(N_PI*(omega*mTimer+i01*90))));
		mBackParts[i+4].SetAngle( 50-i*20+(int)(30*sin(N_PI*(omega*mTimer+i01*90))));

		LinkBackParts(i+8,i,-10+i*20+(int)(50*sin(N_PI*(omega*mTimer+i01*90))));
		LinkBackParts(i+12,i+4, 10-i*20+(int)(50*sin(N_PI*(omega*mTimer+i01*90))));
	}

}

void CEnemyTank03::Killed(){
	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);
	if (mGameInfo->GetStage() == 1) {
		mBltInfo.type = BLT_STRUCTURE;
		for (int i = 0; i < mMaxParts; i++)mParts[i].SetBltType(BLT_STRUCTURE);
		for (int i = 0; i < mMaxBackParts; i++)mBackParts[i].SetBltType(BLT_STRUCTURE);
	}
	if(mKilledTimer%4==0){
		for(int i=0;i<6;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y+m_height/2,EFFECT_EXPLOSION_160,0,rand()%30-15,-rand()%5+60-i*10,0,3,0,0);
		mEffectManager->CreateEffect((int)m_x,(int)m_y+15+m_height/2,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
		for(int i=0;i<4;i++){
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,40-rand()%15,rand()%15-40,1,0,2,10,0);
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,-40+rand()%15,rand()%15-40,1,0,2,10,0);
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
	if(mKilledTimer>=16){
		mDelFlg=true;
		for(int i=0;i<20;i++){
			int v=rand()%20+10;
			double vx=v*cos(N_PI*18*i);
			double vy=v*sin(N_PI*18*i)-20;
			mEffectManager->CreateEffect((int)m_x,(int)m_y+m_height/2,EFFECT_EXPLOSION_90,0,vx,vy,0,3,0,0);
		}
	}
	int pointMul=500-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	if(mKilledTimer==8){
		for(int i=0;i<16;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20);
	}
	if(mKilledTimer==12){
		for(int i=0;i<4;i++)mItemManager->CreateItem((int)m_x,(int)m_y,2,rand()%20-10,0,rand()%20);
	}
}