class CStage1BackgroundManager : public CBackgroundManager{
protected:
	static CStage1BackgroundManager* instance;
public:
	CStage1BackgroundManager():CBackgroundManager(){
		mImgBaseBG.load("dat/img/landscape/stage1_space.bmp");
	}
	static CStage1BackgroundManager* GetInstance(){return instance;}
	void Update();
	void UpdateBoss();
};
CStage1BackgroundManager* CStage1BackgroundManager::instance = new CStage1BackgroundManager();

void CStage1BackgroundManager::Update(){
	UpdateSuper();

	double spd=5;
	if(mTimer<1000)spd=ExMath::asymptote(2.0,5.0,mTimer*0.0075);
	if(mTimer>1000)spd=4;
	if(mTimer>1400)spd=10;
	if(mTimer>3000)spd=40;
	SpreadBaseBG( spd);

	double landSpdY = (mGameInfo->EnemyStopCheck() && mTimer<2950) ? 2.0 : 16.0;
	mLandscapeManagerBack->SetSpeed(0, landSpdY);
	mLandscapeManager->SetSpeed(0, landSpdY);

	int floorTop = mLandscapeManagerBack->seekTop();

	if((1000 < mTimer && mTimer<2000) || (2500 < mTimer && mTimer<3000)){
		if(floorTop>=0){
			mCounter++;
			mCounter%=3;
			if(mCounter==0){
				if(mTimer%500<300){
					mLandscapeManager->CreateLandscape(BATTLE_RECT.right-55+rand()%10,0-182/2,LANDSCAPE_CONTAINER1,0,0,landSpdY);	
					mLandscapeManager->CreateLandscape(BATTLE_RECT.left +55-rand()%10,0-182/2,LANDSCAPE_CONTAINER1,0,0,landSpdY);
				}else{
					mLandscapeManager->CreateLandscape(BATTLE_RECT.right-56/2,0-202/2,LANDSCAPE_GAS_TANK1,0,0,landSpdY);	
					mLandscapeManager->CreateLandscape(BATTLE_RECT.left +56/2,0-202/2,LANDSCAPE_GAS_TANK1,0,0,landSpdY);
				}
			}
		}
	}


	if(mTimer>1000){
		int subKind = 0;
		if (2500 < mTimer && mTimer < 3000) subKind = 0;
		if ((2000 <= mTimer && mTimer <= 2500) || 3000 <= mTimer) subKind = 3;
		if (floorTop >= 0) {
			mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left + 30, floorTop - 64 / 2, LANDSCAPE_FLOOR1, subKind, 0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right - 31, floorTop - 64 / 2, LANDSCAPE_FLOOR1, subKind, 0, landSpdY);
			if ((1200 < mTimer && mTimer<2000) || (2500 < mTimer && mTimer<3000)) {
				int k = (mTimer % 100 < 50) ? 1 : 4;
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left  + 30 + 127 * 1, floorTop - 64 / 2, LANDSCAPE_FLOOR1, k, 0, landSpdY);
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right - 31 - 127 * 1, floorTop - 64 / 2, LANDSCAPE_FLOOR1, k, 0, landSpdY);
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right - 31 - 127 * 2, floorTop - 64 / 2, LANDSCAPE_FLOOR1, 2, 0, landSpdY);
			}
		}
	}
	
}
