#include <Windows.h>
class CTextView{
protected:
	HDC mHDC;
	RECT mRect;
	int mFontHeight;
	bool mItaric,mUnderLine,mStrike;
	double mLineScale;
	LPTSTR mFontFace;
	COLORREF mColor;
	UINT mDTFormat;
	list<string> mStrs;
	int mAngle;
public:
	CTextView() { mDTFormat = DT_EXTERNALLEADING; mAngle = 0; }
	CTextView(HDC hdc,RECT rc,int h,COLORREF c,char* str,double lscale=1.5,LPCTSTR font="ＭＳ Ｐゴシック",bool i=false,bool u=false,bool s=false){
		InitTextView(hdc,rc,h,c,str,lscale,font,i,u,s);
	}
	void InitTextView(HDC hdc,RECT rc,int h,COLORREF c,char* str,double lscale=1.5,LPCTSTR font="ＭＳ Ｐゴシック",bool i=false,bool u=false,bool s=false){
		mHDC=hdc;
		mRect=rc;
		mColor=c;
		SetFontHeight(h);
		SetLineScale(lscale);
		SetText(str);
		mItaric=i;
		mUnderLine=u;
		mStrike=s;
		//lstrcpy(mFontFace,font);
		mDTFormat= DT_EXTERNALLEADING;
		mAngle = 0;
	}
	void OnTimer();
	void SetColor(DWORD c){mColor=c;}
	void SetFontHeight(int h){mFontHeight=h;}
	void SetLineScale(double s){mLineScale=s;}
	void SetText(char* str){mStrs=CStringUtil::split(str,'\n');}
	void SetText(const char* str) { mStrs = CStringUtil::split(str, '\n'); }
	void SetRect(RECT rc){mRect=rc;}
	void SetItaric(bool i){mItaric=i;}
	void SetDTFormat(UINT f) { mDTFormat = f; }
	HFONT MkFont(LPCTSTR face,int h,int angle);
};

void CTextView::OnTimer(){
	HFONT hFontOld,hFont;
	hFont=MkFont((LPCTSTR)mFontFace, mFontHeight,mAngle);
	SetTextColor(mHDC,mColor);
	SetBkMode(mHDC,TRANSPARENT);
	hFontOld= (HFONT)SelectObject(mHDC,hFont);
	
	list<string>::iterator it = mStrs.begin(); // イテレータ
	int j=0;
	while( it != mStrs.end() ){
		RECT rc={mRect.left,mRect.top+(LONG)(mFontHeight*j*mLineScale),mRect.right,mRect.bottom};
		DrawText(mHDC,(LPCTSTR)((*it).c_str()),-1,&rc,mDTFormat);
		++j;
		++it;  // イテレータを１つ進める
	}

	SelectObject(mHDC,hFontOld);
	DeleteObject(hFont);
}

HFONT CTextView::MkFont(LPCTSTR face,int h,int angle=0){
	return CreateFont(
		h,//フォント高さ
		0,//文字幅（高さと同じ）
		angle,//テキストの角度
		0,//ベースラインとｘ軸との角度
		800,//フォントの重さ（太さ）
		mItaric,//イタリック体
		mUnderLine,//アンダーライン
		mStrike,//打ち消し線
		SHIFTJIS_CHARSET,//文字セット
		OUT_DEFAULT_PRECIS,//出力精度
		CLIP_DEFAULT_PRECIS,//クリッピング精度
		PROOF_QUALITY,//出力品質
		FIXED_PITCH|FF_MODERN,  //ピッチとファミリー
		"ＭＳ Ｐ明朝"//書体名
	);
}