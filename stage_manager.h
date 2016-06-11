typedef struct _TStageObject{
	int type,kind,time,x,y,p1,p2;
} TStageObject;

class CStageManager{
protected:
	CEnemyManager* mEnemyManager;
	CEnemyManager* mEnemyManagerBack;
	CEnemyGeneratorManager* mGeneratorManager;
	CBossManager* mBossManager;
	CLandscapeManager* mLandscapeManager;
	CGameInfo* mGameInfo;
	CPlayer *mPlayer;
	CEnemyBulletManager *mEBManager;
	int mTimer;
	int mCurrent;
	bool mLandHeadFlg[5];
	TStageObject mStageObject[1000];

	void UpdateStage1();
	void UpdateStage2();
	void UpdateStage3();
	void UpdateStage4();
	void UpdateStage5();
	void UpdateStage6();
	void UpdateStage7();
public:
	CStageManager():mTimer(0),mCurrent(0){
		mEnemyManager=CEnemyManager::GetInstance();
		mEnemyManagerBack=CEnemyManager::GetInstance2();
		mGeneratorManager=CEnemyGeneratorManager::GetInstance();
		mLandscapeManager=CLandscapeManager::GetInstance();
		mBossManager=CBossManager::GetInstance();
		mGameInfo=CGameInfo::GetInstance();
		mPlayer=CPlayer::GetInstance();
		mEBManager=CEnemyBulletManager::GetInstance();
		for(int i=0;i<5;i++)mLandHeadFlg[i]=false;

	}
	void Update();
	void ReadStage(char* fname);
	void ReadCSV(char* fname);
	void Reset(){mTimer=mCurrent=0;}
};

void CStageManager::UpdateStage1(){
	if(mTimer>200  && (mTimer<2560 || mTimer>2800)){
		if(mTimer%105==0){
			CCreateInfo info(2,6,0,0,0);
			if(mGameInfo->EnemyStopCheck()==false){
				//int k=(mTimer%2==0)?1:0;
			//	mGeneratorManager->Create<CEnemyGenerator>(rand()%(BATTLE_RECT.right-BATTLE_RECT.left)+200,0,k,1,0,5,info);
			}
		}
		if((mTimer%200<30 || (mTimer%200>60 && mTimer%200<90)) && (mTimer<1440 || mTimer>2000)){
			if(mTimer%700<600){
				if(mTimer%3==0){
					CCreateInfo info(0,7+rand()%10,0,0,0);
					if(mGameInfo->EnemyStopCheck()==false)mEnemyManager->Create2(200+(rand()%BATTLE_WIDTH),0,ENEMY_FO2,0,2,info);
				}
			}else{
				if(mTimer%200==0){
					int enemyY=50+mGameInfo->GetLevel()*40;
					CCreateInfo info(enemyY,0,0,0,0);
					int range=BATTLE_WIDTH/2;
					if(mGameInfo->EnemyStopCheck()==false)mEnemyManager->Create2((BATTLE_LEFT+BATTLE_RIGHT)/2,BATTLE_BOTTOM,ENEMY_LARGE1,0,2,info);
				}
			}	
		}
	}
	if(mTimer>2000 && mTimer<2300){
		if(mGameInfo->EnemyStopCheck()==false)mEnemyManagerBack->SetVel(0,10);
	}
}

void CStageManager::UpdateStage2(){

}

void CStageManager::UpdateStage3(){
	if(mTimer%1000>700){
		if(mTimer%9==0){
			CCreateInfo info(0,7+rand()%10,0,0,0);
			if(mGameInfo->EnemyStopCheck()==false)mEnemyManager->Create2(200+(rand()%BATTLE_WIDTH),0,ENEMY_ATTACKER2,0,2,info);
		}
	}
}

void CStageManager::UpdateStage4(){

}


void CStageManager::UpdateStage5(){

}

void CStageManager::UpdateStage6(){

}

void CStageManager::UpdateStage7(){

}

void CStageManager::Update(){

	int stage=mGameInfo->GetStage();
	if(stage==0){ UpdateStage1(); }
	else if(stage==1){ UpdateStage2();}
	else if(stage==2){ UpdateStage3();}
	else if(stage==3){ UpdateStage4();}
	else if(stage==4){ UpdateStage5();}
	else if(stage==5){ UpdateStage6();}
	else if(stage==6){ UpdateStage7();}


	if(mPlayer->isInvincible() && mTimer%2==0){
		mEBManager->KillAllBullet();
	}

	if(mTimer==mStageObject[mCurrent].time){
		CCreateInfo info;
		info.params[0]=mStageObject[mCurrent].p1;
		info.params[1]=mStageObject[mCurrent].p2;
		if(mStageObject[mCurrent].type==0){
			int k=mStageObject[mCurrent].kind;
			if(mGameInfo->EnemyStopCheck()==false)mEnemyManager->Create2(mStageObject[mCurrent].x,mStageObject[mCurrent].y,k,0,5,info);
		}else if(mStageObject[mCurrent].type==1){
			int k=mStageObject[mCurrent].kind;
			if(mGameInfo->EnemyStopCheck()==false)mEnemyManagerBack->Create2(mStageObject[mCurrent].x,mStageObject[mCurrent].y,k,0,5,info);
		}else if(mStageObject[mCurrent].type==2){
			if(mGameInfo->EnemyStopCheck()==false)mGeneratorManager->Create<CEnemyGenerator>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,5,info);
		}else if(mStageObject[mCurrent].type==5){
			int k = mStageObject[mCurrent].kind;
			if(k==0)mBossManager->Create<CBoss1>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,0,info);
			if(k==1)mBossManager->Create<CBoss2>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,0,info);
			if(k==2)mBossManager->Create<CBoss3>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,0,info);
			if(k==3)mBossManager->Create<CBoss4>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,0,info);
			if(k==4)mBossManager->Create<CBoss5>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,0,info);
			if(k==5)mBossManager->Create<CBoss6>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,0,info);
			if(k==6)mBossManager->Create<CBoss7>(mStageObject[mCurrent].x,mStageObject[mCurrent].y,mStageObject[mCurrent].kind,0,0,0,info);
		}
		mCurrent++;
	}
	mTimer++;
}
#include "file_util.h"
void CStageManager::ReadStage(char* fname){
	static const int MAX_LENGTH=256;
	FILE* fin;
	char buf[MAX_LENGTH];
	my_fopen_in(&fin,fname);

	int i=0;
	while(fgets(buf,MAX_LENGTH,fin) != NULL){
		char str[16];
		sscanf_s(buf,"%d,%[^\n,],%d,%d,%d,%d,%d",&mStageObject[i].type,str,16,
			&mStageObject[i].time,&mStageObject[i].x,   &mStageObject[i].y,   &mStageObject[i].p1, &mStageObject[i].p2);
		
		if(mStageObject[i].type==0 || mStageObject[i].type==1)mStageObject[i].kind=CEnemyManager::StrToEnemy(str);
		else mStageObject[i].kind=atoi(str);
		i++;
	}
	fclose(fin);
}
//0:敵機 1:敵機B 2:敵郡 3:地形 4:タイル 5:ボス 6:変更指示
