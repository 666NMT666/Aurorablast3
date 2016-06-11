#include <math.h>
#ifndef _NMT_VECTOR_H_
#define _NMT_VECTOR_H_

class CVector{
public:
	double x,y;
	CVector(){x=0.0;y=0.0;}
	CVector(double i, double j) { x = i; y = j; }
	CVector(double x1, double y1, double x2, double y2) { x = x2 - x1; y = y2 - y1; }
	void SetVector(CVector v){x=v.x; y=v.y;}
	void SetVector(double vx,double vy){x=vx; y=vy;}

	//â¡éZ
	CVector operator+(const CVector& obj);
	CVector& operator+=(const CVector& obj);
	//å∏éZ
	CVector operator-(const CVector& obj);
	CVector& operator-=(const CVector& obj);
	//èÊéZ
	CVector operator*(const double a);
	CVector& operator*=(const double a);
	//èúéZ
	CVector operator/(const double a);
	CVector& operator/=(const double a);
	//ì‡êœ
	double operator*(const CVector& obj);//ì‡êœ
	double Abs(){return sqrt(x*x+y*y);}

	static CVector EigenVector(double x1,double y1,double x2,double y2){
		double r=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
		CVector v((x2-x1)/r,(y2-y1)/r);
		return v;
	}
	static CVector EigenVector(double tx,double ty){
		CVector v(tx/(tx*tx+ty*ty),ty/(tx*tx+ty*ty));
		return v;
	}
	static void getRect(CVector *v, int x,int y, int w,int h, int dl=0,int dt=0,int dr=0,int db=0) {
		v[0].x = x - w / 2 + dl; v[0].y = y - h / 2 + dt;
		v[1].x = x + w / 2 + dr; v[1].y = y - h / 2 + dt;
		v[2].x = x + w / 2 + dr; v[2].y = y + h / 2 + db;
		v[3].x = x - w / 2 + dl; v[3].y = y + h / 2 + db;
	}
	void Set(double setx,double sety){x=setx;y=sety;}
	void Add(double mx,double my){x+=mx;y+=my;}
	void Mul(double c){x*=c;y*=c;}
	void MulH(double c){y*=c;}
	void MulW(double c){x*=c;}
	void Rotate(double angle);
	void RotateAround(double ox,double oy,double angle);
	static CVector Vector(double vx,double vy){
		CVector v(vx,vy);
		return v;
	}
	static CVector TargetVector(int m_x,int m_y,int x,int y,double s){
		CVector v;
		double preVx=x-m_x, preVy=y-m_y;
		if(preVx==0){v.x=0;v.y=s;return v;}
		if(preVy==0){v.x=s;v.y=0;return v;}
		v.x=s*preVx/sqrt((double)preVx*preVx + preVy*preVy);
		v.y=s*preVy/sqrt((double)preVx*preVx + preVy*preVy);
		return v;
	}
	void Resize(double s){
		double length=sqrt(x*x+y*y);
		x=s*x/length; y=s*y/length;
	}
	CVector getEigenVector(){ CVector v(x/(x*x+y*y),y/(x*x+y*y)); return v; }
	CVector getOrthogonalVector(){ CVector v(-y/(x*x+y*y),x/(x*x+y*y)); return v; }


};



#endif