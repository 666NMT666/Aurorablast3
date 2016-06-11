#include <math.h>
#ifndef _NMT_VECTOR_CPP_
#define _NMT_VECTOR_CPP_
#include "vector.h"

// +���Z�q�I�[�o�[���[�h
CVector CVector::operator+(const CVector& obj){
	CVector tmp(x+obj.x, y+obj.y);
	return tmp;
}

// +=���Z�q�I�[�o�[���[�h
CVector& CVector::operator+=(const CVector& obj){
	x += obj.x;
	y += obj.y;
	return *this;
}

// -���Z�q�I�[�o�[���[�h
CVector CVector::operator-(const CVector& obj){
	CVector tmp(x-obj.x, y-obj.y);
	return tmp;
}

// -=���Z�q�I�[�o�[���[�h
CVector& CVector::operator-=(const CVector& obj){
	x -= obj.x;
	y -= obj.y;
	return *this;
}

// *���Z�q�I�[�o�[���[�h
CVector CVector::operator*(const double a){
	CVector tmp(x*a, y*a);
	return tmp;
}

// *=���Z�q�I�[�o�[���[�h
CVector& CVector::operator*=(const double a){
	x *= a;
	y *= a;
	return *this;
}

// /���Z�q�I�[�o�[���[�h
CVector CVector::operator/(const double a){
	CVector tmp(x/a, y/a);
	return tmp;
}

// /=���Z�q�I�[�o�[���[�h
CVector& CVector::operator/=(const double a){
	x /= a;
	y /= a;
	return *this;
}

double CVector::operator*(const CVector& obj){//����
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