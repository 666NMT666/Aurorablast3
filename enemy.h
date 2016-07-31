#include <string>

typedef struct _TEnemyFile{
	std::string fname;
	std::string short_fname;
	int width;
	int height;
	int life;
	int front_parts;
	int back_parts;
} TEnemyFile;


class CEnemy:public CEnemySideObject{
protected:
	bool mStanFlg;
	bool mDisabledFlg;
	static CImage32* mPartsImg;
	int mGameLevel,mLife,mLife0,mExLife;
	int mMaxBackParts,mMaxParts;
	int mRandom;
	bool mReverseFlg,mLandscapeFlg;
	int mLandHeight;
	int mKilledTimer;
	int mHitCounter;
	RECT mRectBulletHit;
	RECT mRectPlayerHit;
	TSingleSound mKilledSound;
	CEnemyBulletManager* mEBManager;
	CEnemyMissileManager* mEMManager;
	CEnemyLazerManager* mELManager;
	CItemManager* mItemManager;
	CItemManager* mItemManagerFront;
	CEnemyParts* mBackParts;
	CEnemyParts* mParts;
	CGameInfo* mGameInfo;
	bool isInPartsCircle(int i, int r);
	bool isInBackPartsCircle(int i, int r);
public:
	static void LoadPartsFiles(){
		CCsvUtil csv("dat/dat/enemy_parts.csv", 7);
		if (csv.getNumLows() - 1 != ENEMY_PARTS_FILES) {exit(0);}
		ENEMY_PARTS_DATA = new TEnemyPartsFile[csv.getNumLows() - 1];
		mPartsImg = new CImage32[csv.getNumLows() - 1];
		for (int i = 1; i < csv.getNumLows(); i++) {
			int j = i - 1;
			ENEMY_PARTS_DATA[j].fname = csv.get(i, 0);
			ENEMY_PARTS_DATA[j].startX = std::stoi(csv.get(i, 1));
			ENEMY_PARTS_DATA[j].startY = std::stoi(csv.get(i, 2));
			ENEMY_PARTS_DATA[j].endX   = std::stoi(csv.get(i, 3));
			ENEMY_PARTS_DATA[j].endY   = std::stoi(csv.get(i, 4));
			ENEMY_PARTS_DATA[j].width  = std::stoi(csv.get(i, 5));
			ENEMY_PARTS_DATA[j].height = std::stoi(csv.get(i, 6));
			mPartsImg[j].load(ENEMY_PARTS_DATA[j].fname.c_str());
		}
	}
	CEnemy():CEnemySideObject(),mLife(2),mLife0(2),mExLife(0),mMaxBackParts(0),mMaxParts(0),mGameLevel(0),mDisabledFlg(false){
		mItemManager=CItemManager::GetInstance();
		mItemManagerFront=CItemManager::GetInstanceFront();
		mEBManager=CEnemyBulletManager::GetInstance();
		mEMManager=CEnemyMissileManager::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		mELManager=CEnemyLazerManager::GetInstance();
		mReverseFlg=false;
		mRandom=rand();
		mLandHeight=0;
		mKilledTimer=0;
		mHitCounter=0;
		mStanFlg = false;
	}
	void Update();
	void UpdateBasic();
	void UpdateStan();
	virtual void UpdateEnemy(){}
	virtual void UpdateEnemyPre(){}
	void Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info, TEnemyFile& data);
	virtual void CreateEnemy(){}
	virtual void Killed();
	void Blt(CImage32* dest,CImage32* img);

	void AngleShot(double x,double y,int kind,int subKind,double vel,int angle,int life=0){
		AngleShot((int)x,(int)y,kind,subKind,vel,angle,life);
	}
	void AngleShot(int x,int y,int kind,int subKind,double vel,int angle,int life=0);

	void NormalShot(double x,double y,int kind,int subKind,double vel,int life=0,int d_angle=0){
		NormalShot((int)x,(int)y,kind,subKind,vel,life,d_angle);
	}
	void NormalShot(int x,int y,int kind,int subKind,double vel,int life=0,int d_angle=0);

	void NormalShotD(int x,int y,int kind,int subKind,double vel,int d_angle=0);

	void AngleMissile(int x,int y,int imgKind,int subKind,int motionKind,double vel,int angle,int p3,int p4,int p5);
	void AngleMissile(int x,int y,int kind,int kind2,double vel,int angle,int p3=0,int p4=0,int p5=0);
	void AngleMissile(int x,int y,int kind,int kind2,double vel,int angle,const CCreateInfo& info);

	void SetVOnDirection(double v);
	void SetVTo(int x,int y,double v);
	void SetVToPlayer(double v);
	void DirectTo(int tx,int ty);
	void DirectToPlayer();
	void DirectWithVel();
	void DirectFrontPartsTo(int i,int tx,int ty);
	void DirectBackPartsTo(int i,int tx,int ty);
	const int GetShotAngleFromBltAngle() { return 90 - mBltInfo.angle; };//Parts[0].GetAngle()-90
	const int GetShotAngleFromPartsAngle(int i) { return 90 - mParts[i].GetAngle(); }
	const int GetShotAngleFromBackPartsAngle(int i) { return 90 - mBackParts[i].GetAngle(); }
	CVector GetFrontPartsHead(int i);
	CVector GetBackPartsHead(int i);

	void LinkFrontPartsToMain(int i,int angle){ LinkFrontPartsToMain(i,angle,(int)m_x,(int)m_y); }

	void LinkFrontPartsToMain(int i,int angle,int ex,int ey){
		mParts[i].SetAngle(angle);
		CVector v(ex-m_x, ey-m_y);
		v.Rotate(N_PI*mBltInfo.angle);
		mParts[i].SetTargetPos((int)(m_x+v.x),(int)(m_y+v.y));
	}

	void LinkFrontParts(int i,int to,int angle,int ex,int ey){
		mParts[i].SetAngle(angle);
		CVector v(ex-mParts[to].GetStartX(), ey-mParts[to].GetStartY());
		v.Rotate(N_PI*mParts[to].GetAngle());
		mParts[i].SetTargetPos(mParts[to].GetTargetX()+(int)v.x,mParts[to].GetTargetY()+(int)v.y);
	}

	void LinkFrontParts(int i,int to,int angle){
		LinkFrontParts(i,to,angle,mParts[to].GetEndX(),mParts[to].GetEndY());
	}
	void LinkBackPartsToFrontParts(int i,int to,int angle,int ex,int ey){
		mBackParts[i].SetAngle(angle);
		CVector v(ex-mParts[to].GetStartX(), ey-mParts[to].GetStartY());
		v.Rotate(N_PI*mParts[to].GetAngle());
		mBackParts[i].SetTargetPos(mParts[to].GetTargetX()+(int)v.x,mParts[to].GetTargetY()+(int)v.y);
	}
	void LinkBackPartsToFrontParts(int i,int to,int angle){
		LinkBackPartsToFrontParts(i,to,angle,mParts[to].GetEndX(),mParts[to].GetEndY());
	}
	void LinkFrontPartsToBackParts(int i,int to,int angle,int ex,int ey){
		mParts[i].SetAngle(angle);
		CVector v(ex-mBackParts[to].GetStartX(), ey-mBackParts[to].GetStartY());
		v.Rotate(N_PI*mBackParts[to].GetAngle());
		mParts[i].SetTargetPos(mBackParts[to].GetTargetX()+(int)v.x,mBackParts[to].GetTargetY()+(int)v.y);
	}
	void LinkFrontPartsToBackParts(int i,int to,int angle){
		LinkFrontPartsToBackParts(i,to,angle,mBackParts[to].GetEndX(),mBackParts[to].GetEndY());
	}
	void LinkBackParts(int i,int to,int angle,int ex,int ey){
		mBackParts[i].SetAngle(angle);
		CVector v(ex-mBackParts[to].GetStartX(), ey-mBackParts[to].GetStartY());
		v.Rotate(N_PI*mBackParts[to].GetAngle());
		mBackParts[i].SetTargetPos(mBackParts[to].GetTargetX()+(int)v.x,mBackParts[to].GetTargetY()+(int)v.y);
	}
	void LinkBackParts(int i,int to,int angle){
		LinkBackParts(i,to,angle,mBackParts[to].GetEndX(),mBackParts[to].GetEndY());
	}
	int angleBetweenPartsAndPlayer(int i){
		return 180-(int)ExMath::angleBetweenPoints((int)m_x+mParts[i].GetTargetX()-m_width/2,
			-m_height/2+(int)m_y+mParts[i].GetTargetY(),mPlayer->GetX(),mPlayer->GetY());
	}
	int angleBetweenBackPartsAndPlayer(int i){
		return 180-(int)ExMath::angleBetweenPoints((int)m_x+mBackParts[i].GetTargetX()-m_width/2,
			-m_height/2+(int)m_y+mBackParts[i].GetTargetY(),mPlayer->GetX(),mPlayer->GetY());
	}
	bool isLanded(){return mLandscapeFlg;}
	const int GetLandHeight(){return mLandHeight;}

	void ChacePartsAngle(CEnemyParts& parts,int x,int y,int omega){
		CVector v1(parts.GetEndX()-parts.GetStartX(),parts.GetEndY()-parts.GetStartY());
		v1.Rotate(N_PI*(parts.GetAngle()));
		CVector v2(x-(parts.GetTargetX()+m_x-m_width/2),y-(parts.GetTargetY()+m_y-m_height/2));
		if(v1.x*v2.y-v1.y*v2.x<0.0){
			parts.AddAngle(omega);
		}else{
			parts.AddAngle(-omega);
		}
	}
	void PurgeBackParts(int minZoom10, int zoomRange10, int maxVx,int maxVy,int biasVx=0, int biasVy=0) {
		if (mKilledTimer == 1) {
			for (int i = 0; i < mMaxBackParts; i++) {
				mBackParts[i].SetVel((double)(rand() % maxVx - maxVx / 2 + biasVy), (double)(rand() % maxVy - maxVy / 2 + biasVy));
			}
		}
		for (int i = 0; i < mMaxBackParts; i++) {
			mBackParts[i].SetAngle(rand() % 360);
			mBackParts[i].Move();
			if (zoomRange10 <= 0)continue;
			double zoom = (double)(minZoom10 + rand() % zoomRange10)*0.1;
			mBackParts[i].SetZoom(zoom);
		}
	}
	void PurgeParts(int minZoom10, int zoomRange10, int maxVx, int maxVy, int biasVx = 0, int biasVy = 0) {
		if (mKilledTimer == 1) {
			for (int i = 0; i < mMaxBackParts; i++) {
				mBackParts[i].SetVel((double)(rand() % maxVx - maxVx / 2 + biasVy), (double)(rand() % maxVy - maxVy / 2 + biasVy));
			}
		}
		for (int i = 0; i < mMaxParts; i++) {
			mParts[i].SetAngle(rand() % 360);
			mParts[i].Move();
			if (zoomRange10 <= 0)continue;
			double zoom = (double)(minZoom10 + rand() % zoomRange10)*0.1;
			mParts[i].SetZoom(zoom);
		}
	}
};
CImage32* CEnemy::mPartsImg=new CImage32[ENEMY_PARTS_FILES];

