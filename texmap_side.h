#ifndef _TEXMAP_SIDE_H_
#define _TEXMAP_SIDE_H_
#include "blt_info.h"
#include "texmap_vertex.h"

// �e�N�X�`���}�b�s���O�p�̕�
struct TTexMapSide{
	TTexMapVertex* v1;
	TTexMapVertex* v2;
};

// �e�N�X�`���}�b�v�̕�///////////////////////////////////////////////////////
class CTexMapSide{
protected:
	int m_num;
	TTexMapSide m_side[4];
public:
	CTexMapSide():m_num(0){}
	BOOL Add( TTexMapVertex* v1, TTexMapVertex* v2 ){
		m_side[ m_num ].v1 = v1;
		m_side[ m_num ].v2 = v2;
		m_num++;
		return TRUE;
	}
	void Get( TTexMapVertex** v1, TTexMapVertex** v2, int index ){
		*v1 = m_side[index].v1;
		*v2 = m_side[index].v2;
	}
	BOOL Intersection( int index, double y, double* x, double* sx, double* sy ){
		TTexMapVertex *v1,*v2;
		Get( &v1,&v2, index );
		// �����������ꍇ�͒e��
		if (v1->dy == v2->dy) return FALSE;
		// �ӂ͈͓̔��H
		if(((y <= v1->dy) && (y >= v2->dy))||((y >= v1->dy) && (y <= v2->dy))){
			// �[�ƌ���
			if (y == v1->dy){
				*x  = v1->dx;
				*sx = v1->sx;
				*sy = v1->sy;
				return TRUE;
			}
			if(y == v2->dy){
				*x  = v2->dx;
				*sx = v2->sx;
				*sy = v2->sy;
				return TRUE;
			}
			if (v2->dy < v1->dy) SWAP( &v1, &v2 );
			double m = (y - v1->dy) / (v2->dy - v1->dy);
			*x  = v1->dx + m*(v2->dx - v1->dx);
			*sx = v1->sx + m*(v2->sx - v1->sx);
			*sy = v1->sy + m*(v2->sy - v1->sy);
			return TRUE;
		}  
		return FALSE;
	}
	// sx,sy�Ƀ\�[�X���W
	int Num(){ return m_num; }
};

#endif