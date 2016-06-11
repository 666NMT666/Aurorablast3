class CLine{
protected:
	void _Init(int sx,int sy,int ex,int ey,int w,DWORD c){}
	bool isOutOfImage(int w,int h);
public:
	CLine(int sx,int sy,int ex,int ey,int w,DWORD c){_Init(sx,sy,ex,ey,w,c);}
	static CLine GetAngleLine(int sx,int sy,int length,int angle,int w,DWORD c){
		int ex=sx+(int)(length*cos(N_PI*angle));
		int ey=sy+(int)(length*sin(N_PI*angle));
		CLine line(sx,sy,ex,ey,w,c);
		return line;
	}
	virtual void Draw(CImage32* dest){}
	static void drawLine(CImage32* dest,int sx,int sy,int ex,int ey,DWORD c,RECT r=WND_RECT);
	static void drawLine2(CImage32* dest,int sx,int sy,int length,int angle,DWORD c,RECT r=WND_RECT){
		drawLine(dest,sx,sy,sx+(int)(length*cos(N_PI*angle)),sy+(int)(length*sin(N_PI*angle)),c,r);
	}
	static void drawFadeLine(CImage32* dest,int sx,int sy,int ex,int ey,int w,DWORD c,int pos,RECT r=WND_RECT);
	static void drawFadeLine2(CImage32* dest,int sx,int sy,int length,int angle,int w,DWORD c,int pos,RECT r=WND_RECT){
		drawFadeLine(dest,sx,sy,sx+(int)(length*cos(N_PI*angle)),sy+(int)(length*sin(N_PI*angle)),w,c,pos,r);
	}
	static void drawGradationLine(CImage32* dest,int sx,int sy,int ex,int ey,int w,DWORD c,DWORD c2,int headStart,int tailStart,int headCutOff,int tailCutOff,RECT r=WND_RECT);
	static void drawGradationLine2(CImage32* dest,int sx,int sy,int length,int angle,int w,DWORD c,DWORD c2,int headStart,int tailStart,int headCutOff,int tailCutOff,RECT r=WND_RECT){
		drawGradationLine(dest,sx,sy,sx+(int)(length*cos(N_PI*angle)),sy+(int)(length*sin(N_PI*angle)),w,c,c2,headStart,tailStart,headCutOff,tailCutOff,r);
	}
};

bool CLine::isOutOfImage(int w,int h){
	return false;
}

void CLine::drawLine(CImage32* dest,int sx,int sy,int ex,int ey,DWORD c,RECT r){

	int minX=(0<r.left)?r.left:0;
	int maxX=(dest->Width()>r.right)?r.right:dest->Width();
	int minY=(0<r.top)?r.top:0;
	int maxY=(dest->Height()>r.bottom)?r.bottom:dest->Height();

	// 開始・終了ともに画像外なら終了
	if((sx<minX && ex<minX) || (sx>=maxX && ex>=maxX) || 
		(sy<minY && ey<minY) || (sy>=maxY && ey>=maxY))return;
	int deltaX=ex-sx;
	int deltaY=ey-sy;
	if(deltaY==0 && deltaX==0)return; //長さが０なら終了

	if(abs(deltaX)>abs(deltaY)){
		int x=(sx<minX)?x=minX:sx;
		int dx=(sx>ex)?-1:1;
		if(x>=maxX)x=maxX-1;

		while(x!=ex){
			int y=sy+(x-sx)*deltaY/deltaX;
			if(y<minY || y>=maxY || x<minX || x>=maxX){x+=dx;continue;}
			dest->PixelSetNC(x,y,c);
			x+=dx;
		}
	}else{
		int y=(sy<minY)?y=minY:sy;
		int dy=(sy>ey)?-1:1;
		if(y>=maxY)y=maxY-1;
		while(y!=ey){
			int x=sx+(y-sy)*deltaX/deltaY;
			if(x<minX || x>=maxX || y<minY || y>=maxY){y+=dy;continue;}
			dest->PixelSetNC(x,y,c);
			y+=dy;
		}
	}
}

