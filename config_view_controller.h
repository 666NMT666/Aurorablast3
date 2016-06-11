class CConfigViewController:public CViewController{
protected:
	int mPosition;
	CImage32 m_image_bg;
	CImage32 mFigConfig;
	CImage32 mNumConfig;
	bool mBackFlg;
	int mKeyShot,mKeyBomb,mKeyChange,mKeyPause;
public:
	CConfigViewController():CViewController(),mPosition(0),mBackFlg(false){
		CImageFactory::InitBitmap(&m_image_bg,"dat/img/keyconfig-bg.bmp");
		CImageFactory::InitBitmap(&mFigConfig,"dat/img/keyconfig-fig.bmp");
		CImageFactory::InitBitmap(&mNumConfig,"dat/img/keyconfig-number.bmp");
		mPad->GetKeyConfig(mKeyShot,mKeyBomb,mKeyChange,mKeyPause);
	}
	void onKeyDownZ();
	void onKeyDownDown(){
		mPosition++;
		if(mPosition>4)mPosition=4;
		mSE->PlaySingleSound(SE_KEY1);
	}
	void onKeyDownUp(){
		mPosition--;
		if(mPosition<0)mPosition=0;
		mSE->PlaySingleSound(SE_KEY1);
	}
	int onTimer();
	int CheckKey(int pos,int def);
};

int CConfigViewController::onTimer(){
	onTimerSuper();
	if(mBackFlg){
		mPad->SaveConfig();
		return TITLE_VIEW_CONTROLLER;
	}	
	CBltInfo bic(BLT_KEY);
	CBltInfo bic2(BLT_KEYBLACKEN);
	bic2.alpha=100;
	CImageBlender::Blt(bg,&m_image_bg,&BLT_INFO_KEY,WND_RECT,0,0);


	for(int j=0;j<5;j++){
		CBltInfo info=bic2;
		if(mPosition==j)info=bic;
		CImageBlender::Blt(bg,&mFigConfig,&info,WND_RECT,150/2*3,150/2*3+j*mFigConfig.Height()/5,0,j*mFigConfig.Height()/5,mFigConfig.Width(),mFigConfig.Height()/5);
	}
	
	int figLeft=640;
	int figRight=660;
	int figTop=240;
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figRight,figTop,(mKeyShot%10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figLeft,figTop,(mKeyShot/10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figRight,figTop+90,(mKeyBomb%10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figLeft,figTop+90,(mKeyBomb/10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figRight,figTop+90*2,(mKeyChange%10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figLeft,figTop+90*2,(mKeyChange/10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figRight,figTop+90*3,(mKeyPause%10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());
	CImageBlender::Blt(bg,&mNumConfig,&bic,WND_RECT,figLeft,figTop+90*3,(mKeyPause/10)*mNumConfig.Width()/10,0,mNumConfig.Width()/10,mNumConfig.Height());

	if(m_timer<20)return 0;
	if(mPosition==0){mKeyShot=CheckKey(mPosition, mKeyShot);}
	else if(mPosition==1)mKeyBomb=CheckKey(mPosition,mKeyBomb);
	else if(mPosition==2)mKeyChange=CheckKey(mPosition,mKeyChange);
	else if(mPosition==3)mKeyPause=CheckKey(mPosition,mKeyPause);

	return 0;
}


int CConfigViewController::CheckKey(int pos,int def){
	int Pad = GetJoypadInputState( DX_INPUT_PAD1 );
	for( int i=4; i<28; i++ ){      //ボタン28個分ループ
		if( Pad & (1<<i) ){             //ボタンiの入力フラグが立っていたら
			if(pos==0)mPad->SetKeyShot(1<<i);
			if(pos==1)mPad->SetKeyBomb(1<<i);
			if(pos==2)mPad->SetKeyChange(1<<i);
			if(pos==3)mPad->SetKeyEsc(1<<i);
			return i-3;
		}
	}
	return def;
}

void CConfigViewController::onKeyDownZ(){
	if(mPosition==4){
		mBackFlg=true;
		mSE->PlaySingleSound(SE_KEY2);
	}
}