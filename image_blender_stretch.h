#ifndef IMAGE_BLENDER_STRETCH_H 
#define IMAGE_BLENDER_STRETCH_H
#include "img32.h"
#include  "blt_info.h"
class CImageBlenderStretch{
protected:
	static const DWORD C_BLACK = 0xFF000000;
	static const DWORD C_WHITE = 0xFFFFFFFF;
	static void BltKey(DWORD* srcadr,DWORD* destadr,int DeltaX,int right);
	static void BltMemcopy(DWORD* srcadr,DWORD* destadr,int DeltaX,int right);
	static void BltKeyBlacken(DWORD* srcadr,DWORD* destadr,int DeltaX,int alpha,int righ);
	static void BltMul(DWORD* srcadr,DWORD* destadr,int DeltaX,int right);
	static void BltMulColor(DWORD* srcadr,DWORD* destadr ,int DeltaX,DWORD color,int right);
	static void BltAdd(DWORD* srcadr,DWORD* destadr,int DeltaX,int right);
	static void BltAddAlpha(DWORD* srcadr,DWORD* destadr,int DeltaX,int alpha,int right);
public:
	static bool Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy,int sx,int sy,int sw,int sh);
	static bool BltCurved(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,double(* func)(int i),int dx,int dy,int sx,int sy,int sw,int sh);
    //bool Blt(const CBltInfo* info,RECT rc,int dx,int dy,CImage32* src,int sx,int sy,int sw,int sh);
};
#endif
