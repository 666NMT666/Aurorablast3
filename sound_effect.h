enum TLoopSound{
	SE_PST1, SE_KEZ1, SE_KEZ2, SE_SLD1, MAX_LOOP_SOUND
};
enum TSingleSound{
	SE_KEY1,SE_KEY2,SE_EXT1,SE_LVU1,SE_TND1,SE_KYP1,
	SE_ITM1,SE_POW1,SE_SHT1,SE_SHT2,
	SE_EXP1,SE_EXP2,SE_EXP3,SE_EXP4,SE_EXP5,SE_EXP6,
	
	SE_LAZ1,SE_BOM1,SE_SHT3,SE_LAZ3,SE_DET1,SE_LAZ4,
	SE_GST1,SE_GST2,SE_SHT4,
	SE_CRY1,
};

class CSoundEffect{
private:
	static const int MAX_SINGLE_SOUND=26;
	int mLoopSound[MAX_LOOP_SOUND];
	int mSingleSound[MAX_SINGLE_SOUND];
	bool mLoopSoundFlg[MAX_LOOP_SOUND];
	bool mSingleSoundFlg[MAX_SINGLE_SOUND];
public:
	CSoundEffect();
	static CSoundEffect* instance;
	static CSoundEffect* GetInstance(){return instance;};
	void initSE();
	void UpdateLoopSE();
	void UpdateSingleSE();
	void PlaySingleSound(TSingleSound i){mSingleSoundFlg[i]=true;}
	void PlayLoopSound(TLoopSound i){mLoopSoundFlg[i]=true;}
};
CSoundEffect* CSoundEffect::instance=new CSoundEffect();

CSoundEffect::CSoundEffect(){
	for(int i=0;i<MAX_LOOP_SOUND;i++){
		mLoopSound[i]=0;
		mLoopSoundFlg[i]=false;
	}
	for(int i=0;i<MAX_SINGLE_SOUND;i++){
		mSingleSound[i]=0;
		mSingleSoundFlg[i]=false;
	}
}
void CSoundEffect::UpdateLoopSE(){
	static int loopCounter[MAX_LOOP_SOUND]={0,0};
	for(int i=0;i<MAX_LOOP_SOUND;i++){
		if(loopCounter[i]<=0)StopSoundMem(mLoopSound[i]);
		if(mLoopSoundFlg[i]){loopCounter[i]=4;}
		if(loopCounter[i]==4 && CheckSoundMem(mLoopSound[i]==0))PlaySoundMem(mLoopSound[i],DX_PLAYTYPE_LOOP+DX_PLAYTYPE_BACK,true);
		if(--loopCounter[i]<0){ loopCounter[i]=0; StopSoundMem(mLoopSound[i]);} // カウンターが0未満になると音停止
		mLoopSoundFlg[i]=false;
	}
}

void CSoundEffect::UpdateSingleSE(){
	for(int i=0;i<MAX_SINGLE_SOUND;i++){
		if(mSingleSoundFlg[i]){ 
			mSingleSoundFlg[i]=false; 
			PlaySoundMem(mSingleSound[i],DX_PLAYTYPE_BACK,true);
		}// 指定効果音再生
	}
}

void CSoundEffect::initSE(){

	mLoopSound[0] = LoadSoundMem( "dat/sound/p-shot1.wav" );
	mLoopSound[1] = LoadSoundMem( "dat/sound/kezuri.wav" );
	mLoopSound[2] = LoadSoundMem( "dat/sound/kezuri2_.wav" );
	mLoopSound[3] = LoadSoundMem( "dat/sound/shield.wav" );

	mSingleSound[0] = LoadSoundMem("dat/sound/key.wav"); //SE_KEY1,
	mSingleSound[1] = LoadSoundMem("dat/sound/kettei1.wav");//SE_KEY2,
	mSingleSound[2] = LoadSoundMem("dat/sound/extend.wav");//SE_EXT1,
	mSingleSound[3] = LoadSoundMem("dat/sound/level.wav");//SE_LVU1,
	mSingleSound[4] = LoadSoundMem("dat/sound/lazer1.wav");//SE_TND1
	mSingleSound[5] = LoadSoundMem("dat/sound/kyupiin.wav");
	mSingleSound[6] = LoadSoundMem("dat/sound/item.wav");//SE_ITM1
	mSingleSound[7] = LoadSoundMem("dat/sound/power.wav");//SE_POW1

	mSingleSound[8] = LoadSoundMem("dat/sound/shoot1.wav");//SE_SHT1
	mSingleSound[9] = LoadSoundMem("dat/sound/shoot2.wav");//SE_SHT2
	mSingleSound[10] = LoadSoundMem("dat/sound/explosion1.wav");//SE_EXP1
	mSingleSound[11] = LoadSoundMem("dat/sound/explosion2.wav");//SE_EXP2
	mSingleSound[12] = LoadSoundMem("dat/sound/explosion3.wav");//SE_EXP3
	mSingleSound[13] = LoadSoundMem("dat/sound/explosion4.wav");//SE_EXP4
	mSingleSound[14] = LoadSoundMem("dat/sound/explosion5.wav");//SE_EXP5
	mSingleSound[15] = LoadSoundMem("dat/sound/explosion6.wav");//SE_EXP6
	mSingleSound[16] = LoadSoundMem("dat/sound/lazer2.wav");
	mSingleSound[17] = LoadSoundMem("dat/sound/bomb1.wav");
	mSingleSound[18] = LoadSoundMem("dat/sound/shoot3.wav");
	mSingleSound[19] = LoadSoundMem("dat/sound/lazer3.wav");
	mSingleSound[20] = LoadSoundMem("dat/sound/death1.wav");
	mSingleSound[21] = LoadSoundMem("dat/sound/lazer4.wav");
	mSingleSound[22] = LoadSoundMem("dat/sound/gunshot.wav");
	mSingleSound[23] = LoadSoundMem("dat/sound/gunshot2.wav");
	mSingleSound[24] = LoadSoundMem("dat/sound/shoot4.wav");
	mSingleSound[25] = LoadSoundMem("dat/sound/cry1.wav");
	for(int i=0;i<MAX_LOOP_SOUND;i++){
		mLoopSoundFlg[i]=false;
	}
	for(int i=0;i<MAX_SINGLE_SOUND;i++){
		mSingleSoundFlg[i]=false;
	}
}

