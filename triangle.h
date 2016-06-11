class CTriangle{
public: 
	static void fillTriangle(CImage32 *dest,CVector r1,CVector r2,CVector r3,DWORD c);
	static void fillTriangle(CImage32 *dest,CVector r1,CVector r2,CVector r3,DWORD c,RECT rect);
};

void CTriangle::fillTriangle(CImage32 *dest,CVector r1,CVector r2,CVector r3,DWORD c,RECT rc){
	if(r3.y<r2.y)SWAP(&r3,&r2); // 
	if(r2.y<r1.y)SWAP(&r1,&r2); // r1���ŏ㕔 , r2���܂�Ԃ�, r3���ŉ���
	if(r3.y<r2.y)SWAP(&r3,&r2); // 
	static const int fixfloat_const=1<<8;
	int size=(int)(r3.y-r1.y); //�o�b�t�@�T�C�Y
	int corner=(int)(r2.y-r1.y); //�܂�Ԃ��܂ł̃T�C�Y
	int y1=(int)r1.y, x1=(int)r1.x, x2=(int)r2.x; // �����Ƃ��Ďg�������͐����ɕۑ�
	if(size==0)return; //�@�T�C�Y�O�Ȃ�I��
	int grad1=(corner>0)?(int)((r2.x-r1.x)/(r2.y-r1.y)*fixfloat_const):0;//0����͔������Ȃ�
	int grad2=(size>corner)?(int)((r3.x-r2.x)/(r3.y-r2.y)*fixfloat_const):0; //0����͔������Ȃ�
	int grad3=(int)((r3.x-r1.x)/(r3.y-r1.y)*fixfloat_const);
	int top=(y1<rc.top)?-y1:rc.top;
	int bottom=(y1+size>=rc.bottom)?rc.bottom-y1-1:size;
	for(int i=top;i<bottom;i++){ // �ŏ㕔����܂�Ԃ��n�_�܂ŕ`��
		int right=((i*grad3)>>8)+x1; // ���̎��_�ł̍��E�͉���
		int left=(i<corner)?((i*grad1)>>8)+x1:(((i-corner)*grad2)>>8)+x2;
		if(left>right)SWAP(&left,&right); //�����ō��E�m��
		if(left>=rc.right || right<=rc.left)continue;
		if(left<rc.left)left=rc.left;
		if(right>rc.right-1)right=rc.right-1;
		DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(left,y1+i);  //���[�A�h���X
		DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(right,y1+i);//�E�[�A�h���X
		for(;leftAdr<rightAdr;leftAdr++)*leftAdr=c;
	}
}

void CTriangle::fillTriangle(CImage32 *dest,CVector r1,CVector r2,CVector r3,DWORD c){
	if(r3.y<r2.y)SWAP(&r3,&r2); // 
	if(r2.y<r1.y)SWAP(&r1,&r2); // r1���ŏ㕔 , r2���܂�Ԃ�, r3���ŉ���
	if(r3.y<r2.y)SWAP(&r3,&r2); // 
	static const int fixfloat_const=1<<8;
	int size=(int)(r3.y-r1.y); //�o�b�t�@�T�C�Y
	int corner=(int)(r2.y-r1.y); //�܂�Ԃ��܂ł̃T�C�Y
	int y1=(int)r1.y, x1=(int)r1.x, x2=(int)r2.x; // �����Ƃ��Ďg�������͐����ɕۑ�
	if(size==0)return; //�@�T�C�Y�O�Ȃ�I��
	int grad1=(corner>0)?(int)((r2.x-r1.x)/(r2.y-r1.y)*fixfloat_const):0;//0����͔������Ȃ�
	int grad2=(size>corner)?(int)((r3.x-r2.x)/(r3.y-r2.y)*fixfloat_const):0; //0����͔������Ȃ�
	int grad3=(int)((r3.x-r1.x)/(r3.y-r1.y)*fixfloat_const);
	int top=(y1<0)?-y1:0;
	int bottom=(y1+size>=dest->Height())?dest->Height()-y1-1:size;
	for(int i=top;i<bottom;i++){ // �ŏ㕔����܂�Ԃ��n�_�܂ŕ`��
		int right=((i*grad3)>>8)+x1; // ���̎��_�ł̍��E�͉���
		int left=(i<corner)?((i*grad1)>>8)+x1:(((i-corner)*grad2)>>8)+x2;
		if(left>right)SWAP(&left,&right); //�����ō��E�m��
		if(left>=dest->Width() || right<=0)continue;
		if(left<0)left=0;
		if(right>dest->Width()-1)right=dest->Width()-1;
		DWORD* leftAdr=(DWORD*)dest->PixelAddressNC(left,y1+i);  //���[�A�h���X
		DWORD* rightAdr=(DWORD*)dest->PixelAddressNC(right,y1+i);//�E�[�A�h���X
		for(;leftAdr<rightAdr;leftAdr++)*leftAdr=c;
	}
}

