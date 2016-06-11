typedef struct _TEBFileData{
	char fname[64];
	int width;
	int height;
	TBltType type;
} TEBFileData;

enum TEBFile{
	EB_10,
	EB_16,
	EB_20,
	EB_26,
	EB_40,
	EB_80,
	EDAB_50,
	EDAB_60,
	EDAB_66,
	EDAB_80,

	NUM_EB_FILES,
};

const int EB_DESTROYABLE[NUM_EB_FILES]={
	2,
	6,
	6,
	5,
	2,
	1
};

const TEBFileData EB_FILE[NUM_EB_FILES]={
	{"dat/img/eb/e-bullets10.bmp",10,10,BLT_KEY},
	{"dat/img/eb/e-bullets16.bmp",16,16,BLT_KEY},
	{"dat/img/eb/e-bullets20.bmp",20,20,BLT_KEY},
	{"dat/img/eb/e-bullets26.bmp",26,26,BLT_KEY},
	{"dat/img/eb/e-bullets40.bmp",40,40,BLT_KEY},
	{"dat/img/eb/e-bullets80.bmp",80,80,BLT_KEY},
	{"dat/img/eb/e-da-bullets50.bmp",50,50,BLT_KEYADD},
	{"dat/img/eb/e-da-bullets60.bmp",60,60,BLT_KEYADD},
	{"dat/img/eb/e-da-bullets66.bmp",66,66,BLT_KEYADD},
	{"dat/img/eb/e-da-bullets80.bmp",80,80,BLT_KEYADD},
};
//include "ebsize.h"
class CEnemyBullet:public CEnemySideObject{
private:
	int mImgRotation;
	bool mDestroyableFlg;////‚±‚ê‚ÅÅŒã‚Ì“ïˆÕ“x’²®‚È params[1]‚Í‹ó‚¢‚Ä‚é
	int mLife;
protected:
	CGameInfo* mGameInfo;
	CBulletManager* mBulletManager;
public:
	CEnemyBullet():CEnemySideObject(),mImgRotation(0),mDestroyableFlg(false),mLife(1){
		mGameInfo=CGameInfo::GetInstance();
		mBulletManager=CBulletManager::GetInstance();
	}
	void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info);
	void SetDelFlg(bool b){mDelFlg=b;}
};

void CEnemyBullet::Update(){
	mBltY=(mSubKind*m_height*4)+(((mImgRotation++)/2)%4)*m_height;
	UpdateGameObject();
	if(mDestroyableFlg){
		RECT rc={(int)m_x-m_width/2,(int)m_y-m_height/2,(int)m_x+m_width/2,(int)m_y+m_height/2};
		if(mBulletManager->HitTestRect(rc) || mBombManager->HitTestRect(rc)){
			mLife--;
			//mSE->PlayLoopSound(SE_KEZ1);
		}
		if(mLife<0)mDelFlg=true;
	}
	//if(mPlayer->isInvincible() && mGameInfo->GetLevel()>1)UpdateGameObject();
	//if(m_x<0 || m_x>660 || m_y<0 || m_y>500)mDelFlg=true;
	/*if(HitRadius(m_width)){
		mDelFlg=true;
		if(!mPlayer->isInvincible())mPlayer->Killed();
	}*/
	if(CHitTest::MovingCircleToPoint((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY(),(int)mPrevX,(int)mPrevY,mPlayer->GetPrevX(),mPlayer->GetPrevY(),m_width/2)){
		mDelFlg=true;
		if(!mPlayer->isInvincible())mPlayer->Killed();
	}
}

void CEnemyBullet::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,subKind,vx,vy);
	mImgId=kind;
	//mImgId=info.params[0]; ‚±‚ê‚É‚æ‚èparam[0]‚ª‹ó‚¢‚½
	mDestroyableFlg=(info.params[1]==0)?false:true;
	mLife=info.params[1];
	mDelFlg=false; mAutoDelFlg=true;
	m_width=EB_FILE[mImgId].width;
	m_height=EB_FILE[mImgId].height;
	mBltInfo.type=EB_FILE[mImgId].type;
}