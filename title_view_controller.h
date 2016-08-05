
double func(int i){
	return fabs((720.0-i)/720.0*(cos(N_PI*i)+sin(N_PI*i/2)))+0.01;
}

class CTitleViewController:public CViewController{
private:
	CImage32 m_image_bg;
	CImage32 m_button_1p;
	CImage32 m_button_2p;
	CImage32 m_button_config;
	CImage32 m_button_quit;
	CImage32 mImgCursor;
	CGameInfo *mGameInfo;
	CTextView* mTextViewDlgTitle;
	CTextView* mTextViewDlgChoice;
	CTextView* mTextViewDlgTitle2;
	CTextView* mTextViewDlgChoice2;
	CTextView* mTextViewDlgNum;
	int m_position;
	int m_nextPage;
	bool mDlgFlg, mConfigDlgFlg;
	bool mSelectStoryModeFlg;
	int mKeyShot,mKeyBomb,mKeyChange,mKeyPause;
	int mPosDlg, mPosDlg2;
	bool mDlgInitFlg;
public:
	CTitleViewController():CViewController(){
		m_position=0;
		m_nextPage=0;
		mPosDlg = mPosDlg2 =0;
		mDlgInitFlg=false;
		mDlgFlg = mConfigDlgFlg = mSelectStoryModeFlg = false;
		m_image_bg.load("dat/img/title.bmp");
		mImgCursor.load("dat/img/csl.bmp");
		mGameInfo=CGameInfo::GetInstance();


		RECT rc={320,170,350+300,170+60};
		mTextViewDlgTitle=new CTextView(bg->hDC(),rc,50,0x88FFFF,"-Level Select-");
		mTextViewDlgChoice=new CTextView[5];
		for(int i=0;i<5;i++){
			static char str[5][16]={"Easy","Normal","Hard","Morbid","Suicidal"};
			RECT rc={350,260+50*i,350+300,260+50*i+50};
			mTextViewDlgChoice[i].InitTextView(bg->hDC(),rc,40,0xFFFFFF,str[i]);
		}


		RECT rc2 = { 320,260+50*5, 350 + 300,260 + 50 * 6 };
		mTextViewDlgTitle2 = new CTextView(bg->hDC(), rc2, 50, 0x88FFFF, "-Story Mode-");
		mTextViewDlgChoice2 = new CTextView[2];
		for (int i = 0; i<2; i++) {
			static char str[2][16] = { "OFF","ON"};
			RECT rc = { 350,510 + 50 * i,350 + 300,510 + 50 * i + 50 };
			mTextViewDlgChoice2[i].InitTextView(bg->hDC(), rc, 40, 0xFFFFFF, str[i]);
		}


		mTextViewDlgNum=new CTextView[4];
		for(int i=0;i<4;i++){
			RECT rc={550,260+55*i,550+100,260+55*i+50};
			mTextViewDlgNum[i].InitTextView(bg->hDC(),rc,50,0xFF99FF,"00");
		}

		mPad->LoadConfig();
		mPad->GetKeyConfig(mKeyShot,mKeyBomb,mKeyChange,mKeyPause);
	}
	~CTitleViewController(){}
	int onTimer();
	void onKeyDownZ();
	void onKeyUpZ(){}
	void onKeyDownX();
	void onKeyDownDown();
	void onKeyDownUp();
	void setDlgTextColor();
	int CheckKey(int pos,int def);
};

void CTitleViewController::setDlgTextColor(){
	for (int i = 0; i<5; i++) {
		if (i == mPosDlg) {
			mTextViewDlgChoice[i].SetColor(0xCCFFFF);
			mTextViewDlgChoice[i].SetItaric(false);
		}
		else {
			mTextViewDlgChoice[i].SetColor(0x885555);
			mTextViewDlgChoice[i].SetItaric(true);
		}
	}
	for (int i = 0; i<2; i++) {
		if (i == mPosDlg2 && mSelectStoryModeFlg) {
			mTextViewDlgChoice2[i].SetColor(0xCCFFFF);
			mTextViewDlgChoice2[i].SetItaric(false);
		}
		else {
			mTextViewDlgChoice2[i].SetColor(0x885555);
			mTextViewDlgChoice2[i].SetItaric(true);
		}
	}
}

