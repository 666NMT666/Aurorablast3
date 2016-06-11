const int KSHOT_FILES=1;
const char KSHOT_FILE[KSHOT_FILES][64]={
	"dat/img/e-bullets1.bmp",
};
class CKillerShotMissile:public CEnemySideObject{
private:
	int mImgRotation;
public:
	CKillerShotMissile():CEnemySideObject(),mImgRotation(0){}
	void Update();
	void Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info);
};

void CKillerShotMissile::Update(){
/*	int img=mKind+(mImgRotation++)%4;
	mBltX=EBMAP[img].x;
	mBltY=EBMAP[img].y;
	if(mPlayer->isInvincible())UpdateGameObject();
	if(m_x<0 || m_x>660 || m_y<0 || m_y>500)mDelFlg=true;
	if(HitRadius(m_width)){
		mDelFlg=true;
		if(!mPlayer->isInvincible())mPlayer->Killed();
	}*/
	UpdateGameObject();
}

void CKillerShotMissile::Create(int x,int y,int kind,double vx,double vy,const CCreateInfo& info){
	CreateGameObject(x,y,kind,vx,vy);
	mImgId=info.params[0];
	mDelFlg=false;
/*	mBltX=EBMAP[kind].x;
	mBltY=EBMAP[kind].y;
	m_width=EBMAP[kind].w;
	m_height=EBMAP[kind].w;
*/
}