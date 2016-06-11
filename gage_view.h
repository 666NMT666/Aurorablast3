enum TGradationType{
	GRD_HORIZONTAL,
	GRD_VERTICAL
};
typedef struct _TGradationColor{
	DWORD start,end;
	TGradationType type;
	_TGradationColor(){
		start=end=0;
		type=GRD_HORIZONTAL;
	}
} TGradationColor;

class CGageView{
private:
	RECT mRect;
	TGradationColor mColorFrame;
	TGradationColor mColorBG;
	TGradationColor mColorGage;
	DWORD* mGradationFrame;
	DWORD* mGradationBG;
	DWORD* mGradationGage;
protected:
	CImage32* mImgDest;
	double mMax;
public:
	CGageView(){
		mRect.bottom=mRect.left=mRect.right=mRect.top=0;
		TGradationColor defaultGrad;
		mColorFrame=mColorBG=mColorGage=defaultGrad;
		mMax=1;
		mImgDest=NULL;
	}
	CGageView(CImage32* img,RECT rc,double max,DWORD colorFrame,DWORD colorGage, DWORD colorBG){
		setRect(rc);
		mMax=max;
		mColorFrame.start=mColorFrame.end=colorFrame;
		mColorBG.start=mColorBG.end=colorBG;
		mColorGage.start=mColorGage.end=colorGage;
		CreateGradation();
		mImgDest=img;
	}
	CGageView(CImage32* img,RECT rc,double max,DWORD colorFrameStart,DWORD colorFrameEnd,DWORD colorGageStart,DWORD colorGageEnd, DWORD colorBGStart, DWORD colorBGEnd){
		setRect(rc);
		mMax=max;
		mColorFrame.start=colorFrameStart;
		mColorFrame.end=colorFrameEnd;
		mColorBG.start=colorBGStart;
		mColorBG.end=colorBGEnd;
		mColorGage.start=colorGageStart;
		mColorGage.end=colorGageEnd;
		CreateGradation();
		mImgDest=img;
	}
	CGageView(CImage32* img,RECT rc,TGradationColor colorFrame,TGradationColor colorGage, TGradationColor colorBG){
		setRect(rc);
		mColorFrame=colorFrame;
		mColorBG=colorBG;
		mColorGage=colorGage;
		CreateGradation();
		mImgDest=img;
	}

	void CreateGradation();
	void setRect(RECT rc){
		mRect.bottom=rc.bottom;
		mRect.left=rc.left;
		mRect.right=rc.right;
		mRect.top=rc.top;
	}
	void setImg(CImage32* img){mImgDest=img;}
	void setFrameColor(DWORD start,DWORD end);
	void setBGColor(DWORD start,DWORD end);
	void setGageColor(DWORD start,DWORD end);
	void Update(double current);
	void Update(double current, double max);
};

void CGageView::setFrameColor(DWORD start,DWORD end){
	mColorFrame.start=start;
	mColorFrame.end=end;
	TARGB argbStart;
	TARGB argbEnd;
	argbStart.ARGB=mColorFrame.start;
	argbEnd.ARGB=mColorFrame.end;
	static const int fixfloat_const=1<<8;
	int sz;
	if(mColorFrame.type==GRD_HORIZONTAL)sz=mRect.right-mRect.left;
	else sz=mRect.bottom-mRect.top;
	int deltaR=(argbEnd.R-argbStart.R)*fixfloat_const/sz;
	int deltaG=(argbEnd.G-argbStart.G)*fixfloat_const/sz;
	int deltaB=(argbEnd.B-argbStart.B)*fixfloat_const/sz;
	TARGB color;

	for(int i=0,R=argbStart.R*fixfloat_const,G=argbStart.G*fixfloat_const,B=argbStart.B*fixfloat_const;
			i<sz;i++,R+=deltaR,G+=deltaG,B+=deltaB){
		color.A=0;
		color.R=R>>8; color.G=G>>8; color.B=B>>8;
		mGradationFrame[i]=color.ARGB;
	}
}

void CGageView::setBGColor(DWORD start,DWORD end){
	mColorBG.start=start;
	mColorBG.end=end;
	TARGB argbStart;
	TARGB argbEnd;
	argbStart.ARGB=mColorBG.start;
	argbEnd.ARGB=mColorBG.end;
	static const int fixfloat_const=1<<8;
	int sz;
	if(mColorBG.type==GRD_HORIZONTAL)sz=mRect.right-mRect.left;
	else sz=mRect.bottom-mRect.top;
	int deltaR=(argbEnd.R-argbStart.R)*fixfloat_const/sz;
	int deltaG=(argbEnd.G-argbStart.G)*fixfloat_const/sz;
	int deltaB=(argbEnd.B-argbStart.B)*fixfloat_const/sz;
	TARGB color;

	for(int i=0,R=argbStart.R*fixfloat_const,G=argbStart.G*fixfloat_const,B=argbStart.B*fixfloat_const;
			i<sz;i++,R+=deltaR,G+=deltaG,B+=deltaB){
		color.A=0;
		color.R=R>>8; color.G=G>>8; color.B=B>>8;
		mGradationBG[i]=color.ARGB;
	}
}

