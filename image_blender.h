#ifndef _CIMAGE_BLENDER_H_
#define _CIMAGE_BLENDER_H_ 
#include "img32.h"
#include  "blt_info.h"
class CImageBlender{
protected:
	static RECT mWndRect;
	static const DWORD C_BLACK = 0xFF000000;
	static const DWORD C_WHITE = 0xFFFFFFFF;
	static const int b255=255;
	static const int fixfloat_const=65536;
	static const CBltInfo* defaultBltInfo;
	static void _BltNC(CImage32* dest,CImage32* src,const CBltInfo* info,int dx,int dy,int sx,int sy,int sw,int sh);
public:
	static void setWndRect(RECT r){mWndRect=r;}
	static bool Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy,int sx,int sy,int sw,int sh);
	static bool Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy);
	static bool Blt(CImage32* dest,CImage32* src,int dx,int dy);
	static bool BltNC(CImage32* dest,CImage32* src,const CBltInfo* info,int dx,int dy,int sx,int sy,int sw,int sh);
	static bool BltNC(CImage32* dest,CImage32* src,const CBltInfo* info,int dx,int dy);
	static bool BltNC(CImage32* dest,CImage32* src,int dx,int dy);
	typedef struct _TBltParams{
		int dx,dy;
		int sx,sy,sw,sh;
		int i_top,i_bottom;
		int alpha;
		DWORD color;
		int d_mem_distance;
		int s_mem_distance;
	} TBltParams;
	static void BNull(TBltParams params,DWORD* destadr,DWORD* srcadr);
	static void BMemCopy(TBltParams params,DWORD* destadr,DWORD* srcadr);
	static void BKey(TBltParams params,DWORD* destadr,DWORD* srcadr);///< J[L[]
	static void BAdd(TBltParams params,DWORD* destadr,DWORD* srcadr);    /// ΑZ]
	static void BMul(TBltParams params,DWORD* destadr,DWORD* srcadr);    /// ζZ]
	static void BMinus(TBltParams params,DWORD* destadr,DWORD* srcadr);  /// ΈZ
	static void BScreen(TBltParams params,DWORD* destadr,DWORD* srcadr);  /// XN[
	static void BAlpha(TBltParams params,DWORD* destadr,DWORD* srcadr);  /// alpha¬
	static void BRed(TBltParams params,DWORD* destadr,DWORD* srcadr);  ///Τ»
	static void BBlacken(TBltParams params,DWORD* destadr,DWORD* srcadr); ///»
	static void BKeyAdd(TBltParams params,DWORD* destadr,DWORD* srcadr); ///L[ΑZ
	static void BAlpha2(TBltParams params,DWORD* destadr,DWORD* srcadr); ///½Ο
	static void BWhiten(TBltParams params,DWORD* destadr,DWORD* srcadr); ///FΟΩ
	static void BKeyBlacken(TBltParams params,DWORD* destadr,DWORD* srcadr);///L[Lθ»
	static void BKeyStructure(TBltParams params,DWORD* destadr,DWORD* srcadr);///L[ θ\’F

	static void BMemCopySkip(TBltParams params, DWORD* destadr, DWORD* srcadr);///L[Θ΅XLbv
	static void BMemSkip(TBltParams params, DWORD* destadr, DWORD* srcadr);///L[ θXLbv
	static void BMemSkip2(TBltParams params, DWORD* destadr, DWORD* srcadr);///L[ θXLbv

	static void BMirrorKeyAdd(TBltParams params,DWORD* destadr,DWORD* srcadr);///½]L[ΑZ
	static void BMirrorKey(TBltParams params,DWORD* destadr,DWORD* srcadr);///L[½]
	static void BMirrorKeyBlacken(TBltParams params,DWORD* destadr,DWORD* srcadr);///½]L[
	static void BXMinus(TBltParams params,DWORD* destadr,DWORD* srcadr);///βFΈZ
	static void BMulColor(TBltParams params,DWORD* destadr,DWORD* srcadr);///FζZ
};
#endif

