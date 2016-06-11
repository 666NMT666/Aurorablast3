class CStage3BackgroundManager : public CBackgroundManager{
protected:
	static CStage3BackgroundManager* instance;
public:
	CStage3BackgroundManager():CBackgroundManager(){
		mImgBaseBG.load("dat/img/landscape/stage3_space.bmp");
	}
	static CStage3BackgroundManager* GetInstance(){return instance;}
	void Update();
};
CStage3BackgroundManager* CStage3BackgroundManager::instance=new CStage3BackgroundManager();

void CStage3BackgroundManager::Update(){
	UpdateSuper();

	double spd=3;
	if(mTimer>1000)spd=4;
	if(mTimer>1400)spd=5;
	if(mTimer>3000)spd=10;
	SpreadBaseBG( spd);

	double landSpdY = 16.0;
	mLandscapeManagerBack->SetSpeed(0, landSpdY);
	mLandscapeManager->SetSpeed(0, landSpdY);

	if(mTimer>100 && (mTimer<2000 || mTimer>2500)){
		CCreateInfo info;
		int dx_cristal=(int)(40*(1.0+sin(N_PI*mTimer)));
		int floorTop=mLandscapeManagerBack->seekTop();
		if(floorTop>=0){
			mCounter++;
			mCounter%=3;
			int k[4]={
				LANDSCAPE_NEEDLE1+rand()%2,
				LANDSCAPE_NEEDLE1+rand()%2,
				LANDSCAPE_NEEDLE1+rand()%2,
				LANDSCAPE_NEEDLE1+rand()%2,
			};
			if(mTimer<3000){
				mLandscapeManager->CreateLandscape(BATTLE_RECT.right+dx_cristal-75+rand()%10,0-182/2,k[0],0,0.0,landSpdY);	
				mLandscapeManager->CreateLandscape(BATTLE_RECT.right+dx_cristal-75+rand()%10,0,k[1],0,0.0,landSpdY);	
				mLandscapeManager->CreateLandscape(BATTLE_RECT.left -dx_cristal+75-rand()%10,0-182/2,k[2],0,0.0,landSpdY);
				mLandscapeManager->CreateLandscape(BATTLE_RECT.left -dx_cristal+75-rand()%10,0,k[3],0,0.0,landSpdY);
			}
			if(mTimer>1200 && mTimer<3000){
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left+30,floorTop-64/2,LANDSCAPE_FLOOR3,0,0.0,landSpdY);
				mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right-31,floorTop-64/2,LANDSCAPE_FLOOR3,0,0.0,landSpdY);
			}
		}
	}
	if(mTimer>=0 && (mTimer<=2500 || mTimer>=3000)){
		int floorTop=mLandscapeManagerBack->seekTop();
		CCreateInfo info;
		if(floorTop>=0){
			mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left+30,floorTop-128/2,LANDSCAPE_FLOOR3,0,0.0,landSpdY);
			mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right-31,floorTop-128/2,LANDSCAPE_FLOOR3,0,0.0,landSpdY);
		}
	}
	if(mTimer%120==0)mLandscapeManagerFront->CreateLandscape(BATTLE_MIDDLE_X,0,LANDSCAPE_BAR2,0,0,60);
}