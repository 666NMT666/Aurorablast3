typedef struct _TItemFile {
	char fname[64];
	int width;
	int height;
	int ext;
	int point;
} TItemFile;

#include "item.h"
class CItemManager:public CObjectManager{
	protected:
	static CItemManager* instance;
	static CItemManager* instance2;
	TItemFile* ITEM_FILE;
public:
	CItemManager();
	~CItemManager(){delete[] mImages;}
	static CItemManager* GetInstance(){return instance;} // インスタンス
	static CItemManager* GetInstanceFront(){return instance2;} // インスタンス
	bool HitTestRect(RECT rc);
	void CreateItem(int x, int y, int kind, int subKind, double vx, double vy);
};
CItemManager* CItemManager::instance = new CItemManager();
CItemManager* CItemManager::instance2 = new CItemManager();

CItemManager::CItemManager():CObjectManager(){
	CCsvUtil csv("dat/dat/item.csv", 3);
	int length = csv.getNumLows();
	mImages=new CImage32[length];
	ITEM_FILE = new TItemFile[length];
	for (int i = 0; i < length; i++) {
		CImageFactory::InitBitmap(&mImages[i], csv.get(i, 0).c_str());
		ITEM_FILE[i].width = mImages[i].Width();
		ITEM_FILE[i].height = mImages[i].Height();
		ITEM_FILE[i].ext = std::stoi(csv.get(i, 1));
		ITEM_FILE[i].point = std::stoi(csv.get(i, 2));
	}
}

void CItemManager::CreateItem(int x, int y, int kind, int subKind, double vx, double vy) {
	CItem* obj = new CItem();
	CCreateInfo info;
	obj->Create(x, y, kind, subKind, vx, vy, info);
	obj->SetSize(ITEM_FILE[kind].width, ITEM_FILE[kind].height);
	obj->setPoints(ITEM_FILE[kind].ext, ITEM_FILE[kind].point);
	mObjectList.push_back(obj);
}

