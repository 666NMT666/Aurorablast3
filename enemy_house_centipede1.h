class CHouseCentipede:public CEnemy{
	int mOmega;
public:
	void UpdateEnemy();
	void CreateEnemy();
	void Walk();
	void Killed();
};
void CHouseCentipede::CreateEnemy(){
	mKilledSound=SE_EXP5;
	mAutoDelFlg=false;
	mInvincibleFlg=true;
	mParts[0].InitParts(COMMON_PARTS_CANNON30x79);//–C‘ä
	mParts[1].InitParts(COMMON_PARTS_CANNON30x79);//–C‘ä
	CExRect::InitRect(&mRectBulletHit,-m_width/2-20,-m_height/2,m_width/2+20,m_height/2+100);
	CExRect::InitRect(&mRectPlayerHit,-m_width/2-20,-m_height/2,m_width/2+20,m_height/2+100-20);

	for(int i=0;i<15;i++){
		mBackParts[i].InitParts(ENEMY_PARTS_HC1_BODY,22,17);
	}


	if (mGameInfo->GetStage() == 2) {
		for (int i = 0; i<15; i++) {
			mBackParts[15 + i].InitParts(ENEMY_PARTS_TANK3_MERUS_LEFT);
			mBackParts[15 + i + 15].InitParts(ENEMY_PARTS_TANK3_MERUS_RIGHT);
			if (0<i && i<14) {
				mBackParts[15 + i + 30].InitParts(ENEMY_PARTS_TANK3_PROPODUS_LEFT);
				mBackParts[15 + i + 45].InitParts(ENEMY_PARTS_TANK3_PROPODUS_RIGHT);
			}
			else {
				mBackParts[15 + i + 30].InitParts(ENEMY_PARTS_TANK3_PROPODUS_LEFT);
				mBackParts[15 + i + 45].InitParts(ENEMY_PARTS_TANK3_PROPODUS_RIGHT);
			}
		}
	}
	else if (mGameInfo->GetStage() == 4 || mGameInfo->GetStage() == 5) {
		for (int i = 0; i<15; i++) {
			mBackParts[15 + i].InitParts(ENEMY_PARTS_TANK4_MERUS_LEFT);
			mBackParts[15 + i + 15].InitParts(ENEMY_PARTS_TANK4_MERUS_RIGHT);
			if (0<i && i<14) {
				mBackParts[15 + i + 30].InitParts(ENEMY_PARTS_TANK4_PROPODUS_LEFT);
				mBackParts[15 + i + 45].InitParts(ENEMY_PARTS_TANK4_PROPODUS_RIGHT);
			}
			else {
				mBackParts[15 + i + 30].InitParts(ENEMY_PARTS_TANK4_PROPODUS_LEFT);
				mBackParts[15 + i + 45].InitParts(ENEMY_PARTS_TANK4_PROPODUS_RIGHT);
			}
		}
	}
	else{
		for(int i=0;i<15;i++){
			mBackParts[15+i   ].InitParts(ENEMY_PARTS_HC1_MERUS_LEFT);
			mBackParts[15+i+15].InitParts(ENEMY_PARTS_HC1_MERUS_RIGHT);
			if(0<i && i<14){
				mBackParts[15+i+30].InitParts(ENEMY_PARTS_HC1_PROPODUS_LEFT_SHORT);
				mBackParts[15+i+45].InitParts(ENEMY_PARTS_HC1_PROPODUS_RIGHT_SHORT);
			}else{
				mBackParts[15+i+30].InitParts(ENEMY_PARTS_HC1_PROPODUS_LEFT_LONG);
				mBackParts[15+i+45].InitParts(ENEMY_PARTS_HC1_PROPODUS_RIGHT_LONG);
			}
		}
	}
	/**/
}

void CHouseCentipede::Walk(){
	int omega=13;
	if(mGameInfo->GetStage()==0)omega=43;
	mBltInfo.angle=(int)(10*sin(N_PI*4*mTimer));
	m_vx=(sin(N_PI*mTimer*4))*sin(3.1415*(mTimer/20.0));
	for(int i=1;i<15;i++){
		LinkBackParts(i,i-1,0);
		mBackParts[i].SetAngle((int)((30.0-i*2+10.0*sin(N_PI*mTimer*4))*sin(3.1415*(i*0.134+mTimer/20.0))));
	}
	for(int i=0;i<15;i++){
		int i01=i;
		LinkBackParts(i+15*1,i  ,mBackParts[i].GetAngle()-40+i*8+(int)(25*sin(N_PI*(omega*mTimer+i01*47))),22-6,17);
		LinkBackParts(i+15*2,i  ,mBackParts[i].GetAngle()+40-i*8+(int)(25*sin(N_PI*(omega*mTimer+i01*47))),22+6,17);

		LinkBackParts(i+15*3,i+15  ,mBackParts[i].GetAngle()-60+i*10+(int)(10*sin(N_PI*(omega*mTimer+i01*47))));
		LinkBackParts(i+15*4,i+15*2,mBackParts[i].GetAngle()+60-i*10+(int)(10*sin(N_PI*(omega*mTimer+i01*47))));
	}

	LinkFrontPartsToBackParts(0,2,0);
	LinkFrontPartsToBackParts(1,8,0);
}