void CGageView::setGageColor(DWORD start,DWORD end){
	mColorGage.start=start;
	mColorGage.end=end;
	TARGB argbStart;
	TARGB argbEnd;
	argbStart.ARGB=mColorGage.start;
	argbEnd.ARGB=mColorGage.end;
	static const int fixfloat_const=1<<8;
	int sz;
	if(mColorBG.type==GRD_HORIZONTAL)sz=mRect.right-mRect.left;
	else sz=mRect.bottom-mRect.top;	
	int deltaR=(argbEnd.R-argbStart.R)*fixfloat_const/sz;
	int deltaG=(argbEnd.G-argbStart.G)*fixfloat_const/sz;
	int deltaB=(argbEnd.B-argbStart.B)*fixfloat_const/sz;
	TARGB color;

	for(int i=0,R=argbStart.R*fixfloat_const,G=argbStart.G*fixfloat_const,B=argbStart.B*fixfloat_const;
			i<sz;i++,R+=deltaR,G+=deltaG,B+=deltaB){
		color.A=0;
		color.R=R>>8; color.G=G>>8; color.B=B>>8;
		mGradationGage[i]=color.ARGB;
	}
}

void CGageView::CreateGradation(){
	int szFrame,szBG,szGage;
	int width=mRect.right-mRect.left;
	int height=mRect.bottom-mRect.top;

	if(mColorFrame.type==GRD_HORIZONTAL)szFrame=width;
	else szFrame=height;
	
	if(mColorBG.type==GRD_HORIZONTAL)szBG=width;
	else szBG=height;
	
	if(mColorGage.type==GRD_HORIZONTAL)szGage=width;
	else szGage=height;

	mGradationFrame=new DWORD[szFrame];
	mGradationBG=new DWORD[szBG];
	mGradationGage=new DWORD[szGage];

	setBGColor(mColorBG.start,mColorBG.end);
	setGageColor(mColorGage.start,mColorGage.end);
	setFrameColor(mColorFrame.start,mColorFrame.end);

}


void CGageView::Update(double current, double max) {
	if (mImgDest == NULL)return;
	int height = mRect.bottom - mRect.top;
	int width = mRect.right - mRect.left;
	if (current<0.0)current = 0.0;
	if (current>max)current = max;
	int limit = (int)(width*(current / max));

	if (mColorBG.type == GRD_HORIZONTAL) {
		for (int i = 0; i<height; i++) {
			for (int j = 0; j<width; j++) {
				mImgDest->PixelSetNC(mRect.left + j, mRect.top + i, mGradationBG[j]);
			}
		}
	}
	else {
		for (int i = 0; i<height; i++) {
			for (int j = 0; j<width; j++) {
				mImgDest->PixelSetNC(mRect.left + j, mRect.top + i, mGradationBG[i]);
			}
		}
	}

	if (mColorGage.type == GRD_HORIZONTAL) {
		for (int i = 0; i<height; i++) {
			for (int j = 0; j<limit; j++) {
				mImgDest->PixelSetNC(mRect.left + j, mRect.top + i, mGradationGage[j]);
			}
		}
	}
	else {
		for (int i = 0; i<limit; i++) {
			for (int j = 0; j<width; j++) {
				mImgDest->PixelSetNC(mRect.left + j, mRect.top + i, mGradationGage[i]);
			}
		}
	}

	if (mColorFrame.type == GRD_HORIZONTAL) {
		for (int j = 0; j<width; j++)mImgDest->PixelSetNC(mRect.left + j, mRect.top, mGradationFrame[j]);
		for (int j = 0; j<width; j++)mImgDest->PixelSetNC(mRect.left + j, mRect.bottom - 1, mGradationFrame[j]);
		for (int j = 0; j<height; j++)mImgDest->PixelSetNC(mRect.left, mRect.top + j, mGradationFrame[0]);
		for (int j = 0; j<height; j++)mImgDest->PixelSetNC(mRect.right - 1, mRect.top + j, mGradationFrame[width - 1]);
	}
	else {
		for (int j = 0; j<width; j++)mImgDest->PixelSetNC(mRect.left + j, mRect.top, mGradationFrame[0]);
		for (int j = 0; j<width; j++)mImgDest->PixelSetNC(mRect.left + j, mRect.bottom - 1, mGradationFrame[height - 1]);
		for (int j = 0; j<height; j++)mImgDest->PixelSetNC(mRect.left, mRect.top + j, mGradationFrame[j]);
		for (int j = 0; j<height; j++)mImgDest->PixelSetNC(mRect.right - 1, mRect.top + j, mGradationFrame[j]);
	}
}

void CGageView::Update(double current){
	Update(current, mMax);
}