void CEnemy::UpdateStan() {
	int rot= m_x0 / 23-12;
	mBltInfo.angle = rot * mTimer / 10;
}

void CEnemy::UpdateBasic(){
	m_x+=m_vx; m_y+=m_vy;
	mBltInfo.type=BLT_KEY;
	for(int i=0;i<mMaxBackParts;i++){ mBackParts[i].SetBltType(BLT_KEY); }
	for(int i=0;i<mMaxParts;i++){mParts[i].SetBltType(BLT_KEY);}
	if(mBulletManager->HitTestRect(mRectBulletHit,m_x,m_y) || mBombManager->HitTestRect(mRectBulletHit,m_x,m_y)){
		if(mPlayer->GetWepon()==1){
			for(int j=0;j<5;j++)mItemManagerFront->CreateItem(mPlayer->GetX()+rand()%60-30,m_y,3,0,rand()%40-20,-rand()%6);
		}
		if(mInvincibleFlg==false){
			mLife--;
			mHitCounter++;
			if(mPlayer->GetWepon()==1)mLife--;
			mSE->PlayLoopSound(SE_KEZ2);
			if(mTimer%3==0){
				mBltInfo.type=BLT_RED;
				for(int i=0;i<mMaxBackParts;i++){ mBackParts[i].SetBltType(BLT_RED); }
				for(int i=0;i<mMaxParts;i++){mParts[i].SetBltType(BLT_RED);}
			}
		}else{
			//mSE->PlayLoopSound(SE_SLD1);
		}
	}
	if(CExRect::isTargetInRect(&mRectPlayerHit,mPlayer->GetX(),mPlayer->GetY(),m_x,m_y)){
		mPlayer->ForcePlayer(0,14);
	}
	if(mLife<=0){
		Killed();
		mKilledTimer++;
	}
	if(!CExRect::isInRect(&mRectScreenOut,m_x,m_y)){
		mDelFlg=true;
		mGameInfo->minusInnerRank(1);
	}
}
void CEnemy::Update(){
	UpdateEnemyPre();
	UpdateBasic();
	if (mStanFlg) UpdateStan();
	else if(mLife>0) UpdateEnemy();
	UpdateGameObject();
}

