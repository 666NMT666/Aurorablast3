#include "image_blender_stretch.h"

bool CImageBlenderStretch::Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy,int sx,int sy,int sw,int sh){
	static const int fixfloat_const=65536;
	double zoom_y=info->zoom_y;
	double zoom_x=info->zoom_x;
	if(info->zoom!=1.0){ zoom_x=zoom_y=info->zoom; }
	int DeltaY=(int)(fixfloat_const/zoom_y);
	int DeltaX=(int)(fixfloat_const/zoom_x);
	if(dx+sw*zoom_x>=rc.right)sw=(((rc.right-dx)*DeltaX)>>16)-1;
	if(dx<rc.left){
		int l=rc.left-dx;
		sw-=((l-1)*DeltaX)>>16;     //sw-=(int)((l-1)/zoom);
		if(sw<=0)return true;  
		sx+=(l*DeltaX)>>16;         //sx+=(int)(l/zoom);
		dx=rc.left;
	}

	int bottom=dy+(int)(sh*zoom_y);
	int right=(int)(sw*zoom_x);
	DWORD *srcadr,*destadr;
	for(int i=dy;i<bottom;i++){
		if(rc.top<=i && i<rc.bottom){   
			srcadr=(DWORD*)src->PixelAddressNC(sx,sy+(((i-dy)*DeltaY)>>16));
			destadr=(DWORD*)dest->PixelAddressNC(dx,i);
			if(info->type == BLT_KEY)BltKey(srcadr,destadr,DeltaX,right);
			else if(info->type == BLT_MEMCOPY)BltMemcopy(srcadr,destadr,DeltaX,right);
			else if(info->type == BLT_MUL)BltMul(srcadr,destadr,DeltaX,right);
			else if(info->type == BLT_KEYBLACKEN)BltKeyBlacken(srcadr,destadr,DeltaX,info->alpha,right);
			else if(info->type == BLT_MULCOLOR)BltMulColor(srcadr,destadr,DeltaX,info->ctr_color,right);
			else if(info->type==BLT_ADD){
                if(info->alpha==255)BltAdd(srcadr,destadr,DeltaX,right);
				else BltAddAlpha(srcadr,destadr,DeltaY,info->alpha,right);
			}
		}
	}
	return true;
}

bool CImageBlenderStretch::BltCurved(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,double(* func)(int i),int dx,int dy,int sx,int sy,int sw,int sh){
	if(rc.right>dest->Width())rc.right=dest->Width();
	static const int fixfloat_const=65536;
	double zoom_y=info->zoom_y;
	double zoom_x=info->zoom_x;
	if(info->zoom!=1.0){ zoom_x=zoom_y=info->zoom; }
	int DeltaY=(int)(fixfloat_const/zoom_y);
	int bottom=dy+(int)(sh*zoom_y);
	
	DWORD *srcadr,*destadr;
	for(int i=dy;i<bottom;i++){
		int sw2=sw;
		double z=func(i);
		int dx2=dx-sw2*z/2;
		int sx2=sx;  
		int DeltaX=(int)(fixfloat_const/z);
		if(dx2+sw2*z>=rc.right)sw2=(rc.right-dx2)/z;
		if(dx2<rc.left){
			int l=rc.left-dx2;
			sw2-=((l-1)*DeltaX)>>16;     //sw-=(int)((l-1)/zoom);
			if(sw2<=0)continue;  
			sx2+=(l*DeltaX)>>16;         //sx+=(int)(l/zoom);
			dx2=rc.left;
		}
		int right=(int)(sw2*z);
		if(rc.top<=i && i<rc.bottom){   
			srcadr=(DWORD*)src->PixelAddressNC(sx2,sy+(((i-dy)*DeltaY)>>16));
			destadr=(DWORD*)dest->PixelAddressNC(dx2,i);
			if(info->type == BLT_KEY)BltKey(srcadr,destadr,DeltaX,right);
			else if(info->type == BLT_MEMCOPY)BltMemcopy(srcadr,destadr,DeltaX,right);
			else if(info->type == BLT_MUL)BltMul(srcadr,destadr,DeltaX,right);
			else if(info->type == BLT_KEYBLACKEN)BltKeyBlacken(srcadr,destadr,DeltaX,info->alpha,right);
			else if(info->type == BLT_MULCOLOR)BltMulColor(srcadr,destadr,DeltaX,info->ctr_color,right);
			else if(info->type==BLT_ADD){
                if(info->alpha==255)BltAdd(srcadr,destadr,DeltaX,right);
				else BltAddAlpha(srcadr,destadr,DeltaY,info->alpha,right);
			}
		}
	}
	return true;
}

