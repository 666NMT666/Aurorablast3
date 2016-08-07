
class CPlayer:public CGameObject{
private:
	static CPlayer* instance;
	static const int WIDTH=60;
	static const int HEIGHT=70;
	static const int SPEED_SET[4][2];
	static const int HORIZONTAL=0;
	static const int VERTICAL=1;
	static const RECT MOTION_RECT;
	static const int QUAKE_MAGNITUDE=70;
	static const int MAX_POWER = 9;
	static const int MAX_LIFE = 7;

	int MAX_INVINCIBLE_COUNTER;
	int MAX_BOMB_COUNTER;
	CImage32* mImages;
	CBulletManager* mBulletManager;
	CBombManager* mBombManager;
	CEffectManager* mEffectManager;
	CEffectManager* mEffectManagerFront;
	CScore* mScore;
	COption mOption[4];
	CSoundEffect* mSE;
	CGameInfo* mGameInfo;
	int mRendaCounter;
	bool mCoughtFlg;
	bool mKeepZFlg;
	int mCaughtTimer;
	int mBombCounter;
	int mInvincibleCounter;
	double mVerticalSpeed,mHorizontalSpeed;
	double inertiaX, inertiaY;
	int mKilledCounter;
	int mShotTimer;
	int mPower,mBomb,mWepon,mLife;
	int mExtendCounter,mPowerUpCounter;
	int mOptions;
	int MAX_EXTEND_COUNTER;
	int MAX_LEVEL_UP_COUNTER;
	void SetOptions(){
		static const int i[10]={1,1,2,3,4,4,4,4,4,4};
		mOptions=i[mPower%10];
		if(isInvincible() || mLife==0)mOptions=i[9];
	}
	bool mFlgExtended,mFlgLevelUp,mFlgGotItem,mFlgDestroyed;
public:
	CPlayer():CGameObject(){
		mGameInfo=CGameInfo::GetInstance();
		Reset();
		mBulletManager=CBulletManager::GetInstance();
		mBombManager=CBombManager::GetInstance();
		mEffectManager=CEffectManager::GetInstance();
		mEffectManagerFront=CEffectManager::GetInstance2();
		mSE=CSoundEffect::GetInstance();
		mScore=CScore::GetInstance();
		mImages=new CImage32("dat/img/player.bmp");
		inertiaX = inertiaY = 0.0;
	}
	const int GetMaxExtendCounter() { return MAX_EXTEND_COUNTER; }
	const int GetMaxLevelUpCounter() { return MAX_LEVEL_UP_COUNTER; }
	void ResetMaxExtend() {
		mGameInfo->addInnerRank(5);
		int lifeRevision = (mLife - 2) * 70;
		if (lifeRevision < 0)lifeRevision = 0;
		MAX_EXTEND_COUNTER = 370 + mGameInfo->GetLevel() * 70 + lifeRevision;
	}
	void ResetMaxLevelUp() {
		int revision = (mPower - 2) * 70;
		if (revision < 0)revision = 0;
		MAX_LEVEL_UP_COUNTER = 380 + mGameInfo->GetLevel() * 40 + revision;
	}
	void Reset(){
		ResetGameObject();
		MAX_INVINCIBLE_COUNTER=50-mGameInfo->GetLevel();
		MAX_BOMB_COUNTER=140;
		ResetMaxExtend();
		ResetMaxLevelUp();
		m_x=(BATTLE_RECT.left+BATTLE_RECT.right)/2; m_y=MOTION_RECT.bottom-30;
		mExtendCounter=0;
		mPowerUpCounter=0;
		mPower=4;
		mWepon=0;
		mBomb=3;
		mLife=3;
		mCaughtTimer=0;
		mKilledCounter=0; mInvincibleCounter=0; mBombCounter=0; mRendaCounter=0; 
		mOptions=0; mShotTimer=0;
		m_width=WIDTH;
		m_height=HEIGHT;
		mKeepZFlg=false;
		mVerticalSpeed=SPEED_SET[0][VERTICAL];
		mHorizontalSpeed=SPEED_SET[0][HORIZONTAL];
		for(int i=0;i<4;i++)mOption[i].ResetTimer();
		mAutoDelFlg=false;
		mCoughtFlg=false;
		mFlgExtended=mFlgLevelUp=mFlgGotItem=mFlgDestroyed=false;
	}
	void ContinuePlyer(){
		mInvincibleCounter=MAX_INVINCIBLE_COUNTER;
	}
	static CPlayer* GetInstance(){return instance;} // 唯一のインスタンス
	void Left();
	void Right();
	void Up();
	void Down();
	void OnZ();
	void OnX();
	void OnC();
	void OnUpZ();
	void Update();
	void Killed();
	void ItemGetBomb(){ mBomb++; }
	void ItemGet(int ext,int point);
	void DestroyEnemy(int i,int point=123);
	void Shot();