void CEnemy::Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info, TEnemyFile& data){
	CreateGameObject(x,y,kind,vx,vy);
	mImgId=kind;
	mDelFlg=false;
	m_vx=vx; m_vy=vy;
	m_width= data.width;
	m_height= data.height;
	mLife= data.life + mGameInfo->getInnerRank()/32;
	mLife0=mLife;
	mLandscapeFlg=false;
	mMaxParts= data.front_parts;
	mMaxBackParts= data.back_parts;
	mKilledSound=SE_EXP2;
	mHitPadding.left=mHitPadding.top=mHitPadding.right=mHitPadding.bottom=0;
	mCreateInfo=info;
	mGameLevel=mGameInfo->GetLevel() + mGameInfo->getInnerRank() / 10;
	if(mPlayer->GetLife()>3)mGameLevel++;
	if(mGameLevel>4)mGameLevel=4;
	if(mMaxBackParts>0){mBackParts=new CEnemyParts[mMaxBackParts];}
	if(mMaxParts>0){mParts=new CEnemyParts[mMaxParts];}
	CExRect::InitRect(&mRectBulletHit,-m_width/2,-m_height/2,m_width/2,m_height/2);
	CExRect::InitRect(&mRectPlayerHit,-m_width/2,-m_height/2,m_width/2,m_height/2-20);
	CExRect::InitRect(&mRectScreenOut,-100-m_width/2,-100-m_height/2,BATTLE_RECT.right+100+m_width/2,BATTLE_RECT.bottom+100+m_height/2);
	CreateEnemy();
	if (mGameInfo->GetStage()) {
		mStanFlg = true;
		mBltInfo.angle = rand() % 360;
		m_vy = (rand() % 150) * 0.1 + 12.0;
		m_vx = (rand() % 100) * 0.1 - 5.0;
	}
}

