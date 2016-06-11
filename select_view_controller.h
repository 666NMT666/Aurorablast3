class CSelectViewController:public CViewController{
protected:
	int mPosition;
	CImage32 mImgBG;
	CImage32 mImgSelected;
	CImage32 mImgFigFormation,mImgFigMainWepon,mImgFigSubWeapon1,mImgFigSubWeapon2;
	CImage32 mImgExpLevel;
	CGameInfo* mGameInfo;
	static char mStrFormation[2][128];
	static char mStrMainWeapon[2][128];
	static char mStrSubWeapon1[3][128];
	static char mStrSubWeapon2[3][128];
	static char mStrLevel[5][128];
	CTextView* mWeaponTextView;
	bool mBackFlg,mStartFlg;
	int mKeyShot,mKeyBomb,mKeyChange,mKeyPause;
	int mForm,mMainWepon,mSubWepon,mBomb,mLevel;
	bool mClearedFlg[5];
	int mMaxLevel;
	int mMaxWeapon1Id;
	int mMaxWeapon2Id;
	static const char CLEAR_FILE_NAME[16];
public:
	CSelectViewController():CViewController(),mPosition(0),mBackFlg(false),mStartFlg(false),mKeyShot(1),mKeyBomb(2),mKeyChange(3),mKeyPause(9){
		mGameInfo=CGameInfo::GetInstance();
		CImageFactory::InitBitmap(&mImgBG,"dat/img/select.bmp");
		
		CImageFactory::InitBitmap(&mImgSelected,"dat/img/select_selected.bmp");

		CImageFactory::InitBitmap(&mImgFigFormation,"dat/img/select-fig-formation.bmp");
		CImageFactory::InitBitmap(&mImgFigMainWepon,"dat/img/select-fig-main.bmp");
		CImageFactory::InitBitmap(&mImgFigSubWeapon1,"dat/img/select-fig-sub1.bmp");
		CImageFactory::InitBitmap(&mImgFigSubWeapon2,"dat/img/select-fig-sub2.bmp");
		CImageFactory::InitBitmap(&mImgExpLevel,"dat/img/select-exp-level.bmp");

		mForm=mGameInfo->GetForm();
		mMainWepon=mGameInfo->GetMainWepon();
		mSubWepon=mGameInfo->GetSubWepon();
		mBomb=mGameInfo->GetUniqueWepon();
		mLevel=mGameInfo->GetLevel();
		RECT rc={330,250,595,329};
		mWeaponTextView=new CTextView(bg->hDC(),rc,16,0xDDDDDD,"");
		for(int i=0;i<5;i++)mClearedFlg[i]=false;
		mMaxLevel=4;
		mMaxWeapon1Id=2;
		mMaxWeapon2Id=2;
		LoadClearInfo();

		if(mClearedFlg[1])mMaxWeapon1Id=3;
		if(mClearedFlg[2])mMaxWeapon2Id=3;
		if(mClearedFlg[3])mMaxLevel=5;
	}
	~CSelectViewController(){

		delete mWeaponTextView;

	}
	void LoadClearInfo();
	void onKeyDownZ();
	void onKeyDownDown(){
		mPosition++;
		if(mPosition>5)mPosition=5;
		mSE->PlaySingleSound(SE_KEY1);
	}
	void onKeyDownUp(){
		mPosition--;
		if(mPosition<0)mPosition=0;
		mSE->PlaySingleSound(SE_KEY1);
	}
	void onKeyDownX(){
		mBackFlg=true;
		mSE->PlaySingleSound(SE_KEY1);
	}
	void onKeyDownRight();
	void onKeyDownLeft();
	int onTimer();
	int CheckKey(int pos,int def);
};
const char CSelectViewController::CLEAR_FILE_NAME[16]="dat/dat/cl.sat";

