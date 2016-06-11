class CEffectEclipsedCircle:public CEffect{
public:
	int mX1,mX2,mY1,mY2,mR1,mR2;
	DWORD mColor;
	void Update();
	void Create(int x1,int y1,int r1,int x2,int y2,int r2,DWORD color);

};

void CEffectEclipsedCircle::Update(){
	CEclipsedCircle::draw(m_bg,mX1,mY1,mR1,mX2,mY2,mR2,mColor);
	mDelFlg=true;
}

void CEffectEclipsedCircle::Create(int x1,int y1,int r1,int x2,int y2,int r2,DWORD color){
	CreateGameObject(x1,y1,0,0,0.0,0.0);
	mX1=x1;
	mX2=x2;
	mY1=y1;
	mY2=y2;
	mR1=r1;
	mR2=r2;
	mColor=color;
	mImgId=0;
	mDelFlg=false;
	m_width=0;
	m_height=0;
}