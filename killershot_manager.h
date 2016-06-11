class CKillershotManager:public CObjectManager{
	static CKillershotManager* instance;
public:
	CKillershotManager();
	~CKillershotManager(){delete[] mImages;}
	static CKillershotManager* GetInstance(){return instance;} // 唯一のインスタンス
};

CKillershotManager* CKillershotManager::instance = new CKillershotManager();
CKillershotManager::CKillershotManager():CObjectManager(){
	mImages=new CImage32[2];
	//CImageFactory::InitBitmap(&mImages[0],EB_FILE[0]);
}

