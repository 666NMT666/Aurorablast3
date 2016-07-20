#pragma once

const int GAME_START_STAGE = 5;
const int MAX_STAGES = 7;
const int MAX_STAGE_TRIAL = 6;

class CGameInfo{
private:
	int mLevel,mMainWepon,mSubWepon,mUniqueWepon,mForm,mStage,mContinueCounter;
	bool mReplayFlg,mContinueFlg,mTrialFlg,mStoryModeFlg;
	bool mEnemyStopFlg;
	int mInnerRank;
	static CGameInfo* instance;
	bool mRevisionCancelFlg, mChatFlg;
	double mQuake;
	static const int MAX_INNER_RANK = 255;
	static const double QUAKE_DAMP;
public:
	static const int NUM_LEVEL=5;
	static const int MAX_CONTINUES[5];
	CGameInfo():mLevel(0),mMainWepon(0),mSubWepon(0),mUniqueWepon(0),mForm(0),mQuake(0.0){Reset();}
	void Reset(){
		mInnerRank = 0;
		mStoryModeFlg = false;
		mEnemyStopFlg=false;
		mTrialFlg=false; /////////////////Trial !!?
		mRevisionCancelFlg=false;
		mStage=GAME_START_STAGE;
		mReplayFlg=false;
		mContinueFlg=false;
		mChatFlg = false;
		mContinueCounter=0;
		mQuake=0.0;
	}
	const bool isTrial(){return mTrialFlg;}
	const int GetLevel(){return mLevel;}
	void SetLevel(const int i){mLevel=i;}

	const bool isStoryMode() { return mStoryModeFlg; }
	void SetStoryMode(bool i) { mStoryModeFlg = i; }
	void SetStoryMode(int i) { mStoryModeFlg = (i==1); }

	const bool isOnChat() { return mChatFlg; }
	void SetChat(bool flg) { mChatFlg = flg; }

	const int GetForm(){return mForm;}
	void SetForm(const int i){mForm=i;}
	const int GetMainWepon(){return mMainWepon;}
	void SetMainWepon(const int i){mMainWepon=i;}
	const int GetSubWepon(){return mSubWepon;}
	void SetSubWepon(const int i){mSubWepon=i;}
	const int GetUniqueWepon(){return mUniqueWepon;}
	void SetUniqueWepon(const int i){mUniqueWepon=i;}
	
	const int GetStage(){return mStage;}
	void SetStage(const int i){mStage=i;}
	void GoToNextStage(){mStage++;}

	const bool isReplay(){return mReplayFlg;}
	void SetReplay(const bool r){mReplayFlg=r;}
	void Continued(){mContinueFlg=true;mContinueCounter++;}
	bool didContinue(){return mContinueFlg;}
	bool GetRevisionCancelFlg(){return mRevisionCancelFlg;}
	void SetRevisionCancelFlg(bool b){mRevisionCancelFlg=b;}
	static CGameInfo* GetInstance(){return instance;}
	bool EnemyStopCheck(){
		return mEnemyStopFlg;
	}
	void StopEnemy(){ mEnemyStopFlg=true; }
	void SetEnemyStopFlg(bool b){mEnemyStopFlg=b;}
	void SetQuake(int q){mQuake=q;}
	const double GetQuake(){return mQuake;}
	void DampQuake(){mQuake*=QUAKE_DAMP;}
	void AddQuake(int max,int q){
		if(mQuake>max)return;
		else if(mQuake+q>max)mQuake=max;
		else mQuake+=q;
	}
	int LeftContinues() {
		return MAX_CONTINUES[mLevel]-mContinueCounter;
	}
	const int getInnerRank() { return mInnerRank; }
	void addInnerRank(unsigned int i);
	void minusInnerRank(unsigned int i);
};
const double CGameInfo::QUAKE_DAMP=0.93;
const int CGameInfo::MAX_CONTINUES[5] = {4,3,2,1,0};
CGameInfo* CGameInfo::instance=new CGameInfo();
void CGameInfo::addInnerRank(unsigned int i) {
	mInnerRank += i;
	if (mInnerRank > MAX_INNER_RANK) {
		mInnerRank = MAX_INNER_RANK;
	}
}
void CGameInfo::minusInnerRank(unsigned int i) {
	mInnerRank -= i;
	if (mInnerRank<0) {
		mInnerRank = 0;
	}
}