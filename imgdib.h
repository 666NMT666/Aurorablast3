#ifndef _IMGDIB_H_
#define _IMGDIB_H_
#include <windows.h>
#include "DxLib.h"
#include"img32.h"

#include "vector.h"
#include "comp.h"
#include "blt_info.h"
#include "img32_line.h"

class CImageDIB : public CImage32{
protected:
	HBITMAP m_hBitmap;
	HDC m_hdc;
	HGDIOBJ m_h01dHandle;
	CBltInfo defaultBltInfo;
public:
	static HINSTANCE hInst;
	CImageDIB();
	CImageDIB(int width, int height);
	CImageDIB(const char* const fname);
	~CImageDIB();
	static CImageDIB* GetInstance(){
		static CImageDIB instance;  // 唯一のインスタンス
		return &instance;
	}
	void Free();
	void Resize(const int width,const int height);
	void Display(int x,int y);
	void Display(int x,int y,int sx,int sy,int sw,int sh);
	void StretchDisplay(int x,int y,double scale);
	void StretchDisplay(int x,int y,int sx,int sy,int sw,int sh,double scale);
	void DisplayText(HFONT hFont,int x,int y,const char* str,DWORD f_color,DWORD bg_color,int mode);
	HDC hDC(){return m_hdc;}
	
	void InitBitmap(const char* const fname);
	void InitBitmapZ(const char* const fname);
	void InitBitmapPNG(const char* const fname);
	
};

#endif

