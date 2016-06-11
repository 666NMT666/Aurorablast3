#include <Windows.h>
#include <math.h>
#include "img32.h"
#include "imgdib.h"
#include "view.h"

class CScrollView : public CView{
protected:
	int mScrollX,mScrollY;

public:
	CScrollView() :CView() {
		initScroll();
	}
	~CScrollView() {

	}
	void initScroll() {
		mScrollX = mScrollY = 0;
	}

};
