#include <math.h>
#ifndef _NMT_VECTOR_CPP_
#define _NMT_VECTOR_CPP_
#include "vector.h"

// +演算子オーバーロード
CVector CVector::operator+(const CVector& obj){
	CVector tmp(x+obj.x, y+obj.y);
	return tmp;
}

// +=演算子オーバーロード
CVector& CVector::operator+=(const CVector& obj){
	x += obj.x;
	y += obj.y;
	return *this;
}

// -演算子オーバーロード
CVector CVector::operator-(const CVector& obj){
	CVector tmp(x-obj.x, y-obj.y);
	return tmp;
}

// -=演算子オーバーロード
CVector& CVector::operator-=(const CVector& obj){
	x -= obj.x;
	y -= obj.y;
	return *this;
}

// *演算子オーバーロード
CVector CVector::operator*(const double a){
	CVector tmp(x*a, y*a);
	return tmp;
}

// *=演算子オーバーロード
CVector& CVector::operator*=(const double a){
	x *= a;
	y *= a;
	return *this;
}

// /演算子オーバーロード
CVector CVector::operator/(const double a){
	CVector tmp(x/a, y/a);
	return tmp;
}

// /=演算子オーバーロード
CVector& CVector::operator/=(const double a){
	x /= a;
	y /= a;
	return *this;
}

double CVector::operator*(const CVector& obj){//内積
	return x*obj.x + y*obj.y;
}

void CVector::Rotate(double angle){
	double c=cos(angle);
	double s=sin(angle);
	SetVector(x*c+y*s, y*c-x*s);
}

void CVector::RotateAround(double ox,double oy,double angle){
	double c=cos(angle);
	double s=sin(angle);
	x-=ox; y-=oy;
	SetVector(x*c+y*s, y*c-x*s);
	x+=ox; y+=oy;
}
#endif