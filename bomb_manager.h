class CBombManager:public CObjectManager{
protected:
	static CBombManager* instance;
public:
	CBombManager();
	~CBombManager(){delete[] mImages;}
	static CBombManager* GetInstance(){return instance;} // 唯一のインスタンス
	bool HitTestRect(RECT rc,int dx=0,int dy=0);
};

CBombManager* CBombManager::instance = new CBombManager();

CBombManager::CBombManager():CObjectManager(){
	mImages=new CImage32[BOMB_FILES];
	for(int i=0;i<BOMB_FILES;i++)
		CImageFactory::InitBitmap(&mImages[i],BOMB_FILE[i].fname);
}

bool CBombManager::HitTestRect(RECT rc,int dx,int dy){
	bool hitFlg=false;
	rc.left+=dx;
	rc.right+=dx;
	rc.top+=dy;
	rc.bottom+=dy;
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CBomb* bullet = (CBomb*)(*it);
		RECT rc2={
			bullet->GetX()-bullet->GetWidth()/2,bullet->GetY()-bullet->GetHeight()/2,
			bullet->GetX()+bullet->GetWidth()/2,bullet->GetY()+bullet->GetHeight()/2};
		if(OVERRAP_RECT(rc,rc2)){
			hitFlg=true;
			bullet->Hit();
		}
		it++;
	}
	return hitFlg;
}