	void ShotMain1();
	void ShotMain2();
	void ShotSub1();

	void UpdateOption();

	void SetMaxInvincibleCounter(int i){MAX_INVINCIBLE_COUNTER=i;}
	bool isInvincible(){return (mInvincibleCounter>0 || mBombCounter>0);}
	bool isOnBomb() { return (mBombCounter > 0); }
	bool isOnRenda() { return (mRendaCounter > 0); }
	const double GetInvincibleRatio(){return ((double)mInvincibleCounter)/((double)MAX_INVINCIBLE_COUNTER);}
	const int GetExtendCounter(){return (mExtendCounter>MAX_EXTEND_COUNTER)? MAX_EXTEND_COUNTER:mExtendCounter;}
	const int GetPowerUpCounter(){return (mPowerUpCounter>MAX_LEVEL_UP_COUNTER)? MAX_LEVEL_UP_COUNTER :mPowerUpCounter;}
	const int GetKilledCounter(){return mKilledCounter;}
	const int GetLife(){return mLife;}
	const int GetPower(){return mPower;}
	const int GetWepon(){return mWepon;}
	const int GetBomb(){return mBomb;}

	void AddInertia(int x, int y) {
		inertiaX = x;
		inertiaY = y;
	}

	void ForcePlayer(int x, int y) {
		m_x += x;
		m_y += y;
		const int margin = 30;
		if (m_x<BATTLE_LEFT + margin)m_x = BATTLE_LEFT + margin;
		if (m_x>BATTLE_RIGHT - margin)m_x = BATTLE_RIGHT - margin;
		if (m_y<BATTLE_TOP + margin)m_y = BATTLE_TOP + margin;
		if (m_y>MOTION_RECT.bottom - margin)m_y = MOTION_RECT.bottom - margin;
	}
	void ForcePlayer(double x, double y, double margin = 0) {
		m_x += x;
		m_y += y;
		if (m_x < BATTLE_LEFT + margin)m_x = BATTLE_LEFT + margin;
		if (m_x > BATTLE_RIGHT - margin)m_x = BATTLE_RIGHT - margin;
		if (m_y < BATTLE_TOP + margin)m_y = BATTLE_TOP + margin;
		if (m_y > MOTION_RECT.bottom - margin)m_y = MOTION_RECT.bottom - margin;
	}
	void CatchPlayer(int t){
		mCaughtTimer=t;
	}
	bool checkLevelUp(){
		bool ret=mFlgLevelUp;
		mFlgLevelUp=false;
		return ret;
	}
	bool checkExtended(){
		bool ret=mFlgExtended;
		mFlgExtended=false;
		return ret;
	}

	bool checkGotItem(){
		bool ret=mFlgGotItem;
		mFlgGotItem=false;
		return ret;
	}
	bool checkDestroyed(){
		bool ret=mFlgDestroyed;
		mFlgDestroyed=false;
		return ret;
	}
};
const RECT CPlayer::MOTION_RECT={200,10,760,710};
CPlayer* CPlayer::instance = new CPlayer();

const int CPlayer::SPEED_SET[4][2]={
	{11,11},
	{ 4, 4},
	{38,38},
	{ 8, 8},
};

