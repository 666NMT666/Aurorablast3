class CEnemyMissileManager:public CObjectManager{
	static CEnemyMissileManager* instance;
public:
	CEnemyMissileManager();
	~CEnemyMissileManager(){delete[] mImages;}
	static CEnemyMissileManager* GetInstance(){return instance;} // �B��̃C���X�^���X
};

CEnemyMissileManager* CEnemyMissileManager::instance = new CEnemyMissileManager();
CEnemyMissileManager::CEnemyMissileManager():CObjectManager(){
	mImages=new CImage32[EMISSILE_FILES];
	for(int i=0;i<EMISSILE_FILES;i++)CImageFactory::InitBitmap(&mImages[i],EMISSILE_FILE[i].fname);
}