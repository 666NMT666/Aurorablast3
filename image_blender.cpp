#include "image_blender.h"
const CBltInfo* CImageBlender::defaultBltInfo=new CBltInfo();
RECT CImageBlender::mWndRect={0,0,960,720};
void CImageBlender::_BltNC(CImage32* dest,CImage32* src,const CBltInfo* info,int dx,int dy,int sx,int sy,int sw,int sh){
	int i_top=dy<0?0:dy;
	int i_bottom=dy+sh>dest->Height()?dest->Height():dy+sh;
	TBltParams params={
		dx,dy,sx,sy,sw,sh,i_top,i_bottom,info->alpha,info->ctr_color,
		dest->Width()-sw, src->Width()-sw
	};
	if(params.alpha>255)params.alpha=255;
	if(params.alpha<0)params.alpha=0;
	void (*a[])(TBltParams params,DWORD* destadr,DWORD* srcadr)={
		&CImageBlender::BNull,
		&CImageBlender::BMemCopy,
		&CImageBlender::BKey,
		&CImageBlender::BAdd,
		&CImageBlender::BMul,
		&CImageBlender::BMinus,
		&CImageBlender::BScreen,
		&CImageBlender::BAlpha,
		&CImageBlender::BBlacken,
		&CImageBlender::BWhiten,
		&CImageBlender::BKeyAdd,
		&CImageBlender::BAlpha2,
		&CImageBlender::BKeyBlacken,
		&CImageBlender::BMulColor,
		&CImageBlender::BRed,
		&CImageBlender::BKeyStructure,
		&CImageBlender::BMemCopySkip,
		&CImageBlender::BMemSkip,
		&CImageBlender::BMemSkip2,
	};
	a[info->type](params,
		(DWORD*)dest->PixelAddressNC(dx,i_top),
		(DWORD*)src->PixelAddressNC(sx,sy-dy+i_top)
	);
	return;
}

bool CImageBlender::Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy,int sx,int sy,int sw,int sh){
	if(info->type==BLT_NULL)return true;
	if(dx>=rc.right || dx+sw<=rc.left)return true;
	if(dx+sw>=rc.right){
		//if(!info->lr)
		sw=rc.right-dx;
		//else
		//{
		//	sx+=dx+sw-rc.right;
		//	sw-=dx+sw-rc.right+1;			
		//}
	}
	if(dx<rc.left){
		//if(!info->lr)
		sx+=rc.left-dx;
		sw-=rc.left-dx;
		if(sw<=0)return true;
		dx=rc.left;
	}
	if(dy<rc.top){
		sh-=rc.top-dy;
		sy+=rc.top-dy;
		dy=rc.top;
	}
	if(dy+sh>=rc.bottom){
		if(dy>=rc.bottom)return true;
		sh-=(dy+sh-rc.bottom);
	}
	_BltNC(dest,src,info,dx,dy,sx,sy,sw,sh);



	return true;
}

bool CImageBlender::BltNC(CImage32* dest,CImage32* src,const CBltInfo* info,int dx,int dy,int sx,int sy,int sw,int sh){
	_BltNC(dest,src,info,dx,dy,sx,sy,sw,sh);return true;
}
bool CImageBlender::Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy){return Blt(dest,src,info,rc,dx,dy,0,0,src->Width(),src->Height());}
bool CImageBlender::BltNC(CImage32* dest,CImage32* src,const CBltInfo* info,int dx,int dy){return BltNC(dest,src,info,dx,dy,0,0,src->Width(),src->Height());}
bool CImageBlender::Blt(CImage32* dest,CImage32* src,int dx,int dy){return Blt(dest,src,defaultBltInfo,mWndRect,dx,dy);}
bool CImageBlender::BltNC(CImage32* dest,CImage32* src,int dx,int dy){return BltNC(dest,src,defaultBltInfo,dx,dy);}

void CImageBlender::BNull(TBltParams p,DWORD* destadr,DWORD* srcadr){return;}
void CImageBlender::BMemCopy(TBltParams p,DWORD* destadr,DWORD* srcadr){
	//#ifndef _DEBUG
	//for(DWORD* top=destadr+m_width*(p.i_top-p.i_bottom);destadr<top;destadr+=m_width,srcadr+=p.src->Width()){
	//	memcpy(destadr,srcadr,p.sw*4);		
	//}
	//#else
	for(int i=p.i_top;i<p.i_bottom;++i,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){*destadr=*srcadr; }
	}
	//#endif
}
void CImageBlender::BKey(TBltParams p,DWORD* destadr,DWORD* srcadr){
	for(int i=p.i_top;i<p.i_bottom;++i,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=C_WHITE)*destadr=*srcadr;
		}
	}
}

