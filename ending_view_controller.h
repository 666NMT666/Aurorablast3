class CEndingViewController:public CViewController{
protected:
	int mWaitTimer;
	static const int FIN_TIME = 2350;
	int mStep;
	int mMaxSteps;
	bool mOnZFlg;
	CImage32* mImgEnding1;
	CTextView* mTextView;
	CGameInfo* mGameInfo;
public:
	CEndingViewController():CViewController(),mWaitTimer(0),mStep(0),mOnZFlg(false){
		mImgEnding1=new CImage32();
		CImageFactory::InitBitmap(mImgEnding1,"dat/img/ending1.bmp");
		mGameInfo=CGameInfo::GetInstance();
		CMusic::Stop();
		CMusic::initMusic("dat/BGM/ed.ogg");
		CMusic::Play();
		RECT rc={100,50,BATTLE_RIGHT-100,BATTLE_BOTTOM-50};
		mTextView=new CTextView(bg->hDC(),rc,20,0xDDDDDD,"");
		//mTextView->SetCenter(true);
		mTextView->SetLineScale(2.0);
		
		/*


		*/
		mTextView->SetText(
			"時は西暦65XX年。\n\
			遥か彼方の惑星より飛来した無数の惑星間弾道ミサイルによって、\n \n \n\
			人類は一瞬にして滅亡した！！\n　\n　\n　\n\
			全生物抹消計画\n\
			\n\
\n\
\n\
\n\
くそっ！奴らめ、地球を丸焦げにして、気が済んだら勝手に死にやがて……\n\
なあに、この程度の大量絶滅、大した事は無い。２億年も待てば、地球はもとの賑やかさを取り戻すだろう。\n\
ふん……気の長い話だ。\n\
そうだな、気長に待とう。人類亡き後、いったいどんな生物が地球を支配するのか、今から楽しみじゃないか。\n\
			Music / Illust/ Program\n\
			NMT\n\n　\n　\
			Special Thanks\n\
			Atsushi\n\
			HRD\n\
			And YOU...\n\n　\n　\
			See You in the Next Disaster.");
		int clearInfo[5]={0,0,0,0,0};
		FILE *fin;
		my_fopen_in(&fin, "dat/dat/cl.sat");
		char buf[256];
		while(fgets(buf,256,fin) != NULL){
			sscanf_s(buf,"%d,%d,%d,%d,%d",&clearInfo[0],&clearInfo[1],&clearInfo[2],&clearInfo[3],&clearInfo[4]);
		}
		fclose(fin);
		clearInfo[mGameInfo->GetLevel()]=1;
		FILE *fout;
		my_fopen_out(&fout, "dat/dat/cl.sat");
		fprintf(fout,"%d,%d,%d,%d,%d",clearInfo[0],clearInfo[1],clearInfo[2],clearInfo[3],clearInfo[4]);
		fclose(fout);
	}
	int onTimer();
	void onKeyDownZ();
	void onKeyUpZ(){mOnZFlg=false;}
	void UpdateNoContinued();
	void UpdateContinued();
	
};

int CEndingViewController::onTimer(){
	if(mNextPage!=0)return mNextPage;
	mWaitTimer++;
	onTimerSuper();
	CBltInfo bi(BLT_BLACKEN);
	
	int alpha=255-m_timer;
	if(alpha<0)alpha=0;
	bi.alpha=alpha;
	
	CImageBlender::Blt(bg,mImgEnding1,&bi,WND_RECT,0,0);
	RECT rc={100,BATTLE_BOTTOM-m_timer,BATTLE_RIGHT-100,BATTLE_BOTTOM};
	if(mOnZFlg==true)m_timer+=1;
	if(m_timer>FIN_TIME)m_timer= FIN_TIME;
	
	mTextView->SetRect(rc);
	mTextView->OnTimer();
	/*
	char str[64];
	wsprintf(str,"X=%d",m_timer);
	TextOut(bg->hDC(),10,10,str,lstrlen(str));
	*/
	return 0;
}
void CEndingViewController::UpdateContinued(){}
void CEndingViewController::UpdateNoContinued(){}
void CEndingViewController::onKeyDownZ(){
	mOnZFlg=true;
	if(m_timer>FIN_TIME-20){
		CMusic::Stop();
		mNextPage=NAME_ENTRY_VIEW_CONTROLLER;
	}
}
