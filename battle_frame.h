#pragma once
#include <Windows.h>
#include "img32.h"
#include "imgdib.h"

class CBattleFrame{
protected:
	static const DWORD C_WHITE = 0xFFFFFFFF;
	CImageDIB* m_bg;
	CImage32* mImgLevelBomb;
	CPlayer* mPlayer;
	CGameInfo* mGameInfo;
	CScore* mScore;
	CImageNumber* mImageNumber;
	CImage32* mFrameLeft1;
	CImage32* mFrameLeft2;
	CImage32* mFrameLeft3;
	CImage32* mFrameRight;
	CImage32* mFrameDash;
	static CBattleFrame *instance;
	CGageView* mTensionGage;
	CGageView* mExtendGage;
	CGageView* mLevelUpGage;
	CCountView* mLifeCount;
	CCountView* mBombCount;
	CCountView* mLevelCount;
	int mAlphaBlacken;
public:
	CBattleFrame(){
		m_bg=CImageDIB::GetInstance();
		mImgLevelBomb=CImageFactory::newBitmap("dat/img/gage-level-bomb.bmp");
		RECT rcLife={785,270,785+155,270+15};
		mLifeCount=new CCountView(m_bg,"dat/img/gage-life-bg.bmp","dat/img/gage-life-filled.bmp",NULL,rcLife,7,22,0,1,1);
		RECT rcLevel={792,413,792+36,676};
		mLevelCount=new CCountView(m_bg,NULL,"dat/img/gage-level-bomb-filled.bmp","dat/img/gage-level-bomb-empty.bmp",rcLevel,9,0,-29,0,232);
		RECT rcBomb={880,440,880+36,703};
		mBombCount=new CCountView(m_bg,NULL,"dat/img/gage-level-bomb-filled.bmp","dat/img/gage-level-bomb-empty.bmp",rcBomb,9,0,-29,0,232);

		mFrameRight=CImageFactory::newBitmap("dat/img/frame-right.bmp");
		mFrameLeft1=CImageFactory::newBitmap("dat/img/frame-left1.bmp");
		mFrameLeft2=CImageFactory::newBitmap("dat/img/frame-left2.bmp");
		mFrameLeft3=CImageFactory::newBitmap("dat/img/frame-left3.bmp");
		mFrameDash=CImageFactory::newBitmap("dat/img/frame-dash.bmp");
		mScore=CScore::GetInstance();
		mPlayer=CPlayer::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		mImageNumber=new CImageNumber("dat/img/figur16_22_v.bmp");
		
		RECT rc={785,180,785+155,180+15};
		mTensionGage=new CGageView(m_bg,rc,1999999999.0,0x00FFFF30,0x00FFFF30,0x00DFFF30,C_WHITE,0x00140030,0x00140030);

		RECT rcExtend={785,302,785+155,302+15};
		mExtendGage=new CGageView(m_bg,rcExtend,(double)mPlayer->GetMaxExtendCounter(),0x00FFFF30,0x00FFFF30,0x00FF30B8,C_WHITE,0x00140030,0x00140030);

		RECT rcLevelUp={785,374,785+155,374+15};
		mLevelUpGage=new CGageView(m_bg,rcLevelUp,(double)mPlayer->GetMaxExtendCounter(),0x00FFFF30,0x00FFFF30,0x0038D0FF,C_WHITE,0x00140030,0x00140030);

		mAlphaBlacken=0;
	}

	void Update();
	static CBattleFrame* GetInstance(){return instance;}

	
};
CBattleFrame* CBattleFrame::instance=new CBattleFrame();

