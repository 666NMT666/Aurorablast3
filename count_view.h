class CCountView:public CView{
protected:
	int mMax;
	int mDeltaX,mDeltaY;
	int mPaddingX,mPaddingY;
	CImage32* mImgBG;/// Background-Frame
	CImage32* mImgFilled;
	CImage32* mImgEmpty;
	CImage32* mImgDest;
public:
	CCountView():CView(){mMax=0;}
	CCountView(CImage32* dest,char* bg,char* filled,char* empty, RECT rc,int max,int dx,int dy,int padX,int padY):CView(dest,rc),mMax(max),
		mDeltaX(dx),mDeltaY(dy),mPaddingX(padX),mPaddingY(padY) {
		if(bg!=NULL)mImgBG=CImageFactory::newBitmap(bg);
		else mImgBG=NULL;
		if(filled!=NULL)mImgFilled=CImageFactory::newBitmap(filled);
		else mImgFilled=NULL;
		if(empty!=NULL)mImgEmpty=CImageFactory::newBitmap(empty);
		else mImgEmpty=NULL;
		mImgDest=dest;
	}
	void Update(int num);
};

void CCountView::Update(int num){
	if(num<0)num=0;
	if(num>mMax)num=mMax;
	CBltInfo bi(BLT_KEY);
	if(mImgBG!=NULL)CImageBlender::Blt(mImgDest,mImgBG,&bi,mRect,mRect.left,mRect.top);
	for(int i=0;i<mMax;i++){
		if(i>=num){
			if(mImgEmpty!=NULL)CImageBlender::Blt(mImgDest,mImgEmpty,&bi,mRect,mPaddingX+mRect.left+mDeltaX*i,mPaddingY+mRect.top+mDeltaY*i);
		}else{
			if(mImgFilled!=NULL)CImageBlender::Blt(mImgDest,mImgFilled,&bi,mRect,mPaddingX+mRect.left+mDeltaX*i,mPaddingY+mRect.top+mDeltaY*i);
		}
	}
}