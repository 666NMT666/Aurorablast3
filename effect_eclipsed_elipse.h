class CEffectEclipsedElipse:public CEffect{
public:
	int mX1,mX2,mY1,mY2,mRX1,mRX2,mRY1,mRY2;
	DWORD mColor;
	void Update();
	void Create(int x1,int y1,int rx1,int ry1,int x2,int y2,int rx2,int ry2,DWORD color);

};

void CEffectEclipsedElipse::Update(){
	CEclipsedElipse::draw(m_bg,mX1,mY1,mRX1,mRY1,mX2,mY2,mRX2,mRY2,mColor);
	mDelFlg=true;
}

void CEffectEclipsedElipse::Create(int x1,int y1,int rx1,int ry1,int x2,int y2,int rx2,int ry2,DWORD color){
	CreateGameObject(x1,y1,0,0,0.0,0.0);
	mX1=x1;
	mX2=x2;
	mY1=y1;
	mY2=y2;
	mRX1=rx1;
	mRX2=rx2;
	mRY1=ry1;
	mRY2=ry2;
	mColor=color;
	mImgId=0;
	mDelFlg=false;
	m_width=0;
	m_height=0;
}