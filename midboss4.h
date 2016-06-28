class CEnemyMidboss4:public CEnemy{
	int mTargetY;
public:
	void UpdateEnemy();
	void CreateEnemy();
	void Killed();
};


void CEnemyMidboss4::CreateEnemy(){
	mParts[0].InitParts(COMMON_PARTS_CANNON29x160,m_width/2,0);// Žå–C
	mAutoDelFlg=false;
	mTargetY=m_y;
	m_y=BATTLE_RECT.bottom+m_height/2-1;
	m_vy=-5;
	if(mTargetY<0)m_vy=-3;
}
void CEnemyMidboss4::UpdateEnemy(){
	mBltInfo.type=BLT_KEY;

	
	if(mTimer<300){
		int freq=80-mGameLevel*5;
		int dist[5]={120,80,40,20,0};
		
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

	if(m_y<mTargetY){ m_vy=0; mAutoDelFlg=true;}
	if(mTimer>300)m_vy=10;
}

void CEnemyMidboss4::Killed(){
	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);
	if(mKilledTimer%4==0){
		for(int i=0;i<6;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y+m_height/2,EFFECT_EXPLOSION_160,0,rand()%30-15,rand()%5-60+i*10,0,3,0,0);
		mEffectManager->CreateEffect((int)m_x,(int)m_y+15+m_height/2,EFFECT_EXPLOSION_HEAD1,0,-15,0,0,1,0,0);
		for(int i=0;i<4;i++){
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,40-rand()%15,rand()%15-40,1,0,2,10,0);
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,-40+rand()%15,rand()%15-40,1,0,2,10,0);
		}
	}
	if(mKilledTimer>=16){
		mDelFlg=true;
		for(int i=0;i<20;i++){
			int v=rand()%20+10;
			double vx=v*cos(N_PI*18*i);
			double vy=-v*sin(N_PI*18*i)-20;
			mEffectManager->CreateEffect((int)m_x,(int)m_y+m_height/2,EFFECT_EXPLOSION_90,0,vx,vy,0,3,0,0);
		}
		mItemManager->CreateItem(m_x, m_y, 4, 0, 4, 4);
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