void CImageBlenderStretch::BltMemcopy(DWORD* srcadr,DWORD* destadr,int DeltaX,int right){
	DWORD* tmp_s=srcadr;
	for(int j=0;j<right;j++){
		srcadr=tmp_s+((j*DeltaX)>>16);
		*destadr=*srcadr;
		destadr++; 
	}
}

void CImageBlenderStretch::BltKey(DWORD* srcadr,DWORD* destadr,int DeltaX,int right){
	DWORD* tmp_s=srcadr;
	for(int j=0;j<right;j++){
		srcadr=tmp_s+((j*DeltaX)>>16);
		if(*srcadr!=C_WHITE)*destadr=*srcadr;
		destadr++; 
	}
}

void CImageBlenderStretch::BltKeyBlacken(DWORD* srcadr,DWORD* destadr,int DeltaX,int alpha,int right){
	DWORD* tmp_s=srcadr;
	TARGB srcpixel,destpixel;
	for(int r,j=0;j<right;j++){
		srcadr=tmp_s+((j*DeltaX)>>16);
		if(*srcadr==C_WHITE){destadr++; continue;}
		srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
		r=srcpixel.R-alpha; destpixel.R=r<0?0:r;
		r=srcpixel.G-alpha; destpixel.G=r<0?0:r;
		r=srcpixel.B-alpha; destpixel.B=r<0?0:r;
		*destadr=destpixel.ARGB;  
		destadr++;
	}
}

void CImageBlenderStretch::BltMul(DWORD* srcadr,DWORD* destadr,int DeltaX,int right){
	DWORD* tmp_s=srcadr;
	TARGB srcpixel,destpixel;
	for(int r,j=0;j<right;j++){
		srcadr=tmp_s+((j*DeltaX)>>16);
		if(*srcadr==C_WHITE){destadr++; continue;}
		srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
		r=(srcpixel.R*destpixel.R)>>8; destpixel.R=r<0?0:r;
		r=(srcpixel.G*destpixel.G)>>8; destpixel.G=r<0?0:r;
		r=(srcpixel.B*destpixel.B)>>8; destpixel.B=r<0?0:r;
		*destadr=destpixel.ARGB;  
		destadr++;
	}
}

void CImageBlenderStretch::BltMulColor(DWORD* srcadr,DWORD* destadr,int DeltaX,DWORD color,int right){
	DWORD* tmp_s=srcadr;
	TARGB srcpixel,destpixel;
	for(int r,j=0;j<right;j++){
		srcadr=tmp_s+((j*DeltaX)>>16);
		if(*srcadr==C_WHITE){destadr++; continue;}
		srcpixel.ARGB=*srcadr; destpixel.ARGB=color;
		r=(srcpixel.R*destpixel.R)>>8; destpixel.R=r<0?0:r;
		r=(srcpixel.G*destpixel.G)>>8; destpixel.G=r<0?0:r;
		r=(srcpixel.B*destpixel.B)>>8; destpixel.B=r<0?0:r;
		*destadr=destpixel.ARGB;  
		destadr++;
	}
}

void CImageBlenderStretch::BltAdd(DWORD* srcadr,DWORD* destadr,int DeltaX,int right){
	DWORD* tmp_s=srcadr;
	TARGB srcpixel,destpixel;
	for(int r,j=0;j<right;j++){
		srcadr=tmp_s+((j*DeltaX)>>16);
		if(*srcadr==0x00000000){destadr++; continue;}
		srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
		r=(srcpixel.R+destpixel.R); destpixel.R=r>255?255:r;
		r=(srcpixel.G+destpixel.G); destpixel.G=r>255?255:r;
		r=(srcpixel.B+destpixel.B); destpixel.B=r>255?255:r;
		*destadr=destpixel.ARGB;  
		destadr++;
	}
}

void CImageBlenderStretch::BltAddAlpha(DWORD* srcadr,DWORD* destadr,int DeltaX,int alpha,int right){
	DWORD* tmp_s=srcadr;
	TARGB srcpixel,destpixel;
	for(int r,j=0;j<right;j++){
		srcadr=tmp_s+((j*DeltaX)>>16);
		if(*srcadr==0x00000000){destadr++; continue;}
		srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
		r=destpixel.R+((srcpixel.R*alpha)>>8); destpixel.R=r>255?255:r;
		r=destpixel.G+((srcpixel.G*alpha)>>8); destpixel.G=r>255?255:r;
		r=destpixel.B+((srcpixel.B*alpha)>>8); destpixel.B=r>255?255:r;
		*destadr=destpixel.ARGB;  
		destadr++;
	}
}