void CEnemy::Killed(){
	if(mKilledTimer==0){ mSE->PlaySingleSound(mKilledSound); }
	mDelFlg=true;
	mPlayer->DestroyEnemy(16);
}

void CEnemy::NormalShotD(int x,int y,int k,int subKind,double vel,int d_angle){
	if(mDisabledFlg)return;
	int a=(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY())+d_angle;
	int p[5]={1,180-a,0,0,0};
	CCreateInfo info(p);
	mEMManager->Create<CEnemyMissile>(x,y,k,subKind,vel*cos(N_PI*a),vel*sin(N_PI*a),info);
}

void CEnemy::NormalShot(int x,int y,int kind,int subKind,double vel,int life,int d_angle){
	if(mDisabledFlg)return;
	CCreateInfo info=defaultCreateInfo;
	info.params[1]=life;
	int a=(int)ExMath::angleBetweenPoints(x,y,mPlayer->GetX(),mPlayer->GetY())+d_angle;
	mEBManager->Create<CEnemyBullet>(x,y,kind,subKind,vel*cos(N_PI*a),vel*sin(N_PI*a),info);
}

void CEnemy::AngleShot(int x,int y,int kind,int subKind,double vel,int angle,int life){
	if(mDisabledFlg)return;
	CCreateInfo info=defaultCreateInfo;
	info.params[1]=life;
	double vx=vel*cos(N_PI*angle);
	double vy=vel*sin(N_PI*angle);
	mEBManager->Create<CEnemyBullet>(x,y,kind,subKind,vx,vy,info);
}
void CEnemy::AngleMissile(int x,int y,int kind,int kind2,double vel,int angle,const CCreateInfo& info){	
	if(mDisabledFlg)return;
	double vx=vel*cos(N_PI*angle);
	double vy=vel*sin(N_PI*angle);
	mEMManager->Create<CEnemyMissile>(x,y,kind,kind2,vx,vy,info);
}

