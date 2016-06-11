#ifndef _BLTINFO_H_
#define _BLTINFO_H_ 
#include <windows.h>
#include <math.h>
#include "prefix.h"
#include "vector.h"

union TARGB{
	DWORD ARGB;
	struct { BYTE B,G,R,A; };
};
enum TBltType
{
  BLT_NULL,   /// 非表示
  BLT_MEMCOPY,  ///コピー
  BLT_KEY,    /// キー色以外コピー
  BLT_ADD,    /// 加算転送
  BLT_MUL,    /// 乗算転送
  BLT_MINUS,  /// 減算
  BLT_SCREEN,  /// スクリーン
  BLT_ALPHA,  /// alpha合成
  BLT_BLACKEN, ///黒化
  BLT_WHITEN, ///白化
  BLT_KEYADD, ///キー色以外加算
  BLT_ALPHA2, ///平均


  BLT_KEYBLACKEN,///キー有り黒化
  BLT_MULCOLOR, /// 特定色乗算
  BLT_RED,  ///反転
  BLT_STRUCTURE,///
  BLT_MEMCOPY_SKIP,
  BLT_SKIP,
	BLT_SKIP2,


  BLT_MIRRORKEY,///キー反転
  BLT_MIRRORKEYADD,///反転キー加算
  
  BLT_XMINUS,///補色減算
  BLT_MIRRORBLACKEN,
  BLT_YELLOW,   /// 黄色加算
  BLT_MULCOLOR__, /// 特定色乗算
  BLT_GREENADD, /// 緑色加算転送
  BLT_BLUEADD, /// 青色加算転送
};

enum TImageExt {
	EXT_BMP,
	EXT_PNG,
	EXT_JPG, // 未使用
	EXT_GIF //未使用
};

// 転送
class CBltInfo{
public:
	TBltType type;  /// 演算
	int alpha;     /// 不透明度
	int angle;     /// 回転角度
	int link_x,link_y; /// リンク座標
	double zoom;
	double zoom_x;
	double zoom_y;
	int hole_x, hole_y, hole_r;
	DWORD ctr_color;///
	CBltInfo(){Clear();}
	CBltInfo( TBltType type_ ){Clear();type=type_;}
	CBltInfo( TBltType type_, int alpha_ ){Clear();type=type_;alpha=alpha_;}
	void Clear(){
		link_x=link_y=0;
		type = BLT_MEMCOPY;
		alpha = 255;
		ctr_color=0x0000000;
		zoom=1.0;
		zoom_x=1.0;
		zoom_y=1.0;
		angle=0;
		hole_x = hole_y = hole_r=0;
	}
};

#endif