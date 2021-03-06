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
  BLT_NULL,   /// ρ\¦
  BLT_MEMCOPY,  ///Rs[
  BLT_KEY,    /// L[FΘORs[
  BLT_ADD,    /// ΑZ]
  BLT_MUL,    /// ζZ]
  BLT_MINUS,  /// ΈZ
  BLT_SCREEN,  /// XN[
  BLT_ALPHA,  /// alpha¬
  BLT_BLACKEN, ///»
  BLT_WHITEN, ///»
  BLT_KEYADD, ///L[FΘOΑZ
  BLT_ALPHA2, ///½Ο


  BLT_KEYBLACKEN,///L[Lθ»
  BLT_MULCOLOR, /// ΑθFζZ
  BLT_RED,  ///½]
  BLT_STRUCTURE,///
  BLT_MEMCOPY_SKIP,
  BLT_SKIP,
	BLT_SKIP2,


  BLT_MIRRORKEY,///L[½]
  BLT_MIRRORKEYADD,///½]L[ΑZ
  
  BLT_XMINUS,///βFΈZ
  BLT_MIRRORBLACKEN,
  BLT_YELLOW,   /// ©FΑZ
  BLT_MULCOLOR__, /// ΑθFζZ
  BLT_GREENADD, /// ΞFΑZ]
  BLT_BLUEADD, /// ΒFΑZ]
};

enum TImageExt {
	EXT_BMP,
	EXT_PNG,
	EXT_JPG, // ’gp
	EXT_GIF //’gp
};

// ]
class CBltInfo{
public:
	TBltType type;  /// Z
	int alpha;     /// s§Ύx
	int angle;     /// ρ]px
	int link_x,link_y; /// NΐW
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