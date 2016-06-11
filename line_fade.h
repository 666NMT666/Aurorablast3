class CFadeLine:public CLine{
protected:
public:
	CFadeLine(int sx,int sy,int ex,int ey,int w,DWORD c,int pos);	
	void Draw(CImage32* dest);
};
