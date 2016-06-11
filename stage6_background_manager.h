class CStage6BackgroundManager : public CBackgroundManager{
private:
	static const int TIME_BOSS = 6400;
	CImage32 _mImgStBG;
protected:
	static CStage6BackgroundManager* instance;
public:
	CStage6BackgroundManager():CBackgroundManager(){
		_mImgStBG.load("dat/img/landscape/stage6_space_2.bmp");
		mImgBaseBG.load("dat/img/landscape/stage6_space.bmp");
	}
	static CStage6BackgroundManager* GetInstance(){return instance;}
	void Update();
};
CStage6BackgroundManager* CStage6BackgroundManager::instance=new CStage6BackgroundManager();

void CStage6BackgroundManager::Update(){
	UpdateSuper();
	double spd=15;
	if(mTimer>1000)spd=15;
	if(mTimer>1400)spd=15;
	if(mTimer>3000)spd=10;

	CBltInfo bi;
	if(mTimer<1000)SpreadBG(spd, bi, &_mImgStBG);
	else if(mTimer<4200)SpreadBaseBG(spd);
	else SpreadBG(spd,bi,&_mImgStBG);

	double landSpdY = 16.0;
	mLandscapeManagerBack->SetSpeed(0, landSpdY);
	mLandscapeManager->SetSpeed(0, landSpdY);

	int floorTop = mLandscapeManagerBack->seekTop();
	if (floorTop >= 0) {
		if (mTimer < 800) {}
		else if (mTimer < 1500) {
			mLandscapeManagerBack->CreateLandscape(BATTLE_LEFT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 0, 0.0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RIGHT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 0, 0.0, landSpdY);
		}
		else if (mTimer < 3000) {
			mLandscapeManagerBack->CreateLandscape(BATTLE_LEFT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 1, 0.0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RIGHT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 1, 0.0, landSpdY);
		}
		else if (mTimer < 3500) {
			mLandscapeManagerBack->CreateLandscape(BATTLE_LEFT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 0, 0.0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RIGHT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 0, 0.0, landSpdY);
		}
		else if (mTimer < 4000) {
			mLandscapeManagerBack->CreateLandscape(BATTLE_LEFT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 1, 0.0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RIGHT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 1, 0.0, landSpdY);
		}
		else if (mTimer < 5500) {
			mLandscapeManagerBack->CreateLandscape(BATTLE_LEFT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 0, 0.0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RIGHT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 0, 0.0, landSpdY);
		}
		else if (mTimer < 6000) {
			mLandscapeManagerBack->CreateLandscape(BATTLE_LEFT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 1, 0.0, landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RIGHT, floorTop - 280 / 2, LANDSCAPE_FLOOR6, 1, 0.0, landSpdY);
		}
	}

	if(mTimer%160==0)mLandscapeManagerFront->CreateLandscape(BATTLE_MIDDLE_X,0,LANDSCAPE_BAR2,0,0,60);
}