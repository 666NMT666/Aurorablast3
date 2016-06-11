#include <math.h>
class CHitTest{
public:
	static bool CircleToPoint(int x1,int y1,int x2,int y2,int radius);
	static bool CircleToCircle(int x1,int y1,int x2,int y2,int radius1,int radius2);
	static bool CircleToLine();// mijissou

	static bool MovingCircleToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int radius);
	static bool MovingCircleToCircle(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int radius1,int radius2);

	static bool MovingPolygonToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,CVector* r,int n);

	static bool sgn(double a){return (a>0);};

};

bool CHitTest::CircleToPoint(int x1,int y1,int x2,int y2,int r){
	int dx=x2-x1;
	int dy=y2-y1;
	return (dx*dx+dy*dy<r*r);
}

bool CHitTest::CircleToCircle(int x1,int y1,int x2,int y2,int radius1,int radius2){
	int dx=x2-x1;
	int dy=y2-y1;
	int r=radius1+radius2;
	return (dx*dx+dy*dy<r*r);
}

bool CHitTest::MovingCircleToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int r){
	if(CircleToPoint(x1,y1,x2,y2,r))return true;
	
	/*����1-2�Ԃ̑��Α��x�x�N�g��vx,vy (����1���Œ�)*/
	int vx=(x2-prevX2)-(x1-prevX1);
	int vy=(y2-prevY2)-(y1-prevY1);
	if(vx==0 && vy==0)return false;

	/*���Α��x�ɒ������锼�ar�̃x�N�g��*/
	double crossVx=-(double)(r*vy)/sqrt((double)(vy*vy+vx*vx));
	double crossVy= (double)(r*vx)/sqrt((double)(vy*vy+vx*vx));
	
	//(x1-crossVx,y1-crossVy)�`(x1+crossVx,y1+crossVy)�Ԃ̐�����(x2,y2)�`(x2-vx,y2-vy)�Ԃ̐������N���X����΃q�b�g
	/*���݂̈ʒu�֌W���ߋ��Ɋ����߂��ߒ��ŏՓ˂��N���邩���m�F*/
	// �_�ix2,y2�j���獶�E�m�F  // �_�ix1+crossVx,y1+crossVy�j���獶�E�m�F
	if(((((x1-crossVx)-x2)*vy-((y1-crossVy)-y2)*vx)*(((x1+crossVx)-x2)*vy-((y1+crossVy)-y2)*vx)<0)
		&& (((x2-(x1+crossVx))*crossVy-(y2-(y1+crossVy))*crossVx)*((x2-vx-(x1+crossVx))*crossVy-(y2-vy-(y1+crossVy))*crossVx)<0)
		){return true;}
	else {return false;}
}

bool CHitTest::MovingCircleToCircle(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int r1,int r2){
	if(CircleToCircle(x1,y1,x2,y2,r1,r2))return true;
	
	/*����1-2�Ԃ̑��Α��x�x�N�g��vx,vy*/
	int vx=(x2-prevX2)-(x1-prevX1);
	int vy=(y2-prevY2)-(y1-prevY1);

	if(vx==0 && vy==0)return false;

	/*���Α��x�ɒ������锼�ar�̃x�N�g��*/
	double crossVx=-(double)((r1+r2)*vy)/sqrt((double)(vy*vy+vx*vx));
	double crossVy= (double)((r1+r2)*vx)/sqrt((double)(vy*vy+vx*vx));
	if(crossVx*(x2-x1)+crossVy*(y2-y1)<0){
		crossVx*=-1; crossVy*=-1; // �����x�N�g���̌������t
	}

	//(x1,y1)�`(x1+crossVx,y1+crossVy)�Ԃ̐�����(x2,y2)�`(x2-vx,y2-vy)�Ԃ̐������N���X����΃q�b�g
	if((sgn((x1-x2)*vy-(y1-y2)*vx)!=sgn((x1+crossVx-x2)*vy-(y1+crossVy-y2)*vx))
		&& (sgn((x2-x1)*crossVy-(y2-y1)*crossVx)!=sgn((x2-vx-x1)*crossVy-(y2-vy-y1)*crossVx))
		){return true;}
	else {return false;}
}

bool CHitTest::MovingPolygonToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,CVector* r,int n){
	//*����1(x1,y1)�͑��p�`�A����2(x2,y2)�͓_�Ar�F���p�`�̑S���_�̍��W�z��An���_�̐�*//
	if(ExMath::isInPoligon(x2,y2,r,n)){ return true; } // �Œ�o�[�W����
	
	/*����1-2�Ԃ̑��Α��x�x�N�g��vx,vy�A���p�`���Œ�*/
	double vx=(x2-prevX2)-(x1-prevX1);
	double vy=(y2-prevY2)-(y1-prevY1);

	/*����2���}�C�i�X���Α��x�����Ɋ����߂��ߒ��ő��p�`�̕ӂƃN���X����ΏՓ˂Ƃ���*/
	for(int i=0;i<n-1;i++){
		if((((-vx*(r[i%n].y-y2)-(-vy*(r[i%n].x-x2))))*((-vx*(r[(i+1)%n].y-y2))-(-vy*(r[(i+1)%n].x-x2)))<0) && 
			(((((r[(i+1)%n].y-r[i%n].y)*(x2-r[i%n].x))-(r[(i+1)%n].x-r[i%n].x)*(y2-r[i%n].y)))*
			 ((((r[(i+1)%n].y-r[i%n].y)*(x2-vx-r[i%n].x))-(r[(i+1)%n].x-r[i%n].x)*(y2-vy-r[i%n].y)))<0)
		){return true;}
	}
	return false;
}