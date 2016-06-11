#ifndef _CIMAGE_FILTERER_H_
#define _CIMAGE_FILTERER_H_ 
#include "img32.h"
class CImageFilter{
	
public:
	static void addBrightness(CImage32* img,int alpha){
		addBrightness(img,alpha,0,0,img->Width(),img->Height());
	}
	static void addBrightness(CImage32* img,int alpha,int x,int y,int w,int h);
	static void setColor(CImage32* img,DWORD color);
	static void operateAnd(CImage32* img,DWORD color);
	static void operateShift(CImage32* img,UINT rs,UINT gs,UINT bs);
};

void CImageFilter::setColor(CImage32* img,DWORD color){
	for(int i=0,j=0;i<img->Height();i++){
		DWORD* destadr=(DWORD*)img->PixelAddressNC(0,i);   
		for(j=0;j<img->Width();j++,destadr++){ *destadr=color; }
	}
}

void CImageFilter::operateAnd(CImage32* img,DWORD color){
	for(int i=0,j=0;i<img->Height();i++){
		DWORD* destadr=(DWORD*)img->PixelAddressNC(0,i);
		for(j=0;j<img->Width();j++,destadr++){ *destadr=(*destadr)&color; }
	}
}

void CImageFilter::operateShift(CImage32* img,UINT rs,UINT gs,UINT bs){
	for(int i=0,j=0;i<img->Height();i++){
		DWORD* destadr=(DWORD*)img->PixelAddressNC(0,i);
		for(j=0;j<img->Width();j++,destadr++){
			TARGB destpixel;
			destpixel.ARGB=*destadr;
			destpixel.R=(destpixel.R>>rs);
			destpixel.G=(destpixel.G>>gs);
			destpixel.B=(destpixel.B>>bs);
			*destadr=destpixel.ARGB;
		}
	}
}

void CImageFilter::addBrightness(CImage32* img,int alpha,int x,int y,int w,int h){
	TARGB destpixel;
	if(alpha>255)alpha=255;
	if(alpha<-255)alpha=-255;
	if(alpha<0){ //ˆÃ‚­‚·‚éê‡
		for(int i=0;i<h;i++){
			DWORD* destadr=(DWORD*)img->PixelAddressNC(x,y+i);
			for(int r,i=0;i<w;i++,destadr++){
				destpixel.ARGB=*destadr;
				r=destpixel.R+alpha;
				destpixel.R=destpixel.R<=-alpha?0:destpixel.R+alpha;
				destpixel.G=destpixel.G<=-alpha?0:destpixel.G+alpha;
				destpixel.B=destpixel.B<=-alpha?0:destpixel.B+alpha;
				*destadr=destpixel.ARGB;
			}
		}
	}else{ //–¾‚é‚­‚·‚éê‡
		for(int i=0;i<h;i++){
			DWORD* destadr=(DWORD*)img->PixelAddressNC(x,y+i);
			for(int r,i=0;i<w;i++,destadr++){
				destpixel.ARGB=*destadr;
				r=destpixel.R+alpha;
				destpixel.R=destpixel.R+alpha>=255?255:destpixel.R+alpha;
				destpixel.G=destpixel.G+alpha>=255?255:destpixel.G+alpha;
				destpixel.B=destpixel.B+alpha>=255?255:destpixel.B+alpha;
				*destadr=destpixel.ARGB;
			}
		}
	}
}
#endif