void CBattleFrame::Update(){
	int maxBlock=mScore->GetMaxBlock();
	int lineNum;
	if(maxBlock<6)lineNum=1;
	else if(maxBlock<13)lineNum=2;
	else lineNum=3;
	
	CBltInfo bi(BLT_KEY);
	{

		CBltInfo biFrame(BLT_MEMCOPY);
		if(mPlayer->isInvincible()){
			mAlphaBlacken+=10;
			if(mAlphaBlacken>140)mAlphaBlacken=255;
			biFrame.type=BLT_BLACKEN;
			biFrame.alpha=mAlphaBlacken;
		}else{
			biFrame.type=BLT_MEMCOPY;
			mAlphaBlacken=0;
		}
		if(lineNum==1)CImageBlender::Blt(m_bg,mFrameLeft1,&biFrame,WND_RECT,0,0);
		if(lineNum==2)CImageBlender::Blt(m_bg,mFrameLeft2,&biFrame,WND_RECT,0,0);
		if(lineNum==3)CImageBlender::Blt(m_bg,mFrameLeft3,&biFrame,WND_RECT,0,0);
		CImageBlender::Blt(m_bg,mFrameRight,&biFrame,WND_RECT,BATTLE_RECT.right,0);

		if(mPlayer->isInvincible()){
			static int y=0;
			for(int i=0;y+i*mFrameDash->Height()<WND_RECT.bottom+mFrameDash->Height();i++){
				CBltInfo bi(BLT_KEY);
				CImageBlender::Blt(m_bg,mFrameDash,&bi,WND_RECT,150-mFrameDash->Width()/2,y+i*mFrameDash->Height()-mFrameDash->Height()/2);
				CImageBlender::Blt(m_bg,mFrameDash,&bi,WND_RECT,BATTLE_RIGHT+50-mFrameDash->Width()/2,y+i*mFrameDash->Height()-mFrameDash->Height()/2);
				
				CImageBlender::Blt(m_bg,mFrameDash,&bi,WND_RECT,50-mFrameDash->Width()/2,y+i*mFrameDash->Height()-mFrameDash->Height()/2);
				CImageBlender::Blt(m_bg,mFrameDash,&bi,WND_RECT,BATTLE_RIGHT+150-mFrameDash->Width()/2,y+i*mFrameDash->Height()-mFrameDash->Height()/2);
				//CShape::fillCircle(m_bg,150,y+i*100,30,0x00FF00FF);
				//CShape::fillCircle(m_bg,BATTLE_RIGHT+50,y+i*100,30,0x00FF00FF);
			}
			y-=29;
			if(y<-100)y+=100;
		}
	}
	
	if(mPlayer->checkGotItem() && rand()%2==0){ mExtendGage->setGageColor(0x00FFBBFF,C_WHITE); }
	else { mExtendGage->setGageColor(0x00FF30B8,C_WHITE); }

	if(mPlayer->checkDestroyed() && rand()%2==0){ mLevelUpGage->setGageColor(0x00FFD0FF,C_WHITE); }
	else { mLevelUpGage->setGageColor(0x0038D0FF,C_WHITE); }

	mExtendGage->Update(mPlayer->GetExtendCounter(),mPlayer->GetMaxExtendCounter());//Extend
	mLevelUpGage->Update(mPlayer->GetPowerUpCounter(), mPlayer->GetMaxLevelUpCounter());//LevelUp
	mTensionGage->Update(mScore->GetHaste());//Tension
	mLifeCount->Update(mPlayer->GetLife());//Life
	mLevelCount->Update(mPlayer->GetPower());//Level
	mBombCount->Update(mPlayer->GetBomb());//Bomb
	
	{//
		//mImageNumber->PutNumberV(200-50,10,mScore->GetScore());
		int nums[3]={7,6,5};
		for(int j=0;j<lineNum;j++){
			string str="";
			for(int i=nums[j]-1;i>=0;i--){
				char s[8];
				if(j==0)sprintf_s(s,8,"%04d",mScore->GetScoreAtLank(i));
				else if(j==1)sprintf_s(s,8,"%04d",mScore->GetScoreAtLank(i+7));
				else if(j==2)sprintf_s(s,8,"%04d",mScore->GetScoreAtLank(i+13));
				str+=s;
			}
			int hDelim=24;
			if(j==2)hDelim=50;
			mImageNumber->PutNumberStrV(90-lineNum*23+j*47,680-j*35,str.c_str(),hDelim);
		}	
	}
}
