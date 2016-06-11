class CShapeBlender{
protected:
public:
	CShapeBlender(){}
	CShapeBlender(DWORD c){}

	static void fillRect(CImage32* dest,int left,int top,int right,int bottom,DWORD color);

	static void fillCircle(CImage32* dest,int x,int y,int radius,DWORD color);
	static void fillEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,DWORD color);
	static void fillSuperEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,double pow,DWORD color);
	static void fillSuperEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,double pow,int angle,DWORD color);
	static void fillRoundRect(CImage32* dest,RECT rc,double radius,DWORD color,TBltType t=BLT_MEMCOPY);

	static void drawCircle(CImage32* dest,int x,int y,int radius,DWORD color);
	static void drawEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,DWORD color);
	static void drawSuperEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,double pow,DWORD color);
	static void drawRoundRect(CImage32* dest,RECT rc,double radius,DWORD color);

	static void bltLineCopy(CImage32* dest,int l,int r,int y,DWORD color);
	static void bltLineAlpha50(CImage32* dest,int l,int r,int y,DWORD color);
	static void bltLineMul(CImage32* dest,int l,int r,int y,DWORD color);

	static void fillRhombus(CImage32* dest,RECT rc,int x,int y,int width,int height,int angle,DWORD color);
};

void CShapeBlender::fillRhombus(CImage32* dest,RECT rc,int x,int y,int width,int height,int digAngle,DWORD color){
	int midX=x;
	int midY=max(0,y);
	
	while( digAngle>90 ){ digAngle-=180; }
	while( digAngle<-90){ digAngle+=180;}
	double angle=digAngle*N_PI;
	int length=height/2;

	if(fabs(cos(angle))>fabs(sin(angle))){
		int bottom=min(BATTLE_BOTTOM-1,(int)(midY+length*cos(angle)));
		int top=max(BATTLE_TOP,(int)(midY-length*cos(angle)));

		int l=abs((int)(length*cos(angle)));
		for(int i=midY;i<bottom ;i++){
			int y=i-midY;
			int dx=(int)(y*tan(angle));
			int w=width*abs(l-y)/(l*2);
			int left=max(midX+dx-w,rc.left);
			int right=min(midX+dx+w,rc.right-1);
			DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
			for(int j=left;j<right;j++,destAdr++){ *destAdr=color; }
		}
		for(int i=min(midY,BATTLE_BOTTOM-1);i>top ;i--){
			int y=i-midY;
			int dx=(int)(y*tan(angle));
			int w=width*abs(l+y)/(l*2);
			int left=max(midX+dx-w,rc.left);
			int right=min(midX+dx+w,rc.right-1);
			DWORD* destAdr=(DWORD*)dest->PixelAddressNC(left,i);
			for(int j=left;j<right;j++,destAdr++){ *destAdr=color; }
		}
	}else{
		int left=max(BATTLE_LEFT,midX);
		int right=min(BATTLE_RIGHT-1,midX+length);
		for(int i=left;i<right;i++){
			int x=i-midX;
			int dy=(int)(x/tan(angle));
			int w=width*abs(length-x)/(length*2);
			int bottom=min(BATTLE_BOTTOM-1,midY+dy+w);
			int top=max(BATTLE_TOP,midY+dy-w);
			for(int j=top;j<bottom;j++){
				dest->PixelSetNC(i,j,color);
			}
		}

		left=max(BATTLE_LEFT,midX-length);
		right=min(BATTLE_RIGHT-1,midX);
		for(int i=right;i>left;i--){
			int x=i-midX;
			int dy=(int)(x/tan(angle));
			int w=width*abs(length+x)/(length*2);
			int bottom=min(BATTLE_BOTTOM-1,midY+dy+w);
			int top=max(BATTLE_TOP,midY+dy-w);
			for(int j=top;j<bottom;j++){
				dest->PixelSetNC(i,j,color);
			}
		}
	}
}

