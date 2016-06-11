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
	static void BKey(TBltParams params,DWORD* destadr,DWORD* srcadr);///< カラーキー転送
	static void BAdd(TBltParams params,DWORD* destadr,DWORD* srcadr);    /// 加算転送
	static void BMul(TBltParams params,DWORD* destadr,DWORD* srcadr);    /// 乗算転送
	static void BMinus(TBltParams params,DWORD* destadr,DWORD* srcadr);  /// 減算
	static void BScreen(TBltParams params,DWORD* destadr,DWORD* srcadr);  /// スクリーン
	static void BAlpha(TBltParams params,DWORD* destadr,DWORD* srcadr);  /// alpha合成
	static void BRed(TBltParams params,DWORD* destadr,DWORD* srcadr);  ///赤化
	static void BBlacken(TBltParams params,DWORD* destadr,DWORD* srcadr); ///黒化
	static void BKeyAdd(TBltParams params,DWORD* destadr,DWORD* srcadr); ///キー加算
	static void BAlpha2(TBltParams params,DWORD* destadr,DWORD* srcadr); ///平均
	static void BWhiten(TBltParams params,DWORD* destadr,DWORD* srcadr); ///白色変異
	static void BKeyBlacken(TBltParams params,DWORD* destadr,DWORD* srcadr);///キー有り黒化
	static void BKeyStructure(TBltParams params,DWORD* destadr,DWORD* srcadr);///キーあり構造色

	static void BMemCopySkip(TBltParams params, DWORD* destadr, DWORD* srcadr);///キーなしスキップ
	static void BMemSkip(TBltParams params, DWORD* destadr, DWORD* srcadr);///キーありスキップ
	static void BMemSkip2(TBltParams params, DWORD* destadr, DWORD* srcadr);///キーありスキップ

	static void BMirrorKeyAdd(TBltParams params,DWORD* destadr,DWORD* srcadr);///反転キー加算
	static void BMirrorKey(TBltParams params,DWORD* destadr,DWORD* srcadr);///キー反転
	static void BMirrorKeyBlacken(TBltParams params,DWORD* destadr,DWORD* srcadr);///反転キー黒
	static void BXMinus(TBltParams params,DWORD* destadr,DWORD* srcadr);///補色減算
	static void BMulColor(TBltParams params,DWORD* destadr,DWORD* srcadr);///色乗算
};
#endif