void CEnemy::AngleMissile(int x,int y,int imgKind,int subKind,double vel,int angle,int p3,int p4,int p5){	
	if(mDisabledFlg)return;
	int p[5]={1,180-angle,p3,p4,p5};
	CCreateInfo info(p);
	double vx=vel*cos(N_PI*angle);
	double vy=vel*sin(N_PI*angle);
	mEMManager->Create<CEnemyMissile>(x,y,imgKind,subKind,vx,vy,info);
}

void CEnemy::AngleMissile(int x,int y,int imgKind,int subKind,int motionKind,double vel,int angle,int p3,int p4,int p5){
	if(mDisabledFlg)return;
	int p[5]={motionKind,180-angle,p3,p4,p5};
	CCreateInfo info(p);
	double vx=vel*cos(N_PI*angle);
	double vy=vel*sin(N_PI*angle);
	mEMManager->Create<CEnemyMissile>(x,y,imgKind,subKind,vx,vy,info);
}

bool CEnemy::isInPartsCircle(int i,int r) {
	TCircle c = { (int)m_x - m_width / 2 + mParts[i].GetTargetX(), (int)m_y - m_height / 2 + mParts[i].GetTargetY() ,r};
	return CExCircle::isInCircle(&c,mPlayer->GetX(),mPlayer->GetY());
}

bool CEnemy::isInBackPartsCircle(int i, int r) {
	TCircle c = { (int)m_x - m_width / 2 + mBackParts[i].GetTargetX(), (int)m_y - m_height / 2 + mBackParts[i].GetTargetY() ,r };
	return CExCircle::isInCircle(&c, mPlayer->GetX(), mPlayer->GetY());
}

