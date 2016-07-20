#include "chat.h"

const int MAX_CHAT[7] = { 1, 1, 1, 1, 1, 1, 1 };

class CEnduranceViewController :public CViewController {
private:
	CChat mChat;
	int _mChatCount;
	CImage32 mImgPause, mImgPauseYes, mImgPauseNo;
	CImage32 mImgContinue, mImgContinueYes, mImgContinueNo;
	CImage32 mImgPauseBG;
	CImage32 mImgClear;
	CBackgroundManager** mBackgroundManager;
	CEffectManager* mEffectManager;
	CEffectManager* mFrontEffectManager;
	CEffectManager* mBackEffectManager;
	CDebrisManager* mDebrisManager;
	CBulletManager* mBulletManager;
	CBombManager* mBombManager;
	CEnemyManager* mEnemyManager;
	CEnemyManager* mEnemyManagerBack;

	CItemManager* mItemManager;
	CItemManager* mItemManagerFront;
	
	CEnemyBulletManager* mEBManager;
	CEnemyMissileManager* mEMManager;
	CEnemyLazerManager* mELManager;

	CEnemyGeneratorManager* mGeneratorManager;
	CBossManager* mBossManager;
	CBattleFrame* mBattleFrame;
	CLandscapeManager* mLandscapeManager;
	CLandscapeManager* mLandscapeManagerBack;
	CLandscapeManager* mLandscapeManagerFront;
	CStageManager* mStageManager;
	CPlayer* mPlayer;
	CScore* mScore;
	CImageNumber* mImageNumber16_22;

	CGameInfo* mGameInfo;
	int mPauseTimer,mTotalizeTimer,mStageTimer;;
	bool mOnRightFlg, mOnLeftFlg, mOnUpFlg, mOnDownFlg;
	bool mContinueViewFlg, mPauseViewFlg, mPauseYesNoFlg,mTotalizeFlg;

	CTextView* mTextViewItems;
	CTextView* mTextViewTension;
	CTextView* mTextViewGameLevel;

