#pragma once
#include <Windows.h>
#include "img32.h"
#include "imgdib.h" 

class CView{
protected:
	RECT mRect;
	CImage32* mImgDest;
public:
	CView(){
		mImgDest=NULL;
		mRect.bottom=mRect.left=mRect.right=mRect.top=0;
	}
	CView(CImage32* dest,int l,int t,int r,int b){
		mImgDest=dest;
		mRect.left=l; mRect.top=t;
		mRect.right=r; mRect.bottom=b;
	}
	CView(CImage32* dest,RECT rc){
		mImgDest=dest;
		mRect=rc;
	}
	virtual void Update() {}
};