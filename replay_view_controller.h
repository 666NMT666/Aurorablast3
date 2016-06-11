#include "file_util.h"

typedef struct _TGameResult{
	char name[8];
	int level;
	bool current;
	CBigInt score;
} TGameResult;

class CReplayViewController:public CViewController{
protected:
	int mPosition;
	CImage32 mImgBG;
	TGameResult mGameResult[5];
	bool mBackFlg;
	bool mOnLoadFlg;
	CTextView* mNameTextView;
	CTextView* mLevelTextView;
	CTextView* mScoreTextView;
	RECT mNameRect[5];
	RECT mLevelRect[5];
	RECT mScoreRect[5];
	static char mLevelStr[5][16];
public:
	CReplayViewController():CViewController(),mPosition(0),mOnLoadFlg(false){
		mBackFlg=false;
		CImageFactory::InitBitmap(&mImgBG,"dat/img/result.bmp");
		mNameTextView=new CTextView[5];
		mLevelTextView=new CTextView[5];
		mScoreTextView=new CTextView[5];
		for(int i=0;i<5;i++){
			for(int j=0;j<3;j++)mGameResult[i].name[j]='_';
			mGameResult[i].level=0;
			CBigInt score(0);
			mGameResult[i].score=score;
		}
		for(int i=0;i<5;i++){
			mNameRect[i].top=mLevelRect[i].top=240+73*i;
			mScoreRect[i].top = 245 + 73 * i;
			mNameRect[i].bottom=mLevelRect[i].bottom=mNameRect[i].top+40;
			mScoreRect[i].bottom=mScoreRect[i].top + 50;
			
			mNameRect[i].left=145;
			mNameRect[i].right=300;

			mLevelRect[i].left=240;
			mLevelRect[i].right=525;

			mScoreRect[i].left=400;
			mScoreRect[i].right=880;
		}
		for(int i=0;i<5;i++){
			mNameTextView[i].InitTextView(bg->hDC(),mNameRect[i],30,0xDDDDDD,"");
			mLevelTextView[i].InitTextView(bg->hDC(),mLevelRect[i],30,0xDDDDDD,"");
			mScoreTextView[i].InitTextView(bg->hDC(),mScoreRect[i],30,0xDDDDDD,"",1.0);
		}
		for (int i = 0; i < 5; i++) {
			mLevelTextView[i].SetDTFormat(DT_BOTTOM | DT_SINGLELINE | DT_EXTERNALLEADING);
			mNameTextView[i].SetDTFormat(DT_BOTTOM | DT_SINGLELINE | DT_EXTERNALLEADING);
			mScoreTextView[i].SetDTFormat(DT_LEFT | DT_EXTERNALLEADING | DT_WORDBREAK);
		}
	}
	void onKeyDownX(){mBackFlg=true;}
	int onTimer();
	void onLoad();
	void SaveResult();
	void LoadResult();
};

char CReplayViewController::mLevelStr[5][16]={
	"Easy","Normal","Hard","Morbid","Suicidal",
};
int CReplayViewController::onTimer(){
	if(mOnLoadFlg==false){
		mOnLoadFlg=true;
		LoadResult();
	}
	onTimerSuper();
	if(mBackFlg){return TITLE_VIEW_CONTROLLER;}
	CBltInfo biMain(BLT_MEMCOPY);
	CImageBlender::Blt(bg,&mImgBG,&biMain,WND_RECT,0,0);
	for(int i=0;i<5;i++){
		mNameTextView[i].OnTimer();
		mLevelTextView[i].OnTimer();
		mScoreTextView[i].OnTimer();
	}
	return 0;
}

void CReplayViewController::LoadResult(){
	FILE* fin;
	char buf[256];
	my_fopen_in(&fin, "dat/dat/result.sat");
	int i=0;
	while(fgets(buf,256,fin) != NULL){
		char score[128];
		sscanf_s(buf,"%[^\n,],%d,%s",&mGameResult[i].name,8,&mGameResult[i].level,score,128);
		mGameResult[i].score.Init(score);
		i++;
	}

	for(int i=0;i<5;i++){
		char str[256];
		mNameTextView[i].SetText(mGameResult[i].name);

		int lv=mGameResult[i].level;
		if(lv<0)lv=0;
		if(lv>4)lv=4;
		mLevelTextView[i].SetText(mLevelStr[lv]);
		
		string scoreStr="";
		mGameResult[i].score.GetStr4S(&scoreStr);
		int maxBlock=mGameResult[i].score.GetMaxBlock();
		int fontSize=16;
		//if (maxBlock >= 7) { fontSize = 20; }
		//if (maxBlock >= 1) { fontSize = 16; }
		//if(maxBlock>8){ scoreStr.insert(scoreStr.length()/2,"\n"); }

		strcpy_s(str,256,scoreStr.c_str());
		mScoreTextView[i].SetText(str);
		mScoreTextView[i].SetFontHeight(fontSize);
	}
	fclose(fin);
}
void CReplayViewController::SaveResult(){
	FILE* fout;
	errno_t error;
	error=fopen_s(&fout,"dat/dat/result.sat","w");
	fclose(fout);
}