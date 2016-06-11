#ifndef _IMGDIB_CPP_
#define _IMGDIB_CPP_
#include "imgdib.h"
HINSTANCE CImageDIB::hInst;
CImageDIB::CImageDIB(int width,int height) : CImage32(NULL){
	m_buffer=NULL;
	Resize(width,height);
}
CImageDIB::CImageDIB() : CImage32(NULL){
	m_buffer=NULL;
	Resize(1,1);
}
CImageDIB::CImageDIB(const char* const fname):CImage32(NULL){
	 m_buffer=NULL;
	 Resize(1,1);
	 InitBitmap(fname);
 }

CImageDIB::~CImageDIB(){Free();}
void CImageDIB::Free(){
	if(m_buffer==NULL)return;
	SelectObject(m_hdc,m_h01dHandle);
	DeleteDC(m_hdc);
	DeleteObject(m_hBitmap);
	m_buffer=NULL;
}

void CImageDIB::InitBitmap(const char* const fname){
	HBITMAP hbmp;
	BITMAP bitmap;
	HDC hMemDC;
	hMemDC=CreateCompatibleDC(m_hdc);
	hbmp = (HBITMAP)LoadImage(hInst,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	GetObject(hbmp,sizeof(BITMAP),&bitmap);
	m_buffer=NULL;
	Resize(bitmap.bmWidth,bitmap.bmHeight);
	HBITMAP old=(HBITMAP)SelectObject(hMemDC,hbmp);
	BitBlt(m_hdc,0,0,bitmap.bmWidth,bitmap.bmHeight,hMemDC,0,0,SRCCOPY);
	DeleteDC(hMemDC);
	DeleteObject(hbmp);
}

void CImageDIB::Resize(const int width,const int height){
	Free();
	m_width=width;
	m_height=height;
	BITMAPINFO bmi;
	ZeroMemory(&bmi,sizeof(bmi));
	bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth=m_width;
	bmi.bmiHeader.biHeight=-m_height;
	bmi.bmiHeader.biPlanes=1;
	bmi.bmiHeader.biBitCount=32;
	bmi.bmiHeader.biCompression=BI_RGB;
	HDC tmpDC = GetDC(GetDesktopWindow());
	m_hBitmap=CreateDIBSection(tmpDC,&bmi,DIB_RGB_COLORS,(void**)&m_buffer,0,0);
	m_hdc=CreateCompatibleDC(tmpDC);
	m_h01dHandle=SelectObject(m_hdc,m_hBitmap);
	ReleaseDC(GetDesktopWindow(),tmpDC);
}

void CImageDIB::Display(int x,int y){
	Display(x,y,0,0,m_width,m_height);
}
void CImageDIB::Display(int x,int y,int sx,int sy,int sw,int sh){
	HDC destDC=GetDC(GetMainWindowHandle());
	BitBlt(destDC,x,y,sw,sh,m_hdc,sx,sy,SRCCOPY);
	ReleaseDC(GetMainWindowHandle(),destDC);
}

void CImageDIB::StretchDisplay(int x,int y,int sx,int sy,int sw,int sh,double scale){
	HDC destDC=GetDC(GetMainWindowHandle());
	StretchBlt(destDC,(int)(x*scale),(int)(y*scale),(int)(sw*scale),(int)(sh*scale),m_hdc,sx,sy,sw,sh,SRCCOPY);
	ReleaseDC(GetMainWindowHandle(),destDC);
}

void CImageDIB::StretchDisplay(int x,int y,double scale){
	StretchDisplay(x,y,0,0,m_width,m_height,scale);
}

void CImageDIB::DisplayText(HFONT hFont,int x,int y,const char* str,DWORD f_color,DWORD bg_color,int mode){
	SetTextColor(m_hdc,f_color);
	if(mode==0){
		SetBkMode(m_hdc,OPAQUE);
		SetBkColor(m_hdc,bg_color);
	}else{SetBkMode(m_hdc,TRANSPARENT);}
	SelectObject(m_hdc,hFont);
	TextOut(m_hdc,x,y,str,lstrlen(str));
}




void CImageDIB::InitBitmapZ(const char* const fname){
	do_decompress(fname,"tmp.bmp");
	load("tmp.bmp");
	remove("tmp.bmp");
}

#endif