void CImageBlender::BAdd(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		for(int j=0,r;j<p.sw;j++,destadr++,srcadr++){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
			r = destpixel.R + srcpixel.R; if (r > 255)r = 255; destpixel.R = r;
			r = destpixel.G + srcpixel.G; if (r > 255)r = 255; destpixel.G = r;
			r = destpixel.B + srcpixel.B; if (r > 255)r = 255; destpixel.B = r;
			*destadr=destpixel.ARGB;
		}
	}
}

void CImageBlender::BMul(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
				destpixel.R=(destpixel.R * srcpixel.R)>>8;
				destpixel.G=(destpixel.G * srcpixel.G)>>8;
				destpixel.B=(destpixel.B * srcpixel.B)>>8;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageBlender::BMinus(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr && *destadr){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
				destpixel.R=destpixel.R>srcpixel.R ? destpixel.R-srcpixel.R:0;
				destpixel.G=destpixel.G>srcpixel.G ? destpixel.G-srcpixel.G:0;
				destpixel.B=destpixel.B>srcpixel.B ? destpixel.B-srcpixel.B:0;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageBlender::BScreen(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int r,i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
			r=destpixel.R + srcpixel.R-((destpixel.R*srcpixel.R)>>8); destpixel.R=r>255?255:r;
			r=destpixel.G + srcpixel.G-((destpixel.G*srcpixel.G)>>8); destpixel.G=r>255?255:r;
			r=destpixel.B + srcpixel.B-((destpixel.B*srcpixel.B)>>8); destpixel.B=r>255?255:r;
			*destadr=destpixel.ARGB;
		}
	}
}

void CImageBlender::BAlpha(TBltParams p,DWORD* destadr,DWORD* srcadr){	
	TARGB srcpixel,destpixel;
	const int re_alpha=255-p.alpha;
	for(int i=p.i_top;i<p.i_bottom;++i,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
				destpixel.R=(destpixel.R*re_alpha+srcpixel.R*p.alpha)>>8;
				destpixel.G=(destpixel.G*re_alpha+srcpixel.G*p.alpha)>>8;
				destpixel.B=(destpixel.B*re_alpha+srcpixel.B*p.alpha)>>8;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageBlender::BBlacken(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr){*destadr=0x00000000;continue;}
			srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
			destpixel.R=srcpixel.R<(p.alpha)?0:srcpixel.R-(p.alpha);\
			destpixel.G=srcpixel.G<(p.alpha)?0:srcpixel.G-(p.alpha);\
			destpixel.B=srcpixel.B<(p.alpha)?0:srcpixel.B-(p.alpha);\
			*destadr=destpixel.ARGB;	
		}
	}
}

void CImageBlender::BXMinus(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){ 
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr && *destadr){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
				r=destpixel.G>srcpixel.G ? destpixel.G-srcpixel.G:0;
				r=destpixel.B>srcpixel.B ? destpixel.B-srcpixel.B:0;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageBlender::BKeyAdd(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
			r=destpixel.R + srcpixel.R; destpixel.R=r>255?255:r;
			r=destpixel.G + srcpixel.G; destpixel.G=r>255?255:r;
			r=destpixel.B + srcpixel.B; destpixel.B=r>255?255:r;
			*destadr=destpixel.ARGB;
		}
	}
}

void CImageBlender::BAlpha2(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
				destpixel.R=(destpixel.R + srcpixel.R)>>1;
				destpixel.G=(destpixel.G + srcpixel.G)>>1;
				destpixel.B=(destpixel.B + srcpixel.B)>>1;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageBlender::BWhiten(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			//if(!*srcadr){*destadr=0x00000000;continue;}
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
				r=srcpixel.R+(p.alpha); destpixel.R=r>255?255:r;
				r=srcpixel.G+(p.alpha); destpixel.G=r>255?255:r;
				r=srcpixel.B+(p.alpha); destpixel.B=r>255?255:r;
				*destadr=destpixel.ARGB;
			}
		}
	}
}


void CImageBlender::BKeyBlacken(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr){*destadr=0x00000000;continue;}
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
				destpixel.R=srcpixel.R<(p.alpha)?0:srcpixel.R-(p.alpha);\
				destpixel.G=srcpixel.G<(p.alpha)?0:srcpixel.G-(p.alpha);\
				destpixel.B=srcpixel.B<(p.alpha)?0:srcpixel.B-(p.alpha);\
				*destadr=destpixel.ARGB;	
			}
		}
	}
}

