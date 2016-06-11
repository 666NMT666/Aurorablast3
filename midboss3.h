class CEnemyMidboss3 :public CEnemy{
public:
	void UpdateEnemy();
	void CreateEnemy();
	void Killed();
	void MainFire(int i);
};

void CEnemyMidboss3::MainFire(int j) {
	CVector head = GetFrontPartsHead(j);
	int angle = 180 - mParts[j].GetAngle();
	double spd = (mGameLevel + 2) * 4;
	mSE->PlaySingleSound(SE_EXP2);
	AngleShot(head.x, head.y, EDAB_66, 0, 20 + spd, angle);
	AngleShot(head.x, head.y, EDAB_66, 0, 16 + spd, angle);
	for (int i = 0; i<16; i++)AngleShot(head.x, head.y, EB_26, 2, 4 + i + spd, angle + rand() % 20 - 10);
	mELManager->Create<CLazerBullet>((int)head.x, (int)head.y, 0, 0, -60.0, 0.0, defaultCreateInfo);
}
void CEnemyMidboss3::CreateEnemy(){
	/*
	mParts[0].InitParts(COMMON_PARTS_CANNON170x500, m_width / 2 + 100, 298);
	mParts[1].InitParts(COMMON_PARTS_CANNON170x500, m_width / 2 - 100, 298);
	CExRect::InitRect(&mRectBulletHit, -m_width / 2 - 20, -m_height / 2, m_width / 2 + 20, -30);
	CExRect::InitRect(&mRectPlayerHit, -m_width / 2 - 20, -m_height / 2, m_width / 2 + 20, 20);
	*/
	
	mParts[0].InitParts(ENEMY_PARTS_SELF,129,118);// Žå–C
	mParts[1].InitParts(ENEMY_PARTS_SELF,43,111);//
	mParts[2].InitParts(ENEMY_PARTS_SELF,214,111);//
	mAutoDelFlg=false;
	m_y=BATTLE_RECT.bottom+m_height/2-1;
	m_vy=-5;
}
void CEnemyMidboss3::UpdateEnemy(){
	/*
	if (mTimer == 1) {
		m_y = BATTLE_BOTTOM + m_height / 2;
		m_x = (BATTLE_RECT.right + BATTLE_RECT.left) / 2;
	}
	if (mTimer <= 200) {
		m_x = ExMath::asymptote(m_x, (BATTLE_RECT.right + BATTLE_RECT.left) / 2, mTimer*0.125);
		m_y = ExMath::asymptote(m_y, 150, mTimer*0.125);
		if (m_y<150)m_y = 150;
	}
	if (mTimer<50) {}
	else if (mTimer<100) {}
	else if (mTimer<200) {
		int freq[5] = { 22,20,18,17,16 };
		if (mTimer%freq[mGameLevel] == 0) {
			int j = rand() % 2;
			mSE->PlaySingleSound(SE_EXP3);
			int p[5] = { 0,20,30,1,0 };
			CCreateInfo info(p);
			for (int i = 0; i<5; i++) {
				int x = mParts[j].GetTargetX() - m_width / 2;
				int y = mParts[j].GetTargetY() - m_height / 2;
				int dx = 40 * sin(N_PI*(20 + 30 * i));
				int dy = 40 * cos(N_PI*(20 + 30 * i));
				mEMManager->Create<CEnemyMissile>((int)m_x + x + dx, (int)m_y + y + dy, 0, 1, dx / 2, dy / 2, info);
				mEMManager->Create<CEnemyMissile>((int)m_x + x - dx, (int)m_y + y + dy, 0, 1, -dx / 2, dy / 2, info);
			}
		}
	}
	else if (mTimer<250) {
	}
	else if (mTimer<400) {
		if (mTimer % 5 == 0) {
			double spd = (double)(14 + mGameLevel * 4 + rand() % 10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head = GetFrontPartsHead(0);
			for (int i = 0; i<3; i++)
				AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
			head = GetFrontPartsHead(1);
			for (int i = 0; i<3; i++)
				AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
		}
	}
	else if (mTimer<600) {
		int freq[5] = { 32,30,26,20,16 };
		if (mTimer%freq[mGameLevel] == 0) {
			int j = rand() % 2;
			mSE->PlaySingleSound(SE_EXP3);
			int p[5] = { 0,20,30,1,0 };
			CCreateInfo info(p);
			for (int i = 0; i<5; i++) {
				int x = mParts[j].GetTargetX() - m_width / 2;
				int y = mParts[j].GetTargetY() - m_height / 2;
				int dx = 40 * sin(N_PI*(20 + 30 * i));
				int dy = 40 * cos(N_PI*(20 + 30 * i));
				mEMManager->Create<CEnemyMissile>((int)m_x + x + dx, (int)m_y + y + dy, 0, 1, dx / 2, dy / 2, info);
				mEMManager->Create<CEnemyMissile>((int)m_x + x - dx, (int)m_y + y + dy, 0, 1, -dx / 2, dy / 2, info);
			}
		}
		if (mTimer % 5 == 0) {
			double spd = (double)(14 + mGameLevel * 4 + rand() % 10);
			mSE->PlaySingleSound(SE_EXP4);
			CVector head = GetFrontPartsHead(0);
			for (int i = 0; i<3; i++)
				AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
			head = GetFrontPartsHead(1);
			for (int i = 0; i<3; i++)
				AngleShot(head.x, head.y, EB_80, 0, spd + i * 2, 90);
		}
	}
	else if (mTimer<800) {
		if (mTimer % 8 == 0) {
			mSE->PlaySingleSound(SE_EXP2);
			mCounter++;
			for (int i = 0; i<3 + mGameLevel / 2; i++) {
				AngleShot(m_x, m_y - 100, EB_80, 0, (double)(1 - i - (4 - mGameLevel)), 30 * mCounter + 20);
				AngleShot(m_x, m_y - 100, EB_40, 0, (double)(13 - i - (4 - mGameLevel)), 30 * mCounter + 30);
				AngleShot(m_x, m_y - 100, EB_80, 0, (double)(13 - i - (4 - mGameLevel)), -30 * mCounter + 20);
				AngleShot(m_x, m_y - 100, EB_40, 0, (double)(13 - i - (4 - mGameLevel)), -30 * mCounter + 30);
			}
		}
	}
	else {
		mLife = -1;
	}
	m_vx = 0;
	return;
	*/
	
	
	
	
	mBltInfo.type=BLT_STRUCTURE;
	mParts[0].SetBltType(BLT_STRUCTURE);
	mParts[1].SetBltType(BLT_STRUCTURE);
	mParts[2].SetBltType(BLT_STRUCTURE);
	{
		CVector v1(mParts[0].GetEndX()-mParts[0].GetStartX(),mParts[0].GetEndY()-mParts[0].GetStartY());
		v1.Rotate(N_PI*(mParts[0].GetAngle()));
		CVector v2(mPlayer->GetX()-(mParts[0].GetTargetX()+m_x-m_width/2),mPlayer->GetY()-(mParts[0].GetTargetY()+m_y-m_height/2));
		if(v1.x*v2.y-v1.y*v2.x<0.0){
			mParts[0].AddAngle(1);
		}else{
			mParts[0].AddAngle(-1);
		}
	}	
	if(mTimer<300){
		int freq=80-mGameLevel*5;
		CVector v(mParts[1].GetEndX()-mParts[1].GetStartX(), mParts[1].GetEndY()-mParts[1].GetStartY());
		CVector v2(mParts[2].GetEndX()-mParts[2].GetStartX(), mParts[2].GetEndY()-mParts[2].GetStartY());
		v.Rotate(N_PI*mParts[1].GetAngle());
		v2.Rotate(N_PI*mParts[2].GetAngle());
		int dist[5]={120,80,40,20,0};
		int freq2=40-mGameLevel*5;
		if(abs((int)m_y-mPlayer->GetY())>dist[mGameLevel] && mTimer>30){
			if(rand()%freq2==0){
				mSE->PlaySingleSound(SE_SHT1);
				AngleMissile((int)m_x-m_width/2+mParts[1].GetTargetX()+(int)v.x, (int)m_y-m_height/2+mParts[1].GetTargetY()+(int)v.y,1,0,18.0,GetShotAngleFromPartsAngle(1));
			}
			if(rand()%freq2==0){
				mSE->PlaySingleSound(SE_SHT1);
				AngleMissile((int)m_x-m_width/2+mParts[2].GetTargetX()+(int)v2.x, (int)m_y-m_height/2+mParts[2].GetTargetY()+(int)v2.y,1,0,18.0,GetShotAngleFromPartsAngle(2));
			}
		}
		if(mTimer>50){
			double spd=10+mGameLevel*4;
			CVector v(mParts[0].GetEndX()-mParts[0].GetStartX(), mParts[0].GetEndY()-mParts[0].GetStartY());
			v.Rotate(N_PI*mParts[0].GetAngle());

			TARGB clr;
			clr.ARGB=0x00FF0000;
			clr.G=124+100*sin(N_PI*mTimer*33);
			CLine::drawLine2(m_bg,(int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x),(int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),700,GetShotAngleFromPartsAngle(0),clr.ARGB,BATTLE_RECT);
			CLine::drawLine2(m_bg,(int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x)+1,(int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),700,GetShotAngleFromPartsAngle(0),clr.ARGB,BATTLE_RECT);
			if((mTimer-50)%freq>5 && (mTimer-50)%freq<30){
				ChacePartsAngle(mParts[0],mPlayer->GetX(),mPlayer->GetY(),1);
			}else if((mTimer-50)%freq<40){
				int t=(mTimer-50)%freq;
				if((mTimer-50)%freq==30)mSE->PlaySingleSound(SE_KYP1);
				int x=(int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x);
				int y=(int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y);
				mFrontEffectManager->CreateEclipsedCircle(x,y,10+((mTimer-50)%freq-30)*12,x-4,y-5,9+((mTimer-50)%freq-30)*11,0xFFFFFFFF);
				mFrontEffectManager->CreateThrash(x,y,14-t/6,t*9,mTimer*5,0xFFFFFFFF);
				mFrontEffectManager->CreateThrash(x,y,14-t/6,t*10,mTimer*5+90,0xFFFFFFFF);
			}
			if((mTimer-50)%freq==freq-1 || (mTimer-50)%freq==freq-1-20){
				mSE->PlaySingleSound(SE_SHT2);
				AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_80,0,18.0,GetShotAngleFromPartsAngle(0));
				for(int i=0;i<5;i++)
					AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_20,3,12.0+i,GetShotAngleFromPartsAngle(0));
				for(int i=0;i<7;i++)
					AngleShot((int)(m_x-m_width/2+mParts[0].GetTargetX()+v.x), (int)(m_y-m_height/2+mParts[0].GetTargetY()+v.y),EB_26,
					2,(double)(17-i),GetShotAngleFromPartsAngle(0)+rand()%16-8);
			}
		}
	}

	if(m_y<300){
		m_vy=0;
	}
	if(mTimer>300)m_vy=10;
}