void CShapeBlender::drawCircle(CImage32* dest,int x,int y,int radius,DWORD color){
	int range=(int)(radius/1.41421356);
	for(int i=y-range;i<=y+range;i++){ // y����H���ĕ`��
		double dy=y-i;
		int dx=(int)(sqrt((radius-dy)*(radius+dy)));
		dest->PixelSet(x+(int)dx,i,color); //�E����`��
		dest->PixelSet(x-dx,i,color);  //������`��
	}
	for(int i=x-range;i<=x+range;i++){ // x����H���ĕ`��
		double dx=x-i;
		int dy=(int)(sqrt((radius-dx)*(radius+dx)));
		dest->PixelSet(i,y+(int)dy,color); //�㑤��`��
		dest->PixelSet(i,y-dy,color); //������`��
	}
}

void CShapeBlender::drawEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,DWORD color){
	//�X����1 �ɂȂ镔�ʂ�xy�̒T��������؂�ւ�
	int range=(int)(radiusY*radiusY/sqrt(radiusX*radiusX+radiusY*radiusY));
	for(int i=y-range;i<=y+range;i++){ // y����H���ĕ`��
		double dy=y-i;
		int dx=(int)(sqrt((radiusY-dy)*(radiusY+dy))*radiusX/radiusY);
		dest->PixelSet(x+dx,i,color); //�E����`��
		dest->PixelSet(x-dx,i,color);  //������`��
	}
	//�X����1 �ɂȂ镔�ʂ�xy�̒T��������؂�ւ�
	range=(int)(radiusX*radiusX/sqrt(radiusX*radiusX+radiusY*radiusY));
	for(int i=x-range;i<=x+range;i++){ // x����H���ĕ`��
		double dx=x-i;
		int dy=(int)(sqrt((radiusX-dx)*(radiusX+dx))*radiusY/radiusX);
		dest->PixelSet(i,y+dy,color); //�㑤��`��
		dest->PixelSet(i,y-dy,color); //������`��
	}
}

void CShapeBlender::drawSuperEllipse(CImage32* dest,int x,int y,
			double radiusX,double radiusY,double p,DWORD color){
	if(p<=0.0 || radiusX==0 || radiusY==0)return;//�`��s�\
	if(p==1.0){ //�H�`
		if(radiusY>radiusX){
			for(int i=0;i<=radiusY;i++){ // y����H���ĕ`��
				int dx=(int)(i*radiusX/radiusY);
				dest->PixelSet((int)(x+radiusX-dx),(int)(y+i),color);
				dest->PixelSet((int)(x-radiusX+dx),(int)(y+i),color);
				dest->PixelSet((int)(x+radiusX-dx),(int)(y-i),color);
				dest->PixelSet((int)(x-radiusX+dx),(int)(y-i),color);
			}
		}else{
			for(int i=0;i<=radiusX;i++){ // x����H���ĕ`��
				int dy=(int)(i*radiusY/radiusX);
				dest->PixelSet((int)(x-i),(int)(y+radiusY-dy),color);
				dest->PixelSet((int)(x-i),(int)(y-radiusY+dy),color);
				dest->PixelSet((int)(x+i),(int)(y+radiusY-dy),color);
				dest->PixelSet((int)(x+i),(int)(y-radiusY+dy),color);
			}
		}
	}else if(p>1.0){ //�H�`���ȉ~���p�ے����`
		//�X����1 �ɂȂ镔�ʂ�xy�̒T��������؂�ւ�
		int range=(int)(radiusY/pow(1.0+exp(log(radiusX/radiusY)*p/(p-1.0)),1.0/p));
		for(int i=y-range;i<=y+range;i++){ // y����H���ĕ`��
			double dy=y-i;
			int dx=(int)(pow(1.0-pow(fabs(dy/radiusY),p),1.0/p)*radiusX);
			dest->PixelSet(x+dx,i,color); //�E����`��
			dest->PixelSet(x-dx,i,color);  //������`��
		}
		//�X����1 �ɂȂ镔�ʂ�xy�̒T��������؂�ւ�
		range=(int)(radiusX/pow(1.0+exp(log(radiusY/radiusX)*p/(p-1.0)),1.0/p));
		for(int i=x-range;i<=x+range;i++){ // x����H���ĕ`��
			double dx=x-i;
			int dy=(int)(pow(1.0-pow(fabs(dx/radiusX),p),1.0/p)*radiusY);
			dest->PixelSet(i,y+dy,color); //�㑤��`��
			dest->PixelSet(i,y-dy,color); //������`��
		}
	}else{//�H�`���A�X�g���C�h�^���\���^
		//�X����1 �ɂȂ镔�ʂ�xy�̒T��������؂�ւ�
		int range=(int)(radiusY/pow(1.0+exp(log(radiusX/radiusY)*p/(p-1.0)),1.0/p));
		for(int i=range;i<=radiusY;i++){ // y����H���ĕ`��
			int dx=(int)(pow(1.0-pow(fabs(i/radiusY),p),1.0/p)*radiusX);
			dest->PixelSet(x+dx,y+i,color); //��E��`��
			dest->PixelSet(x-dx,y+i,color); //�㍶��`��
			dest->PixelSet(x+dx,y-i,color); //���E��`��
			dest->PixelSet(x-dx,y-i,color); //������`��
		}
		range=(int)(radiusX/pow(1.0+exp(log(radiusY/radiusX)*p/(p-1.0)),1.0/p));
		for(int i=range;i<=radiusX;i++){ // x����H���ĕ`��
			int dy=(int)(pow(1.0-pow(fabs(i/radiusX),p),1.0/p)*radiusY);
			dest->PixelSet(x+i,y+dy,color); //�E���`��
			dest->PixelSet(x+i,y-dy,color); //�E����`��
			dest->PixelSet(x-i,y+dy,color); //�����`��
			dest->PixelSet(x-i,y-dy,color); //������`��
		}
	}
}

