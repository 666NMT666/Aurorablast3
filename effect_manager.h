#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H 

enum TEffectFile {
	EFFECT_EXPLOSION_LIGHT_40,
	EFFECT_EXPLOSION_LIGHT_80,
	EFFECT_EXPLOSION_LIGHT_80_2,
	EFFECT_EXPLOSION_LIGHT_70,
	EFFECT_EXPLOSION_LIGHT_40_2,
	EFFECT_EXPLOSION_40,
	EFFECT_EXPLOSION_40_2,
	EFFECT_PARTICLE1,
	EFFECT_PARTICLE2,
	EFFECT_KYP1,
	EFFECT_BACKLIGHT1,
	EFFECT_BACKLIGHT2,
	EFFECT_ICEBLOCK1,
	EFFECT_ICE_DOT1,
	EFFECT_HALO60,
	EFFECT_EXPLOSION_160,
	EFFECT_EXPLOSION_HEAD1,
	EFFECT_PARTICLE_16,
	EFFECT_EXPLOSION_90,
	EFFECT_EXPLOSION_80,
	EFFECT_EXPLOSION_80_2,
	EFFECT_BACKLIGHT3,
	EFFECT_BACKLIGHT4,
	EFFECT_FILES
};

typedef struct _TEffectFileData {
	std::string fname;
	int width, height, numCycle, type;
} TEffectFileData;

class CEffectManager :public CObjectManager {
	static const int MAX_EFFECTS = 200;
	static CEffectManager* instance;
	static CEffectManager* instance2;
	static CEffectManager* instance3;
	TEffectFileData *EFFECT_FILE;
public:
	CEffectManager();
	~CEffectManager() { delete[] mImages; }
	static CEffectManager* GetInstance() { return instance; } // インスタンス
	static CEffectManager* GetInstance2() { return instance2; } // 前方演出インスタンス
	static CEffectManager* GetInstance3() { return instance3; } // 後方演出インスタンス

	void CreateEffect(double x, double y, TEffectFile kind, int subKind, double vx, double vy, int motion, int interval, int end, int delta) {
		CreateEffect((int)x, (int)y, kind, subKind, vx, vy, motion, interval, end, delta);
	}
	void CreateEclipsedCircle(int x1, int y1, int r1, int x2, int y2, int r2, DWORD color);
	void CreateEclipsedElipse(int x1, int y1, int rx1, int ry1, int x2, int y2, int rx2, int ry2, DWORD color);
	void CreateLine(int x1, int y1, int x2, int y2, DWORD color);
	void CreateLineWithAngle(int x1, int y1, int x2, int y2, DWORD color);
	void CreateThrash(int x, int y, int w, int h, int angle, DWORD color);
	void CreateEffect(int x, int y, TEffectFile kind, int subKind, double vx, double vy, int motion, int interval, int end, int delta);
	void DrawEffect(CImageDIB* dest, int x, int y, int kind, int subKind, TBltType type, int alpha);
	void ExplosionSample(int x, int y);
};
CEffectManager* CEffectManager::instance = new CEffectManager();
CEffectManager* CEffectManager::instance2 = new CEffectManager();
CEffectManager* CEffectManager::instance3 = new CEffectManager();


CEffectManager::CEffectManager() :CObjectManager() {
	CCsvUtil csv("dat/dat/effect.csv", 5);
	EFFECT_FILE = new TEffectFileData[csv.getNumLows()-1];
	mImages = new CImage32[csv.getNumLows()-1];
	for (int i = 1; i < csv.getNumLows(); i++) {
		int j = i - 1;
		EFFECT_FILE[j].fname = csv.get(i, 0);
		EFFECT_FILE[j].width = std::stoi(csv.get(i, 1));
		EFFECT_FILE[j].height = std::stoi(csv.get(i, 2));
		EFFECT_FILE[j].numCycle = std::stoi(csv.get(i, 3));
		EFFECT_FILE[j].type = std::stoi(csv.get(i, 4));
		mImages[j].load(EFFECT_FILE[j].fname.c_str());
	}
}

void CEffectManager::DrawEffect(CImageDIB* dest, int x, int y, int kind, int subKind, TBltType type, int alpha) {
	CBltInfo bi(type, alpha);
	int h = EFFECT_FILE[kind].height;
	int w = EFFECT_FILE[kind].width;
	CImageBlender::Blt(dest, &mImages[kind], &bi, BATTLE_RECT, x - w / 2, y - h / 2, 0, h*subKind, w, h);
}

void CEffectManager::CreateEffect(int x, int y, TEffectFile kind, int subKind, double vx, double vy, int motion, int interval, int end, int delta) {
	CEffect* obj = new CEffect();
	int p[5] = { motion,0,interval,end,delta };
	CBltInfo bi;
	CCreateInfo info(p, bi);
	obj->Create(x, y, kind, subKind, vx, vy, info);
	int h = EFFECT_FILE[kind].height;
	int w = EFFECT_FILE[kind].width;
	obj->SetSize(w, h);
	obj->SetNumCycle(EFFECT_FILE[kind].numCycle);
	obj->SetType((TBltType)EFFECT_FILE[kind].type);
	mObjectList.push_back(obj);
}

void CEffectManager::CreateEclipsedCircle(int x1, int y1, int r1, int x2, int y2, int r2, DWORD color) {
	CEffectEclipsedCircle* obj = new CEffectEclipsedCircle();
	CBltInfo bi;
	CCreateInfo info(0, 0, 0, 0, 0, bi);
	obj->Create(x1, y1, r1, x2, y2, r2, color);
	mObjectList.push_back(obj);
}
void CEffectManager::CreateEclipsedElipse(int x1, int y1, int rx1, int ry1, int x2, int y2, int rx2, int ry2, DWORD color) {
	CEffectEclipsedElipse* obj = new CEffectEclipsedElipse();
	CBltInfo bi;
	CCreateInfo info(0, 0, 0, 0, 0, bi);
	obj->Create(x1, y1, rx1, ry1, x2, y2, rx2, ry2, color);
	mObjectList.push_back(obj);
}

void CEffectManager::CreateThrash(int x, int y, int w, int h, int angle, DWORD color) {
	CEffectThrash* obj = new CEffectThrash();
	CBltInfo bi;
	CCreateInfo info(0, 0, 0, 0, 0, bi);
	obj->Create(x, y, w, h, angle, color);
	mObjectList.push_back(obj);
}

void CEffectManager::CreateLine(int x1, int y1, int x2, int y2, DWORD color) {
	CEffectLine* obj = new CEffectLine();
	CBltInfo bi;
	CCreateInfo info(0, 0, 0, 0, 0, bi);
	obj->Create(x1, y1, x2, y2, color);
	mObjectList.push_back(obj);
}

void CEffectManager::CreateLineWithAngle(int x1, int y1, int length, int angle, DWORD color) {
	CEffectLine* obj = new CEffectLine();
	CBltInfo bi;
	CCreateInfo info(0, 0, 0, 0, 0, bi);
	obj->CreateWithAngle(x1, y1, length, angle , color);
	mObjectList.push_back(obj);
}

void CEffectManager::ExplosionSample(int x, int y) {
	double r = 0.5 + 0.05*(rand() % 100);
	double angle = N_PI*(rand() % 360);
	CreateEffect(x, y, EFFECT_EXPLOSION_LIGHT_80, 0, r*cos(angle), r*sin(angle), EFFECT_MOTION_SINGLE, 1, 0, 0);
}

#endif