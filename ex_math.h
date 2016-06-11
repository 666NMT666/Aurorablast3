#ifndef _NMATH_H_
#define _NMATH_H_  

#include <windows.h>
#include <math.h>
#include "vector.h"

typedef struct _TCircle {
	int x, y, r;
} TCircle;

class CExCircle {
public:
	static TCircle initCircle(TCircle* c, int x, int y, int r);
	static bool isInCircle(TCircle* c,int x,int y){
		int dx=x-c->x;
		int dy=y-c->y;
		return (dx*dx+dy*dy < c->r*c->r);
	}
	static bool isCoregion(TCircle c1,TCircle c2);
};

namespace ExMath{
	double angleBetweenPoints(int sx,int sy,int tx,int ty);
	int stableRandom(int i);
	double sigmoid(double amplitude, double t);
	double internalDividingPoint(int left,int right,double div);
	double internalDividingPoint(int left,int right,double divA,double divB);
	double sigmoid(int t,int midT,int gamma, int Amp);
	int delta(int t,int midT);
	double sizedDelta(int t,int midT,int amp);
	int normalizeBetween(int min,int max,int val);
	const int keta(int a){ if(a<=0)return 1; return (int)log10((double)a)+1;}
	const int keta(DWORD a){ if(a==0)return 1; return (int)log10((double)a)+1;}
	double asymptote(double from,double to,double t);
	double superElipse(double from,double to,double t,double maxT,double n){
		if(t<0)return from;
		if(t>maxT)return to;
		return from + ((to-from)-(to-from)*pow(1.0-pow(t/maxT,n),1.0/n));
	}

	CVector asymptote(CVector from,CVector to,double t);
	int linearBetween(double from,double to,double t);
	bool isInCircle(int x,int y,int r);
	bool isInRect(int x,int y,int left,int top,int right,int bottom);
	bool isInPoligon(int x,int y,CVector* r,int n);

	bool isInParallelogram(int x,int y,CVector r1,CVector r2,CVector r3,CVector r4);
	bool isInHorizontalParallelogram(int x,int y,CVector r1,CVector r2,int w);
	bool isInVerticalParallelogram(int x,int y,CVector r1,CVector r2,int w);
	double distanceBetweenPoints(int sx,int sy,int dx,int dy){return sqrt((double)((sx-dx)*(sx-dx)+(sy-dy)*(sy-dy)));} 
	
};

double ExMath::sizedDelta(int t,int midT,int amp){
	return amp/(1+(t-midT)*(t-midT));
}

int ExMath::delta(int t,int midT){
	if(t==midT)return 1;
	else return 0;
}

double ExMath::sigmoid(int t,int midT,int gamma, int Amp){
	return Amp/(1.0 - exp((double)(-gamma*(t-midT))));
}

double ExMath::internalDividingPoint(int left,int right,double div){
	return div-div*left + div*right;
}

double ExMath::internalDividingPoint(int left,int right,double divA,double divB){
	return (divB*left + divA*right) / (divB+divA);
}

double ExMath::angleBetweenPoints(int sx,int sy,int tx,int ty){//戻り値の単位は度
	double pa=0;
	double dx=tx-sx;
	double dy=ty-sy;
	pa=atan2(dy,dx)/0.01745329251994329576;
	return pa;
}

int ExMath::stableRandom(int i){ 
	static const int rnd[]={130,10982,1090,11656,7117,17595,6415,22948,31126,9004};
	static const int length = sizeof rnd /sizeof rnd[0];
	return rnd[i % length];
}
double ExMath::sigmoid(double amplitude,double t){ return amplitude/(1.0+exp(-t)); }

int ExMath::normalizeBetween(int min,int max,int val){
	if(val<min)return min;
	else if(val>max)return val;
	return val;
}

double ExMath::asymptote(double from,double to,double t){
	if(t<1)t=1;
	return to-(to-from)/t;
}

CVector ExMath::asymptote(CVector from,CVector to,double t){
	if(t<1)t=1;
	return to-(to-from)/t;
}

int ExMath::linearBetween(double from,double to,double t){
	if(t<1)t=1;
	return (int)(to-(to-from)/t);
}

bool ExMath::isInCircle(int x,int y,int r){ return x*x+y*y<r*r; }

bool ExMath::isInRect(int x,int y,int left,int top,int right,int bottom){
	return (left<x && x<right && top<y && y<bottom);
}

bool ExMath::isInPoligon(int x,int y,CVector* r,int n){
	CVector o((double)x,(double)y);
	bool isPlus=true; // 結果保存用
	for(int i=0;i<n;i++){
		CVector a=r[(i+1)%n]-r[i]; //辺ベクトル
		CVector b=o-r[i]; //頂点から対象へのベクトル
		bool tmp=(a.x*b.y-a.y*b.x>0.0); //外積Z成分
		if(i==0)isPlus=tmp; //全部マイナスの場合に備えて1回目は保存のみ
		else if(isPlus!=tmp)return false; //2回目以降は1回目の結果と比較。違ったら外側。
	}
	return true; //全て同じなら内側
}

#endif
