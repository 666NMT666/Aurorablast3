#ifndef _TEXMAP_VERTEX_H_
#define _TEXMAP_VERTEX_H_
// テクスチャマッピング用の頂点
struct TTexMapVertex{
	double dx,dy; // 描画先の座標
	double sx,sy; // テクスチャ (描画元) の座標
};

// テクスチャの座標＆描画先座標を指定/////////////////////////////////////
class CTexMapVertex{
protected:
	int m_num;
	TTexMapVertex m_vertex[4];
public:
	CTexMapVertex(){m_num = 0;}
	void Clear(){m_num = 0;}
	BOOL Add( double dx, double dy, double sx, double sy ){ // dx,dy:描画先 sx,sy:テクスチャ座標
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
