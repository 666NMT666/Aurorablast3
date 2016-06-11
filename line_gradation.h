class CGradationLine:public CLine{
protected:
	enum THorizontalGradation{
		GRAD_LINEAR,
		GRAD_GAUSSIAN,
	};
	DWORD* mColors;
	DWORD mBackColor;
	int mTailStart,mHeadStart,mTailCutOff,mHeadCutOff;
public:
	CGradationLine(int sx,int sy,int ex,int ey,int w,DWORD c,DWORD c2,int tailStart,int headStart,int tailCutOff,int headCutOff);
	static CGradationLine GetAngleLine(int sx,int sy,int length,int angle,int w,DWORD c,DWORD c2,int tailStart,int headStart,int tailCutOff,int headCutOff){
		int ex=sx+(int)(length*cos(-N_PI*angle));
		int ey=sy+(int)(length*sin(-N_PI*angle));
		if(fabs(cos(-N_PI*angle))>fabs(sin(-N_PI*angle))){
			tailStart*=(int)fabs(cos(-N_PI*angle));
			headStart*=(int)fabs(cos(-N_PI*angle));
		}else{
			tailStart*=(int)fabs(sin(-N_PI*angle));
			headStart*=(int)fabs(sin(-N_PI*angle));
		}
		CGradationLine line(sx,sy,ex,ey,w,c,c2,tailStart,headStart,tailCutOff,headCutOff);
		return line;
	}
	~CGradationLine(){
		delete[] mColors;
	}
	void Draw(CImage32* dest);
};

CGradationLine::CGradationLine(int sx,int sy,int ex,int ey,int w,DWORD c,DWORD c2,int tailStart,int headStart,int tailCutOff,int headCutOff):CLine(sx,sy,ex,ey,w,c){}
void CGradationLine::Draw(CImage32* dest){}