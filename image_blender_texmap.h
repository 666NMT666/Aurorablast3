#ifndef IMAGE_BLENDER_TEXMAP_H 
#define IMAGE_BLENDER_TEXMAP_H 
#include "img32.h"
#include "blt_info.h"
#include "texmap_side.h"

class CImageBlenderTexmap{
protected:
	static const int fixfloat_const=65536;
	static const DWORD C_BLACK = 0xFF000000;
	static const DWORD C_WHITE = 0xFFFFFFFF;
public:
	static bool Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy,int sx,int sy,int sw,int sh);
	static bool Texmap(const CBltInfo* info,RECT rc,int x,int y,double angle,double mul,double mul2,CImage32* src,int sx,int sy,int sw,int sh);
	static bool Texmap(const CBltInfo* info,RECT rc, CImage32* dest,CImage32* src, CTexMapVertex* vertex);
	
	static bool TexmapLine(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms);
	static bool TexmapLineRed(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms);
	static bool TexmapLineAdd(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms);
	static bool TexmapLineAddAlpha(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms);
	static bool TexmapLineStructure(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms);
};


#endif