void CEnemyMidboss3::Killed(){
	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);
	if(mKilledTimer%4==0){
		for(int i=0;i<6;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y+m_height/2,EFFECT_EXPLOSION_160,0,rand()%30-15,rand()%5-60+i*10,0,3,0,0);
		mEffectManager->CreateEffect((int)m_x,(int)m_y+15+m_height/2,EFFECT_EXPLOSION_HEAD1,0,-15,0,0,1,0,0);
		for(int i=0;i<4;i++){
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,40-rand()%15,rand()%15-40,1,0,2,10,0);
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,-40+rand()%15,rand()%15-40,1,0,2,10,0);
		}
	}
	if(mKilledTimer==8){
		for(int i=0;i<20;i++){
			int v=rand()%10+10;
			double vx=v*cos(N_PI*18*i);
			double vy=-v*sin(N_PI*18*i)-20;
			mEffectManager->CreateEffect(m_x,m_y+m_height/2,EFFECT_EXPLOSION_90,0,vx,vy,0,3,0,0);
		}
	}
	if(mKilledTimer>=16){
		mDelFlg=true;
		for(int i=0;i<20;i++){
			int v=rand()%20+10;
			double vx=v*cos(N_PI*18*i);
			double vy=-v*sin(N_PI*18*i)-20;
			mEffectManager->CreateEffect((int)m_x,(int)m_y+m_height/2, EFFECT_EXPLOSION_90,0,vx,vy,0,3,0,0);
		}
		mItemManager->CreateItem(m_x,m_y,4,0,4,4);
	}
	int pointMul=500-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	if(mKilledTimer==8){
		for(int i=0;i<16;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20);
	}
	if(mKilledTimer==12){
		for(int i=0;i<4;i++)mItemManager->CreateItem((int)m_x,(int)m_y,2,0,rand()%20-10,rand()%20);
	}
}