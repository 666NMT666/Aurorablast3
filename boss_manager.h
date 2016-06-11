class CBossManager:public CObjectManager{
	protected:
	static CBossManager* instance;
public:
	CBossManager():CObjectManager(){
		mImages=new CImage32[BOSS_FILES];
		for(int i=0;i<BOSS_FILES-1;i++)
			CImageFactory::InitBitmap(&mImages[i],BOSS_FILE[i].fname);
	}
	~CBossManager(){delete[] mImages;}
	static CBossManager* GetInstance(){return instance;} // 唯一のインスタンス
	bool isStageEnd();

	int GetBossBackground(){
		if(mObjectList.empty())return -1;
		std::list<CGameObject*>::iterator it = mObjectList.begin();
		CBoss* boss=(CBoss*)(*it);
		return boss->GetBackground();
	}

	int GetBossExLife(){
		if(mObjectList.empty())return -1;
		std::list<CGameObject*>::iterator it = mObjectList.begin();
		CBoss* boss=(CBoss*)(*it);
		return boss->GetExLife();
	}

	int GetBossTimer(){
		if(mObjectList.empty())return -1;
		std::list<CGameObject*>::iterator it = mObjectList.begin();
		CBoss* boss=(CBoss*)(*it);
		return boss->GetTimer();
	}
};
CBossManager* CBossManager::instance = new CBossManager();

bool CBossManager::isStageEnd(){
	if(mObjectList.empty())return false;
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	CBoss* boss=(CBoss*)(*it);
	if(boss->isStageEnd())return true;
	else return false;
}