class CItem:public CEnemySideObject{
protected:
	bool mGetFlg;
	int mGetCounter;
	CGameInfo* mGameInfo;
	int mExt, mPoint;
public:
	CItem():CEnemySideObject(),mGetFlg(false),mGetCounter(0){
		mPlayer=CPlayer::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		mExt=mPoint=0;
	}
	void Update();
	void Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info=defaultCreateInfo);
	void itemExtendChip();
	void itemExtendChip3();
	void itemExtendChip4();
	void itemBomb();
	void setPoints(int ext, int point) {
		mExt = ext;
		mPoint = point;
		if (mGameInfo->GetStage() == 3) {
			mPoint *= 3;
			mExt *= 3;
		}
	}
};

void CItem::Update(){
	UpdateGameObject();
	if(mKind==0){itemExtendChip();}
	else if(mKind==1){itemExtendChip();}
	else if(mKind==2){itemExtendChip3();}
	else if(mKind==3){itemExtendChip4();}
	else if(mKind==4){itemBomb();}
}

void CItem::Create(int x,int y,int kind,int subKind,double vx,double vy,const CCreateInfo& info){
	double dvy=(kind!=3)?(10.0)*(4-mGameInfo->GetLevel()):20.0;
	if(kind==4)dvy=0;
	CreateGameObject(x,y,kind,subKind,vx,vy+dvy);
	mImgId=kind;
	mDelFlg=false;
	mAutoDelFlg=true;
}

void CItem::itemExtendChip(){
	if(mGetFlg==false){
		ForceFriction(0.9, 0.875);
		if (mTimer++<15 + 5 * (4 - mGameInfo->GetLevel())) {
			m_vy -= 0.375;
			if (m_vy < -4.0) m_vy = -4.0;
		}
		else { m_vy -= 0.125; }
	}else
		SetVelTo(10.0, mPlayer->GetX(), mPlayer->GetY());

	int rad=260-mGameInfo->GetLevel()*10;
	if(mTimer>8 && (abs(mPlayer->GetX()-m_x)<rad && abs(mPlayer->GetY()-m_y)<rad)){ mGetFlg=true; }

	if(HitRadius(100)==true){
		mDelFlg=true;
		mPlayer->ItemGet(mExt,mPoint);
	}
}

void CItem::itemExtendChip3(){ // ‘åƒAƒCƒeƒ€
	if (mGetFlg == false) {
		ForceFriction(0.85, 0.875);
		if (mTimer++<15) {
			m_vy -= 0.475;
			if (m_vy < -6.0) m_vy = -6.0;
		}
		else { m_vy -= 0.475; }
	}
	else
		SetVelTo(10.0, mPlayer->GetX(), mPlayer->GetY());

	int rad = 160;
	if (mTimer>8 && (abs(mPlayer->GetX() - m_x)<rad && abs(mPlayer->GetY() - m_y)<rad)) {
		mGetFlg = true;
	}

	if(HitRadius(100)==true){
		mDelFlg=true;
		mGameInfo->addInnerRank(1);
		mPlayer->ItemGet(mExt, mPoint);
	}
}

void CItem::itemExtendChip4(){
	if(mGetFlg==false){
		if(mTimer++ >= 15+5*4){ m_vy+=0.125; }
		m_vx*=0.9;
	} else 
		SetVelTo(10.0, mPlayer->GetX(), mPlayer->GetY());
	
	int rad=70;
	if(mTimer>8 && (abs(mPlayer->GetX()-m_x)<rad && abs(mPlayer->GetY()-m_y)<rad)){ mGetFlg=true; }
	if(HitRadius(50)==true){
		mDelFlg=true;
		mPlayer->ItemGet(mExt, mPoint);
	}
}

void CItem::itemBomb(){
	BackLightSmall();
	if(m_x<=BATTLE_LEFT || m_x>=BATTLE_RIGHT){ m_vx *= -1; }
	if (m_y <= BATTLE_TOP || m_y >= BATTLE_BOTTOM) { m_vy *= -1; }
	if(HitRadius(120)==true){
		mDelFlg=true;
		mPlayer->ItemGetBomb();
		mSE->PlaySingleSound(SE_POW1);
	}
}
