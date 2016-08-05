#pragma once

#include "midboss3.h"
#include "midboss4.h"
#include "midboss5.h"
#include "midboss6.h"
#include "enemy_dragonfly.h"
#include "enemy_tank1.h"
#include "enemy_tank2.h"
#include "enemy_tank3.h"
#include "enemy_tank4.h"
#include "enemy_tank5.h"
#include "enemy_house_centipede1.h"
#include "enemy_boliviabug.h"
#include "enemy_harvestmen.h"
#include "enemy_fo01.h"
#include "enemy_fo02.h"
#include "enemy_fo03.h"
#include "enemy_fo04.h"
#include "enemy_fo05.h"
#include "enemy_fo06.h"
#include "enemy_flank_attacker1.h"
#include "enemy_flank_attacker2.h"
#include "enemy_trail_formed2.h"
#include "enemy_fo09.h"
#include "enemy_fo10.h"
#include "enemy_fo11.h"
#include "enemy_fo12.h"
#include "enemy_fo13.h"
#include "enemy_fo14.h"
#include "enemy_hermit_crab.h"
#include "enemy_propeller.h"
#include "enemy_large01.h"
#include "enemy_large02.h"
#include "enemy_large03.h"
#include "enemy_ball1.h"
#include "enemy_ball2.h"
#include "enemy_spinner1.h"
#include "enemy_spinner2.h"
#include "enemy_spinner3.h"
#include "enemy_spinner4.h"
#include "enemy_spinner5.h"
#include "enemy_spinner6.h"
#include "enemy_kamikaze1.h"
#include "enemy_kamikaze2.h"
#include "enemy_kamikaze3.h"
#include "enemy_kamikaze4.h"
#include "enemy_kamikaze5.h"
#include "enemy_kamikaze6.h"
#include "enemy_attacker2.h"
#include "enemy_bomber2.h"
#include "enemy_shield1.h"
#include "enemy_shield2.h"
#include "enemy_robo1.h"
#include "enemy_robo2.h"
#include "enemy_robo3.h"
#include "enemy_amblypygi1.h"
#include "enemy_amblypygi2.h"
#include "enemy_earth.h"

enum TEnemyKind {
	ENEMY_FO1,
	ENEMY_FO2,
	ENEMY_TRAIL_FORMED1,
	ENEMY_FO4,
	ENEMY_FO5,
	ENEMY_FO6,
	ENEMY_SHIELD1,
	ENEMY_SHIELD2,
	ENEMY_TANK1,
	ENEMY_TANK2,
	ENEMY_TANK3,
	ENEMY_HOUSE_CENTIPEDE1,
	ENEMY_LARGE1,
	ENEMY_LARGE2,
	ENEMY_LARGE3,
	ENEMY_DRAGONFLY1,
	ENEMY_BALL1,
	ENEMY_SPINNER1,
	ENEMY_SPINNER2,
	ENEMY_SPINNER3,
	ENEMY_SPINNER4,
	ENEMY_SPINNER5,
	ENEMY_SPINNER6,
	ENEMY_KAMIKAZE1,
	ENEMY_KAMIKAZE2,
	ENEMY_KAMIKAZE3,
	ENEMY_KAMIKAZE4,
	ENEMY_KAMIKAZE5,
	ENEMY_KAMIKAZE6,
	ENEMY_MIDBOSS3,
	ENEMY_MIDBOSS4,
	ENEMY_MIDBOSS5,
	ENEMY_MIDBOSS6,
	ENEMY_FLANK_ATTACKER1,
	ENEMY_FLANK_ATTACKER2,
	ENEMY_ATTACKER2,
	ENEMY_BOMBER2,
	ENEMY_HARVESTMEN1,
	ENEMY_BOLIVIABUG1,
	ENEMY_TRAIL_FORMED2,
	ENEMY_TANK4,
	ENEMY_TANK5,
	ENEMY_AMBLYPYGI1,
	ENEMY_ROBO1,
	ENEMY_ROBO2,
	ENEMY_ROBO3,
	ENEMY_PROPELLER1,
	ENEMY_AMBLYPYGI2,
	ENEMY_EARTH,
	ENEMY_FILES,
};

