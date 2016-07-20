const int BOSS_PARTS_FILES=10;
const int BOSS_MAIN_FILES=4;

enum TBossFile {
	BOSS1_1,
	BOSS2_1,
	BOSS3_1,
	BOSS4_1,
	BOSS5_1,
	BOSS6_1,
	BOSS7_1,
	BOSS3_2,
	BOSS6_2,
	BOSS7_2,
	BOSS_FILES,
};
const TEnemyFileData BOSS_FILE[BOSS_FILES]={
	{ "dat/img/boss/boss1/boss1.bmp",195,94,5,8 },
	{ "dat/img/boss/boss2/boss2.bmp",521,466,7,0 },
	{ "dat/img/boss/boss3/boss3.bmp",680,610,22,0 },
	{ "dat/img/boss/boss4/boss4.bmp",216,128,0,2 },
	{ "dat/img/boss/boss5/boss5.bmp",540,443,3,0 },
	{ "dat/img/boss/boss6/boss6.bmp",844,602,3,1 },
	{ "dat/img/boss/boss7/boss7.bmp",293,293,0,2 },
	{ "dat/img/boss/boss3/boss3-2.bmp",197,20,0,0 },
	{ "dat/img/boss/boss6/boss6-2.bmp",293,293,0,0 },
	{ "dat/img/boss/boss7/boss7-2.bmp",293,293,0,0 },
};

class CBoss:public CEnemy{
protected:
	int mDeadTimer;
	int mBackground;
	virtual void _UpdateAfterDeath();
	CEnemyManager *mEnemyManager;
public:
	CBoss():CEnemy(),mDeadTimer(0),mBackground(0){
		mAutoDelFlg=false;
		mEnemyManager=CEnemyManager::GetInstance();
	}
	const int GetBackground(){return mBackground;}
	const int GetExLife(){return mExLife;}
	const int GetLife(){return mLife;}
	const int GetDeadTimer(){return mDeadTimer;}
	const bool isStageEnd(){
		if (mKind != mGameInfo->GetStage())return false;
		return (mDeadTimer>100);
	}
	void Update(){}
	void UpdateBoss();
	void CreateBoss();
	virtual void Transform(){}
	void SetImg(int k) {
		mImgId = k;
		m_width = BOSS_FILE[k].width;
		m_height = BOSS_FILE[k].height;
	}
};

void CBoss::CreateBoss() {
	mImgId = mKind;
	m_width = BOSS_FILE[mKind].width;
	m_height = BOSS_FILE[mKind].height;
	CExRect::InitRect(&mRectBulletHit,-m_width/2,-m_height/2,m_width/2,m_height/2);
	CExRect::InitRect(&mRectPlayerHit,-m_width/2,-m_height/2,m_width/2,m_height/2);
	mMaxParts = BOSS_FILE[mKind].front_parts;
	mMaxBackParts = BOSS_FILE[mKind].back_parts;

	if(mMaxBackParts>0)mBackParts=new CEnemyParts[mMaxBackParts];
	if(mMaxParts>0)mParts = new CEnemyParts[mMaxParts];
}

void CBoss::UpdateBoss(){
	if(mKind==mGameInfo->GetStage())mGameInfo->StopEnemy();
	mBltInfo.type=BLT_KEY;
	for(int i=0;i<mMaxBackParts;i++){ mBackParts[i].SetBltType(BLT_KEY); }
	for(int i=0;i<mMaxParts;i++){mParts[i].SetBltType(BLT_KEY);}
	m_x+=m_vx; m_y+=m_vy;
	if(mLife<0){
		m_vx=m_vy=0;
		mExLife--;
		mLife=mLife0;
		mTimer=0;
		mSE->PlaySingleSound(SE_EXP4);
		SampleExplosion((int)m_x,(int)m_y);
	}
	if(mExLife>=0){
		RECT rc={(int)m_x-m_width/2+mHitPadding.left,(int)m_y-m_height/2+mHitPadding.top,
			(int)m_x+m_width/2-mHitPadding.right,(int)m_y+m_height/2-mHitPadding.bottom};
		if(mBulletManager->HitTestRect(mRectBulletHit,m_x,m_y) || mBombManager->HitTestRect(mRectBulletHit,m_x,m_y) &&!mInvincibleFlg){
			mLife--;
			mSE->PlayLoopSound(SE_KEZ2);
			if(mTimer%3==0){
				mBltInfo.type=BLT_RED;
				for(int i=0;i<mMaxBackParts;i++){ mBackParts[i].SetBltType(BLT_RED); }
				for(int i=0;i<mMaxParts;i++){mParts[i].SetBltType(BLT_RED);}
			}
		}
		if(CExRect::isTargetInRect(&mRectPlayerHit,mPlayer->GetX(),mPlayer->GetY(),m_x,m_y)){
			mPlayer->ForcePlayer(0,14);
		}
	} else _UpdateAfterDeath();
}