	CTextView* mTextViewContinueLeft;
	CTextView* mTextViewContinueAdvice;
	static const int MAX_ADVICE = 5;
	static const char STR_ADVICE[MAX_ADVICE][256];
	int _mCurrentAdvice;

public:
	CEnduranceViewController():CViewController(),mOnRightFlg(false),mOnLeftFlg(false),mOnUpFlg(false),mOnDownFlg(false),mTotalizeFlg(false),
		mContinueViewFlg(false), mPauseViewFlg(false),mPauseYesNoFlg(true),mPauseTimer(0),mTotalizeTimer(0),mStageTimer(0){
		mPlayer=CPlayer::GetInstance();
		mEffectManager=CEffectManager::GetInstance();
		mFrontEffectManager=CEffectManager::GetInstance2();
		mBackEffectManager=CEffectManager::GetInstance3();
		mDebrisManager=CDebrisManager::GetInstance();
		mBulletManager=CBulletManager::GetInstance();
		mBombManager=CBombManager::GetInstance();
		mEnemyManager=CEnemyManager::GetInstance();
		mEnemyManagerBack=CEnemyManager::GetInstance2();
		mItemManager=CItemManager::GetInstance();
		mItemManagerFront=CItemManager::GetInstanceFront();
		mEBManager=CEnemyBulletManager::GetInstance();
		mEMManager=CEnemyMissileManager::GetInstance();
		mELManager=CEnemyLazerManager::GetInstance();
		mBattleFrame=CBattleFrame::GetInstance();
		mLandscapeManager=CLandscapeManager::GetInstance();
		mLandscapeManagerBack=CLandscapeManager::GetInstance2();
		mLandscapeManagerFront=CLandscapeManager::GetInstance3();
		mGeneratorManager=CEnemyGeneratorManager::GetInstance();
		mBossManager=CBossManager::GetInstance();
		mStageManager=new CStageManager[MAX_STAGES];
		mStageManager[0].ReadStage("dat/stage/st1.txt");
		mStageManager[1].ReadStage("dat/stage/st2.txt");
		mStageManager[2].ReadStage("dat/stage/st3.txt");
		mStageManager[3].ReadStage("dat/stage/st4.txt");
		mStageManager[4].ReadStage("dat/stage/st5.txt");
		mStageManager[5].ReadStage("dat/stage/st6.txt");
		mStageManager[6].ReadStage("dat/stage/st7.txt");
		mBackgroundManager=new CBackgroundManager*[MAX_STAGES];
		mBackgroundManager[0]=CStage1BackgroundManager::GetInstance();
		mBackgroundManager[1]=CStage2BackgroundManager::GetInstance();

		mBackgroundManager[2]=CStage3BackgroundManager::GetInstance();
		mBackgroundManager[3]=CStage4BackgroundManager::GetInstance();
		mBackgroundManager[4]=CStage5BackgroundManager::GetInstance();
		mBackgroundManager[5]=CStage6BackgroundManager::GetInstance();
		mBackgroundManager[6]=CStage7BackgroundManager::GetInstance();
		
		mScore=CScore::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		mImgPauseBG.Resize(960,720);
		CImageFactory::InitBitmap(&mImgContinue,"dat/img/continue-logo.bmp");
		CImageFactory::InitBitmap(&mImgContinueYes,"dat/img/continue-yes.bmp");
		CImageFactory::InitBitmap(&mImgContinueNo,"dat/img/continue-no.bmp");
		CImageFactory::InitBitmap(&mImgPause,"dat/img/pause-logo.bmp");
		CImageFactory::InitBitmap(&mImgPauseYes,"dat/img/pause-yes.bmp");
		CImageFactory::InitBitmap(&mImgPauseNo,"dat/img/pause-no.bmp");
		CImageFactory::InitBitmap(&mImgClear,"dat/img/clear-fig.bmp");
		mImageNumber16_22=new CImageNumber("dat/img/figur16_22.bmp");

		RECT rcItemCount={830,30,940,60};
		mTextViewItems=new CTextView(bg->hDC(),rcItemCount,20,0xFFFFFF,"111111");
		RECT rcTension={850,65,960,95};
		mTextViewTension=new CTextView(bg->hDC(),rcTension,20,0xFFFFFF,"111111");
		RECT rcLevel={850,100,940,130};
		mTextViewGameLevel=new CTextView(bg->hDC(),rcLevel,20,0xFFFFFF,"111111");

		RECT rcContinueLeft = {335,275,375+ 400,275+50};
		mTextViewContinueLeft=new CTextView(bg->hDC(), rcContinueLeft, 36, 0xFFFFFF, "111111");
		
		RECT rcContinueAdvice = { 275,615,700,725 };
		mTextViewContinueAdvice = new CTextView(bg->hDC(), rcContinueAdvice, 20, 0xFFFFFF, "111111");

		_mCurrentAdvice=rand()% MAX_ADVICE;
	}
	~CEnduranceViewController(){
		delete[] mStageManager;
		delete[] mBackgroundManager;
	}
	int onTimer();
	void onTimerPause();
	void onTimerContinue();
	void onTimerTotalize();
	void onTimerChat();
	void onKeyDownZ();
	void onKeyDownX();
	void onKeyUpZ(){mPlayer->OnUpZ();}
	void onKeyDownC();
	void onKeyDownDown();
	void onKeyDownUp();
	void onKeyDownLeft(){mOnLeftFlg=true;}
	void onKeyDownRight(){mOnRightFlg=true;}

	void onKeyUpDown(){mOnDownFlg=false;}
	void onKeyUpUp(){mOnUpFlg=false;}
	void onKeyUpLeft(){mOnLeftFlg=false;}
	void onKeyUpRight(){mOnRightFlg=false;}
	void onKeyDownEsc(){mPauseViewFlg=true;}

