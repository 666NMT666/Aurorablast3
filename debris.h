const int DEBRIS_FILES=4;
const TEffectFileData DEBRIS_FILE[DEBRIS_FILES]={ 
	{"dat/img/debris/effect-particle1.bmp",7,7,20,BLT_ADD}, //
	{"dat/img/debris/effect-particle2.bmp",14,14,8,BLT_ADD}, //
	{"dat/img/debris/effect-particle4.bmp",16,16,6,BLT_KEY}, //
	{"dat/img/dummy.bmp",1,1,6,BLT_NULL}, //
};

class CDebris:public CGameObject{
	protected:
	int mCycleNum;
	int mMotion,mSubKind,mInterval,mEnd,mDelta;
	CEffectManager* mEffectManager;
public:
	CDebris():CGameObject(),mCycleNum(1),mMotion(0),mSubKind(0),mInterval(0),mEnd(0),mDelta(0){
		Reset();
		mEffectManager=CEffectManager::GetInstance();
	}
	void Reset(){ResetGameObject();}
	void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info=defaultCreateInfo);
};

void CDebris::Update(){
	UpdateGameObject();
	if(mTimer==1){
		mCounter=rand()%mCycleNum;
	}
	if(mInterval==0){
		mInterval=1;
	}
	int cycleId=(mTimer/mInterval+mCounter)%mCycleNum;
	if(mKind==1){
		CVector r1(m_x,m_y);
		CVector r2(mPrevX,mPrevY);
		CVector r3((mPrevX+m_x)/2,(m_y+mPrevY)/2+10);
		CTriangle::fillTriangle(m_bg,r1,r2,r3,0xFF6600,BATTLE_RECT);
	} else if(mKind==2){
		mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_40_2,0,0,0,0,1,0,0);
	} else if(mKind==3){
		CVector r1(m_x,m_y);
		CVector r2(mPrevX,mPrevY);
		int pm=(rand()%2==0)?1:-1;
		CVector r3(mPrevX+4*pm,mPrevY);
		CTriangle::fillTriangle(m_bg,r1,r2,r3,0xFFFF88,BATTLE_RECT);
	}
	mBltY=(cycleId+mSubKind*mCycleNum)*m_height;
	if(mTimer>=mEnd){mDelFlg=true;}
}

void CDebris::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	mImgId=kind;
	mBltInfo=info.bltInfo;
	mDelFlg=false;
	m_width=DEBRIS_FILE[kind].width;
	m_height=DEBRIS_FILE[kind].height;
	mCycleNum=DEBRIS_FILE[kind].numCycle;
	mBltInfo.type=(TBltType)DEBRIS_FILE[kind].type;
	mMotion=info.params[0];
	mSubKind=subKind;
	//mSubKind=info.params[1];
	mInterval=info.params[2];
	mEnd=info.params[3];
	mDelta=info.params[4];
}