void CShapeBlender::drawRoundRect(CImage32* dest,RECT rc,double radius,DWORD color){
	int change=(int)(radius-radius/1.4142);
	for(int i=change;i<radius;i++){
		int y=(int)(radius-sqrt(radius*radius-(radius-i)*(radius-i)));
		dest->PixelSet(rc.left +i,rc.top+y,color);
		dest->PixelSet(rc.left +i,rc.bottom-y,color);
		dest->PixelSet(rc.right-i,rc.top+y,color);
		dest->PixelSet(rc.right-i,rc.bottom-y,color);
	}
	for(int i=change;i<radius;i++){
		int x=(int)(radius-sqrt(radius*radius-(radius-i)*(radius-i)));
		dest->PixelSet(rc.left +x,rc.top+i,color);
		dest->PixelSet(rc.left +x,rc.bottom-i,color);
		dest->PixelSet(rc.right-x,rc.top+i,color);
		dest->PixelSet(rc.right-x,rc.bottom-i,color);
	}
	for(int i=rc.left+(int)radius;i<=rc.right-(int)radius;i++){
		dest->PixelSet(i,rc.top,color);
		dest->PixelSet(i,rc.bottom,color);
	}
	for(int i=rc.top+(int)radius;i<=rc.bottom-(int)radius;i++){
		dest->PixelSet(rc.left,i,color);
		dest->PixelSet(rc.right,i,color);
	}
}

void CShapeBlender::fillRect(CImage32* dest,int left,int top,int right,int bottom,DWORD color){
	if(top<0)top=0;
	if(bottom>dest->Height()-1)bottom=dest->Height()-1;
	if(left<0)left=0;
	if(right>dest->Width()-1)right=dest->Width()-1;
	for(int i=top;i<=bottom;i++){
		DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(left,i);  //���[�A�h���X
		DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(right,i);//�E�[�A�h���X
		for(;leftAdr<=rightAdr;leftAdr++)*leftAdr=color;
	}
}

