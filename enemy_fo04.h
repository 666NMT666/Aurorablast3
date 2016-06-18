class CEnemyFO04:public CEnemy{
protected:
	double mTargetX;
public:
	void UpdateEnemy();
	void CreateEnemy();
	void Killed();
};
void CEnemyFO04::CreateEnemy(){
	mKilledSound=SE_EXP5;
	mTargetX=m_x;
	m_y=mCreateInfo.params[0];
	if(m_x<480)m_x=BATTLE_LEFT-m_width/2;
	else m_x=BATTLE_RIGHT+m_width/2;
	m_vy=0;
}
void CEnemyFO04::UpdateEnemy(){
	int lineLength=200;
	if(mTimer<120){
		lineLength=200-mTimer;
	}else{
		lineLength=200-120+mTimer;
	}
	if(mTimer<40){
		m_x=ExMath::superElipse(m_x,mTargetX,mTimer,180,1.0);
	}else if(mTimer<180){
		m_x=ExMath::superElipse(m_x,mTargetX,mTimer,180,1.0);
		if(mTimer%4==0 && mTimer%30<15){
			AngleShot(m_x-40,m_y,EB_26,3,8,45+15*sin(N_PI*5*mTimer)+90);
			AngleShot(m_x+40,m_y,EB_26,3,8,-45-15*sin(N_PI*5*mTimer)+90);
		}
		if(mTimer==80 && mGameLevel>=3){
			mSE->PlaySingleSound(SE_EXP5);
			NormalShot((int)m_x,(int)m_y,EDAB_66,0,20+mGameLevel*3);
			NormalShot((int)m_x,(int)m_y,EDAB_66,0,16+mGameLevel*3);
			for(int i=0;i<15;i++)AngleShot((int)m_x,(int)m_y,EB_26,2,5+i+mGameLevel*3,(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY())+rand()%10-5);
		}
		m_vy=(mGameLevel+1)*0.2;
	}else{
		if(mGameLevel>1 && mTimer%3==0){
			NormalShot((int)m_x, (int)m_y+m_height/2-rand()%40,EB_16,0,8,0,rand()%10-5);
			NormalShot((int)m_x, (int)m_y-rand()%40,EB_16,0,8,0,rand()%10-5);
		}
		m_vy-=0.1;
	}
	if(mTimer%8==0 && mTimer>100){
		mSE->PlaySingleSound(SE_EXP1);
		if(mTimer%70>30)return; // “ïˆÕ“x‚²‚Æ‚É•Ï‰»
		int a=(int)ExMath::angleBetweenPoints((int)m_x,(int)m_y,mPlayer->GetX(),mPlayer->GetY());
		int p[5]={1,180-a,0,0,0};
		CCreateInfo info(p);
		double vel=13.0+mCounter++;
		if(vel>25+mGameLevel*2)vel=25+mGameLevel*2;
		mEMManager->Create<CEnemyMissile>((int)m_x,(int)m_y,1,0,vel*cos(N_PI*a),vel*sin(N_PI*a),info);
		mEMManager->Create<CEnemyMissile>((int)m_x,(int)m_y,1,0,(vel-4)*cos(N_PI*a),(vel-4)*sin(N_PI*a),info);
	}
	BackLightMedium();
	CLine::drawFadeLine2(m_bg,(int)m_x+30,(int)m_y+28,lineLength   ,90,8,0xFFDDFF,0,BATTLE_RECT);
	CLine::drawFadeLine2(m_bg,(int)m_x-30,(int)m_y+28,lineLength-10,90,6,0xFFDDFF,0,BATTLE_RECT);
}
void CEnemyFO04::Killed(){
	if(mKilledTimer==0) mSE->PlaySingleSound(mKilledSound);

	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_160,0,rand()%30-15,-rand()%10+60-i*10,0,2,0,0);
	for(int i=0;i<4;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80,0,rand()%20-10,-rand()%5+50-i*7,0,2,0,0);
	for(int i=0;i<3;i++)mEffectManager->CreateEffect((int)m_x,(int)m_y,EFFECT_EXPLOSION_80_2,0,rand()%3-1,-rand()%5+5+i*10,0,4,0,0);
	mEffectManager->CreateEffect((int)m_x,(int)m_y+15,EFFECT_EXPLOSION_HEAD1,0,0,-15,0,1,0,0);
	for(int i=0;i<8;i++){
		int v=rand()%40+100;
		double vx=v*cos(N_PI*(10*i+50));
		double vy=-v*sin(N_PI*(10*i+50))-20;
		mDebrisManager->CreateDebris((int)m_x,(int)m_y,1,0,vx,vy,0,0,2,10,0);
	}
	mDelFlg=true;
	int pointMul=300-mTimer;
	if(pointMul<0)pointMul=0;
	mPlayer->DestroyEnemy(16,pointMul*pointMul*pointMul);
	for(int i=0;i<20;i++)mItemManager->CreateItem((int)m_x,(int)m_y,rand()%2,0,rand()%20-10,rand()%20);
}