void CSelectViewController::onKeyDownLeft(){
	mSE->PlaySingleSound(SE_KEY1);
	if(mPosition==0){mForm=(mForm+2-1)%2;}
	if(mPosition==1){mMainWepon=(mMainWepon+2-1)%2;}
	if(mPosition==2){mSubWepon=(mSubWepon+mMaxWeapon1Id-1)%mMaxWeapon1Id;}
	if(mPosition==3){mBomb=(mBomb+mMaxWeapon2Id-1)%mMaxWeapon2Id;}
	if(mPosition==4){mLevel=(mLevel+mMaxLevel-1)%mMaxLevel;}
}
void CSelectViewController::onKeyDownRight(){
	mSE->PlaySingleSound(SE_KEY1);
	if(mPosition==0)++mForm%=2;
	if(mPosition==1)++mMainWepon%=2;
	if(mPosition==2)++mSubWepon%=mMaxWeapon1Id;
	if(mPosition==3)++mBomb%=mMaxWeapon2Id;
	if(mPosition==4)++mLevel%=mMaxLevel;
}
int CSelectViewController::onTimer(){
	onTimerSuper();
	if(mBackFlg){return TITLE_VIEW_CONTROLLER;}
	if(mStartFlg){return ENDURANCE_VIEW_CONTROLLER;}
	CBltInfo bic(BLT_KEY);
	CBltInfo bic2(BLT_KEYBLACKEN);
	bic2.alpha=100;
	CImageBlender::Blt(bg,&mImgBG,&BLT_INFO_KEY,WND_RECT,0,0);
	if(mPosition<=4){
		int x=33,y=80+67*mPosition,w=195,h=27;
		CImageBlender::Blt(bg,&mImgSelected,&BLT_INFO_KEY,WND_RECT,x,y,x,y,w,h);
	}else{
		int x=203,y=416,w=243,h=46;
		CImageBlender::Blt(bg,&mImgSelected,&BLT_INFO_KEY,WND_RECT,x,y,x,y,w,h);
	}
	{//Formation
		int w=39;
		int h=33;
		int x=54+mForm*w;
		int y=110;
		CImageBlender::Blt(bg,&mImgSelected,&BLT_INFO_KEY,WND_RECT,x,y,x,y,w,h);
	}
	{//MainWepon
		int w=29;
		int h=24;
		int x=54+mMainWepon*w;
		int y=179;
		CImageBlender::Blt(bg,&mImgSelected,&BLT_INFO_KEY,WND_RECT,x,y,x,y,w,h);
	}
	{//SubWepon
		int w=29;
		int h=24;
		int x=54+mSubWepon*w;
		int y=245;
		CImageBlender::Blt(bg,&mImgSelected,&BLT_INFO_KEY,WND_RECT,x,y,x,y,w,h);
	}
	{//UniqueWepon
		int w=29;
		int h=24;
		int x=54+mBomb*w;
		int y=311;
		CImageBlender::Blt(bg,&mImgSelected,&BLT_INFO_KEY,WND_RECT,x,y,x,y,w,h);
	}
	{//LEVEL
		int x,y=379,w,h=31;
		if(mLevel==0){x=51; w=62;}
		if(mLevel==1){x=140; w=90;}
		if(mLevel==2){x=257; w=66;}
		if(mLevel==3){x=350; w=94;}
		if(mLevel==4){x=465; w=124;}
		CImageBlender::Blt(bg,&mImgSelected,&BLT_INFO_KEY,WND_RECT,x,y,x,y,w,h);
	}
	int ml=367,mt=83,w=185,h=mImgFigFormation.Height();
	if(mPosition==0){
		CImageBlender::Blt(bg,&mImgFigFormation,&BLT_INFO_KEY,WND_RECT,ml,mt,w*mForm,0,w,h);
	}else if(mPosition==1){
		CImageBlender::Blt(bg,&mImgFigMainWepon,&BLT_INFO_KEY,WND_RECT,ml,mt,w*mMainWepon,0,w,h);
	}else if(mPosition==2){
		CImageBlender::Blt(bg,&mImgFigSubWeapon1,&BLT_INFO_KEY,WND_RECT,ml,mt,w*mSubWepon,0,w,h);
	}else if(mPosition==3){
		CImageBlender::Blt(bg,&mImgFigSubWeapon2,&BLT_INFO_KEY,WND_RECT,ml,mt,w*mBomb,0,w,h);
	}else{
		CImageBlender::Blt(bg,&mImgExpLevel,&BLT_INFO_KEY,WND_RECT,327,75,263*mLevel,0,263,255);
	}
	if(mPosition==0){
		mWeaponTextView->SetText(mStrFormation[mForm]);
	}else if(mPosition==1){
		mWeaponTextView->SetText(mStrMainWeapon[mMainWepon]);
	}else if(mPosition==2){
		mWeaponTextView->SetText(mStrSubWeapon1[mSubWepon]);
	}else if(mPosition==3){
		mWeaponTextView->SetText(mStrSubWeapon2[mBomb]);
	}else{
		mWeaponTextView->SetText(mStrLevel[mLevel]);
	}
	mWeaponTextView->OnTimer();

	if(mMaxWeapon1Id==2){
		CLine::drawLine(bg,117,264,135,246,0xDD0000);
		CLine::drawLine(bg,116,264,134,246,0xDD0000);
	}
	if(mMaxWeapon2Id==2){
		CLine::drawLine(bg,117,264+66,135,246+66,0xDD0000);
		CLine::drawLine(bg,116,264+66,134,246+66,0xDD0000);
	}
	return 0;
}

