class CStage4BackgroundManager : public CBackgroundManager{
protected:
	static CStage4BackgroundManager* instance;
public:
	CStage4BackgroundManager():CBackgroundManager(){
		mImgBaseBG.load("dat/img/landscape/stage4_space.bmp");
	}
	static CStage4BackgroundManager* GetInstance(){return instance;}
	void Update();
};
CStage4BackgroundManager* CStage4BackgroundManager::instance=new CStage4BackgroundManager();

void CStage4BackgroundManager::Update(){
	UpdateSuper();

	double spd=30;
	if(mTimer>1000)spd=40;
	if(mTimer>1400)spd=50;
	if(mTimer>3000)spd=100;
	SpreadBaseBG( spd);

	double landSpdY = 16.0;
	mLandscapeManagerBack->SetSpeed(0, landSpdY);
	mLandscapeManager->SetSpeed(0, landSpdY);
}
