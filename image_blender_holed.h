
#pragma once
#include <Windows.h>
#include <math.h>
#include "img32.h"
#include  "blt_info.h"

namespace CImageBlenderHoled{
	void Blt(CImage32* dest, CImage32* src, RECT rc, int x, int y, int w, int h, int hx, int hy, int r) {
		int top = y;
		int bottom = top + h;
		if (top < rc.top) { top = rc.top; }
		if (bottom > rc.bottom) { bottom = rc.bottom; }

		int left = x;
		int right = left + w;
		if (left < rc.left) { left = rc.left; }
		if (right > rc.right) { right = rc.right; }

		for (int i = top; i < y + h / 2 - r; i++) {
			DWORD* destAddr = (DWORD*)dest->PixelAddress(left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddress(0, i-top);
			for (int j = left; j < right;j++, destAddr++, srcAddr++)
				if(*srcAddr!=0xFFFFFFFF)*destAddr = *srcAddr;
		}

		for (int i = y + h / 2 -r; i < y + h / 2 + r; i++) {
			if (i < 0 || i < top)continue;
			//if (i>bottom || i)
			DWORD* destAddr = (DWORD*)dest->PixelAddress(left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddress(0, i - top);

			double rr = r*r - (i - y - h / 2)*(i - y - h / 2);
			int dx = 0;
			if(rr!=0.0) dx = (int)sqrt(rr);

			for (int j = left; j < x + w / 2 - dx; j++, destAddr++, srcAddr++)
				if (*srcAddr != 0xFFFFFFFF)*destAddr = *srcAddr;

			destAddr = (DWORD*)dest->PixelAddress(x + w / 2 + dx, i);
			srcAddr = (DWORD*)src->PixelAddress(w / 2 + dx, i - top);
			//destAddr += dx+ dx;
			//srcAddr += dx+ dx;
			for (int j = x + w / 2 + dx; j < right; j++, destAddr++, srcAddr++)
				if (*srcAddr != 0xFFFFFFFF)*destAddr = *srcAddr;

		}


		for (int i = y + h / 2 + r; i < bottom; i++) {
			DWORD* destAddr = (DWORD*)dest->PixelAddress(left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddress(0, i - top);
			for (int j = left; j < right; j++, destAddr++, srcAddr++)
				if (*srcAddr != 0xFFFFFFFF)*destAddr = *srcAddr;
		}
	}
};