void CPlayer::Left(){ if(m_x-50>MOTION_RECT.left)m_x-=mHorizontalSpeed; }
void CPlayer::Right(){ if(m_x+50<MOTION_RECT.right)m_x+=mHorizontalSpeed; }
void CPlayer::Up(){ if(m_y-70>MOTION_RECT.top+30)m_y-=mVerticalSpeed; }
void CPlayer::Down(){ if(m_y<MOTION_RECT.bottom-30)m_y+=mVerticalSpeed; }

void CPlayer::OnZ() {
	mRendaCounter=10;
	mKeepZFlg=true;
}

void CPlayer::OnC() {
	if(mWepon==0)mWepon=1;
	else mWepon=0;
}

void CPlayer::OnX() {
	if(mBomb<=0 || isOnBomb())return;
	mSE->PlaySingleSound(SE_BOM1);
	mBomb-=1; //////if(mBomb<0)mBomb=0;
	mBombCounter=MAX_BOMB_COUNTER;
}

void CPlayer::OnUpZ(){ mKeepZFlg=false; }

void CPlayer::Update(){
	UpdateGameObject();
	
	//CLine::drawGradationLine2(m_bg,(int)m_x-30,(int)m_y+5,400,mTimer,11,0xFFFFAA,0xFF5500,100,30,0,0);
	mScore->AddScore(mScore->GetHaste());
	mScore->AddHaste(-(mScore->GetHaste()>>7));
	mShotTimer++;
	Shot();
	mTimer%=360;
	ForcePlayer(inertiaX, inertiaY);
	if (inertiaX > 0.1) {
		inertiaX *= 0.95;
	}
	else {
		inertiaX = 0;
	}
	
	if (inertiaY > 0.1) {
		inertiaY *= 0.95;
	}
	else {
		inertiaY = 0;
	}
	
	int spd=0;
	if(mKeepZFlg && mRendaCounter==0){
		spd=1;
		if(isInvincible())spd=3;
	}
	else if(isInvincible())spd=2;
	mVerticalSpeed=SPEED_SET[spd][VERTICAL];
	mHorizontalSpeed=SPEED_SET[spd][HORIZONTAL];
	
	if ( mCaughtTimer-- >0 ) {
		mVerticalSpeed = 0;
		mHorizontalSpeed = 0;
	}
	if(mCaughtTimer<0)mCaughtTimer=0;
	
	UpdateOption();

	if(mInvincibleCounter>0){
		if(mTimer%5==0){
			mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_HALO60,0,0,50, 3, 20, 0, 3);
		}
		mInvincibleCounter--;
	}
	if(mBombCounter>0)mBombCounter--;
	if(isInvincible()){
		mBltInfo.type=BLT_WHITEN;
		mBltInfo.alpha=120;
		int length=3*120*mInvincibleCounter/MAX_INVINCIBLE_COUNTER;
		CLine::drawFadeLine2(m_bg,(int)m_x-10,(int)m_y,length, 90,6,0xAAFFFF,0,BATTLE_RECT);
		CLine::drawFadeLine2(m_bg,(int)m_x+10,(int)m_y,length, 90,6,0xAAFFFF,0,BATTLE_RECT);
	}else {
		mBltInfo.type=BLT_KEY;
	}

	Blt(m_bg,mImages);

	if(mKilledCounter>0){
		mScore->RezeroHaste();
		mKilledCounter--;
		m_y=1000;
		m_x=(BATTLE_RIGHT+BATTLE_LEFT)/2;
		if(mKilledCounter==0){ 
			mGameInfo->minusInnerRank(10);
			m_x=(BATTLE_RECT.left+BATTLE_RECT.right)/2;
			m_y=MOTION_RECT.bottom-30;
			mInvincibleCounter=MAX_INVINCIBLE_COUNTER;
		}
	}

	if(mTimer%2==0 && isOnBomb()){
		mBombManager->Create<CBomb>((int)m_x,(int)m_y,0,0,0.0,-40.0,defaultCreateInfo);
	}
}

void CPlayer::Shot(){
	SetOptions();
	if(mKilledCounter>0)return;
	if(mRendaCounter>0)mRendaCounter--;
	if(mWepon==0){
		if (isOnRenda() || mKeepZFlg) { ShotMain1(); }
	}
	else if(mWepon==1){
		if (isOnRenda() || mKeepZFlg) ShotSub1();
	}
}