	void Reset();
	void display();
};
void CEnduranceViewController::onKeyDownDown(){
	mOnDownFlg=true;
	if(mPauseViewFlg || mContinueViewFlg){
		mPauseYesNoFlg=!mPauseYesNoFlg;
		mSE->PlaySingleSound(SE_KEY1);
	}
}
void CEnduranceViewController::onKeyDownUp(){
	mOnUpFlg=true;
	if(mPauseViewFlg || mContinueViewFlg){
		mPauseYesNoFlg=!mPauseYesNoFlg;
		mSE->PlaySingleSound(SE_KEY1);
	}
}
void CEnduranceViewController::onKeyDownZ(){
	if (mGameInfo->isOnChat()) {
		_mChatCount++;
	}
	if(mPauseViewFlg){
		if(mPauseTimer<20)return;
		mPauseTimer=0;
		if(mPauseYesNoFlg){
			mPauseViewFlg=false;
			CMusic::Restart();
		}else{
			CMusic::Stop();
			mSE->PlaySingleSound(SE_KEY2);
			mNextPage=TITLE_VIEW_CONTROLLER;
		}
	}else if(mContinueViewFlg){
		if(mPauseTimer<20)return;
		mPauseTimer=0;
		if(mPauseYesNoFlg){
			mPauseViewFlg=false;
			CMusic::Restart();
			mPlayer->Reset();
			mPlayer->ContinuePlyer();
			mContinueViewFlg=false;
			mScore->Reset();
			mGameInfo->Continued();
		}else{
			CMusic::Stop();
			mPlayer->Reset();
			mSE->PlaySingleSound(SE_KEY2);
			mNextPage=TITLE_VIEW_CONTROLLER;
		}
	}else {
		mPlayer->OnZ();
	}
}
void CEnduranceViewController::onKeyDownC(){
	if(mPauseViewFlg || mContinueViewFlg)return;
	mPlayer->OnC();
}
void CEnduranceViewController::onKeyDownX(){
	if(mPauseViewFlg || mContinueViewFlg)return;
	mPlayer->OnX();
}
int CEnduranceViewController::onTimer(){
	if(mNextPage!=0)return mNextPage;
	onTimerSuper();
	mStageTimer++;
	if(m_timer==1){
		Reset();
		CMusic::Play();
	}
	if (mGameInfo->isOnChat()) {
		onTimerChat();
		return 0;
	}else if(mContinueViewFlg){
		onTimerContinue();
		return 0;
	}else if(mPauseViewFlg){
		onTimerPause();
		return 0;
	}
	
	mBackgroundManager[mGameInfo->GetStage()]->Update();
	mLandscapeManagerBack->Update<CLandscape>();
	mBackEffectManager->Update<CEffect>();
	mLandscapeManager->Update<CLandscape>();
	mStageManager[mGameInfo->GetStage()].Update();

	mItemManager->Update<CItem>();
	mGeneratorManager->Update<CEnemyGenerator>();
	
	mGameInfo->SetEnemyStopFlg(false);
	mEnemyManagerBack->Update<CEnemy>();
	mBossManager->Update<CBoss>();
	mEnemyManager->Update<CEnemy>();
	mItemManagerFront->Update<CItem>();
	mLandscapeManagerFront->Update<CLandscape>();
	mEffectManager->Update<CEffect>();
	mDebrisManager->Update<CDebris>();
	mEMManager->Update<CEnemyMissile>();
	mEBManager->Update<CEnemyBullet>();
	mELManager->Update<CLazerBullet>();
	mBulletManager->Update<CBullet>();
	mBombManager->Update<CBomb>();

	if(mTotalizeTimer>0){
		int alpha=mTotalizeTimer*3;
		if(alpha>255)alpha=255;
		CImageFilter::addBrightness(bg,-alpha);
	}
	if(mStageTimer<30){
		int alpha=255-mStageTimer*10;
		if(alpha<0)alpha=0;
		CImageFilter::addBrightness(bg,-alpha);
	}
	mPlayer->Update();
	mFrontEffectManager->Update<CEffect>();
	mBattleFrame->Update();

	if(mBossManager->isStageEnd())mTotalizeFlg=true;
	if(mTotalizeFlg)onTimerTotalize();

	if(mOnRightFlg){mPlayer->Right();}
	if(mOnLeftFlg){mPlayer->Left();}
	if(mOnUpFlg && !mOnDownFlg){mPlayer->Up();}
	if(mOnDownFlg && !mOnUpFlg){mPlayer->Down();}
	if(mPlayer->GetLife()<0 && mPlayer->GetKilledCounter()<5)mContinueViewFlg=true;

	testa = mGameInfo->getInnerRank();
	char str[64];
	wsprintf(str,"X=%d Y=%d",testa,test_fo);
	TextOut(bg->hDC(),10,10,str,lstrlen(str));
	

	char strItems[32];
	wsprintf(strItems,"%d",mScore->GetItems());
	mTextViewItems->SetText(strItems);
	mTextViewItems->OnTimer();
	
	char strHaste[32];
	wsprintf(strHaste,"%d",mScore->GetHaste());
	mTextViewTension->SetText(strHaste);
	mTextViewTension->OnTimer();

	char strLevel[4];
	wsprintf(strLevel,"%d",mGameInfo->GetLevel()+1);
	mTextViewGameLevel->SetText(strLevel);
	mTextViewGameLevel->OnTimer();
	return 0;
}

