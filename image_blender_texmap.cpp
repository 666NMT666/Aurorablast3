#include "image_blender_texmap.h"
#include  <math.h>

bool CImageBlenderTexmap::Blt(CImage32* dest,CImage32* src,const CBltInfo* info,RECT rc,int dx,int dy,int sx,int sy,int sw,int sh){
	//dx+info->link_x,dy+info->link_y,N_PI*(info->angle),
	dx+=(int)(info->link_x*info->zoom);
	dy+=(int)(info->link_y*info->zoom);
	// 描画先座標の設定
	CVector v[4];
	v[0].Set( -info->link_x   , -info->link_y ); // 左上
	v[1].Set( -info->link_x+sw, -info->link_y ); // 右上
	v[2].Set( -info->link_x+sw, -info->link_y+sh ); // 右下
	v[3].Set( -info->link_x   , -info->link_y+sh ); // 左下
	// 回転・拡大をする
	for (int i=0; i<4; i++){
		v[i].Mul( info->zoom );
		v[i].Rotate( N_PI*info->angle );
		v[i].Add(dx,dy);
	}
	// テクスチャの4頂点を指定
	CTexMapVertex vertex;
	vertex.Add( v[0].x, v[0].y, sx, sy );
	vertex.Add( v[1].x, v[1].y, sx + sw, sy );
	vertex.Add( v[2].x, v[2].y, sx + sw, sy + sh );
	vertex.Add( v[3].x, v[3].y, sx, sy + sh );
	return Texmap(info,rc,dest, src, &vertex);
}


bool CImageBlenderTexmap::Texmap(const CBltInfo* info,RECT rc,CImage32* dest, CImage32* src, CTexMapVertex* vertex){
	int num = vertex->Num();
	int miny,maxy; // 一番上と下を見つける
	for (int i=0; i<num; i++){
		double dx,dy;
		vertex->GetDest( &dx, &dy, i );
		if(i == 0){ miny=(int)dy; maxy=(int)dy; continue;  }
		if (dy < miny) miny = (int)dy;
		if (dy > maxy) maxy = (int)dy;
	}
	if (miny < rc.top) miny = rc.top;
	if (miny >= rc.bottom) miny = rc.bottom - 1;
	if (maxy < rc.top) maxy = rc.top;
	if (maxy >= rc.bottom) maxy = rc.bottom - 1;
	CTexMapSide tms;
	for (int i=0; i<num; i++){
		int idx1 = i;
		int idx2 = i+1;
		if (idx2 >= num) idx2 = 0;
		tms.Add( vertex->Vertex( idx1 ), vertex->Vertex( idx2 ) );
	}
	if(info->type==BLT_KEY)return TexmapLine(info,miny,maxy,rc,dest,src,tms);
	else if(info->type==BLT_RED){
		return TexmapLineRed(info,miny,maxy,rc,dest,src,tms);
	}else if(info->type==BLT_ADD){
		if(info->alpha==255)return TexmapLineAdd(info,miny,maxy,rc,dest,src,tms);
		else return TexmapLineAddAlpha(info,miny,maxy,rc,dest,src,tms);
	}else if(info->type==BLT_STRUCTURE)return TexmapLineStructure(info,miny,maxy,rc,dest,src,tms);
	return false;
}

