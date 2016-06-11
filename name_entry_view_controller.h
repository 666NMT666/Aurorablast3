class CNameEntryViewController:public CViewController{
protected:
	int mPosition;
	CImage32 mImgBG;
	CImage32 mImgCsl;
	TGameResult mGameResult[6];
	bool mBackFlg;
	bool mOnLoadFlg;
	CTextView* mNameTextView;
	CTextView* mLevelTextView;
	CTextView* mScoreTextView;
	RECT mNameRect[5];
	RECT mLevelRect[5];
	RECT mScoreRect[5];
	static char mLevelStr[5][16];
	static char mAllChars[64];
	int mCslX,mCslY;
	int mStrCounter;
	int mTimer;
	char mName[16];
	int mCurrentResultPos;

	int GetCurrentResultPos(TGameResult* result,int N){
		for(int i=0;i<N;i++){
			if(result[i].current)return i;
		}
		return N-1;
	}
	CGameInfo* mGameInfo;
	CSoundEffect* mSE;
	CScore* mScore;
public:
	CNameEntryViewController():CViewController(),mPosition(0),mOnLoadFlg(false),mTimer(0),mCurrentResultPos(0){
		mName[0]='_';
		mName[1]='_';
		mName[2]='_';
		mName[3]='\0';
		mBackFlg=false;
		mStrCounter=0;
		mCslX=mCslY=0;
		CImageFactory::InitBitmap(&mImgBG,"dat/img/result_entry.bmp");
		CImageFactory::InitBitmap(&mImgCsl,"dat/img/result_entry_csl.bmp");
		mNameTextView=new CTextView[5];
		mLevelTextView=new CTextView[5];
		mScoreTextView=new CTextView[5];
		for(int i=0;i<5;i++){
			for(int j=0;j<3;j++)mGameResult[i].name[j]='_';
			mGameResult[i].level=0;
			CBigInt score(0);
			mGameResult[i].score=score;
			mGameResult[i].current=false;
		}
		for(int i=0;i<5;i++){
			mNameRect[i].top=mLevelRect[i].top=mScoreRect[i].top=165+52*i;
			mNameRect[i].bottom=mLevelRect[i].bottom=mScoreRect[i].bottom=mNameRect[i].top+45;
			
			mNameRect[i].left=165;
			mNameRect[i].right=300;

			mLevelRect[i].left=310;
			mLevelRect[i].right=450;

			mScoreRect[i].left=450;
			mScoreRect[i].right=900;
		}
		for(int i=0;i<5;i++){
			mNameTextView[i].InitTextView(bg->hDC(),mNameRect[i],30,0xDDDDDD,"");
			mLevelTextView[i].InitTextView(bg->hDC(),mLevelRect[i],30,0xDDDDDD,"");
			mScoreTextView[i].InitTextView(bg->hDC(),mScoreRect[i],20,0xDDDDDD,"",1.0);
		}
		for (int i = 0; i < 5; i++) {
			mLevelTextView[i].SetDTFormat(DT_BOTTOM | DT_SINGLELINE | DT_EXTERNALLEADING);
			mNameTextView[i].SetDTFormat(DT_BOTTOM | DT_SINGLELINE | DT_EXTERNALLEADING);
			mScoreTextView[i].SetDTFormat(DT_LEFT | DT_EXTERNALLEADING | DT_WORDBREAK);
		}
		mGameInfo=CGameInfo::GetInstance();
		mSE=CSoundEffect::GetInstance();
		mScore=CScore::GetInstance();
	}

	void onKeyDownZ();
	void onKeyDownX();

	void onKeyDownLeft();
	void onKeyDownRight();
	void onKeyDownUp();
	void onKeyDownDown();
	int onTimer();
	void onLoad();
	void SaveResult();
	void LoadResult();
	void SortResult(TGameResult *obj,int N);
	void SetTextViews();
	void SaveDefaultFile(){
		FILE* fout;
		errno_t error;
		error=fopen_s(&fout,"dat/dat/result.sat","w");
		fclose(fout);
	}
};
char CNameEntryViewController::mAllChars[64]="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_";
char CNameEntryViewController::mLevelStr[5][16]={
	"Easy","Normal","Hard","Morbid","Suicidal",
};
int CNameEntryViewController::onTimer(){
	mTimer++;
	if(mOnLoadFlg==false){
		mOnLoadFlg=true;
		LoadResult();
		SortResult(mGameResult,6);
		mCurrentResultPos=GetCurrentResultPos(mGameResult,6);
		SetTextViews();
	}
	onTimerSuper();
	if(mBackFlg){return TITLE_VIEW_CONTROLLER;}
	CBltInfo biMain(BLT_MEMCOPY);
	CImageBlender::Blt(bg,&mImgBG,&biMain,WND_RECT,0,0);
	CImageBlender::Blt(bg,&mImgCsl,&BLT_INFO_KEY,WND_RECT,126+mCslX*51,485+mCslY*46);
	for(int i=0;i<5;i++){
		mNameTextView[i].OnTimer();
		mLevelTextView[i].OnTimer();
		mScoreTextView[i].OnTimer();
	}
	if(mStrCounter==3 || mCurrentResultPos==5){
		mCslX=12;
		mCslY=2;
	}
	return 0;
}
void CNameEntryViewController::onKeyDownLeft(){
	if(mStrCounter!=3 && mCslX>0 && mCurrentResultPos!=5){
		mCslX--;
		mSE->PlaySingleSound(SE_KEY1);
	}
}
void CNameEntryViewController::onKeyDownRight(){
	if(mStrCounter!=3 && mCslX<12 && mCurrentResultPos!=5){
		mCslX++;
		mSE->PlaySingleSound(SE_KEY1);
	}
}
void CNameEntryViewController::onKeyDownUp(){
	if(mStrCounter!=3 && mCslY>0 && mCurrentResultPos!=5){
		mCslY--;
		mSE->PlaySingleSound(SE_KEY1);
	}
}
void CNameEntryViewController::onKeyDownDown(){
	if(mStrCounter!=3 && mCslY<2 && mCurrentResultPos!=5){
		mCslY++;
		mSE->PlaySingleSound(SE_KEY1);
	}
}
void CNameEntryViewController::onKeyDownX(){
	if(mStrCounter>0)mStrCounter--;
}
void CNameEntryViewController::onKeyDownZ(){
	if(mTimer<10)return;
	mSE->PlaySingleSound(SE_KEY2);
	if(mCslX==12 && mCslY==2){
		//save
		if(mCurrentResultPos!=5)SaveResult();
		mBackFlg=true;
	}
	else{
		if(mStrCounter<3){
			mName[mStrCounter]=mAllChars[mCslX+mCslY*13];
			mGameResult[mCurrentResultPos].name[mStrCounter]=mAllChars[mCslX+mCslY*13];
			mNameTextView[mCurrentResultPos].SetText(mName);
		}
		if(mStrCounter<3)mStrCounter++;
	}
}
void CNameEntryViewController::LoadResult(){
	FILE* fin;
	char buf[256];
	errno_t error;
	if((error=fopen_s(&fin,"dat/dat/result.sat","r"))!=0) {
		SaveDefaultFile();
		if((error=fopen_s(&fin,"dat/dat/result.sat","r"))!=0)PostQuitMessage(0);
	}
	int i=0;
	while(fgets(buf,256,fin) != NULL){
		char str[128];
		sscanf_s(buf,"%[^\n,],%d,%s",&mGameResult[i].name,8,&mGameResult[i].level,str,128);
		mGameResult[i].score.Init(str);
		i++;
		//if(i==6)break;
	}
	
	//ソート用な
	for(int i=0;i<3;i++)mGameResult[5].name[i]='_';
	mGameResult[5].name[3]='\0';
	mGameResult[5].level=mGameInfo->GetLevel();
	mGameResult[5].score=mScore->GetScore();
	mGameResult[5].current=true;

	fclose(fin);
}
void CNameEntryViewController::SetTextViews(){
	for(int i=0;i<5;i++){
		char str[256];
		mNameTextView[i].SetText(mGameResult[i].name);

		int lv=mGameResult[i].level;
		if(lv<0)lv=0;
		if(lv>4)lv=4;
		mLevelTextView[i].SetText(mLevelStr[lv]);
		

		string scoreStr = "";
		mGameResult[i].score.GetStr4S(&scoreStr);
		int maxBlock = mGameResult[i].score.GetMaxBlock();
		int fontSize = 14;
		//if (maxBlock >= 7) { fontSize = 20; }
		//if (maxBlock >= 1) { fontSize = 16; }
		//if(maxBlock>8){ scoreStr.insert(scoreStr.length()/2,"\n"); }

		strcpy_s(str, 256, scoreStr.c_str());
		mScoreTextView[i].SetText(str);
		mScoreTextView[i].SetFontHeight(fontSize);
	}
}

void CNameEntryViewController::SaveResult(){
	FILE* fout;
	errno_t error=fopen_s(&fout,"dat/dat/result.sat","w");
	for(int i=0;i<5;i++){
		string scoreStr="";
		char s[8];
		int max=mGameResult[i].score.GetMaxBlock();
		for(int j=max;j>=0;j--){
			if(j==max)sprintf_s(s,8,"%d",mGameResult[i].score.GetInt(j));
			else sprintf_s(s,8,"%04d",mGameResult[i].score.GetInt(j));
			scoreStr+=s;
		}
		fprintf(fout,"%s,%d,%s\n",mGameResult[i].name,mGameResult[i].level,scoreStr.c_str());
	}
	fclose(fout);
}

void CNameEntryViewController::SortResult(TGameResult *obj,int N){
	for(int i=0;i<N-1;i++){
	    int max=i;
	    for(int j=i+1;j<N;j++){
			if(obj[max].score.Cmp(&obj[j].score)==-1)max=j;
		}
	    if(i!=max)SWAP(&obj[i],&obj[max]);
    }
}