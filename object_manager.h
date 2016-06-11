#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
class CObjectManager{//インターフェイス
protected:
	static const CCreateInfo defaultCreateInfo;
	std::list<CGameObject*> mObjectList;
	CImage32* mImages;
	CImageDIB* m_bg;
public:
	CObjectManager(){m_bg=CImageDIB::GetInstance();}
	//template <typename T> void Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info=defaultCreateInfo);
	template <typename T> void Create(int x,int y,int kind,int sub_kind,double vx,double vy,const CCreateInfo& info=defaultCreateInfo);
	template <typename T> void Update();
	void DeleteCheck();
	void Reset();
};
const CCreateInfo CObjectManager::defaultCreateInfo;
void CObjectManager::DeleteCheck(){

}
/*
template <typename T> void CObjectManager::Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info){
	T* obj=new T();
	obj->Create(x,y,kind,vx,vy,info);
	mObjectList.push_back(obj);
}*/
template <typename T> void CObjectManager::Create(int x,int y,int kind,int sub_kind,double vx,double vy,const CCreateInfo& info){
	T* obj=new T();
	obj->Create(x,y,kind,sub_kind,vx,vy,info);
	mObjectList.push_back(obj);
}

template <typename T> void CObjectManager::Update(){
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		T* obj = (T*)*it;
		obj->Update();
		if(!(*it)->isDeleted()){
			obj->Blt(m_bg,&mImages[obj->GetImgId()]);
		}
		if((*it)->isDeleted()){
			delete *it;
			it=mObjectList.erase(it);
		}else{
			it++;
		}
	}
}

void CObjectManager::Reset(){
	mObjectList.clear();
}
#endif