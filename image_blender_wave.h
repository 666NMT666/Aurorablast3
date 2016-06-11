#ifndef _CIMAGE_BLENDER_WAVE_H_
#define _CIMAGE_BLENDER_WAVE_H_ 
#include "img32.h"
#include  "blt_info.h"

typedef struct _TWaveInfo{
    double amplitude;
    double length;
    double phase;
    double v_amplitude;
    double v_length;
    double v_phase;
    bool v_loop_flg;
} TWaveInfo;


namespace CImageBlenderWave{
	const DWORD C_WHITE=0xFFFFFFFF;
	const DWORD C_BLACK = 0xFF000000;
	const int b255=255;
	const int fixfloat_const=65536;
	bool Blt(CImage32* dest, CImage32* src, const TBltType t, RECT rc, TWaveInfo wi, int dx, int dy, int sx, int sy, int sw, int sh) {
		if (rc.left<0) { rc.left = 0; }
		if (rc.top<0) { rc.top = 0; }
		if (rc.right>dest->Width()) { rc.right = dest->Width(); }
		if (rc.bottom>dest->Height()) { rc.bottom = dest->Height(); }
		//if (dx >= rc.right || dx + sw <= rc.left)return true;
		if (dy >= rc.bottom || dy + sh < rc.top) { return true; }
		if (dy<rc.top) {
			sh -= rc.top - dy;
			sy += rc.top - dy;
			dy = rc.top;
		}
		if (dy + sh >= rc.bottom) {
			if (dy >= rc.bottom)return true;
			sh -= (dy + sh - rc.bottom);
		}

		for (int i = dy; i<dy + sh; ++i) {
			int w = sw;
			int dx2 = dx + (int)(wi.amplitude*sin(3.1415 * 2 * i / wi.length + wi.phase));
			int sx2 = sx;
			if (dx2 + w >= rc.right) {
				w = rc.right - dx2 -1;
				if (w <= 0)continue;
			}
			if (dx2<rc.left) {
				sx2 += rc.left - dx2;
				w -= rc.left - dx2;
				if (w <= 0)continue;
				dx2 = rc.left;
			}

			int sy2 = (sy + i + (int)(wi.v_amplitude*sin(3.1415 * 2 * i / wi.v_length + wi.v_phase)));
			if (wi.v_loop_flg) { sy2 %= src->Height(); }
			else {
				if (sy2 >= src->Height())return true;
				if (sy2<0)continue;
			}

			DWORD* destadr = (DWORD*)dest->PixelAddress(dx2, i);
			DWORD* srcadr = (DWORD*)src->PixelAddress(sx2, sy2);
			DWORD* right = destadr + w;
			if (t == BLT_MEMCOPY) {
				for (; destadr<right; srcadr++, destadr++) {
					*destadr = *srcadr;
				}
			}
			else {
				for (; destadr<right; srcadr++, destadr++) {
					if (*destadr != C_WHITE)*destadr = *srcadr;
				}
			}
		}
		return true;
	}
	bool Blt(CImage32* dest,CImage32* src,const TBltType t,RECT rc,TWaveInfo wi,int dx,int dy) { return Blt(dest, src, t, rc, wi, dx, dy, 0, 0, src->Width(), src->Height()); }

	void Spread(CImage32* dest, CImage32* src, const TBltType t, RECT rc, TWaveInfo wi) {
		int ny = (rc.bottom - rc.top) / src->Height() + 1;
		int nx = (rc.right - rc.left) / src->Width() + 1;
		for (int i = 0; i < ny; i++) {
			for (int j = -1; j < nx+1; j++) {
				Blt(dest, src, t, rc,wi, rc.left+j*src->Width(), rc.top+i*src->Height());
			}
		}
	}
};


#endif

