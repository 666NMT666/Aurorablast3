class CImageNumber{
protected:
	CImageDIB* m_bg;
	CImage32* mImages;
	int mWidth,mHeight;
public:
	CImageNumber();
	CImageNumber(char* fname){
		m_bg=CImageDIB::GetInstance();
		mImages=new CImage32();
		CImageFactory::InitBitmap(mImages,fname);
		mWidth=mImages->Width()/10;
		mHeight=mImages->Height();
	}
	~CImageNumber(){
		delete mImages;
	}
	void PutNumber(int x,int y,DWORD num);
	void PutNumberV(int x,int y,DWORD num);
	void PutNumberStrV(int x,int y,const char* num,int hDelim=24);
};

void CImageNumber::PutNumber(int x,int y,DWORD n){
	int keta=ExMath::keta(n);
	CBltInfo bi(BLT_KEY);
	for(int j=0;j<keta;j++){
		int num=n%10;
		CImageBlender::Blt(m_bg,mImages,&bi,BATTLE_RECT,x+keta*mWidth-j*mWidth, y,mWidth*num,0,mWidth,mHeight);
		n/=10;
	}
}

void CImageNumber::PutNumberV(int x,int y,DWORD n){
	int keta=ExMath::keta(n);
	CBltInfo bi(BLT_KEY);
	int w=mImages->Width();
	int h=mImages->Height()/10;
	for(int j=0;j<keta;j++){
		int num=n%10;
		CImageBlender::Blt(m_bg,mImages,&bi,WND_RECT,x,y+keta*h-j*h,0,h*num,w,h);
		n/=10;
	}
}

void CImageNumber::PutNumberStrV(int x,int y,const char* str,int hDelim){
	int keta=strlen(str);
	if(keta==0)keta=1;
	CBltInfo bi(BLT_KEY);
	int w=mImages->Width();
	int h=mImages->Height()/10;


	//1a1111a4514a


	for(int j=0,k=0;j<keta;j++){
		if(j%4==0)k++;
		int num=(int)(str[keta-1-j]-'0');
		CImageBlender::Blt(m_bg,mImages,&bi,WND_RECT,x,y-j*h-k*hDelim, 0,h*num,w,h);
	}
}
