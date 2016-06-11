#ifndef DEBRIS_MANAGER_H
#define DEBRIS_MANAGER_H 
class CDebrisManager:public CObjectManager{
	static const int MAX_DEBRIS=200;
	static CDebrisManager* instance;
public:
	CDebrisManager();
	~CDebrisManager(){delete[] mImages;}
	static CDebrisManager* GetInstance(){return instance;} // インスタンス
	void CreateDebris(int x,int y,int kind,int subKind,double vx,double vy,int motion=0,int subId=0,int interval=0,int end=0,int delta=0);
};
CDebrisManager* CDebrisManager::instance = new CDebrisManager();

CDebrisManager::CDebrisManager():CObjectManager(){
	mImages=new CImage32[DEBRIS_FILES];
	for(int i=0;i<DEBRIS_FILES;i++)
		CImageFactory::InitBitmap(&mImages[i],DEBRIS_FILE[i].fname.c_str());
}

void CDebrisManager::CreateDebris(int x,int y,int kind,int subKind,double vx,double vy,int motion,int subId,int interval,int end,int delta){
	CDebris* obj=new CDebris();
	int p[5]={motion,subId,interval,end,delta};
	CBltInfo bi;
	CCreateInfo info(p,bi);
	obj->Create(x,y,kind,subKind,vx,vy,info);
	mObjectList.push_back(obj);
}
#endif