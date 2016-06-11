#include "big_int.h"
static const int NUM_SCORE_BIGINT=20;
class CScore{
private:
	CBigInt mCurrentScore;
	int mItems,mHaste;
	static CScore* instance;
public:
	CScore();
	static CScore* GetInstance(){return instance;}
	void SetCurrentScore(DWORD i){
		//mCurrentScore=i;
	}
	void AddScore(const int i){
		mCurrentScore.Add(i);
	}
	void AddScore(const DWORD i){
		mCurrentScore.Add(i);
	}
	void AddScore(CBigInt i){
		mCurrentScore.Add(i);
	}
	void RezeroHaste() {
		mHaste = 0;
	}

	void AddItem(){
		mItems++;
	}
	void AddHaste(int i){
		mHaste+=i;
		if(mHaste>1999999999)mHaste=1999999999;
		if(mHaste<0)mHaste=0;
	}
	void Reset(){
		mItems=0;mHaste=0;
		mCurrentScore.Init("0");
	}
	CBigInt GetScore(){return mCurrentScore;}
	int GetScoreAtLank(int i){return 
		mCurrentScore.GetInt(i);
	}
	const int GetItems(){return mItems;}
	const int GetHaste(){return mHaste;}
	const int GetMaxBlock(){return mCurrentScore.GetMaxBlock();}

	void MulScore(int n){mCurrentScore.Mul(n);}
};
CScore* CScore::instance=new CScore();
CScore::CScore(){
	Reset();
}
