const int BOMB_FILES=1;
const TFileData BOMB_FILE[BULLET_FILES]={
	{"dat/img/bomb.bmp",216,97,1}
};
class CBomb:public CGameObject{
protected:
	CEffectManager* mEffectManager;
public:
	bool mHitFlg;
	CBomb():CGameObject(),mHitFlg(false){
		mEffectManager=CEffectManager::GetInstance();
	}
	void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info);
	void Hit();
};

void CBomb::Update(){
	if(m_y<-100){mDelFlg=true;}
	UpdateGameObject();
}

void CBomb::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	mImgId=kind;
	mDelFlg=false;
	m_vx=vx; m_vy=vy;
	m_width=BOMB_FILE[kind].width;
	m_height=BOMB_FILE[kind].height;
	mBltX=info.params[0]*m_width;
}

void CBomb::Hit(){
	mHitFlg=true;
	mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_LIGHT_40,1,(rand()%50)*0.1,0, 0, 2, 10, 0);
	for(int i=0;i<15;i++){
		mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_PARTICLE1,0,-(rand()%100)*0.1,rand()%40-20, 1, 2, 20, 0);
	}
}