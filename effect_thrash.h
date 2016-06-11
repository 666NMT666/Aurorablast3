class CEffectThrash:public CEffect{
public:
	DWORD mColor;
	int mAngle;
	void Update();
	void Create(int x,int y,int w,int h,int angle,DWORD color);
};

void CEffectThrash::Update(){
	CShapeBlender::fillRhombus(m_bg,BATTLE_RECT,(int)m_x,(int)m_y,m_width,m_height,mAngle,mColor);
	mDelFlg=true;
}

void CEffectThrash::Create(int x,int y,int w,int h,int angle,DWORD color){
	CreateGameObject(x,y,0,0,0.0,0.0);
	mColor=color;
	mImgId=0;
	mDelFlg=false;
	m_width=w;
	m_height=h;
	mAngle=angle;
}