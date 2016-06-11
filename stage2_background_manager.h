class CStage2BackgroundManager : public CBackgroundManager{
protected:
	static CStage2BackgroundManager* instance;
public:
	CStage2BackgroundManager():CBackgroundManager(){
		mImgBaseBG.load("dat/img/landscape/stage2_space.bmp");
	}
	static CStage2BackgroundManager* GetInstance(){return instance;}
	void Update();
};
CStage2BackgroundManager* CStage2BackgroundManager::instance=new CStage2BackgroundManager();

void CStage2BackgroundManager::Update(){
	UpdateSuper();

	double spd=3;
	if(mTimer>1000)spd=4;
	if(mTimer>1400)spd=5;
	if(mTimer>3000)spd=10;

	SpreadBaseBG( spd);

	double landSpdY = 16.0;
	mLandscapeManagerBack->SetSpeed(0, landSpdY);
	mLandscapeManager->SetSpeed(0, landSpdY);

	if( (100 < mTimer && mTimer < 2000) || (2500 < mTimer && mTimer<3000)){
		if (mTimer % 80 == 0)mLandscapeManagerFront->CreateLandscape(BATTLE_MIDDLE_X, 0, LANDSCAPE_BAR1, 0, 0, 40);
		CCreateInfo info;
		int dx_cristal=(int)(50*(1.0+cos(N_PI*mTimer)));
		int floorTop=mLandscapeManagerBack->seekTop();
		if(floorTop>=0){
			mCounter++;
			mCounter%=3;
			if(mCounter==0){
				int dx_cristal_right2=(int)(60.0*(1.0+sin(N_PI*mTimer*2)));
				int dx_cristal_left2=(int)(60.0*(1.0+sin(N_PI*mTimer*2.5)));
				mLandscapeManager->CreateLandscape(BATTLE_RECT.right + dx_cristal + dx_cristal_right2 - 155 + rand() % 10, 0 - 182 / 2, LANDSCAPE_CRYSTAL1, 0, 0, landSpdY);;
				mLandscapeManager->CreateLandscape(BATTLE_RECT.left - dx_cristal - dx_cristal_left2 + 155 - rand() % 10, 0 - 182 / 2, LANDSCAPE_CRYSTAL1, 0, 0, landSpdY);
			}
			mLandscapeManager->CreateLandscape(BATTLE_RECT.right + dx_cristal - 55 + rand() % 10, 0 - 182 / 2, LANDSCAPE_CRYSTAL1, 0, 0, landSpdY);
			mLandscapeManager->CreateLandscape(BATTLE_RECT.left - dx_cristal + 55 - rand() % 10, 0 - 182 / 2, LANDSCAPE_CRYSTAL1, 0, 0, landSpdY);
			
			if(mTimer>1200){
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left + 30, floorTop - 64 / 2, LANDSCAPE_FLOOR2, 0, 0, landSpdY);
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right - 31, floorTop - 64 / 2, LANDSCAPE_FLOOR2, 0, 0, landSpdY);
			}
		}
	}
	if(mTimer<=2500 || mTimer>=3000){
		int floorTop=mLandscapeManagerBack->seekTop();
		if(floorTop>=0){
			mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left + 30, floorTop - 128 / 2, LANDSCAPE_FLOOR2, 0, 0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right - 31, floorTop - 128 / 2, LANDSCAPE_FLOOR2, 0, 0, landSpdY);
		}
	}

}
