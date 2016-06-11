#pragma once
#include <Windows.h>
#include "img32.h"
#include "imgdib.h" 
#include "view.h"
#include "big_int.h"
class CScoreView :public CView{
protected:
	CBigInt *mScore;
	static const int NUM_INTERVAL = 4;

public:
	CScoreView(CImage32* dest, RECT rc, CBigInt* bi) : CView(dest,rc){
		mScore = bi;
	}

	void Update() {
		int numBlocks = mScore->GetMaxBlock();
		for (int i = 0; i < numBlocks; i++) {

		}
	}

};