void CPlayer::ShotMain1() {
	mShotTimer %= 2;
	int _power = mPower;
	if (mLife == 0)_power = MAX_POWER;
	if (mShotTimer == 0) {
		mSE->PlayLoopSound(SE_PST1);

		int k = isInvincible() ? 1 : 0;
		int spd = isInvincible() ? -60 : -40;
		static const CCreateInfo defaultCreateInfo;
		mBulletManager->Create<CBullet>((int)m_x - 15, (int)m_y, k, 0, 0.0, spd, defaultCreateInfo);
		mBulletManager->Create<CBullet>((int)m_x + 15, (int)m_y, k, 0, 0.0, spd, defaultCreateInfo);

		for (int i = 0; i<mOptions; i++) {//Option Shot
			if(_power < 5)mBulletManager->Create<CBullet>(mOption[i].GetX() + 11, mOption[i].GetY(), k, 0, 0.0, spd, defaultCreateInfo);
			else if (_power < 7) {
				mBulletManager->Create<CBullet>(mOption[i].GetX() + 11, mOption[i].GetY(), BULLET_WIDE1, 1, -10.0, spd, defaultCreateInfo);
				mBulletManager->Create<CBullet>(mOption[i].GetX() + 11, mOption[i].GetY(), BULLET_WIDE1, 0, 10.0, spd, defaultCreateInfo);
			}
			else {
				mBulletManager->Create<CBullet>(mOption[i].GetX() + 11, mOption[i].GetY(), BULLET_WIDE1, 1, -10.0, spd, defaultCreateInfo);
				mBulletManager->Create<CBullet>(mOption[i].GetX() + 11, mOption[i].GetY(), BULLET_WIDE1, 0, 10.0, spd, defaultCreateInfo);
				mBulletManager->Create<CBullet>(mOption[i].GetX() + 11, mOption[i].GetY(), k, 0, 0.0, spd, defaultCreateInfo);
			}
		}

		if (isInvincible()) {
			mBulletManager->Create<CBullet>((int)m_x - 45 - rand() % 90, (int)m_y, BULLET_MAIN2, 0, 0.0, -60.0, defaultCreateInfo);
			mBulletManager->Create<CBullet>((int)m_x + 45 + rand() % 90, (int)m_y, BULLET_MAIN2, 0, 0.0, -60.0, defaultCreateInfo);
		}
	}

	if (mTimer % 4 == 0 && isInvincible()) {
		CCreateInfo info;
		for (int i = 0; i<16; i++) {
			int a = (i * 360 / 16);
			info.bltInfo.angle = a;
			int spd = 25 + rand() % 10;
			double vx = spd*sin(N_PI*a);
			double vy = spd*cos(N_PI*a);
			mBulletManager->Create<CBullet>((int)m_x + vx, (int)m_y + 15 + vy, 5, 0, vx, vy, info);
		}
	}
}

