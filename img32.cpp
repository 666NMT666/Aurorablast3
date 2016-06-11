#include <stdio.h>
#include "img32.h"

#ifndef _IMG32_CPP_
#define _IMG32_CPP_


CImage32::CImage32(char* file){
	if(file==NULL)return;
	else {
		m_buffer=NULL;
		load(file);
	}
}
CImage32::CImage32(const int w,const int h):m_buffer(NULL){Resize(w,h);}
CImage32::CImage32():m_buffer(NULL){Resize(1,1);}
CImage32::~CImage32(){Free();}
void CImage32::Free(){
	if(m_buffer != NULL)free(m_buffer);
	m_buffer = NULL;
}
void CImage32::Resize(const int width,const int height){
	Free();
	m_width=width; m_height=height;
	m_buffer=malloc(width*height*4);
}
void* CImage32::PixelAddress(const int x,const int y){
	return (x<0 || x>=m_width || y<0 || y>=m_height) ? NULL : PixelAddressNC(x,y);
}
const void* CImage32::PixelAddress(const int x,const int y) const {
	return (x<0 || x>=m_width || y<0 || y>=m_height) ? NULL : PixelAddressNC(x,y);
}
void CImage32::PixelSet(const int x,const int y,const DWORD color){
	DWORD* ptr = (DWORD*)PixelAddress(x,y);
	if(ptr!=NULL)*ptr=color;
}
void CImage32::PixelSetNC(const int x,const int y, const DWORD color){
	DWORD* ptr = (DWORD*)PixelAddress(x,y);
	*ptr=color;
}
DWORD CImage32::PixelGet(const int x,const int y) const{
	DWORD* ptr = (DWORD*)PixelAddress(x,y);
	return (ptr==NULL) ? 0:*ptr;
}
DWORD CImage32::PixelGetNC(const int x,const int y) const{return *(DWORD*)PixelAddress(x,y);}

int CImage32::putcLittleEndian2(unsigned short int d, FILE *s){
	putc(d & 0xFF, s);
	return putc(d >> CHAR_BIT, s);
}

int CImage32::putcLittleEndian4(unsigned long d, FILE *s){
	putc(d & 0xFF, s);
	putc((d >> CHAR_BIT) & 0xFF, s);
	putc((d >> CHAR_BIT * 2) & 0xFF, s);
	return putc((d >> CHAR_BIT * 3) & 0xFF, s);
}

int CImage32::putBmpHeader(FILE *s, int x, int y, int c) {
	unsigned long int bfOffBits=14 + 40; // ヘッダサイズ(byte)
	if (x <= 0 || y <= 0) { return 0; } // 画像サイズ異常->エラー返す
	if (s == NULL || ferror(s)) { return 0; }//出力異常->エラー返す
	//BITMAP FILE HEADER(14byte)書出
	fputs("BM", s); //識別文字列
	putcLittleEndian4(bfOffBits + (unsigned long)x * y, s);//bfSize ファイルサイズ(byte)
	putcLittleEndian2(0, s); // bfReserved1 予約領域1
	putcLittleEndian2(0, s); // bfReserved2 予約領域2
	putcLittleEndian4(bfOffBits, s); // bfOffBits ヘッダサイズ
	//* BITMAP INFO HEADER(40byte)書出 
	putcLittleEndian4(40,s); // biSize
	putcLittleEndian4(x, s); // biWidth
	putcLittleEndian4(y, s); // biHeight
	putcLittleEndian2(1, s); // biPlanes
	putcLittleEndian2(c, s); // biBitCount
	putcLittleEndian4(0, s); // biCompression
	putcLittleEndian4(0, s); // biSizeImage
	putcLittleEndian4(0, s); // biXPelsPerMeter
	putcLittleEndian4(0, s); // biYPelsPerMeter
	putcLittleEndian4(0, s); // biClrUsed
	putcLittleEndian4(0, s); // biClrImportant
	if (ferror(s)) { return 0; }// 書出失敗処理
	return 1; // 成功でリターン 
}

