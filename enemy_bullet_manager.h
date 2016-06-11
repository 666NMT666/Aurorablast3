class CEnemyBulletManager:public CObjectManager{
	static CEnemyBulletManager* instance;
public:
	CEnemyBulletManager();
	~CEnemyBulletManager(){delete[] mImages;}
	static CEnemyBulletManager* GetInstance(){return instance;} // 唯一のインスタンス
	void KillAllBullet();
};

CEnemyBulletManager* CEnemyBulletManager::instance = new CEnemyBulletManager();
CEnemyBulletManager::CEnemyBulletManager():CObjectManager(){
	mImages=new CImage32[NUM_EB_FILES];
	for(int i=0;i<NUM_EB_FILES;i++) CImageFactory::InitBitmap(&mImages[i],EB_FILE[i].fname);
}

void CEnemyBulletManager::KillAllBullet(){
	Reset();
}