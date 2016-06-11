#ifndef _CSV_UTIL
#include <windows.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "file_util.h"
class CCsvUtil {
	static const int MAX_STRS=255;
	std::string** mData;
	unsigned int mNumLows, mNumColumns;

	void _read(char* fname,int lows,int cols) {
		mNumLows = lows;
		mNumColumns = cols;
		FILE *fin;
		char *ctx;
		my_fopen_in(&fin, fname);
		char buf[MAX_STRS];
		mData = new std::string*[lows];
		for (int i = 0; i < lows; i++) {
			mData[i] = new std::string[cols];
		}
		int low = 0;
		while (fgets(buf, MAX_STRS, fin) != NULL) {
			if (low >= mNumLows)break;
			mData[low][0] = strtok_s(buf, ",", &ctx);
			for (unsigned int col = 1; col < mNumColumns; col++) {
				mData[low][col] = strtok_s(NULL, ",", &ctx);
				for (int pt = 0; mData[low][col][pt] != '\0'; pt++) {
					if (mData[low][col][pt] == '\n') { //////　改行コードは消す chomp
						mData[low][col][pt] = '\0';
						continue;
					}
				}
			}
			low++;
		}
		fclose(fin);
	}
public:
	~CCsvUtil() {
		for (unsigned int i = 0; i < mNumLows; i++) 
			delete[] mData[i];
		delete[] mData;
	}
	CCsvUtil(char *fname, int cols) {
		FILE *fin;
		char *ctx;
		my_fopen_in(&fin, fname);
		char buf[MAX_STRS];
		int lows = 0;
		while (fgets(buf, MAX_STRS, fin) != NULL) { lows++; }
		if (strlen(buf)==0) {
			MessageBox(GetActiveWindow(), fname, NULL, 0);
			lows--;
		}
		fclose(fin);
		_read(fname, lows, cols);
	}
	CCsvUtil(char *fname,int lows,int cols) { _read(fname, lows, cols); }
	std::string get(int l, int c) { return mData[l][c]; }
	void set(int l, int c,const char *d) { mData[l][c] = d; }
	void save(char* fname) {
		FILE *fout;
		char *ctx;
		my_fopen_out(&fout, fname);
		for (int low = 0; low < mNumLows;low++){
			for (int col = 0; col < mNumColumns-1; col++) { fprintf(fout,"%s,",mData[low][col].c_str()); }
			if(low<mNumLows-1)fprintf(fout, "%s\n", mData[low][mNumColumns - 1].c_str());
			else fprintf(fout, "%s", mData[low][mNumColumns - 1].c_str());
		}
	}
	const unsigned int getNumLows() { return mNumLows; }
};








bool csv_exist(const char* fname){
	struct stat stat_buf;
	return (stat(fname,&stat_buf)==0); 
}

/*VC2010はvscanfが無いので仕方なくマクロ*/
#define csv_fread_once(fname,format, ...) {\
	FILE *fin;\
	errno_t error;\
	char buf[256];\
	if((error=fopen_s(&fin,fname,"r"))!=0){}\
	if(fgets(buf,256,fin) != NULL){\
		if(sscanf_s(buf,format,__VA_ARGS__)!=EOF){}\
	}\
	fclose(fin);\
}

#define csv_fprintf(fname,format, ...) {\
	FILE *fout;\
	errno_t error=fopen_s(&fout,fname,"w");\
	fprintf(fout,format,__VA_ARGS__);\
	fclose(fout);\
}

#endif