void CLine::drawFadeLine(CImage32* dest,int sx,int sy,int ex,int ey,int w,DWORD c,int fadePos,RECT r){
	
	int minX=(0<r.left)?r.left:0;
	int maxX=(dest->Width()>r.right)?r.right:dest->Width();
	int minY=(0<r.top)?r.top:0;
	int maxY=(dest->Height()>r.bottom)?r.bottom:dest->Height();
	
	// 開始・終了ともに画像外なら終了
	if((sx<minX && ex<minX) || (sx>=maxX && ex>=maxX) || 
		(sy<minY && ey<minY) || (sy>=maxY && ey>=maxY))return;
	int r_width=w/2;
	int deltaX=ex-sx;
	int deltaY=ey-sy;
	if(deltaY==0 && deltaX==0)return;
	TARGB destpixel,srcpixel;
	srcpixel.ARGB=c;
	if(abs(deltaX)>abs(deltaY)){
		int x=(sx<minX)?0:sx;
		if(x>=maxX)x=maxX-1;
		int dx=(x>ex)?-1:1;
		int j=0;
		int length=abs(deltaX);
		while(x!=ex){
			int alpha=255;
			if(j>fadePos)alpha=255-255*(j-fadePos)/(length-fadePos);
			int y=sy+(x-sx)*deltaY/deltaX;
			if(y<-r_width || y>=maxY+r_width || x<minX || x>=maxX){x+=dx;j++;continue;}
			for(int i=0;i<w;i++){
				int yy=y-w/2+i;
				if(yy<minY || yy>=maxY)continue;
				destpixel.ARGB=*((DWORD*)dest->PixelAddressNC(x,yy));
				destpixel.R=(destpixel.R*(255-alpha)+srcpixel.R*alpha)>>8;
				destpixel.G=(destpixel.G*(255-alpha)+srcpixel.G*alpha)>>8;
				destpixel.B=(destpixel.B*(255-alpha)+srcpixel.B*alpha)>>8;
				dest->PixelSetNC(x,yy,destpixel.ARGB);
			}
			x+=dx; j++;
		}
	}else{
		int y=(sy<0)?0:sy;
		if(y>=maxY)y=maxY-1;
		int dy=(y>ey)?-1:1;
		for(int j=0;y!=ey;y+=dy,j++){
			int alpha=(j>fadePos)?255-255*(j-fadePos)/(abs(deltaY)-fadePos):255;
			int x=sx+(y-sy)*deltaX/deltaY;
			if(x<-r_width || x>=maxX+r_width || y<minY || y>=maxY){continue;}
			for(int i=0;i<w;i++){
				int xx=x-r_width+i;
				if(xx<minX || xx>=maxX)continue;
				DWORD* destadr=(DWORD*)dest->PixelAddressNC(xx,y);
				destpixel.ARGB=*destadr;
				destpixel.R=(destpixel.R*(255-alpha)+srcpixel.R*alpha)>>8;
				destpixel.G=(destpixel.G*(255-alpha)+srcpixel.G*alpha)>>8;
				destpixel.B=(destpixel.B*(255-alpha)+srcpixel.B*alpha)>>8;
				*destadr=destpixel.ARGB;
			}
		}
	}
}

void CLine::drawGradationLine(CImage32* dest,int sx,int sy,int ex,int ey,int w,DWORD c,DWORD c2,int headStart,int tailLength,int headCutOff,int tailCutOff,RECT r){

	int minX=(0<r.left)?r.left:0;
	int maxX=(dest->Width()>r.right)?r.right:dest->Width();
	int minY=(0<r.top)?r.top:0;
	int maxY=(dest->Height()>r.bottom)?r.bottom:dest->Height();

	// 開始・終了ともに画像外なら終了
	if((sx<minX && ex<minX) || (sx>=maxX && ex>=maxX) || 
		(sy<minY && ey<minY) || (sy>=maxY && ey>=maxY))return;
	int r_width=w/2;
	int deltaX=ex-sx;
	int deltaY=ey-sy;
	if(deltaY==0 && deltaX==0)return;
	DWORD* mColors=new DWORD[w];
	int dAlpha=2*255/w;
	for(int i=0;i<w;i++)mColors[i]= ColorUtil::Alpha(c,c2,dAlpha*abs(r_width-i));
	
	TARGB srcpixel;
	srcpixel.ARGB=c;
	int seekDirection=1;
	int j=0;
	if(abs(deltaX)>abs(deltaY)){
		int x=sx;
		if(x<minX){j-=x;x=minX;}
		if(x>=dest->Width())x=dest->Width()-1;
		if(x>ex)seekDirection=-1;
		int length=abs(deltaX);
		int tailStart=length-(int)fabs(tailLength*cos(atan2(deltaY,(double)deltaX)));
		headStart=(int)fabs(headStart*cos(atan2(deltaY,(double)deltaX)));
		while(x!=ex){
			int width=w;
			if(j>tailStart){
				width=w*(length-j)/(length-tailStart);
				if(width<tailCutOff){x+=seekDirection;j++;continue;}
			}
			if(j<headStart){
				width=width*j/headStart;
				if(width<headCutOff){x+=seekDirection;j++;continue;}
			}
			int y=sy+(x-sx)*deltaY/deltaX;
			if(y<-r_width || y>=maxY+r_width || x<minX || x>=maxX){x+=seekDirection;j++;continue;}
			int rw=width/2;
			for(int i=0;i<w;i++){
				int yy=y-r_width+i;
				if(yy<minY || yy>=maxY || abs(r_width-i)>rw)continue;
				dest->PixelSetNC(x,yy,mColors[i]);
			}
			x+=seekDirection; j++;
		}
	}else{
		int y=sy;
		if(y<minY){j-=y;y=minY;}
		if(y>=maxY)y=maxY-1;
		if(y>ey)seekDirection=-1;
		int length=abs(deltaY);
		int tailStart=length-(int)fabs(tailLength*cos(atan2(deltaX,(double)deltaY)));
		headStart=(int)fabs(headStart*cos(atan2(deltaX,(double)deltaY)));
		while(y!=ey){
			int width=w;
			if(j>tailStart){
				width=w*(length-j)/(length-tailStart);
				if(width<tailCutOff){y+=seekDirection;j++;continue;}
			}
			if(j<headStart){
				width=width*j/headStart;
				if(width<headCutOff){y+=seekDirection;j++;continue;}
			}
			int rw=width/2;
			int x=sx+(y-sy)*deltaX/deltaY;
			if(x<-r_width || x>=dest->Width()+r_width || y<0 || y>=dest->Height()){y+=seekDirection;j++;continue;}
			for(int i=0;i<w;i++){
				int xx=x-w/2+i;
				if(xx<minX || xx>=maxX || abs(r_width-i)>rw)continue;
				dest->PixelSetNC(xx,y,mColors[i]);
			}
			y+=seekDirection;j++;
		}
	}
	delete[] mColors;
}