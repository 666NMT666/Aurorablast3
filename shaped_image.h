class CShapedImage{
protected:
	CShapedImage(){}
	~CShapedImage(){}

public:
	static void drawCircle(CImage32* dest,CImage32* src,int dx,int dy,int outerR,int innerR,int angle,int rep);
	static void drawCircle(CImage32* dest,CImage32* src,int dx,int dy,int outerR,int innerR,int angle,int rep,int zAngle);
	static void drawFlap(CImage32* dest,CImage32* src,int dx,int dy,int linkSx,int linkSy,int dist,int zAngle,int mode);
};

void drawFlap(CImage32* dest,CImage32* src,int dx,int dy,int linkSx,int linkSy,int dist,int zAngle,int mode){
	
	CVector v[4];
	double rev3DOuter =(dist+src->Width()*sin(N_PI*zAngle))/dist;
	if(mode==0){
		v[0].Set(0,0); // 左上
		v[1].Set(src->Width()*rev3DOuter*cos(N_PI*zAngle) ,-src->Height()/2*rev3DOuter); // 右上
		v[2].Set(src->Width()*rev3DOuter*cos(N_PI*zAngle) , src->Height()/2*rev3DOuter); // 右下
		v[3].Set(0,src->Height()-1); // 左下
	}else{
		v[0].Set(-src->Width()*rev3DOuter*cos(N_PI*zAngle) ,-src->Height()/2*rev3DOuter); // 左上
		v[1].Set(0,0); // 右上
		v[2].Set(0,src->Height()-1);// 右下
		v[3].Set(-src->Width()*rev3DOuter*cos(N_PI*zAngle) , src->Height()/2*rev3DOuter); // 左下
	}
	for (int i=0; i<4; i++){ v[i].Add(dx,dy); }
	// テクスチャの4頂点を指定
	CTexMapVertex vertex;
	int sx=0,sy=0;
	vertex.Add( v[0].x, v[0].y, sx, sy );
	vertex.Add( v[1].x, v[1].y, sx + src->Width(), sy );
	vertex.Add( v[2].x, v[2].y, sx + src->Width(), sy + src->Height() );
	vertex.Add( v[3].x, v[3].y, sx, sy + src->Height() );
	CBltInfo info(BLT_KEY);
	CImageBlenderTexmap::Texmap(&info,BATTLE_RECT,dest, src, &vertex);
}

void CShapedImage::drawCircle(CImage32* dest,CImage32* src,int dx,int dy,int outerR,int innerR,int angle,int rep){
	for(int j=0;j<rep;j++){
		double da=360.0/(double)rep;
		double angleFrom=angle+j*da;
		double angleTo=angle+(j+1)*da;
		CVector v[4];
		v[0].Set(outerR*sin(N_PI*angleFrom) ,outerR*cos(N_PI*angleFrom)); // 左上
		v[1].Set(outerR*sin(N_PI*angleTo) ,outerR*cos(N_PI*angleTo)); // 右上
		v[2].Set(innerR*sin(N_PI*angleTo) ,innerR*cos(N_PI*angleTo)); // 右下
		v[3].Set(innerR*sin(N_PI*angleFrom) ,innerR*cos(N_PI*angleFrom)); // 左下
		for (int i=0; i<4; i++){ v[i].Add(dx,dy); }
		// テクスチャの4頂点を指定
		CTexMapVertex vertex;
		int sx=0,sy=0;
		vertex.Add( v[0].x, v[0].y, sx, sy );
		vertex.Add( v[1].x, v[1].y, sx + src->Width(), sy );
		vertex.Add( v[2].x, v[2].y, sx + src->Width(), sy + src->Height() );
		vertex.Add( v[3].x, v[3].y, sx, sy + src->Height() );
		CBltInfo info(BLT_KEY);
		CImageBlenderTexmap::Texmap(&info,BATTLE_RECT,dest, src, &vertex);
	}
}

void CShapedImage::drawCircle(CImage32* dest,CImage32* src,int dx,int dy,int outerR,int innerR,int angle,int rep,int zAngle){
	int dist=600;
	for(int j=0;j<rep;j++){
		double da=360.0/(double)rep;
		double angleFrom=angle+j*da;
		double angleTo=angle+(j+1)*da;
		CVector v[4];
		double rev3DOuterLeft =outerR*(dist+outerR*cos(N_PI*angleFrom)*sin(N_PI*zAngle))/dist;
		double rev3DOuterRight=outerR*(dist+outerR*cos(N_PI*angleTo  )*sin(N_PI*zAngle))/dist;
		double rev3DInnerRight=innerR*(dist+innerR*cos(N_PI*angleTo  )*sin(N_PI*zAngle))/dist;
		double rev3DInnerLeft =innerR*(dist+innerR*cos(N_PI*angleFrom)*sin(N_PI*zAngle))/dist;
		/*tamasudare
		double rev3DOuterLeft=outerR*cos(N_PI*angleFrom)*(dist+outerR*sin(N_PI*zAngle))/dist;
		double rev3DOuterRight=outerR*cos(N_PI*angleTo)*(dist+outerR*sin(N_PI*zAngle))/dist;
		double rev3DInnerRight=innerR*cos(N_PI*angleTo)*(dist+innerR*sin(N_PI*zAngle))/dist;
		double rev3DInnerLeft=innerR*cos(N_PI*angleFrom)*(dist+innerR*sin(N_PI*zAngle))/dist;
		*/
		v[0].Set(rev3DOuterLeft*sin(N_PI*angleFrom) ,rev3DOuterLeft*cos(N_PI*angleFrom)*cos(N_PI*zAngle)); // 左上
		v[1].Set(rev3DOuterRight*sin(N_PI*angleTo) ,rev3DOuterRight*cos(N_PI*angleTo)*cos(N_PI*zAngle)); // 右上
		v[2].Set(rev3DInnerRight*sin(N_PI*angleTo) ,rev3DInnerRight*cos(N_PI*angleTo)*cos(N_PI*zAngle)); // 右下
		v[3].Set(rev3DInnerLeft*sin(N_PI*angleFrom) ,rev3DInnerLeft*cos(N_PI*angleFrom)*cos(N_PI*zAngle)); // 左下
		for (int i=0; i<4; i++){ v[i].Add(dx,dy); }
		// テクスチャの4頂点を指定
		CTexMapVertex vertex;
		int sx=0,sy=0;
		vertex.Add( v[0].x, v[0].y, sx, sy );
		vertex.Add( v[1].x, v[1].y, sx + src->Width(), sy );
		vertex.Add( v[2].x, v[2].y, sx + src->Width(), sy + src->Height() );
		vertex.Add( v[3].x, v[3].y, sx, sy + src->Height() );
		CBltInfo info(BLT_KEY);
		CImageBlenderTexmap::Texmap(&info,BATTLE_RECT,dest, src, &vertex);
	}
}