void CShapeBlender::fillCircle(CImage32* dest,int x,int y,int radius,DWORD color){
	int top=y-radius;
	int bottom=y+radius;
	if(top<0)top=0;
	if(bottom>dest->Height()-1)bottom=dest->Height()-1;
	for(int i=top;i<=bottom;i++){
		int deltaX=(int)sqrt((double)(radius*radius-(i-y)*(i-y)));
		int left=(x<deltaX)?0:x-deltaX; // �������E��؂�l�߂�����
		int right=(x+deltaX>dest->Width()-1)?dest->Width()-1:x+deltaX;
		DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(left,i);  //���[�A�h���X
		DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(right,i);//�E�[�A�h���X
		for(;leftAdr<=rightAdr;leftAdr++)*leftAdr=color;
	}
}

void CShapeBlender::fillEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,DWORD color){
	int top=y-(int)radiusY;
	int bottom=y+(int)radiusY;
	if(top<0)top=0;
	if(bottom>dest->Height()-1)bottom=dest->Height()-1;
	for(int i=top;i<=bottom;i++){
		int deltaX=(int)(radiusX*sqrt((1.0-(i-y)*(i-y)/(radiusY*radiusY))));
		int left=(x<deltaX)?0:x-deltaX; // �������E��؂�l�߂�����
		int right=(x+deltaX>dest->Width()-1)?dest->Width()-1:x+deltaX;
		DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(left,i);  //���[�A�h���X
		DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(right,i);//�E�[�A�h���X
		for(;leftAdr<=rightAdr;leftAdr++)*leftAdr=color;
		/*
		int j=x-radiusX+(x-left);
		for(TARGB destpixel,srcpixel;leftAdr<=rightAdr;leftAdr++,j++){
			int a=255/(((j-x)*(j-x)/radiusX/radiusX+(i-y)*(i-y)/radiusY/radiusY));
			destpixel.ARGB=*leftAdr;
			srcpixel.ARGB=color;
			int r=destpixel.R + ((a*srcpixel.R)>>8); destpixel.R=r>255?255:r;
			r=destpixel.G + ((a*srcpixel.G)>>8); destpixel.G=r>255?255:r;
			r=destpixel.B + ((a*srcpixel.B)>>8); destpixel.B=r>255?255:r;
			*leftAdr=destpixel.ARGB;
		}
		*/
	}
}

void CShapeBlender::fillSuperEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,double p,DWORD color){
	int top=y-(int)radiusY;
	int bottom=y+(int)radiusY;
	if(top<0)top=0;
	if(bottom>dest->Height()-1)bottom=dest->Height()-1;
	for(int i=top;i<=bottom;i++){
		int deltaX=(int)(radiusX*pow(1.0-pow(abs(i-y)/radiusY,p),1.0/p));
		int left=(x<deltaX)?0:x-deltaX; // �������E��؂�l�߂�����
		int right=(x+deltaX>dest->Width()-1)?dest->Width()-1:x+deltaX;
		bltLineAlpha50(dest,left,right,y,color);
	}
}