void CBoss::_UpdateAfterDeath(){
	mDeadTimer++;
	//mBltInfo.hole_r = 45;
	mBltInfo.type = BLT_NULL;
	if (mMaxParts > 0) {
		for (int i = 0; i < mMaxParts; i++) {
			mParts[i].SetAngle(rand()%360);
			mParts[i].SetTargetPos(mParts[i].GetTargetX() + mDeadTimer * 3 * (i - 2), mParts[i].GetTargetY() + mDeadTimer * 4 * (i+1));
		}
	}
	if (mMaxBackParts > 0) {
		for (int i = 0; i < mMaxBackParts; i++) {
			mBackParts[i].SetAngle(rand() % 360);
			mBackParts[i].SetTargetPos(mBackParts[i].GetTargetX() + mDeadTimer * 2 * (i - 3), mBackParts[i].GetTargetY() + mDeadTimer * 3 * (i + 1));
		}
	}
	if(mDeadTimer==2){
		mGameInfo->SetQuake(70);
		mSE->PlaySingleSound(SE_EXP3);
		TEffectFile k = EFFECT_EXPLOSION_LIGHT_40;
		if (rand() == 0)k = EFFECT_EXPLOSION_LIGHT_80;
		for(int i=0;i<20;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,k,0,rand()%20-10,rand()%20-10, 0, 2, 0, 0);
	}

	if(mDeadTimer==4){
		mSE->PlaySingleSound(SE_EXP5);
		for(int i=0;i<16;i++)mEffectManager->CreateEffect(m_x,m_y+m_height/2,EFFECT_EXPLOSION_160,0,rand()%30-15,rand()%5-60+i*10,0,3,0,0);
		mEffectManager->CreateEffect(m_x,m_y+15+m_height/2,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
		for(int i=0;i<4;i++){
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,40-rand()%15,rand()%15-40,1,0,2,10,0);
			mDebrisManager->CreateDebris((int)m_x,(int)m_y+m_height/2,2,0,-40+rand()%15,rand()%15-40,1,0,2,10,0);
		}
	}
	if(mDeadTimer==9){
		mSE->PlaySingleSound(SE_EXP6);
		for(int i=0;i<20;i++){
			int v=rand()%10+10;
			double vx=v*cos(N_PI*18*i);
			double vy=-v*sin(N_PI*18*i)-20;
			mEffectManager->CreateEffect(m_x,m_y+m_height/2, EFFECT_EXPLOSION_90,0,vx,vy,0,3,0,0);
		}
	}
	if(mDeadTimer==19){
		mSE->PlaySingleSound(SE_SHT1);
		for(int i=0;i<20;i++){
			int v=rand()%20+10;
			double vx=v*cos(N_PI*18*i);
			double vy=-v*sin(N_PI*18*i)-20;
			mEffectManager->CreateEffect(m_x,m_y+m_height/2, EFFECT_EXPLOSION_90,0,vx,vy,0,3,0,0);
		}
	}

	if (mDeadTimer == 20) {
		mEnemyManager->DestroyAllEnemy();
		mEBManager->KillAllBullet();
		mEMManager->Reset();
	}
	if(mDeadTimer>60)mBltInfo.type=BLT_NULL;
	if(mDeadTimer>200)mDelFlg=true;
}
