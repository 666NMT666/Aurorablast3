#ifndef _TEXMAP_VERTEX_H_
#define _TEXMAP_VERTEX_H_
// �e�N�X�`���}�b�s���O�p�̒��_
struct TTexMapVertex{
	double dx,dy; // �`���̍��W
	double sx,sy; // �e�N�X�`�� (�`�挳) �̍��W
};

// �e�N�X�`���̍��W���`�����W���w��/////////////////////////////////////
class CTexMapVertex{
protected:
	int m_num;
	TTexMapVertex m_vertex[4];
public:
	CTexMapVertex(){m_num = 0;}
	void Clear(){m_num = 0;}
	BOOL Add( double dx, double dy, double sx, double sy ){ // dx,dy:�`��� sx,sy:�e�N�X�`�����W
		if (m_num >= 4) return FALSE;
		m_vertex[ m_num ].dx = dx;
		m_vertex[ m_num ].dy = dy;
		m_vertex[ m_num ].sx = sx;
		m_vertex[ m_num ].sy = sy;
		m_num++;
		return TRUE;
	}
	void GetDest( double* dx, double* dy, int index ){
		*dx = m_vertex[ index ].dx;
		*dy = m_vertex[ index ].dy;
	}
	int Num(){ return m_num; }
	TTexMapVertex* Vertex( int index ){ return &m_vertex[index]; }
};

#endif