void CTitleViewController::onKeyDownX(){
	if (mDlgFlg) {
		mDlgFlg = false;
		mSelectStoryModeFlg = false;
	}
	else if (mSelectStoryModeFlg) {
		mDlgFlg = true;
		mSelectStoryModeFlg = false;
	}
	mDlgInitFlg=false;
}

void CTitleViewController::onKeyDownZ(){
	if(m_timer<20)return;// 前ページのボタン押下が残っているので回避

	if(mDlgFlg){
		if (!mSelectStoryModeFlg) {
			mSelectStoryModeFlg = true;
			mGameInfo->SetLevel(mPosDlg);
		} else {
			mSelectStoryModeFlg = false;
			mDlgFlg = false;
			mDlgInitFlg = false;
			m_nextPage = ENDURANCE_VIEW_CONTROLLER;    //////////////
			mGameInfo->SetStoryMode(mPosDlg2);
			mPosDlg = 0;
			mPosDlg2 = 0;
		}
		
		mSE->PlaySingleSound(SE_KEY2);
		return;
	} else if(mConfigDlgFlg){
		if(mPosDlg==4){
			mSE->PlaySingleSound(SE_KEY2);
			mPad->SaveConfig();
			mConfigDlgFlg=false;
			mDlgInitFlg=false;
			mPosDlg = 0;
		}
		return;
	}

	if(m_position==0){
		mDlgFlg=true;
		mPosDlg=0;
		mPosDlg2 = 0;
	}else if(m_position==1){
		mConfigDlgFlg=true;
		mPosDlg=0;
		//m_nextPage=CONFIG_VIEW_CONTROLLER;
	}else if(m_position==2)m_nextPage=REPLAY_VIEW_CONTROLLER;//REPLAY_VIEW_CONTROLLER;
	else if(m_position==3)PostQuitMessage(0);
	if(m_position!=3)mSE->PlaySingleSound(SE_KEY2);
	
}
void CTitleViewController::onKeyDownDown(){
	//CImage32 test("dat/img/e-da-bullets60.bmp");
	//test.save("ttetetet.bmp");
	mSE->PlaySingleSound(SE_KEY1);
	if(mDlgFlg){
		if (!mSelectStoryModeFlg) {
			mPosDlg++;
			if (mPosDlg>4)mPosDlg = 4;
		}
		else {
			mPosDlg2++;
			if (mPosDlg2>1)mPosDlg2 = 1;
		}
		setDlgTextColor();
	}
	else if(mConfigDlgFlg){
		mPosDlg++;
		if(mPosDlg>4)mPosDlg=4;
		setDlgTextColor();
	} else {
		m_position++;
		if(m_position>3)m_position=3;
		setDlgTextColor();
	}
}
void CTitleViewController::onKeyDownUp(){
	mSE->PlaySingleSound(SE_KEY1);
	if (mDlgFlg || mConfigDlgFlg) {
		if (!mSelectStoryModeFlg) mPosDlg--;
		else mPosDlg2--;

		if (mPosDlg<0)mPosDlg = 0;
		if (mPosDlg2<0)mPosDlg2 = 0;
		setDlgTextColor();
	}else{
		m_position--;
		if(m_position<0)m_position=0;
		setDlgTextColor();
	}
}
int CTitleViewController::onTimer(){
	onTimerSuper();
	
	if(m_nextPage==ENDURANCE_VIEW_CONTROLLER){
		mDlgFlg = mSelectStoryModeFlg = false;
		////////////mGameInfo->Continued(); return ENDING_VIEW_CONTROLLER; ///////
		return ENDURANCE_VIEW_CONTROLLER;
	}
	else if(m_nextPage==CONFIG_VIEW_CONTROLLER){mConfigDlgFlg=false; return CONFIG_VIEW_CONTROLLER;}
	else if(m_nextPage==REPLAY_VIEW_CONTROLLER)return REPLAY_VIEW_CONTROLLER;
	else if(m_nextPage==NAME_ENTRY_VIEW_CONTROLLER)return NAME_ENTRY_VIEW_CONTROLLER;

	if(mDlgFlg==true){
		CBltInfo bi_blacken(BLT_BLACKEN,100);
		CImageBlender::Blt(bg,&m_image_bg,&bi_blacken,WND_RECT,0,0);
		CShapeBlender::fillRect(bg,334,440,633,719,0x000000);
		int dlg_margin = 110;
		int margin = 10;
		int line_height_h = 50;
		int line_height_li = 40;
		showDialog(dlg_margin);
		if(mDlgInitFlg==false){
			RECT rc = { 320,dlg_margin + margin,350 + 300,dlg_margin + margin + line_height_h };
			mTextViewDlgTitle->SetRect(rc);
			mTextViewDlgTitle->SetText("-Level Select-");
			for(int i=0;i<5;i++){
				static char str[5][16]={"Easy","Normal","Hard","Morbid","Suicidal"};
				RECT rc={350,190+50*i,350+300,190+50*i+50};
				mTextViewDlgChoice[i].InitTextView(bg->hDC(),rc,50,0xFFFFFF,str[i]);
			}

			RECT rc2 = { 320,440,350 + 300,440 + 50 };
			mTextViewDlgTitle2->SetRect(rc2);
			mTextViewDlgTitle2->SetText("-Story Mode-");
			for (int i = 0; i<2; i++) {
				static char str[2][16] = { "OFF","ON" };
				RECT rc = { 350,510 + 50 * i,350 + 300,510 + 50 * i + 50 };
				mTextViewDlgChoice2[i].InitTextView(bg->hDC(), rc, 40, 0xFFFFFF, str[i]);
			}

			setDlgTextColor();
			for (int i = 0; i<5; i++)mTextViewDlgChoice[i].OnTimer();
			for (int i = 0; i<2; i++)mTextViewDlgChoice2[i].OnTimer();
			mTextViewDlgTitle->OnTimer();
			mTextViewDlgTitle2->OnTimer();
			//mDlgInitFlg=true;
		}
		return 0;
	} else if (mConfigDlgFlg) {	
		CBltInfo bi_blacken(BLT_BLACKEN,100);
		CImageBlender::Blt(bg,&m_image_bg,&bi_blacken,WND_RECT,0,0);
		CShapeBlender::fillRect(bg,334,440,633,719,0x000000);
		showDialog();
		mTextViewDlgTitle->OnTimer();

		if(mPosDlg==0){mKeyShot=CheckKey(mPosDlg, mKeyShot);}
		else if(mPosDlg==1)mKeyBomb=CheckKey(mPosDlg,mKeyBomb);
		else if(mPosDlg==2)mKeyChange=CheckKey(mPosDlg,mKeyChange);
		else if(mPosDlg==3)mKeyPause=CheckKey(mPosDlg,mKeyPause);
		if(mDlgInitFlg==false){
			mTextViewDlgTitle->SetText("-Key Config-");
			RECT rc = { 320,170,350 + 300,170 + 60 };
			mTextViewDlgTitle->SetRect(rc);
			for(int i=0;i<5;i++){
				static char str[5][16]={"Shot","Bomb","Weapon","Pause","Exit"};
				RECT rc={350,260+55*i,350+300,260+55*i+50};
				mTextViewDlgChoice[i].InitTextView(bg->hDC(),rc,50,0xFFFFFF,str[i]);
			}
			char str[8];
			sprintf_s(str,8,"%02d",mKeyShot);
			mTextViewDlgNum[0].SetText(str);

			sprintf_s(str,8,"%02d",mKeyBomb);
			mTextViewDlgNum[1].SetText(str);

			sprintf_s(str,8,"%02d",mKeyChange);
			mTextViewDlgNum[2].SetText(str);

			sprintf_s(str,8,"%02d",mKeyPause);
			mTextViewDlgNum[3].SetText(str);
			
			for(int i=0;i<4;i++){
				mTextViewDlgNum[i].OnTimer();
			}
			setDlgTextColor();
			for(int i=0;i<5;i++)mTextViewDlgChoice[i].OnTimer();
			//mDlgInitFlg=true;
		}
		return 0;
	}
	
	CImageBlender::Blt(bg,&m_image_bg,0,0);
	CBltInfo bi(BLT_MEMCOPY);
	//bi.zoom_y=1.2;
	//CImageBlenderStretch::BltCurved(bg,&m_image_bg,&bi,WND_RECT,func,480,0,0,0,960,720);
	//CImageBlender::Blt(bg,&m_image_bg,0,0);
	CImageBlender::Blt(bg,&mImgCursor,&BLT_INFO_ADD,BATTLE_RECT,310,440+m_position*70);

	return 0;
}


int CTitleViewController::CheckKey(int pos,int def){
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