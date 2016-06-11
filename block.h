#ifndef BLOCK_H
#define BLOCK_H

class CBlock:public CGameObject{
	static const int BLOCK_WIDTH=28;
	static const int FRAME_BOTTOM=480-11;
	static const int MAX_SPEED=40;
	static const int ACCEL=8;
	int mTop;
	bool mStableFlg;
	CEffectManager *efm;
public:
	CBlock():mTop(FRAME_BOTTOM){
		Reset();
		efm=CEffectManager::GetInstance();
	}
	void Reset(){ResetGameObject();}
	void Update();
	void Create(int x,int y,int kind,double vx,double vy,CCreateInfo info=defaultCreateInfo);
	void Destroied();
	void SetTop(int i){mTop=i;}
	bool isStable(){return mStableFlg;}
	void setUnstable(){mStableFlg=false;}

};

void CBlock::Destroied(){
	int p[5]={0,20,mKind*28,0,0};
	CCreateInfo info(p);
	efm->Create(m_x,m_y,0,0,0,info);
}

void CBlock::Update(){
	UpdateGameObject();
	if(m_y+m_height>mTop){
		m_y=mTop-m_height;
		m_vy=0.0;
		mStableFlg=true;
	}else{
		m_vy+=(double)ACCEL;
		if(m_vy>MAX_SPEED)m_vy=(double)MAX_SPEED;
	}
}

void CBlock::Create(int x,int y,int kind,double vx,double vy,CCreateInfo info){
	CreateGameObject(x,y,kind,vx,vy);
	mImgId=0;//ŒÅ’è
	mBltX=mKind*BLOCK_WIDTH;
	mBltY=0;
	m_width=m_height=BLOCK_WIDTH;
	mStableFlg=false;

}

#endif