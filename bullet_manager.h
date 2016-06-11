class CBulletManager:public CObjectManager{
protected:
	static CBulletManager* instance;
public:
	CBulletManager();
	~CBulletManager(){delete[] mImages;}
	static CBulletManager* GetInstance(){return instance;} // 唯一のインスタンス
	bool HitTestRect(RECT rc,int dx=0,int dy=0);
	bool HitTestRectWithKind(RECT rc,int k,int dx=0,int dy=0);
	int GetHitTop(){return CBullet::GetHitTop();}
	//void CreateBullet();
	//(int x, int y, TBulletKind kind, int subKind, double vx, double vy, TBulletForm form, int angle)
};

CBulletManager* CBulletManager::instance = new CBulletManager();

CBulletManager::CBulletManager():CObjectManager(){
	mImages=new CImage32[BULLET_FILES];
	for(int i=0;i<BULLET_FILES;i++)
		CImageFactory::InitBitmap(&mImages[i],BULLET_FILE[i].fname);
}

bool CBulletManager::HitTestRect(RECT rcEnemy,int dx,int dy){
	bool hitFlg=false;
	rcEnemy.left+=dx;
	rcEnemy.right+=dx;
	rcEnemy.top+=dy;
	rcEnemy.bottom+=dy;
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CBullet* bullet = (CBullet*)(*it);
		RECT rcBullet={
			bullet->GetX()-bullet->GetWidth()/2,
			bullet->GetY()-bullet->GetHeight()/2,
			bullet->GetX()+bullet->GetWidth()/2,
			bullet->GetY()+bullet->GetHeight()/2};
		if(OVERRAP_RECT(rcEnemy, rcBullet)){
			hitFlg=true;
			bullet->Hit();
		}
		it++;
	}
	return hitFlg;
}

bool CBulletManager::HitTestRectWithKind(RECT rc,int k,int dx,int dy){
	bool hitFlg=false;
	rc.left+=dx;
	rc.right+=dx;
	rc.top+=dy;
	rc.bottom+=dy;
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CBullet* bullet = (CBullet*)(*it);
		RECT rc2={
			bullet->GetX()-bullet->GetWidth()/2,
			bullet->GetY()-bullet->GetHeight()/2,
			bullet->GetX()+bullet->GetWidth()/2,
			bullet->GetY()+bullet->GetHeight()/2};
		if(bullet->GetKind()!=k){
			it++;
			continue;
		}
		if(OVERRAP_RECT(rc,rc2)){
			hitFlg=true;
			bullet->Shielded();
		}
		it++;
	}
	return hitFlg;
}