class CEnemyManager:public CObjectManager{
	static CEnemyManager* instance;
	static CEnemyManager* instance2;
	static TEnemyFile *ENEMY_DATA;
public:
	CEnemyManager();
	~CEnemyManager(){delete[] mImages;}
	void Create2(int x,int y,int kind,double vx,double vy,const CCreateInfo& info);
	static CEnemyManager* GetInstance(){return instance;} //
	static CEnemyManager* GetInstance2(){return instance2;} //
	static int StrToEnemy(char* str);
	void LandEnemy(int x,int y,int w,int h,double forceY);
	void DestroyAllEnemy();
	void SetVel(int vx,int vy);
	
};
TEnemyFile *CEnemyManager::ENEMY_DATA = NULL;
CEnemyManager* CEnemyManager::instance = new CEnemyManager();
CEnemyManager* CEnemyManager::instance2 = new CEnemyManager();
CEnemyManager::CEnemyManager():CObjectManager(){
	mImages=new CImage32[ENEMY_FILES];
	CCsvUtil csv("dat/dat/enemy.csv", 7);
	if(ENEMY_DATA == NULL)ENEMY_DATA = new TEnemyFile[ENEMY_FILES];
	for (int i = 1; i < csv.getNumLows(); i++) {
		int j = i - 1;
		ENEMY_DATA[j].fname = csv.get(i, 0);
		ENEMY_DATA[j].short_fname = csv.get(i, 1);
		ENEMY_DATA[j].width = std::stoi(csv.get(i, 2));
		ENEMY_DATA[j].height = std::stoi(csv.get(i, 3));
		ENEMY_DATA[j].life = std::stoi(csv.get(i, 4));
		ENEMY_DATA[j].front_parts = std::stoi(csv.get(i, 5));
		ENEMY_DATA[j].back_parts = std::stoi(csv.get(i, 6));
		mImages[j].load(ENEMY_DATA[j].fname.c_str());
	}
	CEnemy::LoadPartsFiles();
}