void CShapeBlender::bltLineCopy(CImage32* dest,int l,int r,int y,DWORD color){
	DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(l,y);  //���[�A�h���X
	DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(r,y);//�E�[�A�h���X
	for(;leftAdr<=rightAdr;leftAdr++)*leftAdr=color;
}
void CShapeBlender::bltLineAlpha50(CImage32* dest,int l,int r,int y,DWORD color){
	DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(l,y);  //���[�A�h���X
	DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(r,y);//�E�[�A�h���X
	for(;leftAdr<=rightAdr;leftAdr++){
		TARGB d,s;
		d.ARGB=*leftAdr; s.ARGB=color;
		d.R=(d.R+s.R)>>1;
		d.G=(d.G+s.G)>>1;
		d.B=(d.B+s.B)>>1;
		*leftAdr=d.ARGB;
	}
}
void CShapeBlender::bltLineMul(CImage32* dest,int l,int r,int y,DWORD color){
	DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(l,y);  //���[�A�h���X
	DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(r,y);//�E�[�A�h���X
	for(;leftAdr<=rightAdr;leftAdr++){
		TARGB d,s;
		d.ARGB=*leftAdr; s.ARGB=color;
		d.R=(BYTE)(((int)d.R*s.R)>>8);
		d.G=(BYTE)(((int)d.G*s.G)>>8);
		d.B=(BYTE)(((int)d.B*s.B)>>8);
		*leftAdr=d.ARGB;
	}
}
void CShapeBlender::fillRoundRect(CImage32* dest,RECT rc,double radius,DWORD color,TBltType type){
	for(int i=0;i<rc.bottom-rc.top;i++){
		if(rc.top+i>=dest->Height() || rc.top+i<0)continue;
		int left=rc.left;
		int right=rc.right;
		if(i<radius){
			left =rc.left +(int)radius-(int)sqrt(radius*radius-(i-radius)*(i-radius));
			right=rc.right-(int)radius+(int)sqrt(radius*radius-(i-radius)*(i-radius));
		}
		if(i>rc.bottom-rc.top-radius){
			left =rc.left +(int)radius-(int)sqrt(radius*radius-(radius-(rc.bottom-rc.top-i))*(radius-(rc.bottom-rc.top-i)));
			right=rc.right-(int)radius+(int)sqrt(radius*radius-(radius-(rc.bottom-rc.top-i))*(radius-(rc.bottom-rc.top-i)));
		}
		if(left<0)left=0;
		if(right>=dest->Width())right=dest->Width()-1;
		if(type==BLT_MEMCOPY)bltLineCopy(dest,left,right,rc.top+i,color);
		else if(type==BLT_ALPHA2)bltLineAlpha50(dest,left,right,rc.top+i,color);
		else if(type==BLT_MUL)bltLineMul(dest,left,right,rc.top+i,color);
	}
}

void CShapeBlender::fillSuperEllipse(CImage32* dest,int x,int y,double radiusX,double radiusY,double p,int angle,DWORD color){

	double c=cos(N_PI*angle);
	double s=sin(N_PI*angle);

	int rangeX=(int)max(fabs(radiusX*c),fabs(radiusY*s));
	int	rangeY=(int)max(fabs(radiusY*c),fabs(radiusX*s));
	if(p>1.0){//�O���ɓʂȂ�(radiusX,radiusY)����]�������_�������͈͂̌��
		rangeX=(int)max(fabs(radiusX*c+radiusY*s),rangeX); //��P�ی��̉�]�Ɣ�r
		rangeY=(int)max(fabs(-radiusX*s+radiusY*c),rangeY);//��P�ی��̉�]�Ɣ�r 
		rangeX=(int)max(fabs(radiusX*c-radiusY*s),rangeX);//��S�ی��̉�]�Ɣ�r
		rangeY=(int)max(fabs(-radiusX*s-radiusY*c),rangeY);//��S�ی��̉�]�Ɣ�r
	}

	int left=x-rangeX;
	int right=x+rangeX;
	int top=y-rangeY;
	int bottom=y+rangeY;

	//�`���摜��芮�S�ɊO���Ȃ�`�悵�Ȃ�
	if(left>dest->Width()-1 || right<0 || top>dest->Height()-1 || bottom<0)return;
	//�`��悩��n�~�o����������؂�l�߂�
	if(left<0)left=0;
	if(right>dest->Width()-1)right=dest->Width()-1;
	if(top<0)top=0;
	if(bottom>dest->Height()-1)bottom=dest->Height()-1;

	for(int i=top;i<=bottom;i++){
		for(int j=left;j<=right;j++){
			double x2=fabs((j-x)*c-(i-y)*s);
			double y2=fabs((j-x)*s+(i-y)*c);
			if(pow(x2/radiusX,p)+pow(y2/radiusY,p)<=1.0){
				dest->PixelSetNC(j,i,color); // NC: Non Clip@ing
			}
		}
	}
}