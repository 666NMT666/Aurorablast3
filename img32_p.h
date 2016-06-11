/*
void CImageDIB::BNull(TBltParams p,DWORD* destadr,DWORD* srcadr){return;}
void CImageDIB::BMemCopy(TBltParams p,DWORD* destadr,DWORD* srcadr){
	#ifndef _DEBUG
	for(DWORD* top=destadr+m_width*(p.i_top-p.i_bottom);destadr<top;destadr+=m_width,srcadr+=p.src->Width()){
		memcpy(destadr,srcadr,p.sw*4);		
	}
	#else
	for(int i(p.i_bottom);i<p.i_top;++i,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){*destadr=*srcadr; }
	}
	#endif
}
void CImageDIB::BKey(TBltParams p,DWORD* destadr,DWORD* srcadr){
	for(int i(p.i_bottom);i<p.i_top;++i,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=C_WHITE)*destadr=*srcadr;
		}
	}
}

void CImageDIB::BAdd(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		for(int j=0,r;j<p.sw;j++,destadr++,srcadr++){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			BLT_ADD_PIXEL;
		}
	}
}

void CImageDIB::BMul(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=0x00FFFFFF){BLT_MUL_PIXEL();}
		}
	}
}

void CImageDIB::BMinus(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int r,i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr && *destadr){BLT_MINUS_PIXEL();}
		}
	}
}

void CImageDIB::BScreen(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int r,i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			BLT_SCREEN_PIXEL();
		}
	}
}

void CImageDIB::BAlpha(TBltParams p,DWORD* destadr,DWORD* srcadr){	
	TARGB srcpixel,destpixel;
	const int re_alpha=255-p.alpha;
	for(int i(p.i_bottom);i<p.i_top;++i,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=0x00FFFFFF){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
				destpixel.R=(destpixel.R*re_alpha+srcpixel.R*p.alpha)>>8;
				destpixel.G=(destpixel.G*re_alpha+srcpixel.G*p.alpha)>>8;
				destpixel.B=(destpixel.B*re_alpha+srcpixel.B*p.alpha)>>8;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageDIB::BBlacken(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr){*destadr=0x00000000;continue;}
			BLT_BLACKEN_PIXEL(p.alpha);
		}
	}
}

void CImageDIB::BXMinus(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){ 
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr && *destadr){BLT_XMINUS_PIXEL();}
		}
	}
}

void CImageDIB::BKeyAdd(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			BLT_ADD_PIXEL;
		}
	}
}

void CImageDIB::BAlpha2(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr!=C_WHITE){BLT_ALPHA2_PIXEL();}
		}
	}
}

void CImageDIB::BWhiten(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			//if(!*srcadr){*destadr=0x00000000;continue;}
			if(*srcadr!=C_WHITE){BLT_WHITEN_PIXEL(p.alpha);}
		}
	}
}

void CImageDIB::BKeyBlacken(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr){*destadr=0x00000000;continue;}
			if(*srcadr!=0x00FFFFFF){BLT_BLACKEN_PIXEL(p.alpha);}
		}
	}
}

void CImageDIB::BMulColor(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(!*srcadr){*destadr=0x00000000;continue;}
			if(*srcadr!=0x00FFFFFF){
				srcpixel.ARGB=*srcadr; destpixel.ARGB=p.color;
				destpixel.R=(destpixel.R*srcpixel.R)>>8;
				destpixel.G=(destpixel.G*srcpixel.G)>>8;
				destpixel.B=(destpixel.B*srcpixel.B)>>8;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CImageDIB::BRed(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){      
		int r;
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
}

void CImageDIB::BMirrorKey(TBltParams p,DWORD* destadr,DWORD* srcadr){
	int sdist=p.s_mem_distance+p.sw;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=sdist){  
		DWORD* sadr=srcadr+p.sw-1;
		for(int j(0);j<p.sw;j++,destadr++,sadr--){
			if(*sadr!=0x00FFFFFF)*destadr=*sadr;
		}
	}
}

void CImageDIB::BMirrorKeyAdd(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	int sdist=p.s_mem_distance+p.sw;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=sdist){      
		srcadr+=p.sw-1;
		for(int j(0),r;j<p.sw;j++,destadr++,srcadr--){
			if(!*srcadr || *destadr==C_WHITE){continue;}
			if(*srcadr==C_WHITE){*destadr=*srcadr;continue;}
			BLT_ADD_PIXEL;
		}
	}
}

void CImageDIB::BMirrorKeyBlacken(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance+p.sw){      
		srcadr+=p.sw-1;
		for(int j(0);j<p.sw;j++,destadr++,srcadr--){
			if(*srcadr!=C_WHITE){BLT_BLACKEN_PIXEL(p.alpha);}			
		}
	}
}


void CImageDIB::BKeyStructure(TBltParams p,DWORD* destadr,DWORD* srcadr){
	TARGB srcpixel,destpixel;
	static int mTimer=0;
	mTimer++;
	double deltaX=200*sin(N_PI*mTimer*10)*200*sin(N_PI*mTimer*10);
	for(int i=p.i_bottom;i<p.i_top;i++,destadr+=p.d_mem_distance, srcadr+=p.s_mem_distance){
		double cos_seta=sqrt(300*300/((double)300*300+(i-360)*(i-360)+deltaX));
		int r;
		for(DWORD* right=destadr+p.sw;destadr<right;destadr++,srcadr++){
			if(*srcadr==C_WHITE)continue;
			srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;
			double cos_seta2=cos_seta*srcpixel.R/255.0;
			r=srcpixel.R/255.0*(255-2000*(cos_seta2-1.2)*(cos_seta2-1.2)); destpixel.R=r<0?0:r;
			r=srcpixel.R/255.0*(255-2000*(cos_seta2-0.9)*(cos_seta2-0.9)); destpixel.G=r<0?0:r;
			r=srcpixel.R/255.0*(255-2000*(cos_seta2-0.6)*(cos_seta2-0.6)); destpixel.B=r<0?0:r;
			*destadr=destpixel.ARGB;
		}
	}
}
*/