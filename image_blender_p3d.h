#pragma once

#include "img32.h"
#include  "blt_info.h"
namespace CImageBlenderP3D {
	const DWORD C_BLACK = 0xFF000000;
	const DWORD C_WHITE = 0xFFFFFFFF;
	void getShadow(int* colors, int length,int minus) {
		for (int i = 0; i < length; i++) {
			int tmp = 255 *i / length + minus;
			if (tmp > 255)tmp = 255;
			colors[i] = tmp;
		}
	}
	void BltFloor(CImage32* dest, CImage32* src, RECT rc,
		unsigned int foot,
		const int cx,
		const int phaseX,
		const int phaseY)
	{
		const unsigned int sw = src->Width();
		const unsigned int sh = src->Height();
		if (foot < 1)foot = 1;
		static const int fixfloat_const = 1 << 16;
		for (int i = rc.top + foot; i < rc.bottom; i++) {
			int deltaY = (rc.bottom * 100 / (i - rc.top) + phaseY) % sh;
			DWORD* destAddr = (DWORD*)dest->PixelAddressNC(rc.left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddressNC(0, deltaY); 
			int dx = fixfloat_const * 100 / (i - rc.top);
			const int dxcx = dx*cx;
			int jdx = rc.left*dx;
			for (int j = rc.left; j < rc.right; j++, jdx+=dx ) {
				int deltaX = (((dxcx - jdx) >> 16) + phaseX) % sw;
				*destAddr = *(srcAddr + deltaX);//*destAddr = src->PixelGetNC(deltaX, deltaY);
				destAddr++;
			}
		}
	}

	void BltRoof(CImage32* dest, CImage32* src, RECT rc,
		unsigned int foot,
		const int cx,
		const int phaseX,
		const int phaseY)
	{
		const unsigned int sw = src->Width();
		const unsigned int sh = src->Height();
		if (foot < 1)foot = 1;
		static const int fixfloat_const = 1 << 16;
		for (int i = rc.bottom - foot; i >= rc.top; i--) {
			int deltaY = (rc.bottom * 100 / (i + foot - rc.top) + phaseY) % sh;
			DWORD* destAddr = (DWORD*)dest->PixelAddressNC(rc.left, rc.bottom-foot -i);
			DWORD* srcAddr = (DWORD*)src->PixelAddressNC(0, deltaY); 
			int dx = fixfloat_const * 100 / (i + foot - rc.top);
			const int dxcx = dx*cx;
			int jdx = rc.left*dx;
			for (int j = rc.left; j < rc.right; j++, jdx += dx) {
				int deltaX = (((dxcx - jdx) >> 16) + phaseX) % sw;
				*destAddr = *(srcAddr + deltaX); 
				//*destAddr = src->PixelGetNC(deltaX, deltaY);
				destAddr++;
			}
		}
	}

	
	
	
	void BltFloor(CImage32* dest, CImage32* src, RECT rc,
		unsigned int foot,
		const int cx,
		const int phaseX,
		const int phaseY,
		int *grad, int gradLength)
	{
		const unsigned int sw = src->Width();
		const unsigned int sh = src->Height();
		if (foot < 1)foot = 1;
		static const int fixfloat_const = 1 << 16;
		int l = 0;
		for (int i = rc.top + foot; i < rc.bottom && l < gradLength; i++,l++) {
			int deltaY = (rc.bottom * 100 / (i - rc.top) + phaseY) % sh;
			DWORD* destAddr = (DWORD*)dest->PixelAddressNC(rc.left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddressNC(0, deltaY);
			int dx = fixfloat_const * 100 / (i - rc.top);
			const int dxcx = dx*cx;
			int jdx = rc.left*dx;
			TARGB destPixel;

			for (int j = rc.left; j < rc.right; j++, jdx += dx) {
				int deltaX = (((dxcx - jdx) >> 16) + phaseX) % sw;
				destPixel.ARGB = *(srcAddr + deltaX); //destPixel.ARGB = src->PixelGetNC(deltaX, deltaY);
				destPixel.R = (destPixel.R * grad[l]) >> 8;
				destPixel.G = (destPixel.G * grad[l]) >> 8;
				destPixel.B = (destPixel.B * grad[l]) >> 8;
				*destAddr = destPixel.ARGB;
				destAddr++;
			}
		}

		for (int i = rc.top + foot+gradLength; i < rc.bottom; i++) {
			int deltaY = (rc.bottom * 100 / (i - rc.top) + phaseY) % sh;
			DWORD* destAddr = (DWORD*)dest->PixelAddressNC(rc.left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddressNC(0, deltaY);
			int dx = fixfloat_const * 100 / (i - rc.top);
			const int dxcx = dx*cx;
			int jdx = rc.left*dx;
			for (int j = rc.left; j < rc.right; j++, jdx += dx) {
				int deltaX = (((dxcx - jdx) >> 16) + phaseX) % sw;
				*destAddr = *(srcAddr + deltaX);
				destAddr++;
			}
		}
	}
	
	
	void BltRoof(CImage32* dest, CImage32* src, RECT rc,
		unsigned int foot,
		const int cx,
		const int phaseX,
		const int phaseY,
		int *grad,int gradLength)
	{
		const unsigned int sw = src->Width();
		const unsigned int sh = src->Height();
		if (foot < 1)foot = 1;
		int l = 0;
		static const int fixfloat_const = 1 << 16;
		for (int i = rc.bottom - foot; (i > rc.top && l<gradLength); i--, l++) {
			int deltaY = (rc.bottom * 100 / (rc.bottom - i + foot) + phaseY) % sh;
			DWORD* destAddr = (DWORD*)dest->PixelAddressNC(rc.left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddressNC(0, deltaY);
			int dx = fixfloat_const * 100 / (rc.bottom - i + foot);
			const int dxcx = dx*cx;
			int jdx = rc.left*dx;
			TARGB destPixel;
			for (int j = rc.left; j < rc.right; j++, jdx += dx) {
				int deltaX = (((dxcx - jdx) >> 16) + phaseX) % sw;
				destPixel.ARGB = *(srcAddr + deltaX);
				destPixel.R = (destPixel.R * grad[l]) >> 8;
				destPixel.G = (destPixel.G * grad[l]) >> 8;
				destPixel.B = (destPixel.B * grad[l]) >> 8;
				*destAddr = destPixel.ARGB;
				destAddr++;
			}
		}
		for (int i = rc.bottom - foot - gradLength; i >= rc.top; i--) {
			int deltaY = (rc.bottom * 100 / (rc.bottom - i + foot) + phaseY) % sh;
			DWORD* destAddr = (DWORD*)dest->PixelAddressNC(rc.left, i);
			DWORD* srcAddr = (DWORD*)src->PixelAddressNC(0, deltaY);
			int dx = fixfloat_const * 100 / (rc.bottom - i + foot);
			const int dxcx = dx*cx;
			int jdx = rc.left*dx;
			for (int j = rc.left; j < rc.right; j++, jdx += dx) {
				int deltaX = (((dxcx - jdx) >> 16) + phaseX) % sw;
				*destAddr = *(srcAddr + deltaX); //src->PixelGetNC(deltaX, deltaY);
				destAddr++;
			}
		}
	}


};