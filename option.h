const int OPTION_FILES=1;
const TFileData OPTION_FILE[OPTION_FILES]={
	{"dat/img/option.bmp",22,15,1},
};
class COption:public CGameObject{
protected:
	CEffectManager* mEffectManager;
	CImageDIB* m_bg;
	CImage32* mImages;
	int mAnimations;
	
public:
	COption():CGameObject(){
		mEffectManager=CEffectManager::GetInstance();
		m_bg=CImageDIB::GetInstance();
		mImages=new CImage32();
		CImageFactory::InitBitmap(mImages,OPTION_FILE[0].fname);
		m_width=OPTION_FILE[0].width;
		m_height=OPTION_FILE[0].height;
	
	}
	void Update(){
		mTimer++;
		CBltInfo info(BLT_KEY);
		Blt(m_bg,mImages);
	}
	void ResetTimer(){
		mTimer=0;
	}
	void Killed(){
		for(int j=0;j<15;j++){
			mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_PARTICLE1,0,-(rand()%150)*0.1-1.0,rand()%8*0.125,1,2,20,0);
		}
		mTimer=0;
	}
};