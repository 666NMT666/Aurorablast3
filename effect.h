#ifndef EFFECT_H
#define EFFECT_H

enum TEffectMotion {
	EFFECT_MOTION_SINGLE,
	EFFECT_MOTION_LOOP,
	EFFECT_MOTION_SINGLE_CYCLE_ZOOM,
	EFFECT_MOTION_SINGLE_CYCLE_ZOOM_IN,
	EFFECT_MOTION_FADE_OUT,
};


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
	void fadeOut();

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

void CEffect::fadeOut() {
	int a = 255 - mTimer*mDelta;
	if (a < 0) {
		a = 0;
		mDelFlg = true;
	}
	mBltInfo.alpha = a;
}

void CEffect::Update(){
	UpdateGameObject();
	if (mMotion == EFFECT_MOTION_SINGLE) { singleCycleFlash(); }
	else if (mMotion == EFFECT_MOTION_LOOP) { loopFlash(); }
	else if (mMotion == EFFECT_MOTION_SINGLE_CYCLE_ZOOM) { singleCycleZoom(); }
	else if (mMotion == EFFECT_MOTION_SINGLE_CYCLE_ZOOM_IN) { singleCycleZoomIn(); }
	else if (mMotion == EFFECT_MOTION_FADE_OUT) { fadeOut(); }
}

void CEffect::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,subKind,vx,vy);
	mImgId=kind;
	mBltInfo=info.bltInfo;
	mDelFlg=false;
	mMotion=info.params[0];
	//mParam1=info.params[1];
	mInterval=info.params[2];
	mEnd=info.params[3];
	mDelta=info.params[4];
	if(mInterval<=0)mInterval=1;
}

#endif