bool CImageBlenderTexmap::TexmapLine(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms){
	for (int i=miny; i<maxy; i++){
		int edgenum = 0;
		double edge[2], sx[2], sy[2];
		for (int j=0; j<tms.Num(); j++){
			double x, sx_,sy_;
			if ( tms.Intersection( j, 0.125 + i, &x, &sx_,&sy_ ) ){
				edge[edgenum] = x;
				sx[edgenum] = sx_;
				sy[edgenum] = sy_;
				edgenum++;
				if (edgenum == 2) break;
			}
		}
		if (edgenum != 2 || edge[0] == edge[1]) continue;
		if (edge[0] > edge[1]){
			SWAP( &edge[0], &edge[1] );
			SWAP( &sx[0], &sx[1] );
			SWAP( &sy[0], &sy[1] );
		}
		if(sx[0]>=src->Width()-1)sx[0]=src->Width()-1;
		if(sx[1]>=src->Width()-1)sx[1]=src->Width()-1;
		if(sy[0]>=src->Height()-1)sy[0]=src->Height()-1;
		if(sy[1]>=src->Height()-1)sy[1]=src->Height()-1;
		
		double deltau = (sx[1] - sx[0]) / (edge[1] - edge[0]);
		double deltav = (sy[1] - sy[0]) / (edge[1] - edge[0]);
		if (edge[0] < rc.left){
			sx[0] += deltau * (rc.left-edge[0]);
			sy[0] += deltav * (rc.left-edge[0]);
			edge[0] = rc.left;
		}
		if(edge[1]>rc.right)edge[1]=rc.right-1;
		int left = (int)edge[0];
		int right = (int)edge[1];
		int u = (int)(sx[0] * fixfloat_const);
		int v = (int)(sy[0] * fixfloat_const);
		int du = (int)(deltau * fixfloat_const);
		int dv = (int)(deltav * fixfloat_const); 
		DWORD* dptr = (DWORD*)dest->PixelAddressNC(left,i);
		DWORD* sptr;
		for (int k=left,pu,pv; k<right; k++,u+=du,v+=dv,dptr++){
			pu=(u>>16),pv=(v>>16);
			sptr=(DWORD*)src->PixelAddressNC(pu,pv);
			if(*sptr!=C_WHITE)*dptr=*sptr;  
		}
	}
	return true;
}

bool CImageBlenderTexmap::TexmapLineAdd(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms){
	for (int i=miny; i<maxy; i++){
		int edgenum = 0;
		double edge[2], sx[2], sy[2];
		for (int j=0; j<tms.Num(); j++){
			double x, sx_,sy_;
			if ( tms.Intersection( j, 0.125 + i, &x, &sx_,&sy_ ) ){
				edge[edgenum] = x;
				sx[edgenum] = sx_;
				sy[edgenum] = sy_;
				edgenum++;
				if (edgenum == 2) break;
			}
		}
		if (edgenum != 2 || edge[0] == edge[1]) continue;
		if (edge[0] > edge[1]){
			SWAP( &edge[0], &edge[1] );
			SWAP( &sx[0], &sx[1] );
			SWAP( &sy[0], &sy[1] );
		}
		if(sx[0]>=src->Width()-1)sx[0]=src->Width()-1;
		if(sx[1]>=src->Width()-1)sx[1]=src->Width()-1;
		if(sy[0]>=src->Height()-1)sy[0]=src->Height()-1;
		if(sy[1]>=src->Height()-1)sy[1]=src->Height()-1;
		double deltau = (sx[1] - sx[0]) / (edge[1] - edge[0]);
		double deltav = (sy[1] - sy[0]) / (edge[1] - edge[0]);
		if (edge[0] < rc.left){
			sx[0] += deltau * (rc.left-edge[0]);
			sy[0] += deltav * (rc.left-edge[0]);
			edge[0] = rc.left;
		}
		if(edge[1]>rc.right)edge[1]=rc.right-1;
		int left = (int)edge[0];
		int right = (int)edge[1];
		int u = (int)(sx[0] * fixfloat_const);
		int v = (int)(sy[0] * fixfloat_const);
		int du = (int)(deltau * fixfloat_const);
		int dv = (int)(deltav * fixfloat_const); 
		DWORD* dptr = (DWORD*)dest->PixelAddressNC(left,i);
		DWORD* sptr;
		for (int k=left,pu,pv; k<right; k++,u+=du,v+=dv,dptr++){
			TARGB srcpixel,destpixel;
			pu=(u>>16),pv=(v>>16);
			sptr=(DWORD*)src->PixelAddressNC(pu,pv);
			if(*sptr==C_WHITE)*dptr=*sptr;
			else{
				srcpixel.ARGB=*sptr; destpixel.ARGB=*dptr;
				int r=destpixel.R + srcpixel.R; destpixel.R=r>255?255:r;
				r=destpixel.G + srcpixel.G; destpixel.G=r>255?255:r;
				r=destpixel.B + srcpixel.B; destpixel.B=r>255?255:r;
				*dptr=destpixel.ARGB;
			}
			
		}
	}
	return true;
}