void CPlayer::ShotSub1(){
	int _power = mPower;
	if (mLife == 0)_power = MAX_POWER;
	mSE->PlayLoopSound(SE_PST1);
	double speed=40.0+_power*2.0;
	static const CCreateInfo defaultCreateInfo;
	CLine::drawGradationLine(m_bg,(int)m_x,(int)m_y-5,(int)m_x,(int)(m_y-5-speed*3),11,0xFFFFAA,0xFF5500,100,100,0,0,BATTLE_RECT);

	for(int i=0;i<mOptions;i++){//Option Shot
		CLine::drawGradationLine(m_bg,mOption[i].GetX(),mOption[i].GetY(),(int)m_x,(int)(m_y-5-speed*3),11,0xFFFFAA,0xFF5500,100,100,0,0,BATTLE_RECT);
		double vx = -(mOption[i].GetX() - m_x) / 3.0;
		double tmpSpd=speed+(mOption[i].GetY()-(m_y-5))/3.0;
		mBulletManager->Create<CBullet>((int)mOption[i].GetX(),(int)mOption[i].GetY()-5,4,0,vx,-tmpSpd,defaultCreateInfo);
	}

	if(mTimer%2==0)mBulletManager->Create<CBullet>((int)m_x,(int)m_y-5,4,0,0,-speed,defaultCreateInfo);
	int top=mBulletManager->GetHitTop();
	mEffectManager->CreateEffect((int)(m_x),(int)(m_y-5-speed*3),EFFECT_BACKLIGHT1,2,0.0,0.0,0,2,2,0);
	
	if(isInvincible()){
		for(int i=0;i<3;i++){
			int tx=(int)(m_x+200*sin(N_PI*(72*mTimer+120*i)));
			int ty=(int)(m_y-5+200*cos(N_PI*(72*mTimer+120*i)));
			CLine::drawGradationLine(m_bg,(int)m_x,(int)m_y-5,tx,ty,11,0xFFFFAA,0xFF5500,100,100,0,0,BATTLE_RECT);
		}
		for(int i=0;i<3;i++){
			int tx=(int)(m_x+200*sin(-N_PI*(72*mTimer+120*i)));
			int ty=(int)(m_y-5+200*cos(-N_PI*(72*mTimer+120*i)));
			CLine::drawGradationLine(m_bg,(int)m_x,(int)m_y-5,tx,ty,11,0xFFFFAA,0xFF5500,100,100,0,0,BATTLE_RECT);
		}
	}
	if(isInvincible()){
		CCreateInfo info;
		for(int i=0;i<16;i++){
			int a=(i*360/16);
			info.bltInfo.angle=a;
			int spd=25+rand()%10;
			double vx=spd*sin(N_PI*a);
			double vy=spd*cos(N_PI*a);
			mBulletManager->Create<CBullet>((int)m_x+vx,(int)m_y+15+vy,5,0,vx,vy,info);
		}
	}
}

void CPlayer::UpdateOption(){
	for(int i=mOptions;i<4;i++){ // i = 非表示オプションのインデックス
		if(mOption[i].GetTimer()!=0)mOption[i].Killed(); // Killed未処理ならKill
		mOption[i].SetPos((int)m_x,(int)m_y); //非表示オプションは自機に重ねる
	}
	if(mOptions==0)return; //以下はフォーメーションごとの処理
	if(mGameInfo->GetForm()==0){
		int DeltaA=360/mOptions;
		for(int i=0;i<mOptions;i++){
			CVector to(m_x-10+60*sin(-N_PI*(mTimer*5+i*DeltaA)),m_y+60*cos(-N_PI*(mTimer*5+i*DeltaA)));
			CVector from(m_x,m_y);
			mOption[i].SetPos(ExMath::asymptote(from,to,mOption[i].GetTimer()/4));
			int length=3*120*mInvincibleCounter/MAX_INVINCIBLE_COUNTER;
			CLine::drawFadeLine2(m_bg,mOption[i].GetX()+11,mOption[i].GetY()+6,length,90,6,0xAAFFFF,0,BATTLE_RECT);
			mOption[i].Update();
		}
	}else{
		static const int optionY[4]={ -80, 80,-40, 40,};
		static const int optionX[4]={ 10,10,-40,-40,};
		for(int i=0;i<mOptions;i++){
			CVector to(m_x+optionX[i],m_y+optionY[i]);
			CVector from(m_x,m_y);
			mOption[i].SetPos(ExMath::asymptote(from,to,mOption[i].GetTimer()/4));
			int length=3*120*mInvincibleCounter/MAX_INVINCIBLE_COUNTER;
			CLine::drawFadeLine2(m_bg,mOption[i].GetX()+6,mOption[i].GetY()+5,length,90,6,0xAAFFFF,0,BATTLE_RECT);
			mOption[i].Update();
		}
	}
}

