#ifndef _BLTINFO_H_
#define _BLTINFO_H_ 
#include <windows.h>
#include <math.h>
#include "prefix.h"
#include "vector.h"

union TARGB{
	DWORD ARGB;
	struct { BYTE B,G,R,A; };
};
enum TBltType
{
  BLT_NULL,   /// ��\��
  BLT_MEMCOPY,  ///�R�s�[
  BLT_KEY,    /// �L�[�F�ȊO�R�s�[
  BLT_ADD,    /// ���Z�]��
  BLT_MUL,    /// ��Z�]��
  BLT_MINUS,  /// ���Z
  BLT_SCREEN,  /// �X�N���[��
  BLT_ALPHA,  /// alpha����
  BLT_BLACKEN, ///����
  BLT_WHITEN, ///����
  BLT_KEYADD, ///�L�[�F�ȊO���Z
  BLT_ALPHA2, ///����


  BLT_KEYBLACKEN,///�L�[�L�荕��
  BLT_MULCOLOR, /// ����F��Z
  BLT_RED,  ///���]
  BLT_STRUCTURE,///
  BLT_MEMCOPY_SKIP,
  BLT_SKIP,
	BLT_SKIP2,


  BLT_MIRRORKEY,///�L�[���]
  BLT_MIRRORKEYADD,///���]�L�[���Z
  
  BLT_XMINUS,///��F���Z
  BLT_MIRRORBLACKEN,
  BLT_YELLOW,   /// ���F���Z
  BLT_MULCOLOR__, /// ����F��Z
  BLT_GREENADD, /// �ΐF���Z�]��
  BLT_BLUEADD, /// �F���Z�]��
};

enum TImageExt {
	EXT_BMP,
	EXT_PNG,
	EXT_JPG, // ���g�p
	EXT_GIF //���g�p
};

// �]��
class CBltInfo{
public:
	TBltType type;  /// ���Z
	int alpha;     /// �s�����x
	int angle;     /// ��]�p�x
	int link_x,link_y; /// �����N���W
	double zoom;
	double zoom_x;
	double zoom_y;
	int hole_x, hole_y, hole_r;
	DWORD ctr_color;///
	CBltInfo(){Clear();}
	CBltInfo( TBltType type_ ){Clear();type=type_;}
	CBltInfo( TBltType type_, int alpha_ ){Clear();type=type_;alpha=alpha_;}
	void Clear(){
		link_x=link_y=0;
		type = BLT_MEMCOPY;
		alpha = 255;
		ctr_color=0x0000000;
		zoom=1.0;
		zoom_x=1.0;
		zoom_y=1.0;
		angle=0;
		hole_x = hole_y = hole_r=0;
	}
};

#endif