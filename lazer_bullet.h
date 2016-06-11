const char LZ_FILE[5][64]={
	"dat/img/eb/e-bullets10.bmp",
};
class CLazerBullet:public CEnemySideObject{
private:
	CEffectManager* mEffectManager;
	CEffectManager* mEffectManagerUnder;
	int mParams[5];
	double mTailX,mTailY;
public:
	CLazerBullet():CEnemySideObject(),mTailX(0),mTailY(0){
		mEffectManager=CEffectManager::GetInstance();
	}
	void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info);
	void Move0();
};

void CLazerBullet::Update(){
	UpdateGameObject();
	if(mKind==0){
		Move0();
	}
}

void CLazerBullet::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,subKind,vx,vy);
	mImgId=info.params[0];
	mDelFlg=false;
}

void CLazerBullet::Move0(){
	if((m_x<0 && mTailX<0) || m_x>660 || m_y<0 || m_y>500)mDelFlg=true;
	mTailX=(m_x+m_x0)/2-m_vx;
	mTailY=(m_y+m_y0)/2-m_vy;
	int w=11;
	int tailLength=70;
	CLine::drawGradationLine(m_bg,(int)m_x,(int)m_y,(int)mTailX,(int)mTailY,w,0xFFFFAA,0xFF5500,5,tailLength,4,0);
	CVector r[4];
	CVector h(m_x,m_y);
	CVector ev(mTailX-m_x,mTailY-m_y);
	double length=ev.Abs();
	ev=ev/length;
	CVector ov=ev.getOrthogonalVector();
	r[0]=h-ov*w/2;
	r[1]=h+ov*w/2;
	r[2]=h+ov*w/2+ev*(length-tailLength);
	r[3]=h-ov*w/2+ev*(length-tailLength);
	if(ExMath::isInPoligon(mPlayer->GetX(),mPlayer->GetY(),r,4)){
		if(!mPlayer->isInvincible())mPlayer->Killed();
	}
}
