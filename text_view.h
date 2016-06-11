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
	CTextView(HDC hdc,RECT rc,int h,COLORREF c,char* str,double lscale=1.5,LPCTSTR font="�l�r �o�S�V�b�N",bool i=false,bool u=false,bool s=false){
		InitTextView(hdc,rc,h,c,str,lscale,font,i,u,s);
	}
	void InitTextView(HDC hdc,RECT rc,int h,COLORREF c,char* str,double lscale=1.5,LPCTSTR font="�l�r �o�S�V�b�N",bool i=false,bool u=false,bool s=false){
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
	
	list<string>::iterator it = mStrs.begin(); // �C�e���[�^
	int j=0;
	while( it != mStrs.end() ){
		RECT rc={mRect.left,mRect.top+(LONG)(mFontHeight*j*mLineScale),mRect.right,mRect.bottom};
		DrawText(mHDC,(LPCTSTR)((*it).c_str()),-1,&rc,mDTFormat);
		++j;
		++it;  // �C�e���[�^���P�i�߂�
	}

	SelectObject(mHDC,hFontOld);
	DeleteObject(hFont);
}

HFONT CTextView::MkFont(LPCTSTR face,int h,int angle=0){
	return CreateFont(
		h,//�t�H���g����
		0,//�������i�����Ɠ����j
		angle,//�e�L�X�g�̊p�x
		0,//�x�[�X���C���Ƃ����Ƃ̊p�x
		800,//�t�H���g�̏d���i�����j
		mItaric,//�C�^���b�N��
		mUnderLine,//�A���_�[���C��
		mStrike,//�ł�������
		SHIFTJIS_CHARSET,//�����Z�b�g
		OUT_DEFAULT_PRECIS,//�o�͐��x
		CLIP_DEFAULT_PRECIS,//�N���b�s���O���x
		PROOF_QUALITY,//�o�͕i��
		FIXED_PITCH|FF_MODERN,  //�s�b�`�ƃt�@�~���[
		"�l�r �o����"//���̖�
	);
}