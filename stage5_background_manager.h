class CStage5BackgroundManager : public CBackgroundManager{
protected:
	static const int TIME_BOSS = 3500;
	CImage32 mImgBossBG;
	static CStage5BackgroundManager* instance;
public:
	CStage5BackgroundManager():CBackgroundManager(){
		mImgBaseBG.load( "dat/img/landscape/stage5_space.bmp");
		CImageFactory::InitBitmap(&mImgBossBG, "dat/img/landscape/st1-ship42-old.bmp");
	}
	static CStage5BackgroundManager* GetInstance(){return instance;}
	void Update();
	void UpdateStage();
	void UpdateBossStage();
};
CStage5BackgroundManager* CStage5BackgroundManager::instance=new CStage5BackgroundManager();

void CStage5BackgroundManager::UpdateBossStage() {
	int colors[100];	
	CImageBlenderP3D::getShadow(colors, 100,0);
	RECT rc = { BATTLE_LEFT,400,BATTLE_RIGHT,720 };
	int phase = 400*(mPlayer->GetX() - BATTLE_LEFT)/(BATTLE_RIGHT-BATTLE_LEFT) - 200;
	CImageBlenderP3D::BltFloor(bg, &mImgBossBG, rc, 50, 960 / 2 + phase, 0, mTimer * 12, colors, 100);
	RECT rc2 = {BATTLE_LEFT,0,BATTLE_RIGHT,300 };
	CImageBlenderP3D::BltRoof(bg, &mImgBossBG, rc2, 50, 960 / 2 + phase, 0, mTimer * 12, colors, 100);
	CShapeBlender::fillRect(bg, BATTLE_LEFT, 250, BATTLE_RIGHT, 450,0xFF000000);

	int alpha = 255 - (mTimer - TIME_BOSS) * 5;
	if (alpha > 0)CImageFilter::addBrightness(bg, -alpha);
}
void CStage5BackgroundManager::Update() {
	UpdateSuper();
	if (mTimer<TIME_BOSS) {
		UpdateStage();
	}
	else {
		UpdateBossStage();
	}
}
void CStage5BackgroundManager::UpdateStage(){
	double spd=3;
	if(mTimer>1000)spd=4;
	if(mTimer>1400)spd=5;
	if(mTimer>3000)spd=10;

	CBltInfo bi(BLT_MEMCOPY);
	if (mTimer > TIME_BOSS - 255) {
		bi.type = BLT_BLACKEN;
		bi.alpha = mTimer - TIME_BOSS + 255;
	}
	SpreadBaseBG( spd, bi);

	double landSpdY = 16.0;
	mLandscapeManagerBack->SetSpeed(0, landSpdY);
	mLandscapeManager->SetSpeed(0, landSpdY);

	if(mTimer>100 && (mTimer<2000 || mTimer>2500)){
		CCreateInfo info;
		int dx_cristal=(int)(50*(1.0+sin(N_PI*mTimer)));
		int floorTop=mLandscapeManagerBack->seekTop();
		if(floorTop>=0){
			mCounter++;
			mCounter%=3;
			if(mTimer<3000){
				mLandscapeManager->CreateLandscape(BATTLE_RECT.right+dx_cristal-55+rand()%10,0-182/2,LANDSCAPE_BLOCK2,0,0.0,landSpdY);	
				mLandscapeManager->CreateLandscape(BATTLE_RECT.left -dx_cristal+55-rand()%10,0-182/2,LANDSCAPE_BLOCK2,0,0.0,landSpdY);
			}
		}
	}

	int floorTop=mLandscapeManagerBack->seekTop();
	CCreateInfo info;
	if(floorTop>=0){
		int deltaX = 0;
		if (mTimer > 3000) {
			deltaX = mTimer - 3000;
		}
		if (mTimer < 100) {
			deltaX = 100 - mTimer;
		}
		mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.left+30-deltaX,floorTop-128/2,LANDSCAPE_FLOOR5,0,0.0,landSpdY);
		mLandscapeManagerBack->CreateLandscape(BATTLE_RECT.right-31+ deltaX,floorTop-128/2,LANDSCAPE_FLOOR5,0,0.0,landSpdY);
	}
	if(mTimer%80==0)mLandscapeManagerFront->CreateLandscape(BATTLE_MIDDLE_X,0,LANDSCAPE_BAR1,0,0,40);
}