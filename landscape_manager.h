class CLandscapeManager:public CObjectManager{
protected:
	static CLandscapeManager* instance;
	static CLandscapeManager* instance_back;
	static CLandscapeManager* instance_front;
public:
	CLandscapeManager(); //画像初期化
	~CLandscapeManager(){delete[] mImages;}
	static CLandscapeManager* GetInstance(){return instance;} // 唯一のインスタンス
	static CLandscapeManager* GetInstance2(){return instance_back;} // 唯一のインスタンス
	static CLandscapeManager* GetInstance3(){return instance_front;} // 唯一のインスタンス
	void CreateLandscape(int x, int y, int img_kind, int img_kind_sub, double vx, double vy);
	int seekTop(); //baseFlgの有る物の上端を探索
	void SetBaseSpeed(double x,double y);
	void SetSpeed(double x,double y);
	void moveLandscape(double y);
};
CLandscapeManager* CLandscapeManager::instance = new CLandscapeManager();
CLandscapeManager* CLandscapeManager::instance_back = new CLandscapeManager();
CLandscapeManager* CLandscapeManager::instance_front = new CLandscapeManager();

CLandscapeManager::CLandscapeManager():CObjectManager(){
	mImages=new CImage32[LANDSCAPE_FILES];
	for(int i=0;i<LANDSCAPE_FILES;i++)
		CImageFactory::InitBitmap(&mImages[i],LANDSCAPE_STATUS[i].fname);
}

int CLandscapeManager::seekTop(){
	int top=0;
	bool initFlg=false;
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CLandscape* obj = (CLandscape*)*it;
		int tmp=obj->GetY()-obj->GetHeight()/2;
		if(initFlg==false || (tmp<top && obj->isBase())){
			top=tmp;
			initFlg=true;
		}
		it++;
	}
	return top;
}

void CLandscapeManager::SetBaseSpeed(double x,double y){
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CLandscape* obj = (CLandscape*)*it;
		int tmp=obj->GetX();
		if(obj->isBase()){obj->SetVel((int)x,(int)y);}
		it++;
	}
}

void CLandscapeManager::SetSpeed(double x,double y){
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CLandscape* obj = (CLandscape*)*it;
		int tmp=obj->GetX();
		obj->SetVel((int)x,(int)y);
		it++;
	}
}

void CLandscapeManager::CreateLandscape(int x, int y, int kind, int img_kind_sub, double vx, double vy) {
	CLandscape* obj;

	if (kind == LANDSCAPE_FLOOR1)obj = new CLandscapeNull1();
	else if (kind == LANDSCAPE_GAS_TANK1)obj = new CLandscapeGasTank2();
	else if (kind == LANDSCAPE_CONTAINER1)obj = new CLandscapeContainer1();

	else if (kind == LANDSCAPE_FLOOR2)obj = new CLandscapeNull1();
	else if (kind == LANDSCAPE_CRYSTAL1)obj = new CLandscapeCrystal1();
	else if (kind == LANDSCAPE_CRYSTAL2)obj = new CLandscapeCrystal2();
	else if (kind == LANDSCAPE_CRYSTAL3)obj = new CLandscapeCrystal3();

	else if (kind == LANDSCAPE_VACUUMED_STAR)obj = new CVacuumedStar();
	else if (kind == LANDSCAPE_PASSING_STAR1)obj = new CPassingStar1();
	else if (kind == LANDSCAPE_PASSING_STAR2)obj = new CPassingStar2();
	else if (kind == LANDSCAPE_FLOOR3)obj = new CLandscapeNull1();
	else if (kind == LANDSCAPE_NEEDLE1)obj = new CLandscapeIce1();
	else if (kind == LANDSCAPE_NEEDLE2)obj = new CLandscapeIce1();
	else if (kind == LANDSCAPE_NEEDLE3)obj = new CLandscapeIce1();

	else if (kind == LANDSCAPE_FLOOR4)obj = new CLandscapeNull1();

	else if (kind == LANDSCAPE_BLOCK1)obj = new CLandscapeBlock1();
	else if (kind == LANDSCAPE_BLOCK2)obj = new CLandscapeBlock1();
	else if (kind == LANDSCAPE_GAS_TANK1)obj = new CLandscapeGasTank1();
	else if (kind == LANDSCAPE_CRYSTAL_ST6_1)obj = new CLandscapeCrystal1();
	else if (kind == LANDSCAPE_CRYSTAL_ST6_2)obj = new CLandscapeCrystal2();
	else if (kind == LANDSCAPE_CRYSTAL_ST6_3)obj = new CLandscapeCrystal3();
	else if (kind == LANDSCAPE_CRYSTAL_ST5)obj = new CLandscapeCrystal3();
	else obj = new CLandscape();

	obj->Create(x, y,kind, img_kind_sub, vx, vy);
	mObjectList.push_back(obj);
}

void CLandscapeManager::moveLandscape(double y){
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CLandscape* obj = (CLandscape*)*it;
		obj->ForceObject(0,y);
		it++;
	}
}