bool CImageBlenderTexmap::TexmapLineRed(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms){
	for (int i=miny; i<maxy; i++){
		int edgenum = 0;
		double edge[2], sx[2], sy[2];
		for (int j=0; j<tms.Num(); j++){
			double x, sx_,sy_;
			if ( tms.Intersection( j, 0.125 + i, &x, &sx_,&sy_ ) ){
				edge[edgenum] = x;
				sx[edgenum] = sx_;
				sy[edgenum] = sy_;
				edgenum++;
				if (edgenum == 2) break;
			}
		}
		if (edgenum != 2 || edge[0] == edge[1]) continue;
		if (edge[0] > edge[1]){
			SWAP( &edge[0], &edge[1] );
			SWAP( &sx[0], &sx[1] );
			SWAP( &sy[0], &sy[1] );
		}
		if(sx[0]>=src->Width()-1)sx[0]=src->Width()-1;
		if(sx[1]>=src->Width()-1)sx[1]=src->Width()-1;
		if(sy[0]>=src->Height()-1)sy[0]=src->Height()-1;
		if(sy[1]>=src->Height()-1)sy[1]=src->Height()-1;
		double deltau = (sx[1] - sx[0]) / (edge[1] - edge[0]);
		double deltav = (sy[1] - sy[0]) / (edge[1] - edge[0]);
		if (edge[0] < rc.left){
			sx[0] += deltau * (rc.left-edge[0]);
			sy[0] += deltav * (rc.left-edge[0]);
			edge[0] = rc.left;
		}
		if(edge[1]>rc.right)edge[1]=rc.right-1;
		int left = (int)edge[0];
		int right = (int)edge[1];
		int u = (int)(sx[0] * fixfloat_const);
		int v = (int)(sy[0] * fixfloat_const);
		int du = (int)(deltau * fixfloat_const);
		int dv = (int)(deltav * fixfloat_const); 
		DWORD* dptr = (DWORD*)dest->PixelAddressNC(left,i);
		DWORD* sptr;
		for (int k=left,pu,pv; k<right; k++,u+=du,v+=dv,dptr++){
			TARGB srcpixel,destpixel;
			pu=(u>>16),pv=(v>>16);
			sptr=(DWORD*)src->PixelAddressNC(pu,pv);
			if(*sptr==C_WHITE){}
			else{
				srcpixel.ARGB=*sptr; destpixel.ARGB=*dptr;
				destpixel.R=srcpixel.R;
				destpixel.G=0;
				destpixel.B=0;
				*dptr=destpixel.ARGB;
			}
			
		}
	}
	return true;
}
bool CImageBlenderTexmap::TexmapLineAddAlpha(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms){
	for (int i=miny; i<maxy; i++){
		int edgenum = 0;
		double edge[2], sx[2], sy[2];
		for (int j=0; j<tms.Num(); j++){
			double x, sx_,sy_;
			if ( tms.Intersection( j, 0.125 + i, &x, &sx_,&sy_ ) ){
				edge[edgenum] = x;
				sx[edgenum] = sx_;
				sy[edgenum] = sy_;
				edgenum++;
				if (edgenum == 2) break;
			}
		}
		if (edgenum != 2 || edge[0] == edge[1]) continue;
		if (edge[0] > edge[1]){
			SWAP( &edge[0], &edge[1] );
			SWAP( &sx[0], &sx[1] );
			SWAP( &sy[0], &sy[1] );
		}
		if(sx[0]>=src->Width()-1)sx[0]=src->Width()-1;
		if(sx[1]>=src->Width()-1)sx[1]=src->Width()-1;
		if(sy[0]>=src->Height()-1)sy[0]=src->Height()-1;
		if(sy[1]>=src->Height()-1)sy[1]=src->Height()-1;

		double deltau = (sx[1] - sx[0]) / (edge[1] - edge[0]);
		double deltav = (sy[1] - sy[0]) / (edge[1] - edge[0]);
		if (edge[0] < rc.left){
			sx[0] += deltau * (rc.left-edge[0]);
			sy[0] += deltav * (rc.left-edge[0]);
			edge[0] = rc.left;
		}
		if(edge[1]>rc.right)edge[1]=rc.right-1;
		int left = (int)edge[0];
		int right = (int)edge[1];
		int u = (int)(sx[0] * fixfloat_const);
		int v = (int)(sy[0] * fixfloat_const);
		int du = (int)(deltau * fixfloat_const);
		int dv = (int)(deltav * fixfloat_const); 
		DWORD* dptr = (DWORD*)dest->PixelAddressNC(left,i);
		DWORD* sptr;
		for (int k=left,pu,pv; k<right; k++,u+=du,v+=dv,dptr++){
			TARGB srcpixel,destpixel;
			pu=(u>>16),pv=(v>>16);
			sptr=(DWORD*)src->PixelAddressNC(pu,pv);
			if(*sptr!=0x00000000){
				srcpixel.ARGB=*sptr; destpixel.ARGB=*dptr;
				int r=destpixel.R + ((info->alpha*srcpixel.R)>>8); destpixel.R=r>255?255:r;
				r=destpixel.G + ((info->alpha*srcpixel.G)>>8); destpixel.G=r>255?255:r;
				r=destpixel.B + ((info->alpha*srcpixel.B)>>8); destpixel.B=r>255?255:r;
				*dptr=destpixel.ARGB;
			}
		}
	}
	return true;
}