void CEnduranceViewController::onTimerPause(){
	mPauseTimer++;
	CBltInfo bi_mul(BLT_MUL);
	CBltInfo bi(BLT_MEMCOPY);
	CBltInfo bi_key(BLT_KEY);
	CBltInfo bi_alpha(BLT_ALPHA2);
	CMusic::Stop();
	showDialog();
	if(mPauseTimer==1){
		//CImageBlender::Blt(bg,&mImgPause,&bi_mul,BATTLE_RECT,338,228);
		CImageBlender::Blt(&mImgPauseBG,bg,&bi,BATTLE_RECT,0,0);
		CImageFilter::operateShift(&mImgPauseBG,1,1,0);
	}else{
		CImageBlender::Blt(bg,&mImgPauseBG,&bi,BATTLE_RECT,0,0);
		CImageBlender::Blt(bg,&mImgPause,&bi_key,BATTLE_RECT,338,228);
		if(mPauseYesNoFlg){
			CImageBlender::Blt(bg,&mImgPauseYes,&bi_key,BATTLE_RECT,  348,357);
			CImageBlender::Blt(bg,&mImgPauseNo,&bi_alpha,BATTLE_RECT,342,453);
		}else{
			CImageBlender::Blt(bg,&mImgPauseYes,&bi_alpha,BATTLE_RECT,348,357);
			CImageBlender::Blt(bg,&mImgPauseNo,&bi_key,BATTLE_RECT,  342,453);
		}
	}
}

void CEnduranceViewController::onTimerChat() {
	mChat.showChat(bg, mGameInfo->GetStage(), _mChatCount);
}

void CEnduranceViewController::onTimerContinue(){
	mPauseTimer++;
	CBltInfo bi_mul(BLT_MUL);
	CBltInfo bi(BLT_MEMCOPY);
	CBltInfo bi_key(BLT_KEY);
	CBltInfo bi_alpha(BLT_ALPHA2);
	CMusic::Stop();
	showDialog();
	if(mGameInfo->LeftContinues()<=0){
		mPauseYesNoFlg=false;
	}
	if(mPauseTimer==1){
		_mCurrentAdvice = rand() % MAX_ADVICE;
		CImageBlender::Blt(&mImgPauseBG,bg,&bi,BATTLE_RECT,0,0);
		CImageFilter::operateShift(&mImgPauseBG,1,1,0);//青色を足す
	}else{
		CImageBlender::Blt(bg,&mImgPauseBG,&bi,BATTLE_RECT,0,0);
		CImageBlender::Blt(bg,&mImgContinue,&bi_key,BATTLE_RECT,338,228-40);
		char strContinueNum[32];
		sprintf_s(strContinueNum, 32, "Left %d Continues.", mGameInfo->LeftContinues());
		mTextViewContinueLeft->SetText(strContinueNum);
		mTextViewContinueLeft->OnTimer();

		RECT rcAdv = { BATTLE_MIDDLE_X - 230,BATTLE_MIDDLE_Y + 230,BATTLE_MIDDLE_X + 230,BATTLE_BOTTOM - 30 };
		showDialog(rcAdv);
		mTextViewContinueAdvice->SetText(STR_ADVICE[_mCurrentAdvice]);
		mTextViewContinueAdvice->OnTimer();
		if(mPauseYesNoFlg){
			CImageBlender::Blt(bg,&mImgContinueYes,&bi_key,BATTLE_RECT  ,368,357);
			CImageBlender::Blt(bg,&mImgContinueNo,&bi_alpha,BATTLE_RECT,362,453);
		}else{
			CImageBlender::Blt(bg,&mImgContinueYes,&bi_alpha,BATTLE_RECT,368,357);
			CImageBlender::Blt(bg,&mImgContinueNo,&bi_key,BATTLE_RECT  ,362,453);
		}
	}
}

