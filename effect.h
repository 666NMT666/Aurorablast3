#ifndef EFFECT_H
#define EFFECT_H

const int EFFECT_MOTION_SINGLE = 0;
const int EFFECT_MOTION_LOOP = 1;
class CEffect:public CGameObject{
	int mNumCycle;
	int mMotion,mInterval,mEnd,mDelta;
public:
	CEffect():CGameObject(),mNumCycle(1),mMotion(0),mInterval(0),mEnd(0),mDelta(0){Reset();}
	void Reset(){ResetGameObject();}
	virtual void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info=defaultCreateInfo);
	void singleCycleFlash();
	void loopFlash();
	void singleCycleZoom();
	void singleCycleZoomIn();

	void SetType(TBltType t) { mBltInfo.type = t; }
	void SetNumCycle(int i) { mNumCycle = i; }
	void loopZoom();

	static CCreateInfo* EffectExplosionCreateInfo;
};

void CEffect::singleCycleFlash(){
	int cycleId=(mTimer-1)/mInterval;
	mBltY=(cycleId+mSubKind*mNumCycle)*m_height;
	if(cycleId>=mNumCycle){mDelFlg=true;}
}

void CEffect::loopFlash(){
	if(mTimer==1){ mCounter=rand()%mNumCycle; }
	int cycleId=((mTimer-1)/mInterval+mCounter)%mNumCycle;
	mBltY=(cycleId+mSubKind*mNumCycle)*m_height;
	if(mTimer>=mEnd){mDelFlg=true;}
}

void CEffect::singleCycleZoom(){
	int cycleId=(mTimer-1)/mInterval;
	mBltY=(cycleId+mSubKind*mNumCycle)*m_height;
	mBltInfo.zoom=mEnd*0.01;
	mBltInfo.alpha=mDelta;
	if(cycleId>=mNumCycle){mDelFlg=true;}
}

void CEffect::singleCycleZoomIn(){
	int cycleId=(mTimer-1)/mInterval;
	mBltY=(cycleId+mSubKind*mNumCycle)*m_height;
	mBltInfo.zoom=1.0+mTimer*mDelta*0.1;
	if(cycleId>=mNumCycle){mDelFlg=true;}
}

void CEffect::Update(){
	UpdateGameObject();
	if(mMotion==EFFECT_MOTION_SINGLE){singleCycleFlash();}
	else if(mMotion==1){loopFlash();}
	else if(mMotion==2){singleCycleZoom();}
	else if(mMotion==3){singleCycleZoomIn();}
}

void CEffect::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,subKind,vx,vy);
	mImgId=kind;
	mBltInfo=info.bltInfo;
	mDelFlg=false;
	mMotion=info.params[0];
	//mSubKind=info.params[1];
	mInterval=info.params[2];
	mEnd=info.params[3];
	mDelta=info.params[4];
	if(mInterval<=0)mInterval=1;
}

#endif