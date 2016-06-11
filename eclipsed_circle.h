#ifndef _CECLIPSED_CIRCLE_H_
#define _CECLIPSED_CIRCLE_H_ 
#include "img32.h"
#include  "blt_info.h"

class CEclipsedCircle{
	static RECT mDefaultRect;
public:
	static void draw(CImage32 *dest,int x1,int y1,int r1,int x2,int y2,int r2,DWORD color,RECT rc=mDefaultRect);
	static void setRect(RECT rc){mDefaultRect=rc;}
};

RECT CEclipsedCircle::mDefaultRect={200,0,760,720};

void CEclipsedCircle::draw(CImage32 *dest,int x1,int y1,int r1,int x2,int y2,int r2,DWORD color,RECT rc){
	int midX=x1;
	int midY=y1;
	int midX2=x2;
	int midY2=y2;

	int top=max((midY-r1),mDefaultRect.top);
	int bottom=min((midY2-r2),mDefaultRect.bottom-1);
	for(int i=top;i<bottom;i++){
		int y =i-midY;
  		int r=(int)sqrt((double)r1*r1-y*y);
		int left=max((midX-r),mDefaultRect.left);
		int right=min((midX+r),mDefaultRect.right-1);
		DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
  		for(int j=left;j<=right;j++,destAdr++){
			if((j-midX)*(j-midX)+y*y< r1*r1){ *destAdr=color; }
		}
	}

	top=max((midY2-r2),mDefaultRect.top);
	bottom=min((midY2+r2),mDefaultRect.bottom-1);
	for(int i=top ;i<bottom ;i++){
		int y =i-midY;
		int y_2=i-midY2;
		int r=(int)sqrt((double)r1*r1 - y*y);
		int left=max((midX-r),mDefaultRect.left);
		int right=min((midX2),mDefaultRect.right-1);
		DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
		for(int j=left; j<right ;j++,destAdr++){
			if( (j-midX2)*(j-midX2)+y_2*y_2<= r2*r2 ){break;}
			if((j-midX)*(j-midX)+y*y< r1*r1){ *destAdr=color; }
		}
		left=max((midX),mDefaultRect.left);
		right=min((midX+r),mDefaultRect.right-1);
		destAdr=(DWORD*)dest->PixelAddressNC(right,i);
		for(int j=right; j>=left ;j--,destAdr--){
  			if( (j-midX2)*(j-midX2)+y_2*y_2<= r2*r2 ){break;}
  			if((j-midX)*(j-midX)+y*y< r1*r1){ *destAdr=color; }
		}
	}

	top=max((midY2+r2),mDefaultRect.top);
	bottom=min((midY+r1),mDefaultRect.bottom-1);
	for(int i=top ;i<bottom;i++){
		int y =i-midY;	
		int r=(int)sqrt((double)r1*r1-y*y);
		int left=max((midX-r),mDefaultRect.left);
		int right=min((midX+r),mDefaultRect.right-1);
		DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
  		for(int j=left;j<=right;j++,destAdr++){
			if((j-midX)*(j-midX)+y*y< r1*r1){ *destAdr=color; }
		}
  	}	
}

#endif