void CImage32::save(const char* fname){
	int imgsize=(m_width*4)*m_height; //イメージのサイズ
	BYTE *buf,*buf_top;// 画像データとその先頭ポインタ
	FILE* fp;
	errno_t err;
	if ((err = fopen_s(&fp, fname, "wb")) != 0) { return; }

	putBmpHeader(fp,m_width, m_height,32); //ヘッダ出力
	buf_top = buf = (BYTE*)malloc(imgsize); //出力バッファ確保
	if(buf_top == NULL) return; //メモリ確保失敗
	for(int i=m_height-1;i>=0;i--){ //データ整列
		for(int j=0;j<m_width;j++){
			TARGB c;
			c.ARGB=PixelGet(j,i);
			*(buf++)=(BYTE)c.B;
			*(buf++)=(BYTE)c.G;
			*(buf++)=(BYTE)c.R;
			*(buf++)=(BYTE)c.A;
		}
	}
	if(fwrite((void*)buf_top,1,imgsize,fp) != imgsize){ //画像データ出力
		free(buf_top);
		return;// 書き込み失敗
	}
	free(buf_top);
	fclose(fp);
}
#include <windows.h>
// void CImage32::load(char* fname,TImageType t){}
void CImage32::load(const char* fname){
	FILE *fin;
	BYTE *p;
    WORD biBitCount;
	DWORD dummy;
	errno_t err;
	if((err=fopen_s(&fin ,fname, "rb"))!=0){
		perror(fname);
		//MessageBox(GetActiveWindow(), fname, NULL, 0);
		return;// exit(EXIT_FAILURE);
	}
	//BITMAPFILEHEADER
	fread(&dummy, sizeof(WORD), 1, fin);
	fread(&dummy, sizeof(DWORD), 1, fin);
	fread(&dummy, sizeof(WORD), 1, fin);
	fread(&dummy, sizeof(WORD), 1, fin);
	fread(&dummy, sizeof(DWORD), 1, fin);
	//BITMAPINFOHEADER
	fread(&dummy, sizeof(DWORD), 1, fin);
	fread(&m_width, sizeof(LONG), 1, fin);//サイズ取得
	fread(&m_height, sizeof(LONG), 1, fin);//サイズ取得
	fread(&dummy, sizeof(WORD), 1, fin);
	fread(&biBitCount, sizeof(WORD), 1, fin);//bit数取得
	fread(&dummy, sizeof(DWORD), 1, fin);
	fread(&dummy, sizeof(DWORD), 1, fin);
	fread(&dummy, sizeof(LONG), 1, fin);
	fread(&dummy, sizeof(LONG), 1, fin);
	fread(&dummy, sizeof(DWORD), 1, fin);
	fread(&dummy, sizeof(DWORD), 1, fin);
	// free
	if(m_buffer != NULL)free(m_buffer);
	m_buffer = (void*)malloc(m_width*m_height*4);
	// read data
	p = (BYTE*)m_buffer+m_width*(m_height-1)*4;
	int pad=4-(m_width*3)%4;
	if(pad==4)pad=0;
	if (biBitCount == 24) {
		BYTE rgb[3];
		for (int i = 0; i < m_height; i++) {
			p=(BYTE*)m_buffer+m_width*(m_height-1-i)*4;
			for (int j=0;j<m_width;j++) {
				fread(&rgb, 3*sizeof(BYTE),1,fin);
				for(int k=0;k<3;k++){*(p++)=rgb[k];}
				*(p++) = 0xff;
			}
			if(m_width%4!=0){
				for (int j=0;j<pad;j++)fread(&dummy,1,1,fin);
			}
		}
	}else if(biBitCount == 32){
		BYTE rgb[4];
		for (int i = 0; i < m_height; i++) {
			p = (BYTE*)m_buffer+m_width*(m_height-1-i)*4;
			for (int j = 0; j < m_width; j++) {
				fread(&rgb, 4 * sizeof(BYTE), 1, fin);
				for (int k = 0; k<3; k++) { *(p++) = rgb[k]; }
				*(p++) = 0xff;
				//fread(&rgb, 4*sizeof(BYTE), 1, fin); //アルファ値を生かす場合はこちらを復活させる
				//for(int k=0;k<4;k++)*(p++)=rgb[k];   //ただしbmpのアルファ値はSAIでは無視され編集困難
			}
		}
	}
	fclose(fin);
}

#endif

/*
void CImage32::save(char* fname){
	static const int byte4=4;//24bitなら3
	int pad=(m_width*byte4)%4; //32bitパディング
	int imgsize=(m_width*byte4+pad)*m_height; //イメージのサイズ
	BYTE *buf,*buf_top;// 画像データとその先頭ポインタ
	FILE* fp=fopen(fname,"wb");
	if(fp == NULL) return; // 引数異常
	putBmpHeader(fp,m_width, m_height, 8*byte4); //ヘッダ出力
	buf_top = buf = (BYTE*)malloc(imgsize); //出力バッファ確保
	if(buf_top == NULL) return; //メモリ確保失敗
	for(int i = m_height - 1 ; i >= 0 ; i--){ //データ整列
		for(int j=0;j<m_width;j++){
			TARGB c;
			c.ARGB=PixelGet(j,i);
			*(buf++)=(BYTE)c.B;
			*(buf++)=(BYTE)c.G;
			*(buf++)=(BYTE)c.R;
			*(buf++)=(BYTE)c.A;
		}
		for(int j=0;j<pad;j++)*(buf++) = 0;
	}
	if(fwrite((void*)buf_top,1,imgsize,fp) != imgsize){ //画像データ出力
		free(buf_top);
		return;// 書き込み失敗
	}
	free(buf_top);
	fclose(fp);
}


int CImage32::putBmpHeader(FILE *s, int x, int y, int c) {
	unsigned long int bfOffBits=14 + 40;
	if (x <= 0 || y <= 0) { return 0; }
	if (s == NULL || ferror(s)) { return 0; }
	if (c < 24) {
		int color = 1;
		for (int i=1;i<=c;i++) { color *= 2; }
		bfOffBits=14+40+4*color;
	}

	fputs("BM", s);
	putcLittleEndian4(bfOffBits + (unsigned long)x * y, s);
	putcLittleEndian2(0, s);
	putcLittleEndian2(0, s);
	putcLittleEndian4(bfOffBits, s);

	putcLittleEndian4(40,s);
	putcLittleEndian4(x, s);
	putcLittleEndian4(y, s);
	putcLittleEndian2(1, s);
	putcLittleEndian2(c, s);
	putcLittleEndian4(0, s);
	putcLittleEndian4(0, s);
	putcLittleEndian4(0, s);
	putcLittleEndian4(0, s);
	putcLittleEndian4(0, s);
	putcLittleEndian4(0, s);
	if (ferror(s)) { return 0; }
	return 1;
}
*/