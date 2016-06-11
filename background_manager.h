class CBackgroundManager{
protected:
	int mTimer;
	int mQuake;
	int mCounter;
	double mBG_Y;
	CImageDIB *bg; 
	CPlayer *mPlayer;
	CLandscapeManager* mLandscapeManager;
	CLandscapeManager* mLandscapeManagerBack;
	CLandscapeManager* mLandscapeManagerFront;
	CGameInfo* mGameInfo;
	CBossManager* mBossManager;
	CImage32 mImgBaseBG;
public:
	CBackgroundManager():mTimer(0),mQuake(0){
		mPlayer=CPlayer::GetInstance();
		mCounter = 0;
		mBG_Y = 0.0;
		mBossManager=CBossManager::GetInstance();
		bg=CImageDIB::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		mLandscapeManager=CLandscapeManager::GetInstance();
		mLandscapeManagerBack=CLandscapeManager::GetInstance2();
		mLandscapeManagerFront=CLandscapeManager::GetInstance3();
	}
	virtual void Update(){}
	void UpdateSuper(){
		mTimer++;
		if (mPlayer->isInvincible()) {
			int quaceSize = (int)(40.0*(mPlayer->GetInvincibleRatio()*mPlayer->GetInvincibleRatio())) + 1;
			mQuake = rand() % quaceSize - quaceSize / 2;
		}
	}
	virtual void Reset(){mTimer=0;mQuake=0;}
	void SpreadBaseBG(double spd) {
		CBltInfo bi(BLT_MEMCOPY);
		//if( mTimer%2==0 )bi.type = BLT_MEMCOPY_SKIP;
		SpreadBaseBG(spd, bi);
	}

	void SpreadBaseBG(double spd, CBltInfo bi) {
		SpreadBG(spd,bi,&mImgBaseBG);
	}

	void SpreadBG(double spd, CBltInfo bi, CImage32* img) {
		mBG_Y += spd;
		if (mBG_Y > BATTLE_TOP) mBG_Y -= img->Height();
		for (int i = 0; mBG_Y + i*img->Height() < BATTLE_BOTTOM; i++) {
			CImageBlender::Blt(bg, img, &bi, BATTLE_RECT, BATTLE_RECT.left, (int)mBG_Y + i*img->Height() + mQuake);
		}
	}
};

