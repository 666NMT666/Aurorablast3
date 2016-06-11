#pragma once
#include "img32.h"
class CAnimation {
	//1111111
protected:
	CImage32* mImages;
	unsigned int mNumFrames, mInterval;
	bool mFlgRepeat;
public:
	CAnimation() { mNumFrames = 0; }
	void init(int num, CImage32 * imgs, bool rep = false) {
		mImages = imgs;
		mNumFrames = num;
		mFlgRepeat = rep;
	}
};