void CEnemyManager::Create2(int x, int y, int kind, double vx, double vy, const CCreateInfo& info) {
	CEnemy* obj;

	switch (kind) {
		case ENEMY_FO1:obj = new CEnemyFO01(); break;
		case ENEMY_FO2:obj = new CEnemyFO02(); break;
		case ENEMY_FO4:obj =new CEnemyFO04(); break;
		case ENEMY_FO5:obj =new CEnemyFO05(); break;
		case ENEMY_FO6:obj =new CEnemyFO06(); break;
		case ENEMY_SHIELD1:obj = new CEnemyShield1(); break;
		case ENEMY_SHIELD2:obj = new CEnemyShield2(); break;//
		case ENEMY_SPINNER1:obj = new CEnemySpinner1(); break;
		case ENEMY_SPINNER2:obj = new CEnemySpinner2(); break;
		case ENEMY_SPINNER3:obj = new CEnemySpinner3(); break;
		case ENEMY_SPINNER4:obj = new CEnemySpinner4(); break;
		case ENEMY_SPINNER5:obj = new CEnemySpinner5(); break;
		case ENEMY_SPINNER6:obj = new CEnemySpinner6(); break;
		case ENEMY_KAMIKAZE1:obj =new CEnemyKamikaze1(); break;
		case ENEMY_KAMIKAZE2:obj =new CEnemyKamikaze2(); break;
		case ENEMY_KAMIKAZE3:obj = new CEnemyKamikaze3(); break;
		case ENEMY_KAMIKAZE4:obj = new CEnemyKamikaze4(); break;
		case ENEMY_KAMIKAZE5:obj = new CEnemyKamikaze5(); break;
		case ENEMY_KAMIKAZE6:obj = new CEnemyKamikaze6(); break;
		case ENEMY_MIDBOSS3:obj =new CEnemyMidboss3(); break;
		case ENEMY_MIDBOSS4:obj =new CEnemyMidboss4(); break;
		case ENEMY_MIDBOSS5:obj =new CEnemyMidboss5(); break;
		case ENEMY_MIDBOSS6:obj =new CEnemyMidboss6(); break;
		case ENEMY_FLANK_ATTACKER1:obj = new CEnemyFlankAttacker1(); break;
		case ENEMY_FLANK_ATTACKER2:obj = new CEnemyFlankAttacker2(); break;
		case ENEMY_ATTACKER2:obj =new CEnemyAttacker2(); break;
		case ENEMY_BOMBER2:obj =new CEnemyBomber2(); break;
		case ENEMY_TRAIL_FORMED2:obj =new CEnemyTrailFormed2(); break;
		case ENEMY_TANK1:obj =new CEnemyTank01(); break;
		case ENEMY_TANK2:obj =new CEnemyTank02(); break;
		case ENEMY_TANK3:obj =new CEnemyTank03(); break;
		case ENEMY_TANK4:obj = new CEnemyTank04(); break;
		case ENEMY_TANK5:obj = new CEnemyTank05(); break;
		case ENEMY_HOUSE_CENTIPEDE1:obj =new CHouseCentipede(); break;
		case ENEMY_DRAGONFLY1:obj =new CEnemyDragonfly1(); break;
		case ENEMY_BALL1:obj =new CEnemyBall1(); break;
		case ENEMY_HARVESTMEN1:obj =new CEnemyHarvestmen01(); break;
		case ENEMY_BOLIVIABUG1:obj =new CBoliviabug(); break;
		case ENEMY_LARGE1:obj = new CEnemyLarge01(); break;
		case ENEMY_LARGE2:obj = new CEnemyLarge02(); break;
		case ENEMY_LARGE3:obj = new CEnemyLarge03(); break;
		case ENEMY_ROBO1:obj = new CEnemyRobo1(); break;
		case ENEMY_ROBO2:obj = new CEnemyRobo2(); break;
		case ENEMY_ROBO3:obj = new CEnemyRobo3(); break;
		case ENEMY_AMBLYPYGI1:obj = new CEnemyAmblypygi1(); break;
		case ENEMY_AMBLYPYGI2:obj = new CEnemyAmblypygi2(); break;
		case ENEMY_EARTH:obj = new CEnemyEarth(); break;
		default:obj = new CEnemy(); break;
	}
	obj->Create(x,y,kind,vx,vy,info, ENEMY_DATA[kind]);
	mObjectList.push_back(obj);
}

int CEnemyManager::StrToEnemy(char* str){
	for(int i=0;i<ENEMY_FILES;i++){
		if(str==ENEMY_DATA[i].short_fname)return i;
	}
	return 0;
}

void CEnemyManager::LandEnemy(int x,int y,int w,int h,double forceY){
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CEnemy* obj = (CEnemy*)*it;
		if(obj->isLanded() && x < obj->GetX() && obj->GetX() <x+w){
			int dy=y-obj->GetY()-obj->GetLandHeight();
			if(abs(dy)<2){}
			else if(dy>forceY)obj->PushObject(0,forceY);
			else if(dy>0)obj->PushObject(0,dy/4);
			else if(dy<0)obj->PushObject(0,dy/4);
			else if(dy<-forceY)obj->PushObject(0,-forceY);
		}
		it++;
	}
}

void CEnemyManager::DestroyAllEnemy(){
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CEnemy* obj = (CEnemy*)*it;
		obj->Killed();
		it++;
	}
}

void CEnemyManager::SetVel(int vx,int vy){
	std::list<CGameObject*>::iterator it = mObjectList.begin();
	while(it!=mObjectList.end()){
		CEnemy* obj = (CEnemy*)*it;
		obj->SetVel(vx,vy);
		it++;
	}
}