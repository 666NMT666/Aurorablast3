class CEnemySideObject:public CGameObject{
protected:
	bool mInvincibleFlg;
	CPlayer* mPlayer;
	CCreateInfo mCreateInfo;
	CBulletManager* mBulletManager;
	CBombManager* mBombManager;
	CEffectManager* mEffectManager;
	CDebrisManager* mDebrisManager;
	CEffectManager* mFrontEffectManager;
	CEffectManager* mBackEffectManager;
	CSoundEffect* mSE;
	RECT mHitPadding;
public:
	CEnemySideObject():CGameObject(),mInvincibleFlg(false){
		mPlayer=CPlayer::GetInstance();
		mSE=CSoundEffect::GetInstance();
		mEffectManager=CEffectManager::GetInstance();
		mFrontEffectManager=CEffectManager::GetInstance2();
		mBackEffectManager=CEffectManager::GetInstance3();
		mBulletManager=CBulletManager::GetInstance();
		mBombManager=CBombManager::GetInstance();
		mDebrisManager=CDebrisManager::GetInstance();
		mHitPadding.left=0;
		mHitPadding.top=0;
		mHitPadding.right=0;
		mHitPadding.bottom=0;
	}
	bool HitRadius(int r);
	bool HitRadius(int tx,int ty,int r);
	bool HitRect(RECT rc);
	void SampleExplosion2(int x,int y);
	void SampleExplosion(int x,int y);
	void StageRevision(){
		m_y=ExMath::internalDividingPoint((int)(m_y0+200),(int)(m_y0-200),mPlayer->GetY(),480-mPlayer->GetY());
	}

	
	void BackLightSmall(int subKind=0){
		mBackEffectManager->DrawEffect(m_bg,m_x,m_y,EFFECT_BACKLIGHT1,subKind,BLT_ADD,255);
	}
	void BackLightSmall(int x,int y,int subKind=0){
		mBackEffectManager->DrawEffect(m_bg,x,y,EFFECT_BACKLIGHT1,subKind,BLT_ADD,255);
	}
	void BackLightMedium(int subKind=0){
		mBackEffectManager->DrawEffect(m_bg,m_x,m_y,EFFECT_BACKLIGHT3,subKind,BLT_ADD,255);
	}
	void BackLightMedium(int x,int y,int subKind=0){
		mBackEffectManager->DrawEffect(m_bg,x,y,EFFECT_BACKLIGHT3,subKind,BLT_ADD,255);
	}
	void BackLightLarge(int subKind=0){
		mBackEffectManager->DrawEffect(m_bg,m_x,m_y,EFFECT_BACKLIGHT4,subKind,BLT_ADD,255);
	}
	void BackLightLarge(int x, int y, int subKind = 0) {
		mBackEffectManager->DrawEffect(m_bg, x, y, EFFECT_BACKLIGHT4, subKind, BLT_ADD, 255);
	}
	void BackLightLargeEx(int x, int y, int subKind = 0) {
		mBackEffectManager->DrawEffect(m_bg, x, y, EFFECT_BACKLIGHT4, subKind, BLT_ADD, 255);
	}

	CVector GetVectorToPlayer(double amp) {
		double dx = mPlayer->GetX() - m_x;
		double dy = mPlayer->GetY() - m_y;
		double x = amp * dx / sqrt(dx*dx + dy*dy);
		double y = amp * dy / sqrt(dx*dx + dy*dy);
		CVector v(x, y);
		return v;
	}

};
void CEnemySideObject::SampleExplosion2(int x,int y){
	const TEffectFile e[2] = { EFFECT_EXPLOSION_LIGHT_40 ,EFFECT_EXPLOSION_LIGHT_80 };
	for (int i = 0; i < 20; i++) mBackEffectManager->CreateEffect(x, y, e[rand() % 2], 0, rand() % 20 - 10, rand() % 20 - 10, 0, 2, 0, 0);
}
void CEnemySideObject::SampleExplosion(int x,int y){
	const TEffectFile e[2] = { EFFECT_EXPLOSION_LIGHT_40 ,EFFECT_EXPLOSION_LIGHT_80 };
	for (int i = 0; i < 20; i++)mEffectManager->CreateEffect(x, y, e[rand() % 2], 0, rand() % 20 - 10, rand() % 20 - 10, 0, 2, 0, 0);
}

bool CEnemySideObject::HitRadius(int tx,int ty,int r){
	int left  =(int)tx-r/2;
	int right =(int)tx+r/2;
	int top   =(int)ty-r/2;
	int bottom=(int)ty+r/2;
	return (mPlayer->GetX() > left && mPlayer->GetX() < right 
		&& mPlayer->GetY() < bottom && mPlayer->GetY() > top);
}
bool CEnemySideObject::HitRadius(int r){
	return HitRadius((int)m_x,(int)m_y,r);
}

bool CEnemySideObject::HitRect(RECT rc){
	int x=(rc.right+rc.left)/2;
	int y=(rc.bottom+rc.top)/2;
	int w=(rc.right-rc.left)/2;
	int h=(rc.bottom-rc.top)/2;
	int dx=abs(x-mPlayer->GetX());
	int dy=abs(y-mPlayer->GetY());
	return (dx<w && dy<h);
}