void CHouseCentipede::UpdateEnemy(){
	Walk();
	DirectFrontPartsTo(0,mPlayer->GetX(),mPlayer->GetY());
	DirectFrontPartsTo(1,mPlayer->GetX(),mPlayer->GetY());
	if(mTimer==1){
		m_y=BATTLE_RECT.bottom+m_height/2-1;
		m_vy=-5;
	}else if(m_y<mCreateInfo.params[0]){
		m_vy=0;
	}
	if(mTimer>10){
		mAutoDelFlg=true;
		mInvincibleFlg=false;
	}
	if(mTimer<200){
		CVector v(mParts[0].GetEndX()-mParts[0].GetStartX(), mParts[0].GetEndY()-mParts[0].GetStartY());
		CVector v2(mParts[1].GetEndX()-mParts[1].GetStartX(), mParts[1].GetEndY()-mParts[1].GetStartY());
		v.Rotate(N_PI*mParts[0].GetAngle());
		v2.Rotate(N_PI*mParts[1].GetAngle());
		int dist[5]={120,80,40,20,0};
		int freq=80-mGameLevel*10;
		if(abs((int)m_y-mPlayer->GetY())>dist[mGameLevel] && mTimer>30 && m_vy==0){
			double spd=12.0;
			if(rand()%freq==0){
				mSE->PlaySingleSound(SE_SHT1);
				NormalShot((int)m_x-m_width/2+mParts[0].GetTargetX()+(int)v.x, (int)m_y-m_height/2+mParts[0].GetTargetY()+(int)v.y,EB_40,0,spd);
				for(int i=0;i<5;i++)
					NormalShot((int)m_x-m_width/2+mParts[0].GetTargetX()+(int)v.x, (int)m_y-m_height/2+mParts[0].GetTargetY()+(int)v.y,EB_20,3,spd-6+i);
			}
			if(rand()%freq==0){
				mSE->PlaySingleSound(SE_SHT1);
				NormalShot((int)m_x-m_width/2+mParts[1].GetTargetX()+(int)v2.x, (int)m_y-m_height/2+mParts[1].GetTargetY()+(int)v2.y,EB_40,0,spd);
				for(int i=0;i<5;i++)
					NormalShot((int)m_x-m_width/2+mParts[1].GetTargetX()+(int)v2.x, (int)m_y-m_height/2+mParts[1].GetTargetY()+(int)v2.y,EB_20,3,spd-6+i);
			}
		}
	}
	if(mTimer>150){
		m_vy=5;
	}
}


void CHouseCentipede::Killed(){
	m_y += 4.0;
	/////////////        PURGE  PARTS      ///////////////////
	PurgeParts(0,0,mMaxParts*3,4,0,5);
	if (mGameInfo->GetStage() == 0)PurgeBackParts(5, 30, mMaxBackParts * 2, 8, 0, 5);
	if (mGameInfo->GetStage() == 2)PurgeBackParts(3, 20, mMaxBackParts * 2, 4, 0, 5);
	if (mGameInfo->GetStage() == 4)PurgeBackParts(3, 30, mMaxBackParts * 2, 4, 0, 5);

	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);
	if(mKilledTimer%4==0){
		for(int i=0;i<6;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y+m_height/2,EFFECT_EXPLOSION_160,0,rand()%30-15,-rand()%5+60+i*10,0,3,0,0);
		mEffectManager->CreateEffect((int)m_x,(int)m_y+15+m_height/2,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
		for(int i=0;i<4;i++){
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,40-rand()%15,rand()%15-40,1,0,2,10,0);
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,-40+rand()%15,rand()%15-40,1,0,2,10,0);
		}
	}
	if(mKilledTimer>=16){
		mDelFlg=true;
		for(int i=0;i<18;i++){
			int v=rand()%20+10;
			double vx=v*cos(N_PI*20*i);
			double vy=v*sin(N_PI*20*i)-18;
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
		for(int i=0;i<4;i++)mItemManager->CreateItem((int)m_x,(int)m_y,2,0,rand()%20-10,-rand()%20);
	}
}