bool CImageBlenderTexmap::TexmapLineStructure(const CBltInfo* info,int miny,int maxy,RECT rc,CImage32* dest,CImage32* src,CTexMapSide tms){
	for (int i=miny; i<maxy; i++){
		int edgenum = 0;
		double edge[2], sx[2], sy[2];
		for (int j=0; j<tms.Num(); j++){
			double x, sx_,sy_;
			if ( tms.Intersection( j, 0.125 + i, &x, &sx_,&sy_ ) ){
				edge[edgenum] = x;
				sx[edgenum] = sx_;
				sy[edgenum] = sy_;
				edgenum++;
				if (edgenum == 2) break;
			}
		}
		if (edgenum != 2 || edge[0] == edge[1]) continue;
		if (edge[0] > edge[1]){
			SWAP( &edge[0], &edge[1] );
			SWAP( &sx[0], &sx[1] );
			SWAP( &sy[0], &sy[1] );
		}
		if(sx[0]>=src->Width()-1)sx[0]=src->Width()-1;
		if(sx[1]>=src->Width()-1)sx[1]=src->Width()-1;
		if(sy[0]>=src->Height()-1)sy[0]=src->Height()-1;
		if(sy[1]>=src->Height()-1)sy[1]=src->Height()-1;
		
		double deltau = (sx[1] - sx[0]) / (edge[1] - edge[0]);
		double deltav = (sy[1] - sy[0]) / (edge[1] - edge[0]);
		if (edge[0] < rc.left){
			sx[0] += deltau * (rc.left-edge[0]);
			sy[0] += deltav * (rc.left-edge[0]);
			edge[0] = rc.left;
		}
		if(edge[1]>rc.right)edge[1]=rc.right-1;
		int left = (int)edge[0];
		int right = (int)edge[1];
		int u = (int)(sx[0] * fixfloat_const);
		int v = (int)(sy[0] * fixfloat_const);
		int du = (int)(deltau * fixfloat_const);
		int dv = (int)(deltav * fixfloat_const); 
		DWORD* dptr = (DWORD*)dest->PixelAddressNC(left,i);
		DWORD* sptr;
		
		
		double cos_seta=sqrt(300*300/((double)300*300+(i-360)*(i-360)));
		for (int k=left,pu,pv; k<right; k++,u+=du,v+=dv,dptr++){
			pu=(u>>16),pv=(v>>16);
			sptr=(DWORD*)src->PixelAddressNC(pu,pv);
			TARGB srcpixel,destpixel;
			if(*sptr!=C_WHITE){
				srcpixel.ARGB=*sptr; destpixel.ARGB=*dptr;
				int r;
				double cos_seta2=cos_seta*srcpixel.R/255.0;
				r=cos_seta*srcpixel.R/255.0*(255-2000*(cos_seta2-1.2)*(cos_seta2-1.2)); destpixel.R=r<0?0:r;
				r=cos_seta*srcpixel.R/255.0*(255-2000*(cos_seta2-0.9)*(cos_seta2-0.9)); destpixel.G=r<0?0:r;
				r=cos_seta*srcpixel.R/255.0*(255-2000*(cos_seta2-0.6)*(cos_seta2-0.6)); destpixel.B=r<0?0:r;
				*dptr=destpixel.ARGB;
			}
		}
	}
	return true;
}
