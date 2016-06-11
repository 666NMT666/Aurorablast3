class CStage7BackgroundManager : public CBackgroundManager{
protected:
	static CStage7BackgroundManager* instance;
public:
	CStage7BackgroundManager():CBackgroundManager(){
		mImgBaseBG.load("dat/img/landscape/stage7_space.bmp");
	}
	static CStage7BackgroundManager* GetInstance(){return instance;}
	void Update();
};
CStage7BackgroundManager* CStage7BackgroundManager::instance=new CStage7BackgroundManager();

void CStage7BackgroundManager::Update(){
	UpdateSuper();

	double spd=3;
	if(mTimer>1000)spd=4;
	if(mTimer>1400)spd=5;
	if(mTimer>3000)spd=10;
	SpreadBaseBG( spd);

	double landSpdY =  16.0;
	mLandscapeManagerBack->SetSpeed(0, landSpdY);
	mLandscapeManager->SetSpeed(0, landSpdY);

	if(mTimer<2000){
		int dx_cristal=(int)(50*(1.0+sin(N_PI*mTimer)));
		int floorTop=mLandscapeManagerBack->seekTop();
		if(floorTop>=0){
			if(mTimer>1200 && mTimer<3000){
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left+30,floorTop-64/2,LANDSCAPE_FLOOR2,0,0.0 ,landSpdY);
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right-31,floorTop-64/2,LANDSCAPE_FLOOR2,0,0.0 ,landSpdY);
			}
		}
	}
}