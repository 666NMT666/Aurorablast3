#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
typedef struct _TSize2D{
	int w,h;
} TSize2D;
class CCreateInfo{
public:
	int params[5];
	CBltInfo bltInfo;
	CCreateInfo(){
		bltInfo=BLT_INFO_KEY;
		for(int i=0;i<5;i++)params[i]=0;
	}
	CCreateInfo(int p[]){
		bltInfo=BLT_INFO_KEY;
		for(int i=0;i<5;i++)params[i]=p[i];
	}
	CCreateInfo(int p1,int p2,int p3,int p4,int p5){
		bltInfo=BLT_INFO_KEY;
		params[0]=p1;params[1]=p2;params[2]=p3;params[3]=p4;params[4]=p5;
	}
	CCreateInfo(int p[], const CBltInfo &info){
		bltInfo=info;
		for(int i=0;i<5;i++)params[i]=p[i];
	}
	CCreateInfo(int p1,int p2,int p3,int p4,int p5, const CBltInfo &info){
		bltInfo=info;
		params[0]=p1;params[1]=p2;params[2]=p3;params[3]=p4;params[4]=p5;
	}
	static CCreateInfo createInfo(int p[]){CCreateInfo info(p); return info;}
	static CCreateInfo createInfo(int p1,int p2,int p3,int p4,int p5){CCreateInfo info(p1,p2,p3,p4,p5); return info;}
	static CCreateInfo createInfo(int p[], const CBltInfo &bi){CCreateInfo info(p,bi); return info;}
};

class CGameObject{
protected:
	static const CCreateInfo defaultCreateInfo;
	double m_x,m_y,m_vx,m_vy,m_x0,m_y0;
	double mPrevX,mPrevY;
	int m_width,m_height;
	int mBltX,mBltY;
	int mImgId;
	int mKind,mSubKind;
	int mTimer;
	int mCounter;
	bool mDelFlg,mAutoDelFlg;
	CBltInfo mBltInfo;
	CImageDIB* m_bg;
	RECT mRectScreenOut;
	RECT mRectBlt;
public:
	CGameObject():mDelFlg(false),mAutoDelFlg(false){ResetGameObject();}
	virtual void Update(){}
	virtual void Reset(){}
	//virtual void Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info=defaultCreateInfo){}
	virtual void Create(int x,int y,int kind,int sub_kind,double vx,double vy,const CCreateInfo& info=defaultCreateInfo){}
	int GetX() const{return (int)m_x;}
	int GetY() const{return (int)m_y;}

	const int GetPrevX(){return (int)mPrevX;}
	const int GetPrevY(){return (int)mPrevY;}
	int GetBltX() const{return (int)mBltX;}
	int GetBltY() const{return (int)mBltY;}
	void SetPos(CVector v){m_x=v.x; m_y=v.y;}
	void SetPos(int x,int y){m_x=x;m_y=y;}
	void SetVel(CVector v){m_vx=v.x; m_vy=v.y;}
	void SetVel(double x,double y){m_vx=x;m_vy=y;}
	void SetVelPolar(double v,int angle){
		m_vx=v*cos(angle*N_PI);
		m_vy=v*sin(angle*N_PI);
	}
	void ForceObject(double x,double y){m_vx+=x;m_vy+=y;}
	void PushObject(double x,double y){m_x+=x;m_y+=y;}
	const int GetHeight(){return m_height;}
	const int GetWidth(){return m_width;}
	const int GetKind(){return mKind;}
	const int GetImgId(){return mImgId;}
	const bool isDeleted(){return mDelFlg;}
	const int GetTimer(){return mTimer;}
	void SetSize(int width,int height){m_width=width;m_height=height;}
	void UpdateGameObject(){
		mPrevX=m_x; mPrevY=m_y;
		m_x+=m_vx; m_y+=m_vy;
		mBltInfo.link_x=m_width/2;
		mBltInfo.link_y=m_height/2;
		mTimer++;
		if(mAutoDelFlg){
			if(!CExRect::isInRect(&mRectScreenOut,m_x,m_y,m_width,m_height))mDelFlg=true;
		}
	}
	void CreateGameObject(int x,int y,int kind,double vx,double vy){ CreateGameObject(x,y,kind,0,vx,vy); }
	void CreateGameObject(int x,int y,int kind,int subKind,double vx,double vy){
		ResetGameObject();
		CExRect::InitRect(&mRectScreenOut,BATTLE_LEFT,BATTLE_TOP,BATTLE_RIGHT,BATTLE_BOTTOM);
		m_x=x; m_y=y; mKind=kind; mSubKind=subKind; m_vx=vx; m_vy=vy;
		mPrevX=x; mPrevY=y;
		m_x0=x; m_y0=y;
	}
	void ResetGameObject(){
		CExRect::InitRect(&mRectScreenOut,0,0,960,720);
		m_x=m_y=m_x0=m_y0=m_vx=m_vy=0.0;
		mPrevX=mPrevY=0;
		m_width=m_height=mBltX=mBltY=0;
		mImgId=mKind=mSubKind=0;
		mTimer=0;
		mDelFlg=false;
		mAutoDelFlg=false;
		mCounter=0;
		mBltInfo=BLT_INFO_KEY;
		m_bg=CImageDIB::GetInstance();
		mRectBlt = BATTLE_RECT;
	}
	const CBltInfo* const GetBltInfo(){ return &mBltInfo; }

	void SetRectBlt(RECT rc) { mRectBlt = rc; }
	void ForceFriction(double c) { ForceFriction(c, c); } /// c == 1 - Frction_Coefficient
	void ForceFriction(double cx, double cy) {
		m_vy *= cy;
		m_vx *= cx;
	}
	void SetVelTo(double vel, int x, int y) {
		CVector v = CVector::EigenVector(m_x, m_y, x, y);
		v.Mul(vel);
		m_vx = v.x;
		m_vy = v.y;
	}
	virtual void Blt(CImageDIB* dest,CImage32* src);
};
const CCreateInfo CGameObject::defaultCreateInfo;

void CGameObject::Blt(CImageDIB* dest,CImage32* src){
	if(mBltInfo.zoom==1.0 && mBltInfo.angle==0){
		CImageBlender::Blt(dest,src,&mBltInfo, mRectBlt,(int)m_x-mBltInfo.link_x,(int)m_y-mBltInfo.link_y,mBltX,mBltY,m_width,m_height);
	}else if(mBltInfo.zoom!=1.0 && mBltInfo.angle==0)
		CImageBlenderStretch::Blt(dest,src,&mBltInfo, mRectBlt,(int)(m_x-mBltInfo.link_x*mBltInfo.zoom),(int)(m_y-mBltInfo.link_y*mBltInfo.zoom),mBltX,mBltY,m_width,m_height);
	else
		CImageBlenderTexmap::Blt(dest,src,&mBltInfo, mRectBlt,(int)(m_x-mBltInfo.link_x*mBltInfo.zoom),(int)(m_y-mBltInfo.link_y*mBltInfo.zoom),mBltX,mBltY,m_width,m_height);

}
#endif