void CEnduranceViewController::onTimerTotalize(){
	mTotalizeTimer++;
	CImageBlender::Blt(bg,&mImgClear,&BLT_INFO_KEY,BATTLE_RECT,(BATTLE_RECT.right+BATTLE_RECT.left)/2-mImgClear.Width()/2,158);
	if(mTotalizeTimer>1){ 
		CMusic::Stop(); 
	}
	if(mTotalizeTimer>100){
		mTotalizeTimer=0;
		mStageTimer=0;
		mTotalizeFlg=false;
		int MAX_STAGES[5]={6,6,7,7,7};
		int max_stage=(mGameInfo->isTrial())?MAX_STAGE_TRIAL:MAX_STAGES[mGameInfo->GetLevel()];
		if(mGameInfo->GetStage()>=max_stage-1){
			if(mGameInfo->isTrial())mNextPage=NAME_ENTRY_VIEW_CONTROLLER;
			else if(mGameInfo->didContinue()==false)mNextPage=ENDING_VIEW_CONTROLLER;
			else mNextPage=NAME_ENTRY_VIEW_CONTROLLER;
		}else{
			mEBManager->Reset();
			mLandscapeManager->Reset();
			mLandscapeManagerBack->Reset();
			mLandscapeManagerFront->Reset();
			char fname[256];
			sprintf_s(fname,256,"dat/BGM/stage%d.ogg",mGameInfo->GetStage()+2);
			CMusic::initMusic(fname);
			CMusic::Play();
			mGameInfo->GoToNextStage();
		}
	}
}

void CEnduranceViewController::Reset(){
	mEffectManager->Reset();
	mBackEffectManager->Reset();
	mFrontEffectManager->Reset();
	mBulletManager->Reset();
	mBombManager->Reset();
	mBossManager->Reset();
	mEnemyManager->Reset();
	mEnemyManagerBack->Reset();
	mItemManager->Reset();
	mItemManagerFront->Reset();
	mEBManager->Reset();
	mEMManager->Reset();
	mDebrisManager->Reset();
	mLandscapeManager->Reset();
	mLandscapeManagerBack->Reset();
	mLandscapeManagerFront->Reset();
	mGeneratorManager->Reset();

	//mBackgroundManager[0]->Reset();
	//mStageManager[0].Reset();
	for(int i=0;i<MAX_STAGES;i++){
		mBackgroundManager[i]->Reset();
		mStageManager[i].Reset();
	}

	mPlayer->Reset();
	mScore->Reset();
	mGameInfo->Reset();
	mELManager->Reset();

	char fname[256];
	sprintf_s(fname,256,"dat/BGM/stage%d.ogg",mGameInfo->GetStage()+1);
	CMusic::initMusic(fname);
	mStageTimer=0;
	_mChatCount = 0;
}

void CEnduranceViewController::display(){
	if(mGameInfo->GetQuake()<1.0){
		mGameInfo->SetQuake(0);
		bg->Display(0,0,0,0,WND_RECT.right,WND_RECT.bottom);
	}else{
		int deltaX=rand()%((int)mGameInfo->GetQuake())-(int)(mGameInfo->GetQuake()/2);
		int deltaY=rand()%((int)mGameInfo->GetQuake())-(int)(mGameInfo->GetQuake()/2);
		bg->Display(200+deltaX,deltaY,200,0,WND_RECT.right-400,WND_RECT.bottom);
		mGameInfo->DampQuake();

		bg->Display(0,0,0,0,200,WND_RECT.bottom);
		bg->Display(WND_RECT.right-200,0,WND_RECT.right-200,0,200,WND_RECT.bottom);
	}
}



const char CEnduranceViewController::STR_ADVICE[MAX_ADVICE][256] = {
	"武器チェンジを使いこなせ！！\n近接レーザーで敵機に突進だ！！",
	"敵の弾丸を見てから避けるのでは遅すぎる！\n生き残るために動き回れ！！",
	"盾や装甲で守られた敵にはレーザーが有効だぞ！！",
	"敵機に衝突してもミスにはならないぞ！！\n接近して殴り合え！！！",
	"敵機を破壊して何度でも１UP出来るぞ。\n恐れずに突き進むべし！！",
};