void CSelectViewController::onKeyDownZ(){
	if(m_timer<4)return;
	mGameInfo->SetForm(mForm);
	mGameInfo->SetMainWepon(mMainWepon);
	mGameInfo->SetSubWepon(mSubWepon);
	mGameInfo->SetUniqueWepon(mBomb);
	mGameInfo->SetLevel(mLevel);

	if(mPosition>=5){
		mSE->PlaySingleSound(SE_KEY2);
		mStartFlg=true;
	}else{
		mSE->PlaySingleSound(SE_KEY1);
		mPosition++;
	}
}

char CSelectViewController::mStrFormation[2][128]={
	"【旋回オプション】\n自機周辺をオプションが回転。",
	"【相対位置固定オプション】\n自機との位置関係を保って\nオプションが移動。"
};
char CSelectViewController::mStrMainWeapon[2][128]={
	"【前方射撃用機関砲】\n自機前方に狙いを絞った\nシンプルで攻撃力の高い武器。",
	"【広範囲射撃用機関砲】\n前方・斜め上下方向への攻撃を\n同時に行う武器。"
};
char CSelectViewController::mStrSubWeapon1[3][128]={
	"【空対地ロケット砲】\n低空や地上の敵を攻撃力の高い\nロケットで攻撃。",
	"【対後方機関砲】\n自機後方に回り込んだ敵機を\n広範囲攻撃で迎撃。",
	"【シールド砲】\n全方向の敵機を迎撃。\n威力と射程距離は小さい。"
};
char CSelectViewController::mStrSubWeapon2[3][128]={
	"【無し】\n第三の武器など不要！\nシンプルな操作性。",
	"【レーザー集光機】\n至近距離の敵機をレーザーで焼却。",
	"【貫通弾】\n敵機を貫通する武器。\n連射力は無いが高い攻撃力。",
};
char CSelectViewController::mStrLevel[5][128]={
	"※全6ステージ。","※全6ステージ。","※全7ステージ。","※全7ステージ。","※全7ステージ。\n　コンテニュー不可。",
};

void CSelectViewController::LoadClearInfo(){
	if(!csv_exist(CLEAR_FILE_NAME)) csv_fprintf(CLEAR_FILE_NAME,"0,0,0,0,0");
	int cleared[5];
	csv_fread_once(CLEAR_FILE_NAME,"%d,%d,%d,%d,%d",&cleared[0],&cleared[1],&cleared[2],&cleared[3],&cleared[4]);
	for(int i=0;i<5;i++){ mClearedFlg[i]=(cleared[i]==1); }
}