void CPlayer::Killed(){
	mLife--;
	mInvincibleCounter=MAX_INVINCIBLE_COUNTER;
	mPower-=1;
	if(mPower<0)mPower=0;
	for(int i=0;i<14;i++){
		TEffectFile e[2] = { EFFECT_EXPLOSION_LIGHT_40 ,EFFECT_EXPLOSION_LIGHT_80 };
		mEffectManager->CreateEffect((int)m_x, (int)m_y, e[rand() % 2], 0, rand() % 30 - 15, rand() % 10 - 5,  0, 2, 0, 0);
		mEffectManager->CreateEffect((int)m_x, (int)m_y, e[rand() % 2], 0, -rand() % 30 + 15, rand() % 10 - 5, 0, 2, 0, 0);
	}
	for(int i=0;i<2;i++){
		mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_160,0,rand()%5+40-i*10,rand()%30-15,0,2,0,0);
		mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_160,0,-rand()%5-40+i*10,rand()%30-15,0,2,0,0);
	}
	for(int i=0;i<3;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y, EFFECT_EXPLOSION_80,0,rand()%20-10,rand()%5+30-i*7,0,2,0,0);
	mSE->PlaySingleSound(SE_DET1);
	m_y=1100;
	mCoughtFlg = false;
	//m_x=240;
	mKilledCounter=20;
}

void CPlayer::ItemGet(int ext,int point){//現在ポイント（point）未使用

	mScore->AddItem();
	mFlgGotItem=true;

	CBigInt bigInt(61+mScore->GetItems());
	bigInt.Mul(mScore->GetHaste());
	bigInt.Mul(mGameInfo->GetStage()/2+1);
	bigInt.Mul(mGameInfo->getInnerRank()*mGameInfo->getInnerRank() *mGameInfo->getInnerRank()+1);
	//bigInt.Mul((mGameInfo->GetLevel()+1)*(mGameInfo->GetLevel()+1));
	int _life = mLife + (MAX_LIFE - mLife) * mGameInfo->GetStage() / MAX_LIFE;
	int _power = mPower + (MAX_POWER - mPower) * mGameInfo->GetStage() / MAX_POWER;

	int sft = 13 *( _life + _power + mGameInfo->GetLevel()) / (7 + MAX_POWER + 5);
	if (sft != 0) {
		sft = rand() % sft;
		bigInt.Shift(sft);
	}
	
	mScore->AddScore(bigInt);

	int bonus = (mGameInfo->GetStage() != 3) ? 1 : 3;
	mExtendCounter += ext*bonus;
	if(mExtendCounter>=MAX_EXTEND_COUNTER){
		mSE->PlaySingleSound(SE_EXT1);
		mLife++;
		mFlgExtended=true;
		mGameInfo->SetQuake(QUAKE_MAGNITUDE);
		if(mLife>MAX_LIFE)mLife=MAX_LIFE;
		mExtendCounter=0;
		ResetMaxExtend();
		mInvincibleCounter=MAX_INVINCIBLE_COUNTER;// - GAME_LEVEL*20
		CCreateInfo info=CCreateInfoFactory::GetEffectBltInfo(0,0,2,0,0);
		for(int i=0;i<20;i++)mEffectManager->CreateEffect((int)m_x+40,(int)m_y, EFFECT_EXPLOSION_LIGHT_40,0,rand()%20-23,rand()%10-5, 0, 2, 0, 0);
	}
}

void CPlayer::DestroyEnemy(int i,int point){
	int bonus=(mGameInfo->GetStage()!=3 && mGameInfo->GetStage()!=6)?1:4;
	i-=mGameInfo->GetLevel()/2+2;
	mPowerUpCounter+=i*bonus;
	mFlgDestroyed=true;
	CBigInt bigInt(60);
	bigInt.Mul(mScore->GetHaste());
	bigInt.Mul(mGameInfo->GetLevel());
	bigInt.Mul(point);
	mScore->AddScore(bigInt);

	if(mPowerUpCounter>=MAX_LEVEL_UP_COUNTER){
		mGameInfo->SetQuake(QUAKE_MAGNITUDE);
		mGameInfo->addInnerRank(5);
		mSE->PlaySingleSound(SE_LVU1);
		ResetMaxLevelUp();
		mPower++;
		mFlgLevelUp=true;
		if (mPower > MAX_POWER)mPower = MAX_POWER;
		mPowerUpCounter=0;
		mInvincibleCounter=MAX_INVINCIBLE_COUNTER;// - GAME_LEVEL*20
		for(int i=0;i<20;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y+40, EFFECT_EXPLOSION_LIGHT_40,0,rand()%10-5,-rand()%25+33,0,2,0,0);
	}
}