void CImageBlender::BMulColor(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr){*destadr=0x00000000;continue;}
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=p.color;
				destpixel.R=(destpixel.R*srcpixel.R)>>8;
				destpixel.G=(destpixel.G*srcpixel.G)>>8;
				destpixel.B=(destpixel.B*srcpixel.B)>>8;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageBlender::BRed(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr){*destadr=0x00000000;continue;}
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr;
				destpixel.ARGB=*destadr;
				destpixel.R=srcpixel.R;
				destpixel.G=0;
				destpixel.B=0;
				*destadr=destpixel.ARGB;
			}
		}
	}
	/*for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance+p.sw){      
		srcadr+=p.sw-1;
		for(int j(0);j<p.sw;j++,destadr++,srcadr--){*destadr=*srcadr;}
	}*/
}

void CImageBlender::BMirrorKey(TBltParams p,DWORD* destadr,DWORD* srcadr){
	int sdist=p.s_mem_distance+p.sw;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=sdist){  
		DWORD* sadr=srcadr+p.sw-1;
		for(int j(0);j<p.sw;j++,destadr++,sadr--){
			if(*sadr!=C_WHITE)*destadr=*sadr;
		}
	}
}

void CImageBlender::BMirrorKeyAdd(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	int sdist=p.s_mem_distance+p.sw;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=sdist){      
		srcadr+=p.sw-1;
		for(int j(0),r;j<p.sw;j++,destadr++,srcadr--){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
			r=destpixel.R + srcpixel.R; destpixel.R=r>255?255:r;
			r=destpixel.G + srcpixel.G; destpixel.G=r>255?255:r;
			r=destpixel.B + srcpixel.B; destpixel.B=r>255?255:r;
			*destadr=destpixel.ARGB;
		}
	}
}

void CImageBlender::BMirrorKeyBlacken(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance+p.sw){      
		srcadr+=p.sw-1;
		for(int j(0);j<p.sw;j++,destadr++,srcadr--){
			if(*srcadr!=C_WHITE){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
				destpixel.R=srcpixel.R<(p.alpha)?0:srcpixel.R-(p.alpha);\
				destpixel.G=srcpixel.G<(p.alpha)?0:srcpixel.G-(p.alpha);\
				destpixel.B=srcpixel.B<(p.alpha)?0:srcpixel.B-(p.alpha);\
				*destadr=destpixel.ARGB;	
			}			
		}
	}
}

void CImageBlender::BKeyStructure(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	static int mTimer=0;
	mTimer++;
	double deltaX=200*sin(N_PI*mTimer*10)*200*sin(N_PI*mTimer*10);
	for(int i=p.i_top;i<p.i_bottom;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		double cos_seta=sqrt(300*300/((double)300*300+(i-360)*(i-360)+deltaX));
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr==C_WHITE)continue;
			srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
			double cos_seta2=cos_seta*srcpixel.R/255.0;
			r=srcpixel.R/255.0*(255-2000*(cos_seta2-1.1)*(cos_seta2-1.1)); destpixel.R=r<0?0:r;
			r=srcpixel.R/255.0*(255-2000*(cos_seta2-0.8)*(cos_seta2-0.8)); destpixel.G=r<0?0:r;
			r=srcpixel.R/255.0*(255-2000*(cos_seta2-0.5)*(cos_seta2-0.5)); destpixel.B=r<0?0:r;
			*destadr=destpixel.ARGB;
		}
	}
}

void CImageBlender::BMemCopySkip(TBltParams p, DWORD* destadr, DWORD* srcadr) {
	for (int i = p.i_top; i<p.i_bottom; i++, destadr += p.d_mem_distance, srcadr += p.s_mem_distance) {
		for (DWORD* right = destadr + p.sw; destadr < right; destadr++, srcadr++) { *destadr = *srcadr; }
		i++; destadr += p.d_mem_distance; srcadr += p.s_mem_distance;
		if (i >= p.i_bottom)break;
		for (DWORD* right = destadr + p.sw; destadr < right; destadr++) { *destadr = 0x000000; }
		srcadr += p.sw;
	}
}

void CImageBlender::BMemSkip(TBltParams p, DWORD* destadr, DWORD* srcadr) {
	int destD = p.d_mem_distance * 2 + p.sw;
	int srcD = p.s_mem_distance * 2 + p.sw;
	for (int i = p.i_top; i<p.i_bottom; i+=2, destadr += destD, srcadr += srcD) {
		for (DWORD* right = destadr + p.sw; destadr < right; destadr++, srcadr++) {
			if (*srcadr != C_WHITE)*destadr = *srcadr;
		}
	}
}

void CImageBlender::BMemSkip2(TBltParams p, DWORD* destadr, DWORD* srcadr) {
	int destD = p.d_mem_distance * 3 + p.sw*2;
	int srcD = p.s_mem_distance * 3 + p.sw*2;
	for (int i = p.i_top; i<p.i_bottom; i+=3, destadr += destD, srcadr += srcD) {
		for (DWORD* right = destadr + p.sw; destadr < right; destadr++, srcadr++) {
			if (*srcadr != C_WHITE)*destadr = *srcadr;
		}
	}
}