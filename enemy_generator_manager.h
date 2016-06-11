class CEnemyGeneratorManager:public CObjectManager{
	static CEnemyGeneratorManager* instance;
public:
	CEnemyGeneratorManager();
	~CEnemyGeneratorManager(){delete[] mImages;}
	static CEnemyGeneratorManager* GetInstance(){return instance;} // 唯一のインスタンス
};
CEnemyGeneratorManager* CEnemyGeneratorManager::instance = new CEnemyGeneratorManager();
CEnemyGeneratorManager::CEnemyGeneratorManager():CObjectManager(){
	mImages=new CImage32[GENERATOR_FILES];
	for(int i=0;i<GENERATOR_FILES;i++)
		CImageFactory::InitBitmap(&mImages[i],ENEMY_GENERATOR_DATA[i].fname.c_str());
}
