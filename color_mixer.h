#include <Windows.h>
#include "blt_info.h"
namespace ColorUtil{
	DWORD Alpha(DWORD dest,DWORD src,int alpha){
		TARGB destpixel,srcpixel;
		destpixel.ARGB=dest;
		srcpixel.ARGB=src;
		destpixel.R=(destpixel.R*(255-alpha)+srcpixel.R*alpha)>>8;
		destpixel.G=(destpixel.G*(255-alpha)+srcpixel.G*alpha)>>8;
		destpixel.B=(destpixel.B*(255-alpha)+srcpixel.B*alpha)>>8;
		return destpixel.ARGB;
	}
};