void CEnemy::Blt(CImage32* dest,CImage32* img){
	//if(mExLife<0)return;
	if(mMaxBackParts>0){
		for(int i=mMaxBackParts-1;i>=0;i--){
			CImage32* partsImg=(mBackParts[i].GetImgId()==0)?img:&mPartsImg[mBackParts[i].GetImgId()];
			mBackParts[i].Blt((int)m_x-m_width/2+mBackParts[i].GetTargetX()-mBackParts[i].GetStartX(),(int)m_y-m_height/2+mBackParts[i].GetTargetY()-mBackParts[i].GetStartY(),partsImg);
		}
	}

	if(mBltInfo.zoom==1.0 && mBltInfo.angle==0){
		if(mBltInfo.hole_r==0)CImageBlender::Blt(dest, img, &mBltInfo, BATTLE_RECT, (int)m_x - mBltInfo.link_x, (int)m_y - mBltInfo.link_y, mBltX, mBltY, m_width, m_height);
		else CImageBlenderHoled::Blt(dest, img, BATTLE_RECT, (int)m_x - mBltInfo.link_x, (int)m_y - mBltInfo.link_y, m_width, m_height, mBltInfo.hole_x, mBltInfo.hole_y,mBltInfo.hole_r);
	}else if(mBltInfo.zoom!=1.0 && mBltInfo.angle==0)
		CImageBlenderStretch::Blt(dest,img,&mBltInfo,BATTLE_RECT,(int)(m_x-mBltInfo.link_x*mBltInfo.zoom),(int)(m_y-mBltInfo.link_y*mBltInfo.zoom),mBltX,mBltY,m_width,m_height);
	else
		CImageBlenderTexmap::Blt(dest,img,&mBltInfo,BATTLE_RECT,(int)(m_x-mBltInfo.link_x*mBltInfo.zoom),(int)(m_y-mBltInfo.link_y*mBltInfo.zoom),mBltX,mBltY,m_width,m_height);

	if(mMaxParts>0){
		for(int i=0;i<mMaxParts;i++){
			CImage32* partsImg=(mParts[i].GetImgId()==0)?img:&mPartsImg[mParts[i].GetImgId()];
			mParts[i].Blt((int)m_x-m_width/2+mParts[i].GetTargetX()-mParts[i].GetStartX(),(int)m_y-m_height/2+mParts[i].GetTargetY()-mParts[i].GetStartY(),partsImg);
		}
	}
}

void CEnemy::DirectWithVel() {
	DirectTo(m_x + m_vx, m_y + m_vy);
}

void CEnemy::DirectToPlayer(){
	DirectTo(mPlayer->GetX(),mPlayer->GetY());
}
void CEnemy::DirectTo(int tx,int ty){
	mBltInfo.angle=90-(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,tx,ty);
}

void CEnemy::DirectFrontPartsTo(int i,int tx,int ty){
	int angle=90-(int)ExMath::angleBetweenPoints((int)m_x-m_width/2+mParts[i].GetTargetX(),(int)m_y-m_height/2+mParts[i].GetTargetY(),tx,ty);
	mParts[i].SetAngle(angle);
}

void CEnemy::DirectBackPartsTo(int i,int tx,int ty){
	int angle=90-(int)ExMath::angleBetweenPoints((int)m_x-m_width/2+mBackParts[i].GetTargetX(),(int)m_y-m_height/2+mBackParts[i].GetTargetY(),tx,ty);
	mBackParts[i].SetAngle(angle);
}

CVector CEnemy::GetFrontPartsHead(int i){
	CVector v(mParts[i].GetEndX()-mParts[i].GetStartX(), mParts[i].GetEndY()-mParts[i].GetStartY());
	v.Rotate(N_PI*mParts[i].GetAngle());
	v.Add(m_x-m_width/2+mParts[i].GetTargetX(),m_y-m_height/2+mParts[i].GetTargetY());
	return v;
}

CVector CEnemy::GetBackPartsHead(int i){
	CVector v(mBackParts[i].GetEndX()-mBackParts[i].GetStartX(), mBackParts[i].GetEndY()-mBackParts[i].GetStartY());
	v.Rotate(N_PI*mBackParts[i].GetAngle());
	v.Add(m_x-m_width/2+mBackParts[i].GetTargetX(),m_y-m_height/2+mBackParts[i].GetTargetY());
	return v;
}

void CEnemy::SetVOnDirection(double v){    SetVel(CVector::EigenVector(m_vx,m_vy)*v); }
void CEnemy::SetVTo(int x,int y,double v){ SetVel(CVector::TargetVector(m_x,m_y,x,y,v)); }
void CEnemy::SetVToPlayer(double v){       SetVTo(mPlayer->GetX(),mPlayer->GetY(),v); }