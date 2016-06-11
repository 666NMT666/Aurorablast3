#ifndef _CECLIPSED_ELIPSE_H_
#define _CECLIPSED_ELIPSE_H_ 
#include "img32.h"
#include  "blt_info.h"

class CEclipsedElipse{
public:
	static void draw(CImage32 *dest,int x1,int y1,int rx1,int ry1,int x2,int y2,int rx2,int ry2,DWORD color);
};

void CEclipsedElipse::draw(CImage32 *dest,int x1,int y1,int rx1,int ry1,int x2,int y2,int rx2,int ry2,DWORD color){
	int midX=x1;
	int midY=y1;
	int midX2=x2;
	int midY2=y2;

	int top=max((midY-ry1),BATTLE_TOP);
	int bottom=min((midY2-ry2),BATTLE_BOTTOM-1);
	for(int i=top;i<bottom;i++){
		int y =i-midY;
		int r=(int)(rx1*sqrt((double)(ry1-y)*(ry1+y))/ry1);
		int left=max((midX-r),BATTLE_LEFT);
		int right=min((midX+r),BATTLE_RIGHT-1);
		DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
  		for(int j=left;j<=right;j++,destAdr++){
			//if((j-midX)*(j-midX)+y*y< r1*r1)
			{ *destAdr=color; }
		}
	}

	top=max((midY2-ry2),BATTLE_TOP);
	bottom=min((midY2+ry2),BATTLE_BOTTOM-1);
	for(int i=top ;i<bottom ;i++){
		int y =i-midY;
		int y_2=i-midY2;
		int r=(int)(rx1*sqrt((double)(ry1-y)*(ry1+y))/ry1);
		int left=max((midX-r),BATTLE_LEFT);
		int right=min((midX2),BATTLE_RIGHT-1);
		DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
		
		for(int j=left; j<right ;j++,destAdr++){
			if( (j-midX2)*(j-midX2)<=(rx2-rx2*y_2/ry2)*(rx2+rx2*y_2/ry2) ){break;}
			if( (j-midX)*(j-midX)<=(rx1-rx1*y/ry1)*(rx1+rx1*y/ry1) ){ *destAdr=color; }
		}
		left=max((midX),BATTLE_LEFT);
		right=min((midX+r),BATTLE_RIGHT-1);
		destAdr=(DWORD*)dest->PixelAddressNC(right,i);
		for(int j=right; j>=left ;j--,destAdr--){
  			if( (j-midX2)*(j-midX2)<=(rx2-rx2*y_2/ry2)*(rx2+rx2*y_2/ry2) ){break;}
			if( (j-midX)*(j-midX)<=(rx1-rx1*y/ry1)*(rx1+rx1*y/ry1) ){ *destAdr=color; }
		}
	}

	top=max((midY2+ry2),BATTLE_TOP);
	bottom=min((midY+ry1),BATTLE_BOTTOM-1);
	for(int i=top ;i<bottom;i++){
		int y =i-midY;	
		int r=(int)(rx1*sqrt((double)(ry1-y)*(ry1+y))/ry1);
		int left=max((midX-r),BATTLE_LEFT);
		int right=min((midX+r),BATTLE_RIGHT-1);
		DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
  		for(int j=left;j<=right;j++,destAdr++){
			//if((j-midX)*(j-midX)+y*y< r1*r1)
			{ *destAdr=color; }
		}
  	}	
}

#endif