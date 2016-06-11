class CEnemyLazerManager:public CObjectManager{
	static CEnemyLazerManager* instance;
public:
	CEnemyLazerManager();
	~CEnemyLazerManager(){delete[] mImages;}
	static CEnemyLazerManager* GetInstance(){return instance;} // �B��̃C���X�^���X
};

CEnemyLazerManager* CEnemyLazerManager::instance = new CEnemyLazerManager();
CEnemyLazerManager::CEnemyLazerManager():CObjectManager(){
	mImages=new CImage32[1];
	CImageFactory::InitBitmap(&mImages[0],LZ_FILE[0]);
}
